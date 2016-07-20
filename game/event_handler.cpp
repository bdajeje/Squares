#include "event_handler.hpp"

namespace game {

utils::KeyLimitor EventHandler::s_key_limitor { 150 };

bool EventHandler::isKeyPressed(sf::Keyboard::Key key)
{
  return sf::Keyboard::isKeyPressed(key) && s_key_limitor.isAllow(key);
}

}
