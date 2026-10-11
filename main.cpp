#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Paddle.hpp"
#include "Ball.hpp"

int main() {
    sf::RenderWindow PingPong(sf::VideoMode(1200, 800), "Ping-Pong");
    PingPong.setFramerateLimit(60);
    Paddle gracz(15.f,80.f,100.f,350.f);
    Paddle konkuter(15.f,80.f,1100.f,350.f);
    Ball pilka(10,590.f,250.f);

    int pktGracz = 0;
    int pktKonkuter = 0;

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/timesbd.ttf")) {
        std::cerr << "font error" << std::endl;
    }

    sf::Text textGracz;
    textGracz.setFont(font);
    textGracz.setCharacterSize(50);
    textGracz.setPosition(sf::Vector2f(545,20));
    textGracz.setString(std::to_string(pktGracz));

    sf::Text textKonkuter;
    textKonkuter.setFont(font);
    textKonkuter.setCharacterSize(50);
    textKonkuter.setPosition(sf::Vector2f(640,20));
    textKonkuter.setString(std::to_string(pktKonkuter));

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setPosition(sf::Vector2f(600,20));
    text.setString(":");

    while (PingPong.isOpen()) {

        sf::Event Event;
        while (PingPong.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                PingPong.close();

            if (Event.type == sf::Event::KeyPressed)
                gracz.processEvents(Event.key.code,true);
            if (Event.type == sf::Event::KeyReleased)
                gracz.processEvents(Event.key.code,false);
        }

        gracz.update();
        konkuter.ai(pilka.srodekPilki());
        pilka.update();

        if (pilka.getX() < 0) {
            pktKonkuter++;
            pilka.reset();
            gracz.reset();
            konkuter.resetai();
            textKonkuter.setString(std::to_string(pktKonkuter));
        }else if (pilka.getX() > 1200){
            pktGracz++;
            pilka.reset();
            gracz.reset();
            konkuter.resetai();
            textGracz.setString(std::to_string(pktGracz));
        }

        pilka.collision(gracz);
        pilka.collision(konkuter);

        PingPong.clear(sf::Color::Black);

        konkuter.drawTo(PingPong);
        gracz.drawTo(PingPong);
        pilka.drawTo(PingPong);

        PingPong.draw(textGracz);
        PingPong.draw(textKonkuter);
        PingPong.draw(text);

        PingPong.display();
    }

    return 0;
}
