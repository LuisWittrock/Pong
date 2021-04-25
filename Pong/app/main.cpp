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
            window.setFramerateLimit(30);
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
            ballShape.setFillColor(sf::Color(100,250,50));
            ballShape.setRadius(20.f);
            ballShape.setPosition(WINDOW_WIDTH/2-10, WINDOW_HEIGHT/2-10);
            
            cout << "ball constructor";
        }

        CircleShape getBallshape()
        {
            return ballShape;
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
           window.draw(ball.getBallshape());
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
                
                //check for collision
                checkCollision();
                //Movement (paddle, ball)
                move();
                //update
                
                window.clear();
                
                // draw everything here...
                //redraw();
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