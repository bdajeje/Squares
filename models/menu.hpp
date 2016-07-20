#ifndef MENU_HPP
#define MENU_HPP

#include <memory>
#include <vector>

#include <SFML/Audio/Sound.hpp>

#include "graphics/window.hpp"

namespace model {

class Menu final : public graphics::Window
{
  public:

    Menu(std::shared_ptr<sf::RenderWindow>& window);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& elapsed_time);
    void focus();
    void unfocus() {}

  private:

    void changeMenuItem(int number, bool play_sound = true);
    game::EventAction handleEvents(const sf::Event& event);

  private:

    std::shared_ptr<sf::RenderWindow> _window;
    std::vector<sf::Text> _texts;
    size_t _selected_menu_item {0};
    sf::Sound _change_item_sound;
    sf::Sound _select_item_sound;

    static const std::array<std::string, 5> s_menu_items;
    static const std::array<game::EventAction, 5> _s_item_actions;
    static const sf::Color s_default_color;
    static const sf::Color s_selected_color;
};

}

#endif // MENU_HPP
