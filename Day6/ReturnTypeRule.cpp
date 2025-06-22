#include<iostream>
using namespace std;

// Return type Rule:
// Subtype overridden method return type should be either identical
// or narrower than the parent method's return type.
// This is also called as return type covariance.
// C++ enforces this by covariance

class Animal{
// some common Animal Methods
};

class Dog: public Animal{
// Additional Dog methods specific to Dogs
};

class Parent{
public:
    virtual Animal* getAnimal(){
        cout<<"Parent: Returning Animal instance"<<endl;
        return new Animal();
    }
};

class Child: public Parent{
public:
// override and returning the narrower class this is called covariance
// but if we return the parent of Animal class lets says Organism class then it must not be accepted
    Dog* getAnimal() override{
        cout<<"Child: Returning Dog instance"<<std::endl;
        return new Dog();
    }
};

class Client{
private:
    Parent* p;

public:
    Client(Parent* p){
        this->p = p;
    }

    void takeAnimal(){
        p->getAnimal();
    }
};

int main(){
    Parent* parent = new Parent();
    Child* child = new Child();

    Client* client = new Client(parent);
    client->takeAnimal();

    return 0;
}