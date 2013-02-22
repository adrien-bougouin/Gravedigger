#include "CharacterFactory.hpp"

CharacterFactory::CharacterFactory() {
  // Nothing yet
}

/**
 ** Names must be set as it were class Name
 **/
Character * CharacterFactory::get(const std::string name) {
  Character * character;

  if (name.compare("Gravedigger")==0) { // Instance of Gravedigger required
    character = new Character(std::string("Gravedigger"));
    CComponent * position = new CPosition(character,100,240);
    CComponent * boundingbox = new CBoundingBox(character,
						sf::IntRect(100,240,42,38));
    CComponent * sprite =
      new CSprite(character,
		  std::string("material/img/chara-design/gravedigger.png"),
		  1.0);
    //((CSprite *) sprite)->updateSubSprite(3,3,42,38); // TODO: Rework on it
    //    ((CSprite *) sprite)->setOrigin("middle","bottom");
    CComponent * speed = new CSpeed(character);
    CComponent * acceleration = new CAcceleration(character);
    character->addComponent(std::string("Position"),position);
    character->addComponent(std::string("BoundingBox"),boundingbox);
    character->addComponent(std::string("Sprite"),sprite);
    character->addComponent(std::string("Speed"),speed);
    character->addComponent(std::string("Acceleration"),acceleration);
    
    // Creating states
    sf::Time oneSec = sf::seconds(1.0);
    sf::Int64 thousandMillisec = oneSec.asMicroseconds(); 
    CState * state = new CState(character, thousandMillisec);
    AStand * stand = new AStand(character, 2.0*thousandMillisec);
    sf::IntRect subSprite1(3,3,42,45); // Stand 1
    sf::IntRect subSprite2(52,3,42,45); // Stand 2
    stand->addSubSprite(subSprite1);
    stand->addSubSprite(subSprite2);
    ALeft  * left  = new ALeft (character, 0.5*thousandMillisec);
    ARight * right = new ARight(character, 0.5*thousandMillisec);
    sf::IntRect subSprite3(3,52,42,38);
    sf::IntRect subSprite4(52,52,42,38);
    sf::IntRect subSprite5(102,52,42,38);
    sf::IntRect subSprite6(152,52,42,38);
    left->addSubSprite(subSprite3); left->addSubSprite(subSprite4);
    left->addSubSprite(subSprite5); left->addSubSprite(subSprite6);
    right->addSubSprite(subSprite3); right->addSubSprite(subSprite4);
    right->addSubSprite(subSprite5); right->addSubSprite(subSprite6);    
    state->addAnimation(std::string("Stand"),stand);
    state->addAnimation(std::string("Left"),  left);
    state->addAnimation(std::string("Right"),right);
    
    character->addComponent(std::string("State"),state);
    state->setState("Stand");
  }
  
  return character;

}
