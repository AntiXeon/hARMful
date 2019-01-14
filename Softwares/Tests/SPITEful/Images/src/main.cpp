#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <files/images/JPEGTurboFile.hpp>
#include <files/images/PNGFile.hpp>
#include <files/images/JPEGFile.hpp>
#include <utils/LogSystem.hpp>

static SDL_Texture* loadBackground(SDL_Renderer* renderer) {
    Spite::RawImage raw(Spite::ColorFormat::RGB) ;
    Spite::JPEGTurboFile pic("../pictures/cornucopia.jpg") ;
    pic.open(Spite::File::Open_ReadOnly) ;
    pic.load(&raw) ;
    // Convert pictures to SDL structures.
    unsigned char* pixelData = nullptr ;
    unsigned int pixelDataSize = 0 ;
    raw.data(pixelData, pixelDataSize) ;
    Spite::ColorFormat format = Spite::ColorFormat::Get(raw.format()) ;

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
        pixelData,
        raw.width(),
        raw.height(),
        format.colorDepth(),
        format.pixelSizeInBytes() * raw.width(),
        SDL_PIXELFORMAT_RGB24
    ) ;

    return SDL_CreateTextureFromSurface(renderer, surface) ;
}

static SDL_Texture* loadDices(SDL_Renderer* renderer) {
    Spite::RawImage raw(Spite::ColorFormat::RGBA) ;
    Spite::PNGFile pic("../pictures/dices.png") ;

    pic.open(Spite::File::Open_ReadOnly) ;
    pic.load(&raw) ;
    // Convert pictures to SDL structures.
    unsigned char* pixelData = nullptr ;
    unsigned int pixelDataSize = 0 ;
    raw.data(pixelData, pixelDataSize) ;
    Spite::ColorFormat format = Spite::ColorFormat::Get(raw.format()) ;

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
        pixelData,
        raw.width(),
        raw.height(),
        format.colorDepth(),
        format.pixelSizeInBytes() * raw.width(),
        SDL_PIXELFORMAT_RGBA32
    ) ;

    return SDL_CreateTextureFromSurface(renderer, surface) ;
}

int main(int, char**) {
    Doom::LogSystem::Initialize("Images.log", Doom::LogSystem::Gravity::Debug) ;


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
    SDL_Texture* bgTexture = loadBackground(renderer) ;
    SDL_Texture* dicesTexture = loadDices(renderer) ;

    SDL_Rect dicesRect ;
    dicesRect.x = 150 ;
    dicesRect.y = 180 ;
    dicesRect.w = 320 ;
    dicesRect.h = 240 ;

    // Display pictures.
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL) ;
    SDL_RenderCopy(renderer, dicesTexture, NULL, &dicesRect) ;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) ;
    SDL_RenderPresent(renderer) ;
    SDL_RenderClear(renderer) ;

    // Show on screen.
    SDL_Delay(3000) ;
    SDL_DestroyWindow(window) ;
    SDL_Quit() ;

    return 0 ;
}
