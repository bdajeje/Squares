#include "welcome_screen.hpp"

#include "utils/graphics.hpp"
#include "managers/fontmanager.hpp"

namespace game {

const sf::Color WelcomeScreen::s_default_color {255, 255, 255};
const sf::Color WelcomeScreen::s_selected_color {0, 0, 255};

WelcomeScreen::WelcomeScreen(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<utils::Settings>& settings)
  : _window {window}
{
  const float sound_volume = settings->get<float>(utils::Settings::SoundVolume, 50.f);
  _select_item_sound.setVolume(sound_volume);

  const sf::Vector2u window_size = _window->getSize();
  const sf::Font& font = font::FontManager::get(font::Consolas);

  // Title
  _title_text.setString("SQUARES");
  _title_text.setFont(font);
  _title_text.setCharacterSize(45);
  _title_text.setPosition(0, s_title_margin * window_size.y);
  utils::graphics::centerHonrizontally(_title_text, window_size.x);

  // Name text input
  const sf::Vector2f input_name_size {window_size.x / 2.f, window_size.y * 0.05f};
  const sf::Vector2f input_name_pos {(window_size.x - input_name_size.x) / 2, (window_size.y - input_name_size.y) / 2};
  _name_input.reset( new graphics::TextInput{sf::Color::Black, font, 25,
                                             s_default_color, input_name_size, input_name_pos,
                                             28, "[a-zA-Z0-9]+"} );

  // Fill player name input with last player name who played
  _name_input->setText( settings->get<std::string>(utils::Settings::LastPlayer, "") );

  // Intro sentence
  _intro_text.setString("Enter your player name");
  _intro_text.setFont(font);
  _intro_text.setCharacterSize(25);
  _intro_text.setPosition(0, input_name_pos.y - input_name_size.y - s_title_margin * window_size.y);
  utils::graphics::centerHonrizontally(_intro_text, window_size.x);

  // Next "button"
  _next_text.setString("NEXT");
  _next_text.setFont(font);
  _next_text.setCharacterSize(30);
  _next_text.setPosition(0, input_name_pos.y + input_name_size.y + (window_size.y * s_item_margin));
  utils::graphics::centerHonrizontally(_next_text, window_size.x);  

  // Add next button to mouse overables
  addOverrableText(&_next_text);
}

void WelcomeScreen::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_title_text, states);
  target.draw(_intro_text, states);
  target.draw(*_name_input, states);
  target.draw(_next_text, states);
}

void WelcomeScreen::update(const sf::Time& elapsed_time)
{
  _name_input->update(elapsed_time);
}

EventAction WelcomeScreen::handleEvents(const sf::Event& event)
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
      // There is only one focusabled text, so if any is found, we already know which one has been clicked
      const sf::Text* overred_text = checkTextOvered(sf::Mouse::getPosition(*_window));
      if(overred_text && !_name_input->empty())
        return EventAction::CreateGame;
    }
    case sf::Event::TextEntered:
    {
      _name_input->addText(sf::String{event.text.unicode});
      break;
    }
    case sf::Event::KeyPressed:
    {
      if(isKeyPressed(sf::Keyboard::BackSpace))
        _name_input->removeFromEnd(1);
      else if(isKeyPressed(sf::Keyboard::Return) && !_name_input->empty())
        return EventAction::CreateGame;

      break;
    }
  }

  return EventAction::Continue;
}

void WelcomeScreen::focusOverrabledText(const sf::Text* text)
{
  if(!text)
  {
    _next_text.setColor( s_default_color );
    return;
  }

  // Because there is only one focusable text in this window, we already know which text is focused :)
  _next_text.setColor( s_selected_color );
}

}
