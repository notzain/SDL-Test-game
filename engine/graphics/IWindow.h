#ifndef SDL_GAME_IWINDOW_H
#define SDL_GAME_IWINDOW_H

#include <string>

namespace engine {

class IWindow {
protected:
    std::string m_windowName;
    int m_width;
    int m_height;

public:
    IWindow(std::string windowName, int width, int height)
        : m_windowName(std::move(windowName))
        , m_width(width)
        , m_height(height)
    {
    }
};

} // end namespace engine

#endif //SDL_GAME_IWINDOW_H
