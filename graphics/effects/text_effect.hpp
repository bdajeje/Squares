#ifndef TEXTEFFECT_HPP
#define TEXTEFFECT_HPP

#include "graphics/effect.hpp"

namespace graphics {
namespace effect {

class TextEffect : public Effect
{
  public:

    TextEffect(const std::shared_ptr<sf::Text>& target, const sf::Time& duration);
};

}
}

#endif // TEXTEFFECT_HPP
