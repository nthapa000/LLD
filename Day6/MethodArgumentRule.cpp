#include<iostream>
using namespace std;

// Method Argument Rule
// Subtype method arguments can be identical or wider than the supertype
// C++ imposes this by keeping signature identical

class Parent{
public:
    virtual void print(string msg){
        cout<<"Parent: "<<msg<<endl;
    }
};

class Child: public Parent{
public:
// member function declared with 'override' does not override a base class member, we will get this error message when we override with the different argument
// Here MethodArgumentRule followed
    void print(string msg) override{
        cout<<"Child: "<<msg<<endl;
    }
};

// Client that pass string as msg as client expects.
class Client{
private:
    Parent *p;

public:
    Client(Parent *p){
        this->p = p;
    }
    void printMsg(){
        p->print("Hello");
    }
};

int main(){
    Parent* parent = new Parent();
    Parent* child = new Child();

    // Client* client = new Client(parent);
    // even on passing child instance things work perfectly
    Client* client = new Client(child);
    client->printMsg();
}