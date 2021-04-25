#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Frame
{
    public:
        RenderWindow window;
        Event event;
        int WINDOW_WIDTH = 800;
        int WINDOW_HEIGHT = 600;
        Frame()
        {
            window.setFramerateLimit(50);
        }
};

class Ball : Frame
{
    public:
        int xVelocity;
        int yVelocity;
        int xPos;
        int yPos;
        
        CircleShape ballShape;

        Ball()
        {
            ballShape.setRadius(5000);
            ballShape.setFillColor(sf::Color(100,250,50));
            drawBall();
        }

        void drawBall()
        {
            window.clear(Color::Black);
            // draw everything here...
            window.draw(ballShape);
            // end the current frame
            window.display();
            
        }
        void move()
        {

        }

};

class Paddle
{
    public:
        int xPos;
        int yPos;
        RectangleShape rectangleShape;

        void drawPaddle()
        {

        }
        void move()
        {

        }
};

class Panel : Frame
{
    public:
        Paddle paddle1;
        Paddle paddle2;
        Ball ball;

        void redraw()
        {
           paddle1.drawPaddle();
           paddle2.drawPaddle();
           ball.drawBall(); 
        }

        void move()
        {
            paddle1.move();
            paddle2.move();
            ball.move();
        }

        void checkCollision()
        {
            //bounce ball of paddle
            //bounce ball of horizontal edge
            //update score if hit vertical edge 
        }

        void drawWindow()
        {
            window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong");
            while(window.isOpen())
            {
                //Player Input
                ball.drawBall();
                //check for collision
                checkCollision();
                //Movement (paddle, ball)
                move();
                //update
                
                window.clear(sf::Color::Black);
                cout << "test";
                // draw everything here...
                redraw();
                // window.draw(...);

                // end the current frame
                window.display();

                //close window
                while (window.pollEvent(Frame::Frame::event))
                {
                    if (event.type == Event::Closed) window.close();
                }
            }
        }
};


class Pong
{
    public:
        Pong()
        {
           Frame frame; 
        }
};

int main() 
{
    Pong pong;
    Panel panel;

    panel.drawWindow();
}