#include <iostream>
#include <MINDful/Math.h>
#include <DOOMful/utils/Processor.h>
#include <DOOMful/utils/Profiler.h>
#include <DOOMful/utils/String.h>
#include <DOOMful/utils/ThreadManager.h>
#include <DOOMful/debug/Log.h>
#include <Fractals/fractals/JuliaFractal.h>
#include <Fractals/graphics/ViewportPart.h>

using namespace std ;

#define MAX_AMOUNT_THREADS  12
static const bool Multithreading = true ;
volatile bool StopFractal = false ;

static std::string ThreadNames[MAX_AMOUNT_THREADS] ;


                                          	  /** CONSTRUCTION / DESTRUCTION **/
JuliaFractal::JuliaFractal(
                           const Mind::Dimension2Df& spaceXBounds,
                           const Mind::Dimension2Df& spaceYBounds,
                           const ComplexNumber& seed
                          ) : Fractal(
                                      spaceXBounds,
                                      spaceYBounds,
                                      seed
                                     ) {
    for (int threadIndex = 0 ; threadIndex < MAX_AMOUNT_THREADS ; ++threadIndex) {
        ThreadNames[threadIndex] = Doom::String::Random(16) ;
    }
}

JuliaFractal::~JuliaFractal() {}


                                                           	   /** UTILITIES **/
void JuliaFractal::draw(
                        SDLWindow& window,
                        FractalColors& colors
                       ) {
    // Profiler_Start("compute") ;

    static JuliaFractalThreadParameters parameters[MAX_AMOUNT_THREADS] ;

    int imageResolutionX ;
    int imageResolutionY ;
    window.getSize(imageResolutionX, imageResolutionY) ;
    float zoomOnX = (imageResolutionX / m_spaceXBounds.getHeight()) * 2.f ;
    float zoomOnY = (imageResolutionY / m_spaceYBounds.getHeight()) * 2.f ;

    // Compute the amount of parts and their resolution.
    int amountOfParts = (Multithreading) ? MAX_AMOUNT_THREADS : 1 ;
    int amountOfPartsOnY = (Multithreading) ? 4 : 1 ;
    int amountOfPartsByLine = (amountOfParts / amountOfPartsOnY) ;
    int partResolutionX = imageResolutionX / amountOfPartsByLine ;
    int partResolutionXAdditional = imageResolutionX % amountOfPartsByLine ;
    int partResolutionY = imageResolutionY / amountOfPartsOnY ;
    int partResolutionYAdditional = imageResolutionY % amountOfPartsOnY ;

    int threadIndex = 0 ;

    // Generate all the threads for all the parts of the picture.
    int maximalPartIndexOnX = amountOfPartsByLine - 1 ;
    int maximalPartIndexOnY = amountOfPartsOnY - 1 ;
    for (int partX = 0 ; partX < amountOfPartsByLine ; ++partX) {
        for (int partY = 0 ; partY < amountOfPartsOnY ; ++partY) {
            parameters[threadIndex].Fractal = this ;
            parameters[threadIndex].Window = &window ;
            parameters[threadIndex].Colors = &colors ;
            parameters[threadIndex].PartZoom = Mind::Dimension2Df(zoomOnX, zoomOnY) ;

            // Position on X axis and width of the part.
            parameters[threadIndex].PartPosition.setX(partX * partResolutionX) ;
            if (partX == maximalPartIndexOnX) {
                // Part contains all the remaining pixels to draw
                parameters[threadIndex].PartSize.setWidth(partResolutionX + partResolutionXAdditional) ;
            }
            else {
                parameters[threadIndex].PartSize.setWidth(partResolutionX) ;
            }

            // Position on Y axis and height of the part.
            parameters[threadIndex].PartPosition.setY(partY * partResolutionY) ;
            if (partY == maximalPartIndexOnY) {
                // Part contains all the remaining pixels to draw
                parameters[threadIndex].PartSize.setHeight(partResolutionY + partResolutionYAdditional) ;
            }
            else {
                parameters[threadIndex].PartSize.setHeight(partResolutionY) ;
            }

            // Create the threads...
            JuliaFractalMethod drawMethod = &JuliaFractal::drawPart;

            Doom::ThreadManager::Run(
                                     ThreadNames[threadIndex],
                                     drawMethod,
                                     &parameters[threadIndex],
                                     &StopFractal
                                    ) ;

            threadIndex = threadIndex + 1 ;
        }
    }

    for (int part = 0 ; part < amountOfParts ; ++part) {
        Doom::ThreadManager::Join(ThreadNames[part]) ;
    }

    // Profiler_Stop("compute") ;
}

void* JuliaFractal::drawPart(void* parameter) {
    JuliaFractalThreadParameters parameters = *((JuliaFractalThreadParameters*) parameter) ;

    // Shortcuts for values.
    int imageResolutionX = parameters.PartSize.getWidth() ;
    int imageResolutionY = parameters.PartSize.getHeight() ;
    int maxIterations = parameters.Colors -> getFractalIterations() ;
    float zoomOnX = parameters.PartZoom.getWidth() ;
    float zoomOnY = parameters.PartZoom.getHeight() ;

    // Render part dedicated to the thread.
    ViewportPart renderPart = ViewportPart(
                                          parameters.PartPosition.getX(),
                                          parameters.PartPosition.getY(),
                                          imageResolutionX,
                                          imageResolutionY
                                         ) ;

    // Compute and draw the part.
    for (int x = 0 ; x < imageResolutionX ; ++x) {
        for (int y = 0 ; y < imageResolutionY ; ++y) {
            int xOffset = x + parameters.PartPosition.getX() ;
            int yOffset = y + parameters.PartPosition.getY() ;

            float zReal = xOffset / (zoomOnX + parameters.Fractal -> m_spaceXBounds.getHeight()) ;
            float zImaginary = yOffset / (zoomOnY + parameters.Fractal -> m_spaceXBounds.getHeight()) ;
            ComplexNumber z(zReal, zImaginary) ;

            int iteration = 0 ;
            do {
                z.setReal((zReal * zReal) - (zImaginary * zImaginary) + parameters.Fractal -> m_seed.getReal()) ;
                z.setImaginary((2.f * zImaginary * zReal) + parameters.Fractal -> m_seed.getImaginary()) ;
                zReal = z.getReal() ;
                zImaginary = z.getImaginary() ;

                ++iteration ;
            } while (
                     (((zReal * zReal) + (zImaginary * zImaginary)) < 4.f) &&
                        (iteration < maxIterations)
                   ) ;

            renderPart.setPixelColor(x, y, parameters.Colors -> getColor(iteration)) ;
        }
    }

    parameters.Window -> addViewportPart(renderPart) ;

    return NULL ;
}
