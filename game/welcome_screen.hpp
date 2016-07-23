#ifndef WELCOMESCREEN_HPP
#define WELCOMESCREEN_HPP

#include <memory>
#include <vector>

#include <SFML/Audio/Sound.hpp>

#include "graphics/window.hpp"
#include "graphics/widget/text_input.hpp"
#include "game/mouse_texts_focusable.hpp"
#include "utils/settings.hpp"
#include "models/map.hpp"

namespace game {

class WelcomeScreen final : public graphics::Window,
                            public MouseTextsFocusable
{
  public:

    WelcomeScreen(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<utils::Settings>& settings);

    void update(const sf::Time& elapsed_time);
    void focus() {}
    void unfocus() {}

    std::string getPlayerName() const { return _name_input->getText(); }

  private:

    EventAction handleEvents(const sf::Event& event);
    void focusOverrabledText(const sf::Text* text);
    void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    std::shared_ptr<sf::RenderWindow> _window;
    sf::Text _title_text;
    sf::Text _intro_text;
    sf::Text _next_text;
    sf::Sound _select_item_sound;
    std::unique_ptr<graphics::TextInput> _name_input;
    std::shared_ptr<model::Map> _map;

    static const sf::Color s_default_color;
    static const sf::Color s_selected_color;
    static constexpr float s_item_margin {0.05};
    static constexpr float s_title_margin {0.05};
};

}

#endif // WELCOMESCREEN_HPP
