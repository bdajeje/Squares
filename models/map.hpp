#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <vector>

#include <SFML/Audio/Sound.hpp>

#include "graphics/drawable.hpp"
#include "graphics/effect.hpp"
#include "models/auto_block.hpp"
#include "models/player.hpp"

namespace model {

class Map final : public graphics::Drawable
{
  public:

    Map(float width, float height, float sound_volume);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& elapsed_time);

    void applyCollision(std::shared_ptr<Player>& player);

  private:

    void generateSquares(const sf::Time& elapsed_time);
    void createEffectsInformation(const std::vector<BlockEffect>& effects_information, const sf::Vector2f& position);

  private:

    float _width;
    float _height;

    std::vector<std::unique_ptr<model::AutoBlock>> _map_blocks;
    std::map<std::string, sf::Sound> _sounds;

    unsigned int _time_since_last_square_generation {0}; // in ms
    unsigned int _generate_square_interval {1000}; // in ms    

    std::vector<std::shared_ptr<sf::Text>> _flying_texts;
    std::vector<std::unique_ptr<graphics::Effect>> _graphic_effects;

    static constexpr float min_block_size {10};
    static constexpr float max_block_size {27};
    static constexpr int   min_speed_percent {35};
    static constexpr float max_speed {0.25};
    static constexpr int bonus_block_chance {20};
    static constexpr float s_flying_text_move {0.05};
    static constexpr float s_flying_text_margin {0.01};
};

}

#endif // MAP_HPP
