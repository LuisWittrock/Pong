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
        int xVelocity = 1;
        int yVelocity = 1;
        int xPos;
        int yPos;
        
        CircleShape ballShape;

        Ball()
        {
            xPos = WINDOW_WIDTH/2-10;
            yPos = WINDOW_WIDTH/2-10;
                
            ballShape.setFillColor(sf::Color(100,250,50));
            ballShape.setRadius(20.f);
            ballShape.setPosition(xPos, yPos);
        }

        CircleShape getBallshape()
        {
            return ballShape;
        }
        void move()
        {
            ballShape.setPosition(xPos += xVelocity, yPos += yVelocity);
        }

};

class Paddle : Frame
{
    public:
        int xPos;
        int yPos;
        RectangleShape rectangleShape;

        Paddle()
        {
            rectangleShape.setSize(Vector2f(10.f, 100.f));
            rectangleShape.setFillColor(Color(0,0,255));
        } 

        RectangleShape getRectangleShape()
        {
            return rectangleShape;
        }

        void setPosition(int x, int y)
        {
            rectangleShape.setPosition(Vector2f(x,y));
        }

        void move()
        {
            rectangleShape.setPosition(Vector2f(xPos, yPos));
        }
};

class Panel : Frame
{
    public:
        Ball ball;
        Paddle paddle1;
        Paddle paddle2;
        Panel()
        {
            paddle1.setPosition(5,WINDOW_HEIGHT/2-50);
            paddle1.xPos = 5;
            paddle1.yPos = WINDOW_HEIGHT/2-50;

            paddle2.setPosition(WINDOW_WIDTH - 15, WINDOW_HEIGHT/2-50); 
            paddle2.xPos = WINDOW_WIDTH - 15;
            paddle2.yPos = WINDOW_HEIGHT/2-50;
        }

        void redraw()
        {
           window.draw(ball.getBallshape());
           window.draw(paddle1.getRectangleShape());
           window.draw(paddle2.getRectangleShape());
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
            if(ball.yPos <= 0) ball.yVelocity  *= -1;
            if(ball.yPos >= WINDOW_HEIGHT - 10) ball.yVelocity  *= -1;
            if(ball.xPos <= 0) ball.xVelocity *= -1;
            if(ball.xPos >= WINDOW_WIDTH - 10) ball.xVelocity *= -1;
            
            //update score if hit vertical edge 
        }

        void drawWindow()
        {
            window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong");
            while(window.isOpen())
            {
                //Player Input
                if(Keyboard::isKeyPressed(Keyboard::W)) paddle1.yPos -= 1;
                if(Keyboard::isKeyPressed(Keyboard::S)) paddle1.yPos += 1;

                if(Keyboard::isKeyPressed(Keyboard::Up)) paddle2.yPos -= 1;
                if(Keyboard::isKeyPressed(Keyboard::Down)) paddle2.yPos += 1;
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