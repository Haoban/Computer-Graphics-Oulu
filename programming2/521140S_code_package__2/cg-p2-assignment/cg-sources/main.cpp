/**
 * \brief OpenGL sample selection application
 * \file
 */
#include "sdlwrapper.h"                 // libSDL helper class to initialize library and OpenGL context
#include "streamredirector.h"           // Redirects standard output and standard error to files to help debugging on Windows
#include "assignment2.h"


/**
 * \brief Check for any OpenGL errors that might have happened
 */
bool checkOpenGLErrors()
{
	GLenum e;
	bool allOk = true;
	while ((e = glGetError()) != GL_NO_ERROR)
	{
		allOk = false;

		switch (e)
		{
#ifdef GL_INVALID_ENUM
		case GL_INVALID_ENUM:
			std::cerr << "OpenGL error GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument." << std::endl;
			break;
#endif
#ifdef GL_INVALID_VALUE
		case GL_INVALID_VALUE:
			std::cerr << "OpenGL error GL_INVALID_VALUE: A numeric argument is out of range." << std::endl;
			break;
#endif
#ifdef GL_INVALID_OPERATION
		case GL_INVALID_OPERATION:
			std::cerr << "OpenGL error GL_INVALID_OPERATION: The specified operation is not allowed in the current state." << std::endl;
			break;
#endif
#ifdef GL_INVALID_FRAMEBUFFER_OPERATION
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cerr << "OpenGL error GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete." << std::endl;
			break;
#endif
#ifdef GL_OUT_OF_MEMORY
		case GL_OUT_OF_MEMORY:
			std::cerr << "OpenGL error GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. The state of the GL is undefined now!" << std::endl;
			break;
#endif
#ifdef GL_STACK_UNDERFLOW
		case GL_STACK_UNDERFLOW:
			std::cerr << "OpenGL error GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow." << std::endl;
			break;
#endif
#ifdef GL_STACK_OVERFLOW
		case GL_STACK_OVERFLOW:
			std::cerr << "OpenGL error GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow." << std::endl;
			break;
#endif
		}
	}

	return allOk;
}

int main(int argc, char **argv)
{

#ifdef _WIN32
	StreamRedirector streamRedirector("stdout.txt", "stderr.txt");
#endif

	// Initialize libSDL, create an application window and initialize it with OpenGL context
	// See sdlwrapper.* for implementation details
	bool enableOpenGLDebugging = true;                        // Enable OpenGL debug context and install debug message callback if available
	int ogl_major_version = 3;                                // OpenGL major version to request. See https://www.opengl.org/wiki/History_of_OpenGL
	int ogl_minor_version = 2;                                // OpenGL minor version to request.
	Uint32 sdl_init_flags = SDL_INIT_TIMER | SDL_INIT_VIDEO;  // What SDL subsystems to initialize. See https://wiki.libsdl.org/SDL_Init
	std::string window_name = "CG_Programming_2019";              // Created window name - should be UTF-8 string for libSDL
	Uint32 window_width = 640;                                // Initial window width
	Uint32 window_height = 480;                               // Initial window height
	SDL sdl(enableOpenGLDebugging, ogl_major_version, ogl_minor_version, sdl_init_flags, window_name, window_width, window_height);

	if (!sdl.isOk())
	{
		std::cerr << "Unable to initialize SDL" << std::endl;
		return -1;
	}

	if (!checkOpenGLErrors())
	{
		std::cerr << "OpenGL Errors detected during SDL initialization" << std::endl;
		return -1;
	}

	Assignment2 scene; // A texturemapped flag

	if (!scene.init())
	{
		std::cerr << "Unable to init scene." << std::endl;
		return -1;
	}

	if (!checkOpenGLErrors())
	{
		std::cerr << "OpenGL Errors detected during scene.init()" << std::endl;
		return -1;
	}

	scene.resize(window_width, window_height);
	std::cout << "Initial width and height: " << window_width << " x " << window_height << std::endl;

	bool runRenderLoop = true;
	Uint32 prevTicks = SDL_GetTicks();
	while (runRenderLoop)
	{
		// Update the scene
		Uint32 curTicks = SDL_GetTicks();
		scene.update(0.001f * (curTicks - prevTicks)); // Parameter in seconds
		prevTicks = curTicks;

		// Render the scene
		scene.render();

		runRenderLoop &= checkOpenGLErrors();

		// Display window
		SDL_GL_SwapWindow(sdl.getWindow());

		// Process events
		SDL_Event e;

		while(SDL_PollEvent(&e))
		{
			// Sample event handling code. Some of this could be useful in your own scene's handleEvent() function
			switch (e.type)
			{
				// Program window closed etc.
			case SDL_QUIT:
				runRenderLoop = false;
				break;

			case SDL_WINDOWEVENT:
				// See https://wiki.libsdl.org/SDL_WindowEvent
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					window_width = e.window.data1;
					window_height = e.window.data2;
					std::cout << "Window Resized to : " << window_width << " x " << window_height << std::endl;
					scene.resize(window_width, window_height);
					break;
				}
				break;
			}

			runRenderLoop &= scene.handleEvent(e);
		}
	}

	return 0;
}
