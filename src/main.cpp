#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "CharacterFactory.hpp"
#include "EnvironmentFactory.hpp"
#include "ItemFactory.hpp"
#include "AThrow.hpp"

using namespace std;

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Gravedigger");
  window.setFramerateLimit(60);

  // Character
  CharacterFactory cf;
  Character * gravedigger = cf.get("Gravedigger");
  CSprite * sprite = (CSprite *) gravedigger->getComponent("Sprite");
  CState * state = (CState*) gravedigger->getComponent("State");
  sprite->updatePosition();

  // Environment
  EnvironmentFactory ef;
  Environment * floor = ef.get("Floor");
  CSprite * fsprite = (CSprite *) floor->getComponent("Sprite");
  fsprite->updatePosition();

  // Main loop
  bool thrown= false;
  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    sf::Time elapsed = clock.restart();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
	window.close();
      }
      if ((event.type == sf::Event::KeyPressed) &&
	  (event.key.code == sf::Keyboard::D) &&
	  (state->getState().compare("Right")!=0)) {
	state->setState("Right");
      }
      if ((event.type == sf::Event::KeyPressed) &&
	  (event.key.code == sf::Keyboard::Q) &&
	  (state->getState().compare("Left")!=0)) {
	state->setState("Left");
      }
      if ((event.type == sf::Event::KeyReleased) &&
	  (event.key.code == sf::Keyboard::D) &&
	  (state->getState().compare("Right")==0)) {
	state->setState("Stand");
      }
      if ((event.type == sf::Event::KeyReleased) &&
	  (event.key.code == sf::Keyboard::Q) &&
	  (state->getState().compare("Left")==0)) {
	state->setState("Stand");
      }
      if (event.type == sf::Event::MouseButtonPressed) {
	ACThrow * throwAction = (ACThrow*) gravedigger->getComponent("Throw");
	throwAction->setX(event.mouseButton.x);
	throwAction->setY(event.mouseButton.y);
	throwAction->execute();
	thrown  = true;
      }
      

    }

    // TODO register elements
    // Ask in collision handler item to draw
    state->update(elapsed.asMicroseconds());

    window.clear(); // not sure why i do dat
    window.draw(sprite->getSprite() );
    if (thrown) {
      GameObject * shovel;
      shovel = ((ACThrow*)gravedigger->getComponent("Throw"))->getItem();
      ((CState*)shovel->getComponent("State"))->update(elapsed.asMicroseconds());
      window.draw(((CSprite*)shovel->getComponent("Sprite"))->getSprite());
    }

    window.draw(fsprite->getSprite());
    window.display();

  }

return 0;
}

