#ifndef MAPBLOCK_HPP
#define MAPBLOCK_HPP

#include <memory>

#include "graphics/drawable.hpp"

namespace model {

class Player;

struct Direction
{
  float x {0.f};
  float y {0.f};
};

class MapBlock : public graphics::Drawable
{
  public:

    MapBlock(const sf::Vector2f& position, float size, const sf::Color& color);    

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void update(const sf::Time& elapsed_time);

    void setPosition(const sf::Vector2f& position);
    void setDirection(const float x, const float y) { _direction.x = x; _direction.y = y; }

    const sf::Vector2f& getPosition() const { return _shape.getPosition(); }
    sf::FloatRect getBounds() const { return _shape.getGlobalBounds(); }

  private:

    void rotate(const sf::Time& elapsed_time);

  private:

    sf::RectangleShape _shape;
    float _rotation_speed {0.1};
    float _angle {0.f};
    Direction _direction;
};

}

#endif // MAPBLOCK_HPP
