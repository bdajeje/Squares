#ifndef AUTOBLOCK_HPP
#define AUTOBLOCK_HPP

#include <vector>

#include "models/mapblock.hpp"

namespace model {

struct BlockEffect
{
  BlockEffect(const std::string& text, const sf::Color& color)
    : text {text}
    , color {color}
  {}

  std::string text;
  sf::Color color;
};

class AutoBlock : public MapBlock
{
  public:

    static const std::string EnnemyLifeText;
    static const std::string EnnemyScoreText;
    static const std::string EnnemyShieldText;
    static const std::string LifeText;
    static const std::string ShieldText;
    static const std::string ScoreText;
    static const std::string ScaleText;

    static const sf::Color EnnemyColor;
    static const sf::Color LifeColor;
    static const sf::Color ShieldColor;
    static const sf::Color ScoreColor;
    static const sf::Color ScaleColor;

    AutoBlock(const sf::Vector2f& position, float size, const Direction& direction, const sf::Color& color, const std::string& sound_file);

    /*! Apply collision effect with player
     *  \returns effects power and color for the map to display information
     */
    virtual std::vector<BlockEffect> collision(std::shared_ptr<Player>& player) = 0;

    const std::string& getSoundFile() const { return _sound_file; }

  protected:

    std::string _sound_file;
};

}

#endif // AUTOBLOCK_HPP
