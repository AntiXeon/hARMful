#include <scene/ogl/textures/environment/EnvironmentMap.hpp>
#include <scene/common/algorithms/GaussianBlur.hpp>
#include <files/images/ImageFile.hpp>

using namespace Hope::GL ;

EnvironmentMap::EnvironmentMap(const std::string& path) {
    Spite::RawImage rawData = EnvironmentMapProcessing::LoadRawPicture(path) ;
    m_environmentMap = std::make_unique<EnvironmentMapTexture>(rawData) ;

    auto resizedMap = Spite::ImageFile::Resize(rawData, 128, 64) ;
    Hope::GaussianBlur blur(resizedMap) ;
    resizedMap = blur.process(4.f) ;
    m_irradianceMap = std::make_unique<EnvironmentMapTexture>(resizedMap) ;
}

EnvironmentMap::EnvironmentMap(
    const std::string& pathEnvironment,
    const std::string& pathIrradiance,
    const std::string& pathRadiance
) {
    Spite::RawImage rawData ;
    rawData = EnvironmentMapProcessing::LoadRawPicture(pathEnvironment) ;
    m_environmentMap = std::make_unique<EnvironmentMapTexture>(rawData) ;

    rawData = EnvironmentMapProcessing::LoadRawPicture(pathIrradiance) ;
    m_irradianceMap = std::make_unique<EnvironmentMapTexture>(rawData) ;

    rawData = EnvironmentMapProcessing::LoadRawPicture(pathRadiance) ;
    m_radianceMap = std::make_unique<EnvironmentMapTexture>(rawData) ;
}
