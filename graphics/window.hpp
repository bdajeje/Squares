#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "drawable.hpp"
#include "game/event_handler.hpp"

namespace graphics {

class Window : public Drawable,
               public game::EventHandler
{

};

}

#endif // WINDOW_HPP
