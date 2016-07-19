#include "player.hpp"

namespace model {

Player::Player(const std::string& name, const sf::Vector2f& position)
  : MapBlock {position, _base_size, sf::Color::White}
  , _name {name}
  , _health {_max_health}
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

void Player::update(const sf::Time& elapsed_time)
{
  MapBlock::update(elapsed_time);

  // Update score every seconds
  _last_score_update += elapsed_time.asMilliseconds();
  if( _last_score_update >= _update_score_step )
  {
    _last_score_update -= _update_score_step;
    gainScore(10);
  }
}

}
