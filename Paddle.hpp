//
// Created by pc on 11.10.2026.
//

#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle(float szerokosc, float wysokosc, float pozx, float pozy) {
        rect.setSize(sf::Vector2f(szerokosc,wysokosc));
        rect.setPosition(sf::Vector2f(pozx,pozy));
        up = false;
        down = false;
    }

    void processEvents(sf::Keyboard::Key key,bool checkPressed) {
        if (checkPressed == true) {
            if (key == sf::Keyboard::W) {
                up = true;
            }
            if (key == sf::Keyboard::S) {
                down = true;
            }
        }
        if (checkPressed == false) {
            up = false;
            down = false;
        }
    }

    void update() {
        sf::Vector2f movement(0.f, 0.f);
        if (up && rect.getPosition().y > 0)
            movement.y -= 7.f;
        if (down && rect.getPosition().y + rect.getSize().y < 800)
            movement.y += 7.f;
        rect.move(movement);
    }

    void reset() {
        rect.setPosition(sf::Vector2f(100.f,350.f));
    }
    void resetai() {
        rect.setPosition(sf::Vector2f(1100.f,350.f));
    }

    void ai(float ballY) {
        float srodekPaletki = rect.getPosition().y + (rect.getSize().y / 2.f);
        float roznica = ballY - srodekPaletki;
        float predkoscAi = roznica * 0.08f;
        if (predkoscAi > 6.f) predkoscAi = 6.f;
        if (predkoscAi < -6.f) predkoscAi = -6.f;
        if (predkoscAi < 0 && rect.getPosition().y > 0)
            rect.move(0.f, predkoscAi);
        if (predkoscAi > 0 && rect.getPosition().y + rect.getSize().y < 800)
            rect.move(0.f, predkoscAi);
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(rect);
    }

    sf::FloatRect getBounds() const {
        return rect.getGlobalBounds();
    }

private:
    sf::RectangleShape rect;
    bool up;
    bool down;
};

#endif //PADDLE_HPP
