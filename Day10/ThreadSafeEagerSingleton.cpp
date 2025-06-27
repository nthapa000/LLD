#include<iostream>
#include<mutex>

// eager initialization 
// not practical
// since it waste lot of memory if our object is expensive to create
// we can use it only when our object is light weight
using namespace std;

class Singleton{
private:
    static Singleton *instance;
    
    Singleton(){
        cout<<"Singleton constructor called!!"<<endl;
    }

public:
    static Singleton* getInstance(){
        // now we will get that instance only which is created once
        // it can never be null now since we gave it object during initialization
        return instance;
    }
};

// Initialize static members
// here while initializing we gave it a new Singleton create kar diya 
// as we declare it then we made Singleton type object in heap and gave its instance to this Singleton* type variable
Singleton* Singleton::instance = new Singleton();

int main(){
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    cout<<(s1 == s2)<<endl; 
}
