#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <DOOMful/utils/Profiler.h>
#include <Fractals/graphics/SDLWindow.h>


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
	Profiler_Start("render") ;

	m_mutex.lock() ;
		// Render the different parts (and remove them).
		while(m_parts.size() > 0) {
			ViewportPart& part = m_parts.front() ;
			render(part) ;
			m_parts.pop_front() ;
		}

		// Display the whole picture on screen.
		SDL_RenderPresent(m_renderer) ;
	m_mutex.unlock() ;

	Profiler_Stop("render") ;
}

void SDLWindow::save(const std::string& filepath) {
	int width, height ;
	getSize(width, height) ;

	SDL_Surface* screenshot = SDL_CreateRGBSurface(
												   0, width, height,
												   32, 0, 0, 0, 0
											   	  ) ;
	SDL_RenderReadPixels(
						 m_renderer, NULL,
						 SDL_PIXELFORMAT_ARGB8888,
					 	 screenshot -> pixels,
					 	 screenshot -> pitch
				 		) ;
	SDL_SaveBMP(screenshot, filepath.c_str()) ;

	SDL_FreeSurface(screenshot) ;
}

void SDLWindow::addViewportPart(const ViewportPart& part) {
	m_mutex.lock() ;
		m_parts.push_back(part) ;
	m_mutex.unlock() ;
}

void SDLWindow::render(const ViewportPart& part) {
	Profiler_Start("render") ;

	const int ColorDepth = 32 ;
	const int RowByteSize = part.getWidth() * sizeof(int) ;
	SDL_Surface* tmpSurface = SDL_CreateRGBSurfaceFrom(
													   part.getPixels(),
													   part.getWidth(),
													   part.getHeight(),
													   ColorDepth,
													   RowByteSize,
													   0, 0, 0, 0
													  ) ;
   SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurface) ;
   SDL_FreeSurface(tmpSurface) ;

	SDL_Rect* WholeTexture = NULL ;
	SDL_Rect RenderCopyParams ;
	RenderCopyParams.x = part.getX() ;
	RenderCopyParams.y = part.getY() ;
	RenderCopyParams.w = part.getWidth() ;
	RenderCopyParams.h = part.getHeight() ;

   SDL_RenderCopy(
				   m_renderer,
				   tmpTexture,
				   WholeTexture,
				   &RenderCopyParams
			   	  ) ;

	SDL_DestroyTexture(tmpTexture) ;

	Profiler_Stop("render") ;
}

                                                             /** SETTERS **/
void SDLWindow::setTitle(const char* title) {
	m_mutex.lock() ;
		SDL_SetWindowTitle(m_window, title) ;
	m_mutex.unlock() ;
}

void SDLWindow::setPosition(int x, int y) {
	m_mutex.lock() ;
		SDL_SetWindowPosition(m_window, x, y) ;
	m_mutex.unlock() ;
}

void SDLWindow::setFullscreen(bool fullscreen) {
	m_mutex.lock() ;
		if (fullscreen) {
			SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN) ;
		}
		else {
			SDL_SetWindowFullscreen(m_window, 0) ;
		}
	m_mutex.unlock() ;
}

void SDLWindow::setVisible(bool visible) {
	m_mutex.lock() ;
		if (visible) {
			SDL_ShowWindow(m_window) ;
		}
		else {
			SDL_HideWindow(m_window) ;
		}
	m_mutex.unlock() ;
}

void SDLWindow::getSize(int& width, int& height) {
	m_mutex.lock() ;
		SDL_GetWindowSize(m_window, &width, &height) ;
	m_mutex.unlock() ;
}
