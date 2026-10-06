

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main() {
    RenderWindow window(VideoMode(800, 600), "Bounce");
    World world(Vector2f(0, 1));

    PhysicsCircle ball;
    ball.setCenter(Vector2f(200, 100));
    ball.setRadius(20);
    world.AddPhysicsBody(ball);

    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);

    PhysicsRectangle Lwall;
    Lwall.setSize(Vector2f(20, 600));
    Lwall.setCenter(Vector2f(10, 300));
    Lwall.setStatic(true);
    world.AddPhysicsBody(Lwall);

    PhysicsRectangle Rwall;
    Rwall.setSize(Vector2f(20, 600));
    Rwall.setCenter(Vector2f(800, 290));
    Rwall.setStatic(true);
    world.AddPhysicsBody(Rwall);

    PhysicsRectangle roof;
    roof.setSize(Vector2f(800, 20));
    roof.setCenter(Vector2f(400, 10));
    roof.setStatic(true);
    world.AddPhysicsBody(roof);

    PhysicsRectangle box;
    box.setSize(Vector2f(75, 75));
    box.setCenter(Vector2f(400, 300));
    box.setStatic(true);
    world.AddPhysicsBody(box);

    int thudCount(1);
    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };
    int bangCount(0);
    box.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
        bangCount++;
        cout << "bang! " << bangCount << endl;
        if (bangCount == 3) {
            cout << "Hit the center 3 times, now ending program..." << endl;
            exit(0);
        }
    };

    Clock clock;
    Time lastTime(clock.getElapsedTime());
    while (true) {
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());
        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }

        window.clear(Color(0, 0, 0));
        window.draw(ball);
        window.draw(floor);
        window.draw(roof);
        window.draw(Rwall);
        window.draw(Lwall);
        window.draw(box);
        window.display();
    }
    
}
