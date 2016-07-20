#ifndef AUTOBLOCK_HPP
#define AUTOBLOCK_HPP

#include "models/mapblock.hpp"

namespace model {

class AutoBlock : public MapBlock
{
  public:

    AutoBlock(const sf::Vector2f& position, float size, const Direction& direction, const sf::Color& color, const std::string& sound_file);

    virtual void collision(std::shared_ptr<Player>& player) = 0;

    const std::string& getSoundFile() const { return _sound_file; }

  protected:

    std::string _sound_file;
};

}

#endif // AUTOBLOCK_HPP
