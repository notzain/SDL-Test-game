#ifndef SDL_GAME_SDLWINDOW_H
#define SDL_GAME_SDLWINDOW_H

#include "graphics/IWindow.h"
#include <SDL.h>
#include <functional>
#include <memory>

namespace engine {

class SDLWindow : public IWindow {
    std::unique_ptr <SDL_Window, std::function<void(SDL_Window*)>> m_window;

public:
    SDLWindow(std::string windowName, int width, int height);
};

} //end namespace engine

#endif //SDL_GAME_SDLWINDOW_H
