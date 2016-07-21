#ifndef MOVE_HPP
#define MOVE_HPP

#include "graphics/effect.hpp"

namespace graphics {
namespace effect {

class Move final : public Effect
{
  public:

    /*! Constructor
     *  \param move - total distance to move
     */
    Move(const std::shared_ptr<sf::Transformable>& target, const sf::Time& duration, const sf::Vector2f& move);

  private:

    void applyUpdate(sf::Int32 elapsed_ms);

  private:

    sf::Vector2f _move_per_ms;
};

}
}

#endif // MOVE_HPP
