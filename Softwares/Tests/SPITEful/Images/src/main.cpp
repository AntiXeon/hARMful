#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <files/images/JPEGTurboFile.hpp>
#include <files/images/PNGFile.hpp>
#include <files/images/JPEGFile.hpp>

int main(int, char**) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::string errorMessage = "Error on SDL initialization: " + std::string(SDL_GetError()) ;
        throw std::runtime_error(errorMessage) ;
    }

    // Create and display a window.
    SDL_Window* window = SDL_CreateWindow (
        "SPITEful Test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        480,
        SDL_WINDOW_SHOWN
    ) ;

    if (!window) {
        std::string errorMessage = "Error on windows creation: " + std::string(SDL_GetError()) ;
        throw std::runtime_error(errorMessage) ;
    }

    const int RendererIndex = -1 ;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, RendererIndex, SDL_RENDERER_ACCELERATED) ;

    if (!renderer) {
        std::string errorMessage = "Error on creation accelerated renderer: " + std::string(SDL_GetError()) ;
        throw std::runtime_error(errorMessage) ;
    }

    // Load pictures.
    Spite::RawImage backgroundRaw(Spite::ColorFormat::RGB) ;
    Spite::JPEGTurboFile backgroundPic("../pictures/cornucopia.jpg") ;
    backgroundPic.open(Spite::File::Open_ReadOnly) ;
    backgroundPic.load(&backgroundRaw) ;
    // Convert pictures to SDL structures.
    unsigned char* bgPixelData = nullptr ;
    unsigned int bgPixelDataSize = 0 ;
    backgroundRaw.data(bgPixelData, bgPixelDataSize) ;
    Spite::ColorFormat bgFormat = Spite::ColorFormat::Get(backgroundRaw.format()) ;

    SDL_Surface* bgSurface = SDL_CreateRGBSurfaceWithFormatFrom(
        bgPixelData,
        backgroundRaw.width(),
        backgroundRaw.height(),
        bgFormat.colorDepth(),
        bgFormat.pixelSizeInBytes() * backgroundRaw.width(),
        SDL_PIXELFORMAT_RGB24
    ) ;

    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface) ;

    // Display pictures.
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL) ;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) ;
    SDL_RenderPresent(renderer) ;
    SDL_RenderClear(renderer) ;

    // Show on screen.
    SDL_Delay(3000) ;
    SDL_DestroyWindow(window) ;
    SDL_Quit() ;

    return 0 ;
}
