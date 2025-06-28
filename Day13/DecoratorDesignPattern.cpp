#include <iostream>
#include <string>

using namespace std;

// Component Interface: defines a common interface for Mario and all power up decorators.
class Character{
public:
    virtual string getAbilities() const = 0;
    virtual ~Character(){} //virtual destructor
};

// Concrete Component : Basic mario character without power up
// is a relationship
class Mario : public Character{
public:
    string getAbilities() const override{
        return "Mario";
    }
};

// Abstract Decorator: CharacterDecorator "is-a" Character and "has-a" character.
class CharacterDecorator : public Character {
protected:
    Character* character;

public:
    CharacterDecorator(Character* c){
        this->character = c;
    }
};

// Concrete Decorator: Height-Increasing Power-up.
class HeightUp : public CharacterDecorator{
public: 
    HeightUp(Character *c) : CharacterDecorator(c){}

    string getAbilities() const override{
        return character->getAbilities() + "with HeightUp";
    }
};

// Concrete Decorator: Gun Shooting Power-up
class GunPowerUp : public CharacterDecorator{
public:
    GunPowerUp(Character *c) : CharacterDecorator(c){}

    string getAbilities() const override{
        return character->getAbilities() + "with Gun";
    }    
};

// Concrete Decorator : Star Power - up (temporary Abilities)
class StarPowerUp : public CharacterDecorator{
public:
    StarPowerUp(Character* c):CharacterDecorator(c){}

    string getAbilities() const override{
        return character->getAbilities() + " with Star power (Limited Time)";
    }

    ~StarPowerUp(){
        cout<<"Destroying StarPowerUp Decorator"<<endl;
    }
};

int main() {
    // Create a basic Mario character.
    Character* mario = new Mario();
    cout << "Basic Character: " << mario->getAbilities() << endl;

    // Decorate Mario with a HeightUp power-up.
    mario = new HeightUp(mario);
    cout << "After HeightUp: " << mario->getAbilities() << endl;

    // Decorate Mario further with a GunPowerUp.
    mario = new GunPowerUp(mario);
    cout << "After GunPowerUp: " << mario->getAbilities() << endl;

    // Finally, add a StarPowerUp decoration.
    mario = new StarPowerUp(mario);
    cout << "After StarPowerUp: " << mario->getAbilities() << endl;

    delete mario;

    return 0;
}