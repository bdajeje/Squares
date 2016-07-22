#include "hud.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>

#include "managers/fontmanager.hpp"
#include "utils/graphics.hpp"

namespace model {

HUD::HUD(std::shared_ptr<Player>& player, float width, float height)
  : _player {player}
  , _width {width}
  , _height {height}
{
  const sf::Font& font = font::FontManager::get(font::Consolas);
  const sf::Color color {255, 255, 255};

  // Margin between HUD borders and texts (ratio of sizes)
  const float width_margin  = width * _margin;

  // Player's name
  _player_name.setFont(font);
  _player_name.setColor(color);
  _player_name.setCharacterSize(20);
  _player_name.setString(_player->getName());
  _player_name.setPosition( width_margin, height * _margin );

  // Player's health bar
  _health_bar.setPosition(width_margin, _player_name.getPosition().y + _player_name.getGlobalBounds().height + itemMargin());
  _health_bar.setFillColor(sf::Color::Green);
  updateBar(_health_bar, player->getHealth(), player->getMaxHealth());

  // Player's shield bar
  _shield_bar.setPosition(width_margin, _health_bar.getPosition().y + _health_bar.getGlobalBounds().height + itemMargin());
  _shield_bar.setFillColor(sf::Color::Blue);
  updateBar(_shield_bar, player->getShield(), player->getMaxShield());

  // Elapsed time
  _elapsed_time_text.setFont(font);
  _elapsed_time_text.setColor(color);
  _elapsed_time_text.setCharacterSize(20);
  updateElapsedTime(0);

  // Score
  _score.setFont(font);
  _score.setColor(color);
  _score.setCharacterSize(20);
  updateScore(0);

  // Game over text
  _game_over.setFont(font);
  _game_over.setColor(color);
  _game_over.setCharacterSize(35);
  _game_over.setString("Game Over");
  utils::graphics::centerPosition(_game_over, _width, _height);

  // Game over score
  _game_over_score.setFont(font);
  _game_over_score.setColor(color);
  _game_over_score.setCharacterSize(30);
}

void HUD::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_player_name, states);
  target.draw(_health_bar, states);
  target.draw(_shield_bar, states);
  target.draw(_elapsed_time_text, states);
  target.draw(_score, states);

  if(_show_game_over)
  {
    target.draw(_game_over, states);
    target.draw(_game_over_score, states);
  }
}

void HUD::update(const sf::Time& elapsed_time)
{
  _elapsed_time += elapsed_time.asMilliseconds();

  updateElapsedTime(_elapsed_time);
  updateScore(_player->getScore());
  updateBar(_health_bar, _player->getHealth(), _player->getMaxHealth());
  updateBar(_shield_bar, _player->getShield(), _player->getMaxShield());
}

void HUD::updateElapsedTime(sf::Int32 value)
{
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << value / 1000.f;
  const std::string value_str = stream.str();

  _elapsed_time_text.setString(value_str);
  _elapsed_time_text.setPosition( _width - _width * _margin - _elapsed_time_text.getGlobalBounds().width, _height * _margin );
}

void HUD::updateScore(unsigned int score)
{
  const std::string score_str = std::to_string(score);
  if( score_str == _score.getString() )
    return;

  _score.setString(score_str);
  _score.setPosition( _width - _width * _margin - _score.getGlobalBounds().width, _elapsed_time_text.getPosition().y + itemMargin() );
}

void HUD::updateBar(sf::RectangleShape& bar, float value, float max_value)
{
  const float max_width_pixels = _width * _bar_max_width;
  const float width = max_width_pixels * value / max_value;
  bar.setSize( sf::Vector2f{width, _bar_height * _height} );
}

float HUD::itemMargin() const
{
  return _height * _item_margin;
}

void HUD::showGameOver()
{
  _show_game_over = true;
  _game_over_score.setString("Score: " + std::to_string(_player->getScore()));
  _game_over_score.setPosition(0, _game_over.getPosition().y + _game_over.getGlobalBounds().height + itemMargin());
  utils::graphics::centerHonrizontally(_game_over_score, _width);
}

}
