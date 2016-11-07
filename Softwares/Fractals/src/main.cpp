#include <Fractals/fractals/JuliaFractal.h>
#include <DOOMful/utils/CallStack.h>
#include <DOOMful/utils/Profiler.h>
#include <DOOMful/utils/String.h>
#include <DOOMful/debug/Log.h>
#include <sys/stat.h>
#include <iostream>

using namespace std ;

int main() {
    // Log_InitSystem("fractals.log", LogDebug) ;
    Doom::CallStack::Initialize() ;
    // Profiler_Initialize() ;
    // Profiler_AddSource("compute") ;
    // Profiler_AddSource("render") ;

    const std::string SaveFolder = "render/" ;
    const std::string FileExtension = ".png" ;
    const int filenameCharactersCount = 4 ;

    mkdir(SaveFolder.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH) ;

    const float WindowWidth = 800.f ;
    const float WindowHeight = 600.f ;
    SDLWindow mainWindow("Fractal Julia", WindowWidth, WindowHeight) ;
    // mainWindow.setFullscreen(true) ;

    std::vector<PixelColor> colors ;
    colors.push_back(PixelColor(32, 24, 64)) ;
    colors.push_back(PixelColor(148, 255, 255)) ;
    colors.push_back(PixelColor(0, 0, 148)) ;
    colors.push_back(PixelColor(64, 220, 255)) ;
    colors.push_back(PixelColor(0, 0, 148)) ;
    FractalColors fractalColors(256) ;
    fractalColors.setColors(colors) ;

    float spaceX = 0.75f ;
    float spaceY = 0.75f * (WindowHeight / WindowWidth) ;

    Mind::Dimension2Df xDim(-spaceX, spaceX) ;
    Mind::Dimension2Df yDim(-spaceY, spaceY) ;
    ComplexNumber juliaSeed(-0.786f, 0.132) ;
    JuliaFractal julia(xDim, yDim, juliaSeed) ;

    for (int iter = 0 ; iter < 1000 ; ++iter) {
        // cout << "Compute time = " << (Profiler_GetTime("compute") / 1000.f) << " ms" << endl ;
        // cout << "Render time = " << (Profiler_GetTime("render") / 1000.f) << " ms" << endl ;

        julia.draw(mainWindow, fractalColors) ;
        mainWindow.display() ;

        std::string filename = Doom::String::ToStringi(iter) ;
        int remainingCharacters = filenameCharactersCount - filename.size() ;
        for (int charIndex = 0 ; charIndex < remainingCharacters ; ++charIndex) {
            filename = "0" + filename ;
        }

        mainWindow.save(SaveFolder + filename + FileExtension) ;
        //
        // juliaSeed.setReal(juliaSeed.getReal() * 1.01f) ;
        juliaSeed.setImaginary(juliaSeed.getImaginary() + 0.00001f) ;
        julia.setSeed(juliaSeed) ;

        // Profiler_Flush() ;
    }

   SDL_Delay(20000) ;

    // Profiler_Close() ;
    // Log_Stop() ;

    return 0 ;
}
