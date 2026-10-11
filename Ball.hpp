//
// Created by pc on 11.10.2026.
//

#ifndef BALL_HPP
#define BALL_HPP

#include "SFML/Graphics/CircleShape.hpp"
#include "Paddle.hpp"

class Ball {
public:
    Ball(float radius, float pozx, float pozy) {
        circ.setRadius(radius);
        circ.setPosition(sf::Vector2f(pozx,pozy));
        circPosition = sf::Vector2f(pozx,pozy);
        circ.setFillColor(sf::Color::Red);
    }

    void update() {

        circPosition.x += xVelocity;
        circPosition.y += yVelocity;
        circ.setPosition(circPosition);

        if (circPosition.y <= 0) {
            circPosition.y = 0;
            yVelocity = -yVelocity;
        }
        if (circPosition.y + circ.getRadius() * 2 >= 800) {
            circPosition.y = 800 - circ.getRadius() * 2;
            yVelocity = -yVelocity;
        }
    }

    void reset() {
        circPosition = sf::Vector2f(590.f,250.f);
        circ.setPosition (circPosition);
        if (xVelocity > 0) xVelocity = -5.f;
        else xVelocity = 5.f;
        yVelocity = 1.f;
        pierwszyRzut = true;
    }

    void collision(Paddle &paddle) {
        if (getBounds().intersects(paddle.getBounds())) {
            xVelocity = - xVelocity;
            if (pierwszyRzut) {
                if (xVelocity > 0) {
                    xVelocity = 10.f;
                }else {
                    xVelocity = -10.f;
                    pierwszyRzut = false;
                }
            }

            if (xVelocity > 0) {
                circPosition.x = paddle.getBounds().left + paddle.getBounds().width + 1.f;
            } else {
                circPosition.x = paddle.getBounds().left - (circ.getRadius() * 2) - 1.f;
            }

            float srodekPaletki = paddle.getBounds().top + (paddle.getBounds().height / 2.f);
            float roznica = srodekPilki() - srodekPaletki;
            yVelocity = roznica * 0.1f;
        }
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(circ);
    }

    sf::FloatRect getBounds() const {
        return circ.getGlobalBounds();
    }

    float srodekPilki() const {
        return circPosition.y + circ.getRadius();
    }

    float getX() const {
        return circPosition.x;
    }

private:
    sf::CircleShape circ;
    sf::Vector2f circPosition;
    float xVelocity =  -5.f;
    float yVelocity = 1.f;
    bool pierwszyRzut = true;
};

#endif //BALL_HPP
