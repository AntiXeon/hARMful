#include <scene/ogl/textures/environment/EnvironmentMap.hpp>
#include <HOPEStrings.hpp>
#include <stdexcept>

using namespace Hope::GL ;

std::array<EnvironmentMap::CoordsCubeFaces, EnvironmentMap::AmountFaces> EnvironmentMap::CoordinatesFaces(const EnvironmentMap::CubemapType type) {
    std::array<CoordsCubeFaces, AmountFaces> coordinates ;

    const float TopYMin = 0.f ;
    const float TopYMax = 1.f/3.f ;
    const float BottomYMin = 2.f/3.f ;
    const float BottomYMax = 1.f ;

    coordinates[CubeFaces::Left] = {  .startX = 0.f,   .stopX = 0.25f, .startY = TopYMax, .stopY = BottomYMin } ;
    coordinates[CubeFaces::Front] = { .startX = 0.25f, .stopX = 0.5f,  .startY = TopYMax, .stopY = BottomYMin } ;
    coordinates[CubeFaces::Right] = { .startX = 0.5f,  .stopX = 0.75f, .startY = TopYMax, .stopY = BottomYMin } ;
    coordinates[CubeFaces::Back] = {  .startX = 0.75f, .stopX = 1.f,   .startY = TopYMax, .stopY = BottomYMin } ;

    switch (type) {
        case Cube_LeftAligned:
            coordinates[CubeFaces::Top] = {
                .startX = coordinates[CubeFaces::Left].startX,
                .stopX = coordinates[CubeFaces::Left].stopX,
                .startY = TopYMin,
                .stopY = TopYMax
            } ;
            coordinates[CubeFaces::Bottom] = {
                .startX = coordinates[CubeFaces::Left].startX,
                .stopX = coordinates[CubeFaces::Left].stopX,
                .startY = BottomYMin,
                .stopY = BottomYMax
            } ;
            break ;

        case Cube_FrontAligned:
            coordinates[CubeFaces::Top] = {
                .startX = coordinates[CubeFaces::Front].startX,
                .stopX = coordinates[CubeFaces::Front].stopX,
                .startY = TopYMin,
                .stopY = TopYMax
            } ;
            coordinates[CubeFaces::Bottom] = {
                .startX = coordinates[CubeFaces::Front].startX,
                .stopX = coordinates[CubeFaces::Front].stopX,
                .startY = BottomYMin,
                .stopY = BottomYMax
            } ;
            break ;

        case Cube_RightAligned:
            coordinates[CubeFaces::Top] = {
                .startX = coordinates[CubeFaces::Right].startX,
                .stopX = coordinates[CubeFaces::Right].stopX,
                .startY = TopYMin,
                .stopY = TopYMax
            } ;
            coordinates[CubeFaces::Bottom] = {
                .startX = coordinates[CubeFaces::Right].startX,
                .stopX = coordinates[CubeFaces::Right].stopX,
                .startY = BottomYMin,
                .stopY = BottomYMax
            } ;
            break ;

        case Cube_BackAligned:
            coordinates[CubeFaces::Top] = {
                .startX = coordinates[CubeFaces::Back].startX,
                .stopX = coordinates[CubeFaces::Back].stopX,
                .startY = TopYMin,
                .stopY = TopYMax
            } ;
            coordinates[CubeFaces::Bottom] = {
                .startX = coordinates[CubeFaces::Back].startX,
                .stopX = coordinates[CubeFaces::Back].stopX,
                .startY = BottomYMin,
                .stopY = BottomYMax
            } ;
            break ;
    }

    return coordinates ;
}

GLenum EnvironmentMap::GLCoordinates(const CubeFaces face) {
    switch (face) {
        case CubeFaces::Left:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_X ;
        case CubeFaces::Front:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_Z ;
        case CubeFaces::Right:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_X ;
        case CubeFaces::Back:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z ;
        case CubeFaces::Top:
            return GL_TEXTURE_CUBE_MAP_POSITIVE_Y ;
        case CubeFaces::Bottom:
            return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y ;
       default:
        throw std::runtime_error(Texts::EnvironmentMap_UnknownFaceID) ;
    }
}
