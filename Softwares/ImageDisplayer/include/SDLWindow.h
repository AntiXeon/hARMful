#ifndef __SDL_WINDOW__
#define __SDL_WINDOW__

#include <list>
#include <string>
#include <SDL2/SDL.h>
#include <SPITEful/files/images/data/RawImage.h>
#include <SPITEful/files/images/data/ColorFormat.h>

/**
 * @brief	A SDLWindow uses SDL2 library to generate a Window and display
 *			a 2D graphics inside it.
 *
 * @author  Denis CARLUS
 * @version 1.0     01/31/2015
 */
class SDLWindow {
	private:
		/**
		 * @brief	The underlying SDL_Window instance.
		 */
		 SDL_Window* m_window ;

		 /**
		  * @brief 	2D renderer.
		  */
		 SDL_Renderer* m_renderer ;


	public:
                                          	  /** CONSTRUCTION / DESTRUCTION **/
		/**
		 * @brief	Create a new SDLWindow.
		 * @param	title 	Title of the SDLWindow.
		 * @param	width	Width of the SDLWindow.
		 * @param	height	Height of the SDLWindow.
		 */
		SDLWindow(
				  const char* title,
				  unsigned int width,
				  unsigned int height
				 ) ;

		/**
		 * @brief	Destruction of the SDLWindow.
		 */
		virtual ~SDLWindow() ;


                                                           	   /** UTILITIES **/
        /**
         * @brief   Effectively send the rendered content to framebuffer.
         */
        void display() ;


		/**
		 * @brief 	Render a part into the framebuffer.
		 */
		void render(const Spite::RawImage& image) ;


	public:
                                                             	 /** SETTERS **/
        /**
         * @brief	Set the title of the Window.
         * @param	title 	Title of the Window.
         */
        void setTitle(const char* title) ;

        /**
         * @brief   Set the position of the window on screen.
         * @param   x           Position on screen of the Window on X axis.
         * @param   y           Position on screen of the Window on Y axis.
         */
        void setPosition(int x, int y) ;

        /**
         * @brief	Set the Window in fullscreen mode.
         * @param	fullscreen 	TRUE to display window on full screen, FALSE
         *						to display the window in a part of the
         *						screen.
         */
        void setFullscreen(bool fullscreen) ;

        /**
         * @brief	Show or hide the window.
         * @param	visible 	TRUE to show the window, FALSE to hide it.
         */
        void setVisible(bool visible) ;


		/**
		 * @brief 	Get the size of the window.
		 */
		void getSize(int& width, int& height) ;
} ;

#endif // __HOPE__SDL_WINDOW__
