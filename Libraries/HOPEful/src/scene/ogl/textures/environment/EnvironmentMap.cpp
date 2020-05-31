#include <scene/ogl/textures/environment/EnvironmentMap.hpp>
#include <files/archives/TARUtils.hpp>

#include <iostream>

using namespace Hope::GL ;

EnvironmentMap::EnvironmentMap(const std::string& hemFilepath) {
    auto hemContent = Spite::TARUtils::Load(hemFilepath) ;

    auto listDirectories = hemContent.directories() ;
    for (auto& dirPath : listDirectories) {
        std::cout << dirPath.string() << std::endl ;
    }
}
