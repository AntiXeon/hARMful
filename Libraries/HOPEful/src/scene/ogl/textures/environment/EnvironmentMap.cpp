#include <scene/ogl/textures/environment/EnvironmentMap.hpp>
#include <files/images/ImageFile.hpp>

#include <files/images/ImageWriter.hpp>

using namespace Hope::GL ;

EnvironmentMap::EnvironmentMap(
    const std::string& directory,
    const std::string& name
) {
    Spite::RawImage rawData = EnvironmentMapProcessing::LoadRawPicture(directory + "/" + name + ".hdr") ;
    m_environmentMap = std::make_unique<EnvironmentMapTexture>(rawData) ;

    auto resizedMap = Spite::ImageFile::Resize(rawData, 128, 64) ;
    m_irradianceMap = std::make_unique<EnvironmentMapTexture>(resizedMap) ;
}
