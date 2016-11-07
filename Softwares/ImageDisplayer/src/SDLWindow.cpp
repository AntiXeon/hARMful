#include <stdlib.h>
#include <SDLWindow.h>
#include <DOOMful/debug/Test.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <iostream>


                                          /** CONSTRUCTION / DESTRUCTION **/
SDLWindow::SDLWindow(
					 const char* title,
					 unsigned int width,
					 unsigned int height
					) {
	SDL_Init(SDL_INIT_VIDEO) ;
	atexit(SDL_Quit) ;

    m_window = NULL ;
    m_renderer = NULL ;
	SDL_CreateWindowAndRenderer(
								width,
								height,
								SDL_RENDERER_ACCELERATED,
								&m_window,
								&m_renderer
							   ) ;
	if (m_window == NULL || m_renderer == NULL) {
		LogPrint(
				 LogError,
				 "Unable to create SDL Window and Renderer. %s",
				 SDL_GetError()
			 	) ;
		exit(-1) ;
	}

	setTitle(title) ;
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255) ;
	SDL_RenderClear(m_renderer) ;
	display() ;
}

SDLWindow::~SDLWindow() {
    SDL_RenderClear(m_renderer) ;
    SDL_DestroyRenderer(m_renderer) ;
    SDL_DestroyWindow(m_window) ;
}

                                                           /** UTILITIES **/
void SDLWindow::display() {
	// Display the whole picture on screen.
	SDL_RenderPresent(m_renderer) ;
}


void SDLWindow::render(const Spite::RawImage& part) {
    void* rawData ;
    unsigned int size ;
    ((Spite::RawImage&) part).getData(rawData, size) ;

    Spite::ColorFormat* format = (Spite::ColorFormat*) part.getFormat() ;
    int depth = format -> getColorDepth() ;
    int pitch = part.getWidth() * (format -> getPixelSizeInBytes()) ;

	SDL_Surface* rawSurface = SDL_CreateRGBSurfaceFrom(
                                                       rawData,
                                                       part.getWidth(),
                                                       part.getHeight(),
                                                       depth,
                                                       pitch,
                                                       format -> getMask(0),
                                                       format -> getMask(1),
                                                       format -> getMask(2),
                                                       format -> getMask(3)
                                                      ) ;

	if (rawSurface != NULL) {
	    SDL_Texture* rawTexture = SDL_CreateTextureFromSurface(
	                                                           m_renderer,
	                                                           rawSurface
	                                                          ) ;
	    SDL_FreeSurface(rawSurface) ;
	    SDL_RenderCopy(m_renderer, rawTexture, NULL, NULL) ;
		SDL_DestroyTexture(rawTexture) ;
	}
	else {
		std::cout << SDL_GetError() << std::endl ;
	}
}

                                                             /** SETTERS **/
void SDLWindow::setTitle(const char* title) {
	SDL_SetWindowTitle(m_window, title) ;
}

void SDLWindow::setPosition(int x, int y) {
	SDL_SetWindowPosition(m_window, x, y) ;
}

void SDLWindow::setFullscreen(bool fullscreen) {
	if (fullscreen) {
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN) ;
	}
	else {
		SDL_SetWindowFullscreen(m_window, 0) ;
	}
}

void SDLWindow::setVisible(bool visible) {
	if (visible) {
		SDL_ShowWindow(m_window) ;
	}
	else {
		SDL_HideWindow(m_window) ;
	}
}

void SDLWindow::getSize(int& width, int& height) {
	SDL_GetWindowSize(m_window, &width, &height) ;
}
