#include <scene/ogl/textures/environment/EnvironmentMap.hpp>
#include <files/archives/TARUtils.hpp>
#include <Math.hpp>
#include <algorithm>

#include <iostream>

using namespace Hope::GL ;

const std::string EnvironmentMap::EnvironmentMapName = "envmap" ;
const std::string EnvironmentMap::IrradianceMapName = "irradiance" ;
const std::string EnvironmentMap::SpecularMapName = "specular" ;

EnvironmentMap::EnvironmentMap(const std::string& hemFilepath) {
    auto hemContent = Spite::TARUtils::Load(hemFilepath) ;

    std::vector<unsigned int> specularLevels ;
    orderedSpecularLevels(hemContent, specularLevels) ;
    unsigned int amountLevels = specularLevels.size() ;

    m_envMap = std::shared_ptr<EnvironmentMapTexture>(new EnvironmentMapTexture(hemContent, EnvironmentMapName, true)) ;
    m_irradianceMap = std::shared_ptr<EnvironmentMapTexture>(new EnvironmentMapTexture(hemContent, IrradianceMapName, true)) ;

    fs::path specularPath(SpecularMapName + "/" + std::to_string(specularLevels.front())) ;
    m_specularMap = std::shared_ptr<EnvironmentMapTexture>(new EnvironmentMapTexture(hemContent, specularPath, true)) ;

    for (unsigned int level = 1 ; level < amountLevels ; ++level) {
        specularPath = fs::path(SpecularMapName + "/" + std::to_string(specularLevels[level])) ;
        m_specularMap -> addMipmap(hemContent, specularPath, level) ;
    }
}

bool EnvironmentMap::orderedSpecularLevels(
    const Spite::TARData& hemContent,
    std::vector<unsigned int>& levels
) {
    auto listDirectories = hemContent.directories() ;
    levels.reserve(listDirectories.size()) ;

    // Directories are named as specular/[size] (where [size] is a numeric value).
    for (auto dirPath : listDirectories) {
        auto dirNameIt = dirPath.begin() ;

        if ((*dirNameIt).string() == SpecularMapName) {
            dirNameIt++ ;
            std::string mapSize = (*dirNameIt).string() ;
            levels.push_back(std::stoi(mapSize)) ;
        }
    }

    // Sort from the biggest value to the lower.
    std::sort(
        levels.begin(),
        levels.end(),
        [](unsigned int i, unsigned int j) {
            return i > j ;
        }
    ) ;

    return checkSpecularLevels(levels) ;
}

bool EnvironmentMap::checkSpecularLevels(const std::vector<unsigned int>& levels) {
    {
        auto firstLevel = levels[0] ;
        auto firstLevelPow2 = Mind::Math::closestPower2(firstLevel) ;

        if (firstLevel != firstLevelPow2) {
            return false ;
        }
    }

    size_t maxIndex = levels.size() ;
    for (size_t index = 1 ; index < maxIndex ; index++) {
        auto previousLevel = levels[index - 1] ;
        auto currentLevel = levels[index] ;

        auto currentLevelPow2 = Mind::Math::closestPower2(currentLevel) ;

        if (currentLevel != currentLevelPow2) {
            return false ;
        }

        bool isPreviousDouble = (previousLevel == (2 * currentLevel)) ;

        if (!isPreviousDouble) {
            return false ;
        }
    }

    return true ;
}
