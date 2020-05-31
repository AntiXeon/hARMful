#include <scene/ogl/textures/environment/CubeFaces.hpp>
#include <array>

namespace Hope::GL {
    const unsigned int AmountFaces = CubeFace::Last - CubeFace::First ;

    const std::string& FaceName(const Hope::GL::CubeFace face) {
        static const std::array<std::string, 6> FaceNames = {{
            "right",
            "left",
            "top",
            "bottom",
            "back",
            "front"
        }} ;

        return FaceNames[face - Hope::GL::CubeFace::First] ;
    }
}
