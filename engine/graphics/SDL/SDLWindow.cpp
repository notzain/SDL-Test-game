#include "SDLWindow.h"

namespace engine {

SDLWindow::SDLWindow(std::string windowName, int width, int height)
    : IWindow(std::move(windowName), width, height)
    , m_window(
          SDL_CreateWindow(
              windowName.c_str(),
              SDL_WINDOWPOS_UNDEFINED,
              SDL_WINDOWPOS_UNDEFINED,
              width, height,
              SDL_WINDOW_OPENGL),
          SDL_DestroyWindow)
{
}

} // end namespace engine
