#include <scene/ogl/textures/environment/EquirectangularToCubemap.hpp>
#include <files/images/ImageFile.hpp>
#include <HOPEStrings.hpp>
#include <Math.hpp>
#include <algorithm>
#include <cassert>

using namespace Hope::GL ;

EquirectangularToCubemap::EquirectangularToCubemap(Spite::RawImage& equirectData) {
    m_equirectWidth = equirectData.width() ;
    m_equirectHeight = equirectData.height() ;
    m_faceEdgeLength = Mind::Math::closestPower2(m_equirectWidth / Cubemapping::AmountCubeFacesX) ;

    m_format = equirectData.format() ;
    unsigned int pixelWidth = m_format.pixelSizeInBytes() ;

    auto* rawEquirectData = equirectData.data().data() ;
    unsigned int equirectByteSize = equirectData.data().size() ;

    for (unsigned int pixel = 0 ; pixel < equirectByteSize ; pixel += pixelWidth) {
        Hope::HDRRGB pixelColor = *reinterpret_cast<Hope::HDRRGB*>(rawEquirectData + pixel) ;
        m_equirectPixelChannels.push_back(pixelColor) ;
    }
}

void EquirectangularToCubemap::convert() {
    const float DefaultRotation = Mind::Math::toRadians(180) ;

    std::vector<Hope::HDRRGB> facePixels ;
    unsigned int faceSize = m_faceEdgeLength * m_faceEdgeLength ;
    facePixels.resize(faceSize) ;

    for (unsigned int faceID = Cubemapping::First ; faceID <= Cubemapping::Last ; ++faceID) {
        auto face = static_cast<Cubemapping::CubeFaces>(faceID) ;

        for (unsigned int x = 0 ; x < m_faceEdgeLength ; ++x) {
            for (unsigned int y = 0 ; y < m_faceEdgeLength ; ++y) {
                unsigned int to = From2DTo1D(x, y, m_faceEdgeLength) ;

                Mind::Vector3f cube = orientation(
                    2.f * (x + 0.5f) / m_faceEdgeLength - 1.f,
                    2.f * (y + 0.5f) / m_faceEdgeLength - 1.f,
                    face
                ) ;

                float cubeX = cube.get(Mind::Vector3f::X) ;
                float cubeY = cube.get(Mind::Vector3f::Y) ;
                float cubeZ = cube.get(Mind::Vector3f::Z) ;

                float r = std::sqrt((cubeX * cubeX) + (cubeY * cubeY) + (cubeZ * cubeZ)) ;
                float theta = std::fmod(std::atan2(cubeY, cubeX) + DefaultRotation, Mind::Math::PiTwice) ;
                float phi = std::acos(cubeZ / r) ;

                writeBilinearInterpolation(
                    theta,
                    phi,
                    to,
                    facePixels
                ) ;
            }
        }

        // Copy bytes.
        for (unsigned int pixel = 0 ; pixel < faceSize ; ++pixel) {
            m_faceBytes[face].insert(
                m_faceBytes[face].end(),
                facePixels[pixel].bytes,
                facePixels[pixel].bytes + sizeof(Hope::HDRRGB)
            ) ;
        }
    }
}

void EquirectangularToCubemap::writeBilinearInterpolation(
    const float theta,
    const float phi,
    const unsigned int to,
    std::vector<Hope::HDRRGB>& facePixels
) {
    float xFrom = (m_equirectWidth * theta / Mind::Math::Pi / 2.f - 0.5f) ;
    float yFrom = (m_equirectHeight * phi / Mind::Math::Pi - 0.5f) ;

    unsigned int xl = std::clamp(std::floor(xFrom), 0.f, (m_equirectWidth - 1.f)) ;
    unsigned int xr = std::clamp(std::ceil(xFrom), 0.f, (m_equirectWidth - 1.f)) ;
    float xf = xFrom - xl ;

    unsigned int yl = std::clamp(std::floor(yFrom), 0.f, (m_equirectHeight - 1.f)) ;
    unsigned int yr = std::clamp(std::ceil(yFrom), 0.f, (m_equirectHeight - 1.f)) ;
    float yf = yFrom - yl ;

    unsigned int p00 = From2DTo1D(xl, yl, m_equirectWidth) ;
    unsigned int p10 = From2DTo1D(xr, yl, m_equirectWidth) ;
    unsigned int p01 = From2DTo1D(xl, yr, m_equirectWidth) ;
    unsigned int p11 = From2DTo1D(xr, yr, m_equirectWidth) ;

    Hope::HDRRGB p00Pixel = m_equirectPixelChannels[p00] ;
    Hope::HDRRGB p10Pixel = m_equirectPixelChannels[p10] ;
    Hope::HDRRGB p01Pixel = m_equirectPixelChannels[p01] ;
    Hope::HDRRGB p11Pixel = m_equirectPixelChannels[p11] ;

    for (unsigned int channel = 0 ; channel < AmountRGBChannels ; ++channel) {
        float p0 = p00Pixel.array[channel] * (1.f - xf) + p10Pixel.array[channel] * xf ;
        float p1 = p01Pixel.array[channel] * (1.f - xf) + p11Pixel.array[channel] * xf ;
        facePixels[to].array[channel] = p0 * (1.f - yf) + p1 * yf ;
    }
}

Mind::Vector3f EquirectangularToCubemap::orientation(
    const float u,
    const float v,
    const Cubemapping::CubeFaces face
) {
    switch (face) {
        case Cubemapping::Back:
            return Mind::Vector3f(1.f, u, -v) ;
        case Cubemapping::Left:
            return Mind::Vector3f(-u, 1.f, -v) ;
        case Cubemapping::Front:
            return Mind::Vector3f(-1.f, -u, -v) ;
        case Cubemapping::Right:
            return Mind::Vector3f(u, -1.f, -v) ;
        case Cubemapping::Top:
            return Mind::Vector3f(-v, -u, 1.f) ;
        case Cubemapping::Bottom:
            return Mind::Vector3f(v, -u, -1.f) ;
        default:
            throw std::runtime_error(Texts::EnvironmentMap_UnknownFaceID) ;
    }
}
