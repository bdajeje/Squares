#include "text_effect.hpp"

namespace graphics {
namespace effect {

TextEffect::TextEffect(const std::shared_ptr<sf::Text>& target, const sf::Time& duration)
  : Effect {target, duration}
{

}

}
}
