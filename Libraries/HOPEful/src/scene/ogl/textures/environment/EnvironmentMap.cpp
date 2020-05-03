#include <scene/ogl/textures/environment/EnvironmentMap.hpp>
#include <files/images/ImageFile.hpp>

using namespace Hope::GL ;

EnvironmentMap::EnvironmentMap(const std::string& path) {
    Spite::RawImage rawData = EnvironmentMapProcessing::LoadRawPicture(path) ;
    m_environmentMap = std::make_unique<EnvironmentMapTexture>(rawData) ;

    rawData = Spite::ImageFile::Resize(rawData, 128, 64) ;
    m_irradianceMap = std::make_unique<EnvironmentMapTexture>(rawData) ;
}
