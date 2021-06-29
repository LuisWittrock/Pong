#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Frame
{
    public:
        RenderWindow window;
        Event event;
        int WINDOW_WIDTH = 1000;
        int WINDOW_HEIGHT = 600;
        Frame()
        {
            window.setFramerateLimit(10);
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
            if(ball.xPos <= 15 && ball.yPos >= paddle1.yPos - 30 && ball.yPos <= paddle1.yPos + 120) ball.xVelocity *= -1;

            if((ball.xPos + 35) >= (WINDOW_WIDTH - 20) && ball.yPos >= paddle2.yPos - 30 && ball.yPos <= paddle2.yPos + 120) ball.xVelocity *= -1; 

            //bounce ball of horizontal edge
            if(ball.yPos <= 0) ball.yVelocity *= -1;
            if(ball.yPos + 40 >= WINDOW_HEIGHT) ball.yVelocity *= -1;


            if(ball.xPos <= 0)
            {
                ball.xPos = WINDOW_WIDTH/2-10;
                ball.yPos = WINDOW_WIDTH/2-10;
            }
            if(ball.xPos >= WINDOW_WIDTH)
            {
                ball.xPos = WINDOW_WIDTH/2-10;
                ball.yPos = WINDOW_WIDTH/2-10;
            }

            //stop paddle from leaving the screen
            if(paddle1.yPos<=0) paddle1.yPos=0;
			if(paddle1.yPos >= (WINDOW_HEIGHT-100)) paddle1.yPos = WINDOW_HEIGHT - 100;
			    
		    if(paddle2.yPos<=0) paddle2.yPos=0;
			    
		    if(paddle2.yPos >= (WINDOW_HEIGHT-100)) paddle2.yPos = WINDOW_HEIGHT-100;
        }

        void drawWindow()
        {
            window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong");
            while(window.isOpen())
            {
                sleep((milliseconds(4)));
                //Player Input
                if(Keyboard::isKeyPressed(Keyboard::W)) paddle1.yPos -= 2;
                if(Keyboard::isKeyPressed(Keyboard::S)) paddle1.yPos += 2;

                if(Keyboard::isKeyPressed(Keyboard::Up)) paddle2.yPos -= 2;
                if(Keyboard::isKeyPressed(Keyboard::Down)) paddle2.yPos += 2;
                //check for collision
                
                //Movement (paddle, ball)
                move();
                //update
                checkCollision();
                
                window.clear();
                
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

int main() 
{
    Frame frame;
    Panel panel;
    panel.drawWindow();
}