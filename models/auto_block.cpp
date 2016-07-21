#include "auto_block.hpp"

#include "managers/sound_manager.hpp"

namespace model {

const std::string AutoBlock::EnnemyLifeText {"-life"};
const std::string AutoBlock::EnnemyScoreText {"-score"};
const std::string AutoBlock::EnnemyShieldText {"-shield"};
const std::string AutoBlock::LifeText {"+life"};
const std::string AutoBlock::ShieldText {"+shield"};
const std::string AutoBlock::ScoreText {"+score"};
const std::string AutoBlock::ScaleText {"-size"};

const sf::Color AutoBlock::EnnemyColor {sf::Color::Red};
const sf::Color AutoBlock::LifeColor {sf::Color::Green};
const sf::Color AutoBlock::ShieldColor {sf::Color::Blue};
const sf::Color AutoBlock::ScoreColor {sf::Color::Yellow};
const sf::Color AutoBlock::ScaleColor {sf::Color::Cyan};

AutoBlock::AutoBlock(const sf::Vector2f& position, float size, const Direction& direction, const sf::Color& color, const std::string& sound_file)
  : MapBlock {position, size, color}
  , _sound_file {sound_file}
{
  setDirection(direction.x, direction.y);
}

}
