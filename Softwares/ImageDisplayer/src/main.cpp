#include <SDLWindow.h>
#include <DOOMful/DOOMful.h>
#include <SPITEful/files/images/PNGFile.h>
#include <SPITEful/files/images/JPEGFile.h>
#include <SPITEful/files/images/data/RawImage.h>

#include <iostream>

using namespace std ;


#define WindowTitle "Vers l'infini et au-dela !"


void open_jpeg(SDLWindow*& mainWindow, const std::string& file) {
    Spite::ColorFormat::ID jpegColorFormat = Spite::ColorFormat::RGB ;
    Spite::ColorFormat::Create(jpegColorFormat) ;
    Spite::ColorFormat& rgb = Spite::ColorFormat::Get(jpegColorFormat) ;
    Spite::RawImage jpegImage(&rgb) ;
    Spite::JPEGFile jpegFile(file) ;

    if (jpegFile.load(&jpegImage)) {
        if (mainWindow == NULL) {
            mainWindow = new SDLWindow(
                                       WindowTitle,
                                       jpegImage.getWidth(),
                                       jpegImage.getHeight()
                                      ) ;
        }

        mainWindow -> render(jpegImage) ;
        jpegImage.freeData() ;
    }
}

void open_png(SDLWindow*& mainWindow, const std::string& file) {
    Spite::RawImage pngImage ;
    Spite::PNGFile pngFile(file) ;

    if (pngFile.load(&pngImage)) {
        if (mainWindow == NULL) {
            mainWindow = new SDLWindow(
                                       WindowTitle,
                                       pngImage.getWidth(),
                                       pngImage.getHeight()
                                      ) ;
        }
        mainWindow -> render(pngImage) ;
        pngImage.freeData() ;
    }
}

int main() {
    // Log_InitSystem("imgdisp.log", LogDebug) ;
    Spite::ColorFormat::Initialize() ;

    SDLWindow* mainWindow = NULL ;
    open_jpeg(mainWindow, "../resources/endor.jpg") ;
    open_png(mainWindow, "../resources/squeeze.png") ;
    open_png(mainWindow, "../resources/buzz.png.ga") ;
    open_png(mainWindow, "../resources/woody.png") ;
    mainWindow -> display() ;
    SDL_Delay(50000) ;

    Spite::ColorFormat::Clear() ;

    return 0 ;
}
