#include "player.hpp"

#include "utils/file.hpp"

namespace model {

const std::string Player::s_score_path {"resources/scores/"};

Player::Player(const std::string& name, const sf::Vector2f& position)
  : MapBlock {position, _base_size, sf::Color::White}
  , _name {name}
  , _health {_max_health}
  , _scale {1.f, 1.f}
  , _highest_score {retrieveHighestScore(name)}
{}

void Player::hit(int value)
{
  _shield -= value;
  if(_shield < 0)
  {
    _health += _shield; // at this point shield value is negative, so this line actually decreases life
    _shield = 0;
  }
}

bool Player::gainLife(int value)
{
  if(_health == _max_health)
    return false;

  _health += value;
  if(_health > _max_health)
    _health = _max_health;

  return true;
}

bool Player::gainShield(int value)
{
  if(_shield == _max_shield)
    return false;

  _shield += value;
  if(_shield > _max_shield)
    _shield = _max_shield;

  return true;
}

void Player::gainScale(float value)
{
  _scale.x += value;
  if(_scale.x < 1.f)
    _scale.x = 1.f;
  else if(_scale.x > _max_scale)
    _scale.x = _max_scale;

  _scale.y = _scale.x;
  _shape.setScale(_scale);
}

void Player::update(const sf::Time& elapsed_time)
{
  MapBlock::update(elapsed_time);

  // Update score every seconds
  const sf::Int32 milliseconds = elapsed_time.asMilliseconds();
  _last_score_update += milliseconds;
  if( _last_score_update >= _update_score_step )
  {
    _last_score_update -= _update_score_step;
    gainScore(10);
  }

  // Update square size
  if( _scale.x < _max_scale )
    gainScale(milliseconds * _growth);
}

void Player::saveScore()
{
  if(_score > _highest_score)
  {
    utils::files::create(s_score_path + utils::files::sanitize(_name), std::to_string(_score), true);
    _highest_score = _score;
  }
}

int Player::retrieveHighestScore(const std::string& player_name)
{
  std::string content;
  try
  {
    utils::files::read(s_score_path + utils::files::sanitize(player_name), content);
    return std::stoi(content);
  }
  catch(...)
  {
    return 0;
  }
}

}
