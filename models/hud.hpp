#ifndef HUD_HPP
#define HUD_HPP

#include <memory>

#include "graphics/drawable.hpp"
#include "models/player.hpp"

namespace model {

class HUD final : public graphics::Drawable
{
  public:

    HUD(std::shared_ptr<Player>& player, float width, float height);

    void update(const sf::Time& elapsed_time);

    void updateScore(unsigned int score);

    void showGameOver();
    void hideGameOver() { _show_game_over = false; }

  protected:

    void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateElapsedTime(sf::Int32 value);    
    void updateBar(sf::RectangleShape& bar, float value, float max_value);
    float itemMargin() const;

  private:

    std::shared_ptr<Player> _player;
    float _width;
    float _height;
    sf::Text _player_name;
    sf::Text _elapsed_time_text;
    sf::Text _score;
    sf::Text _game_over;
    sf::Text _game_over_score;
    sf::RectangleShape _health_bar;
    sf::RectangleShape _shield_bar;
    sf::Int32 _elapsed_time {0};
    bool _show_game_over {false};

    static constexpr float _margin {0.03};
    static constexpr float _item_margin {0.03};
    static constexpr float _bar_max_width {0.15};
    static constexpr float _bar_height {0.01};
};

}

#endif // HUD_HPP
