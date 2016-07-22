#include "map.hpp"

#include "models/ennemy_block.hpp"
#include "models/life_block.hpp"
#include "models/shield_block.hpp"
#include "models/score_block.hpp"
#include "models/scale_block.hpp"
#include "utils/mathematics.hpp"
#include "managers/sound_manager.hpp"
#include "managers/fontmanager.hpp"
#include "graphics/effects/move.hpp"
#include "graphics/effects/fading.hpp"
#include "graphics/effects/remove_from.hpp"

namespace model {

Map::Map(float width, float height, float sound_volume)
  : _width {width}
  , _height {height}
{
  // By default reserver some space for future map blocks
  _map_blocks.reserve(100);

  // Load sounds
  std::array<std::string, 5> sound_files = {"bonus_life.wav", "bonus_shield.wav", "bonus_score.wav", "bonus_scale.wav", "ennemy_beep.wav"};
  for(const std::string& sound_file : sound_files)
  {
    sf::Sound& sound = _sounds[sound_file];
    sound.setBuffer(sound::SoundManager::get(sound_file));
    sound.setVolume(sound_volume);
  }
}

void Map::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Draw flying texts
  for(const std::shared_ptr<sf::Text>& flying_text : _flying_texts)
    target.draw(*flying_text, states);

  // Draw block
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

  // Update effects
  for(auto it = _graphic_effects.begin(); it < _graphic_effects.end(); ++it)
  {
    std::unique_ptr<graphics::Effect>& effect = *it;

    if(effect->isFinished())
    {
      _graphic_effects.erase(std::remove(_graphic_effects.begin(), _graphic_effects.end(), effect), _graphic_effects.end());
      continue;
    }

    effect->update(elapsed_time);
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
      const std::vector<BlockEffect> effects_information = map_block->collision(player);

      // Create collision effect messages      
      createEffectsInformation(effects_information, map_block->getPosition());

      // Play sound
      _sounds.at(map_block->getSoundFile()).play();

      // Destroy block
      _map_blocks.erase(block_it);

      break;
    }
  }
}

void Map::createEffectsInformation(const std::vector<BlockEffect>& effects_information, const sf::Vector2f& position)
{
  float y_offset = 0;
  for(const BlockEffect& effect_info : effects_information)
  {
    sf::Vector2f effect_pos = position;

    // Create flying text
    std::shared_ptr<sf::Text> flying_text = std::make_shared<sf::Text>(effect_info.text, font::FontManager::get(font::Consolas), 17);

    // Place text correctly
    effect_pos.x -= flying_text->getGlobalBounds().width / 2;
    effect_pos.y -= y_offset;

    flying_text->setPosition(effect_pos);
    flying_text->setColor(effect_info.color);
    _flying_texts.push_back(flying_text);

    // Prevent multipe effects from stacking (having same position)
    y_offset -= flying_text->getGlobalBounds().height + _height * s_flying_text_margin;

    // Create associated effect
    static const sf::Time duration = sf::milliseconds(750);
    static const sf::Vector2f move {0, -_height * s_flying_text_move};
    _graphic_effects.emplace_back( new graphics::effect::Move{flying_text, duration, move} );
    _graphic_effects.emplace_back( new graphics::effect::Fading{flying_text, duration, 0} );
    _graphic_effects.emplace_back( new graphics::effect::RemoveFrom<std::vector<std::shared_ptr<sf::Text>>>{flying_text, duration, &_flying_texts} );
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

  // Randomly generate ennemy or bonus
  if( utils::maths::random(0, 101) <= bonus_block_chance )
  {
    const int type = utils::maths::random(0, 4);
    switch(type)
    {
      case 0: _map_blocks.emplace_back( new LifeBlock{position, size, direction, "bonus_life.wav"} ); break;
      case 1: _map_blocks.emplace_back( new ShieldBlock{position, size, direction, "bonus_shield.wav"} ); break;
      case 2: _map_blocks.emplace_back( new ScoreBlock{position, size, direction, "bonus_score.wav"} ); break;
      case 3: _map_blocks.emplace_back( new ScaleBlock{position, size, direction, "bonus_scale.wav"} ); break;
    }
  }
  else
    _map_blocks.emplace_back( new EnnemyBlock{position, size, direction, "ennemy_beep.wav"} );

  _time_since_last_square_generation = 0;
}

}
