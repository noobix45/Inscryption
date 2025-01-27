#include "end_screen.h"

#include "SFML/Window/Mouse.hpp"

EndScreen::EndScreen(sf::RenderWindow &window, const sf::Font &font, int player_id) : window(window), font(font)
{
    init_text(player_id);
}

void EndScreen::init_text(const int player_id)
{
    winner_text.setFont(font);
    winner_text.setCharacterSize(100);
    winner_text.setFillColor(text_color);
    winner_text.setString("Player " + std::to_string(player_id) + " wins!");
    winner_text.setOrigin(winner_text.getGlobalBounds().width / 2.0f, winner_text.getGlobalBounds().height / 2.0f);
    winner_text.setPosition(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f - 300.0f);

    play_again_text.setFont(font);
    play_again_text.setCharacterSize(80);
    play_again_text.setFillColor(text_color);
    play_again_text.setString("Care to try again?");
    play_again_text.setOrigin(play_again_text.getGlobalBounds().width / 2.0f, play_again_text.getGlobalBounds().height / 2.0f);
    play_again_text.setPosition(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f);

    yes_button.setFont(font);
    yes_button.setCharacterSize(70);
    yes_button.setFillColor(text_color);
    yes_button.setString("Yes");
    yes_button.setOrigin(yes_button.getGlobalBounds().width / 2.0f, yes_button.getGlobalBounds().height / 2.0f);
    yes_button.setPosition(static_cast<float>(window.getSize().x) / 2.0f + 300.0f, static_cast<float>(window.getSize().y) / 2.0f + 150.0f);

    no_button.setFont(font);
    no_button.setCharacterSize(60);
    no_button.setFillColor(text_color);
    no_button.setString("No");
    no_button.setOrigin(no_button.getGlobalBounds().width / 2.0f, no_button.getGlobalBounds().height / 2.0f);
    no_button.setPosition(static_cast<float>(window.getSize().x) / 2.0f - 300.0f, static_cast<float>(window.getSize().y) / 2.0f + 150.0f);

}

void EndScreen::render() const
{
    window.draw(winner_text);
    window.draw(play_again_text);
    window.draw(no_button);
    window.draw(yes_button);
}

void EndScreen::handleClick(const sf::RenderWindow &window)
{
    const sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if(no_button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        restart = false;
    if(yes_button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        restart = true;
}

bool EndScreen::gameStatus() const
{
    return restart;
}