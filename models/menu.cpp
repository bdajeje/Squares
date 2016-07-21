#include "menu.hpp"

#include "managers/fontmanager.hpp"
#include "managers/sound_manager.hpp"
#include "utils/graphics.hpp"

namespace model {

const std::array<std::string, 2> Menu::s_menu_items = {"Resume", "Quit"};
const std::array<game::EventAction, 2> Menu::_s_item_actions = {
  game::EventAction::ShowGame,
  game::EventAction::Exit,
};
const sf::Color Menu::s_default_color {255, 255, 255};
const sf::Color Menu::s_selected_color {0, 0, 255};

Menu::Menu(std::shared_ptr<sf::RenderWindow>& window, const std::shared_ptr<utils::Settings>& settings)
  : _window {window}
  , _change_item_sound {sound::SoundManager::get("menu_change_item.wav")}
  , _select_item_sound {sound::SoundManager::get("menu_select_item.wav")}
  , _settings {settings}
{
  const float sound_volume = settings->get<float>(utils::Settings::SoundVolume, 50.f);
  _change_item_sound.setVolume(sound_volume);
  _select_item_sound.setVolume(sound_volume);

  const sf::Font& font = font::FontManager::get(font::Consolas);

  _texts.resize(s_menu_items.size());

  for(size_t i = 0; i < s_menu_items.size(); ++i)
  {
    sf::Text& text = _texts[i];
    text.setString(s_menu_items[i]);
    text.setFont(font);
    text.setCharacterSize(45);

    // Add item to mouse overables
    addOverrableText(&text);
  }

  const sf::Vector2u window_size = window->getSize();
  utils::graphics::centerVerticalPosition(_texts, window_size.x, window_size.y);

  changeMenuItem(_selected_menu_item, false);
}

void Menu::changeMenuItem(int number, bool play_sound)
{
  _texts[_selected_menu_item].setColor(s_default_color);

  if(number >= static_cast<int>(s_menu_items.size()))
    number = 0;
  else if(number < 0)
    number = s_menu_items.size() - 1;

  _selected_menu_item = number;
  _texts[_selected_menu_item].setColor(s_selected_color);

  // Play sound
  if(play_sound)
    _change_item_sound.play();
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  for(const sf::Text& text : _texts)
    target.draw(text, states);
}

void Menu::update(const sf::Time& /*elapsed_time*/)
{}

game::EventAction Menu::handleEvents(const sf::Event& event)
{
  // Remove compiler warnings about some enumeration values not handled in switch
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::MouseMoved:
    {
      checkTextOvered(sf::Mouse::getPosition(*_window));
      break;
    }
    case sf::Event::MouseButtonReleased:
    {
      // Check mouse is overred currently selected item, if yes return related item action
      const sf::Text* overred_text = checkTextOvered(sf::Mouse::getPosition(*_window));
      if(overred_text)
        return _s_item_actions.at(_selected_menu_item);
    }
    case sf::Event::KeyPressed:
    {
      if(isKeyPressed(sf::Keyboard::Up))
         changeMenuItem(_selected_menu_item - 1);
      else if(isKeyPressed(sf::Keyboard::Down))
         changeMenuItem(_selected_menu_item + 1);
      else if(isKeyPressed(sf::Keyboard::Escape))
        return game::EventAction::ShowGame;
      else if(isKeyPressed(sf::Keyboard::Return))
      {
        _select_item_sound.play();
        return _s_item_actions.at(_selected_menu_item);
      }

      break;
    }
  }

  return game::EventAction::Continue;
}

void Menu::focus()
{
  _window->setMouseCursorVisible(true);
}

void Menu::focusOverrabledText(const sf::Text* text)
{
  const size_t nbr_items = Menu::s_menu_items.size();
  for(size_t i = 0; i < nbr_items; ++i)
  {
    if(&_texts.at(i) == text)
    {
      changeMenuItem(i);
      return;
    }
  }
}

}
