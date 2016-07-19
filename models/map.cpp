#include "map.hpp"

#include "models/ennemy_block.hpp"
#include "models/life_block.hpp"
#include "models/shield_block.hpp"
#include "models/score_block.hpp"
#include "utils/mathematics.hpp"

namespace model {

Map::Map(float width, float height)
  : _width {width}
  , _height {height}
{
  // By default reserver some space for future map blocks
  _map_blocks.reserve(100);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  for(const std::unique_ptr<model::AutoBlock>& map_block : _map_blocks)
    target.draw(*map_block, states);
}

void Map::update(const sf::Time& elapsed_time)
{
  // Update each square
  for(std::vector<std::unique_ptr<model::AutoBlock>>::iterator block_it = _map_blocks.begin(); block_it < _map_blocks.end(); ++block_it)
  {
    const std::unique_ptr<model::AutoBlock>& map_block = *block_it;

    // Remove square if out of screen
    const sf::Vector2f& position = map_block->getPosition();
    const sf::FloatRect bounds   = map_block->getBounds();
    if(position.x < -bounds.width         ||
       position.x > _width + bounds.width ||
       position.y < -bounds.height         ||
       position.y > _height + bounds.height )
    {
      _map_blocks.erase(block_it);
      continue;
    }

    // Block still in map, update it
    map_block->update(elapsed_time);
  }

  // Generate new square
  generateSquares(elapsed_time);
}

void Map::applyCollision(std::shared_ptr<Player>& player)
{
  const sf::FloatRect rectangle = player->getBounds();

  // Check if any blocks intersects with player
  const auto end = _map_blocks.end();
  for(std::vector<std::unique_ptr<model::AutoBlock>>::iterator block_it = _map_blocks.begin(); block_it < end; ++block_it)
  {
    const std::unique_ptr<model::AutoBlock>& map_block = *block_it;
    if( rectangle.intersects(map_block->getBounds()) )
    {
      // Apply collision effect
      map_block->collision(player);

      // Destroy block
      _map_blocks.erase(block_it);

      break;
    }
  }
}

void Map::generateSquares(const sf::Time& elapsed_time)
{
  _time_since_last_square_generation += elapsed_time.asMilliseconds();
  if(_time_since_last_square_generation < _generate_square_interval)
    return;

  const int side = utils::maths::random(0, 4);
  sf::Vector2f position;
  Direction direction;

  const float x_speed = max_speed * utils::maths::random(min_speed_percent, 100) / 100;
  const float y_speed = max_speed * utils::maths::random(min_speed_percent, 100) / 100;

  switch(side)
  {
    // Top
    case 0:
    {
      position.x = utils::maths::random(0, _width);
      position.y = 0;
      direction.x = 0;
      direction.y = y_speed;
      break;
    }
    // Right
    case 1:
    {
      position.x = _width;
      position.y = utils::maths::random(0, _height);
      direction.x = -x_speed;
      direction.y = 0;
      break;
    }
    // Bottom
    case 2:
    {
      position.x = utils::maths::random(0, _width);
      position.y = _height;
      direction.x = 0;
      direction.y = -y_speed;
      break;
    }
    // Left
    case 3:
    {
      position.x = 0;
      position.y = utils::maths::random(0, _height);
      direction.x = x_speed;
      direction.y = 0;
      break;
    }
  }

  const float size = utils::maths::random(min_block_size, max_block_size);

  // Generate ennemy or bonus ?
  if( utils::maths::random(0, 101) <= bonus_block_chance )
  {
    const int type = utils::maths::random(0, 3);
    switch(type)
    {
      case 0: _map_blocks.emplace_back( new LifeBlock{position, size, direction} ); break;
      case 1: _map_blocks.emplace_back( new ShieldBlock{position, size, direction} ); break;
      case 2: _map_blocks.emplace_back( new ScoreBlock{position, size, direction} ); break;
    }
  }
  else
    _map_blocks.emplace_back( new EnnemyBlock{position, size, direction} );

  _time_since_last_square_generation = 0;
}

}
