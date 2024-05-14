#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<sstream>
#include<windows.h>
using namespace sf;
const unsigned width = 1100;
const unsigned height = 900;
std::string scor(double n);
int main() {

    int dx = 1, dy = 1;
    int ballposx = 525, ballposy = 420;
    double c1 = 0, c2 = 0;
    int a = 0, b = 0;
    int mode = 0;
    Font myfont;
    Text player;
    Text computer;
    Text splayer;
    Text scomputer;
    myfont.loadFromFile("font/Pacifico.ttf");

    RenderWindow window(VideoMode(width, height), "ball");

    Texture balll, j1, j2, terrain, hors2, hors1, s;
    hors1.loadFromFile("images/hors1.png");
    hors2.loadFromFile("images/hors2.png");
    balll.loadFromFile("images/ball.jpg");
    j1.loadFromFile("images/red.jpg");
    j2.loadFromFile("images/blue.jpg");
    terrain.loadFromFile("images/Background.jpg");
    s.loadFromFile("images/start.png");
    SoundBuffer buffer;
    SoundBuffer buffer1;
    SoundBuffer buffer2;
    buffer.loadFromFile("sound/ball-tap.wav");
    buffer1.loadFromFile("sound/fail.wav");
    buffer2.loadFromFile("sound/out.wav");

    Sound sound;
    Sound sound1;
    Sound sound2;
    sound1.setBuffer(buffer1);
    sound.setBuffer(buffer);
    sound2.setBuffer(buffer2);


    Sprite player1(j1);
    Sprite player2(j2);
    Sprite h1(hors1);
    Sprite h2(hors2);

    RectangleShape s4(Vector2f(1100, 900));
    s4.setTexture(&terrain);

    h1.setPosition(300, 270);
    h2.setPosition(300, 270);
    player1.setPosition(10, 380);
    player2.setPosition(1050, 380);

    CircleShape ball(25.0f);
    ball.setTexture(&balll);
    Vector2f ball1Position(525, 420);
    ball.setPosition(ball1Position);

    RectangleShape start(Vector2f(1100, 900));
    start.setTexture(&s);

    Text timetext;
    timetext.setFont(myfont);
    timetext.setCharacterSize(40);
    timetext.setPosition(450, 830);

    //timer

    Clock timer;
    timer.restart();

    while (!Keyboard::isKeyPressed(Keyboard::Num1) && !Keyboard::isKeyPressed(Keyboard::Num2)) {
        window.draw(start);
        window.display();
    }

    while (window.isOpen())
    {
        a = 0; b = 0;
        window.setFramerateLimit(500);
        Event e;
        splayer.setFont(myfont);
        splayer.setString("player :");
        splayer.setCharacterSize(40);
        splayer.setPosition(100, 830);

        player.setFont(myfont);
        player.setString(scor(c2));
        player.setCharacterSize(40);
        player.setPosition(250, 830);

        scomputer.setFont(myfont);
        scomputer.setString("computer :");
        scomputer.setCharacterSize(40);
        scomputer.setPosition(760, 830);

        computer.setFont(myfont);
        computer.setString(scor(c1));
        computer.setCharacterSize(40);
        computer.setPosition(960, 830);



        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) window.close();
            if (Keyboard::isKeyPressed(Keyboard::Num1)) {
                mode = 1;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
                mode = 2;
            }

        }
        //----------------ball------------
        ball.move(dx, dy);
        Vector2f d = ball.getPosition();
        if (d.x < 0 || d.x>1050) {
            dx = -dx; sound.play();
        }
        if (d.y < 0 || d.y>850) {
            dy = -dy;
            sound.play();
        }

        //------------------player1---------
        if (Keyboard::isKeyPressed(Keyboard::A) && player1.getPosition().y > 0)  player1.move(0, -1);
        if (Keyboard::isKeyPressed(Keyboard::Q) && player1.getPosition().y < 730) player1.move(0, 1);
        Vector2f d2 = player1.getPosition();
        if (d2.y < 0) { d2.y = 0; player1.setPosition(10, 0); }
        if (d2.y > 730) { d2.y = 730; player1.setPosition(10, 730);}
        if (d.x == 45 && d.y > d2.y - 75 && d.y <= d2.y + 150) { dx = -dx; sound.play();}

        //---------------player2--------------
        if (mode == 1) {
            Vector2f d3 = player2.getPosition();
            if (d.y > d3.y && d.x > 600) player2.move(0, 1);
            if (d.y < d3.y && d.x > 600) player2.move(0, -1);

            if (d3.y < 0) { d3.y = 0; player2.setPosition(1050, 0); }
            if (d3.y > 730) { d3.y = 730; player2.setPosition(1050, 730); }

            if (d.x == 1015 && d.y > d3.y - 75 && d.y <= d3.y + 150) { dx = -dx; sound.play(); }
        }
        if (mode == 2) {
            if (Keyboard::isKeyPressed(Keyboard::P) && player2.getPosition().y > 0)  player2.move(0, -1);
            if (Keyboard::isKeyPressed(Keyboard::M) && player2.getPosition().y < 730) player2.move(0, 1);
            Vector2f d3 = player2.getPosition();
            if (d3.y < 0) { d3.y = 0; player2.setPosition(10, 0); }
            if (d3.y > 730) { d3.y = 730; player2.setPosition(10, 730); }
            if (d.x == 1000 && d.y > d3.y - 75 && d.y <= d3.y + 150) { dx = -dx; }


        }


        //*******************hors***************
        if (d.x == -1) {
            c1++;
            ballposx = rand() % 500 + 400;
            ball.setPosition(ballposx, ballposy);
            sound2.play();
            sound1.pause();
            Sleep(1000);
        }
        if (d.x == 1051) {
            c2++;
            ballposx = rand() % 500 + 400;
            ball.setPosition(ballposx, ballposy);
            sound2.play();
            Sleep(1000);

        }

        if (c1 == 2  ) {
            window.setFramerateLimit(1100);

        }
        if (c2 == 2) {
            window.setFramerateLimit(1100);

        }

        if (c1 == 3|| c2 == 3) {
            window.setFramerateLimit(950);

        }
        if (c1 == 4|| c2 == 4) {
            window.setFramerateLimit(1000);
        }
        if (c1 == 5) {
            window.draw(h2); window.setFramerateLimit(1); window.display();
            ball.setPosition(ball1Position);
            sound1.play();
            Sleep(2000);
            c1 = 0;
            c2 = 0;
        }
        if (c2 == 5) {
            window.draw(h1); window.setFramerateLimit(1); window.display();
            ball.setPosition(ball1Position);
            Sleep(2000);
            sound1.play();
            c1 = 0;
            c2 = 0;
   
        }
        //compteur du temps ecoule 
        int seconds = timer.getElapsedTime().asSeconds();
        std::stringstream time;
        time << "time:" << seconds << "s";
        timetext.setString(time.str());

        window.clear();
        window.draw(s4);
        window.draw(ball);
        window.draw(player1);
        window.draw(player2);
        window.draw(splayer);
        window.draw(player);
        window.draw(scomputer);
        window.draw(computer);
        window.draw(timetext);
        window.display();
    }
}
std::string scor(double n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}