#include<iostream>
using namespace std;

// this singleton class is not thread safe
// multiple thread can access our application if it support multiple threading
// getInstance() method can be parallel accessed by two threads and two thread can simultaneously create two separate object 
// but we want it to have only single object
// we will put locks 
// 

class Singleton{
// Now lets make the constructor private such that it cannot be accessed from outside the class
// after making the constructor private i cannot create object it in this way
// "Singleton::Singleton()" is inaccessible
// Singleton* s1 = new Singleton();
// Now we have closed the object creation of the this class
// We will move forward to how we can create a only a single object of the class so we have to provide a public method 

public:
// I want that anyone from outside who want to create the object of Singleton will be able to make through getInstance() only
    // static Singleton* getInstance(){
        // to call the getInstance we need an object but we are making getInstance to make the object
        // hence we need to make it static
        // static method belong to class 
        // usko call krne ke liye class ka naam and then function name
        // all object have same static function
    //     return new Singleton();
    // }
    static Singleton* getInstance(){
        if(instance == nullptr){
            instance = new Singleton();
        }
        return instance;
        // now once the object is created we will return it again and again instead of creating a new object 
    }

private:
    // We need a thing which can control that ek hi instance banne
    // lets take a variable which will hold the instance of the Singleton, that variable will hold the pointer which points to the object in the heap memory
    // it will see that it is already created or not if create getInstance will return it only else it will create a new one
    
    static Singleton *instance; 
    // since i want that this variable is accessed by anyone hence i have to also make this static
    // since it is static variable we have to declare it 
    // in c++ it is declared outside class


// public:
    // constructor always called only when object is created
    Singleton(){
        cout<<"Singleton Constructor called. New object created."<<endl;
    }

};

Singleton* Singleton::instance = nullptr;//Singelton type pointer is assigned a null pointer

int main(){
    // s1 and s2 are the name of the two pointer which point to the object which is declared in the heap memory
    // Singleton* s1 = new Singleton();
    // Singleton* s2 = new Singleton();

    // is object created s1 and s2 are same? No
    // Hence we can create as many object we want
    // cout<<(s1 == s2)<<endl;

    // Singleton* s1 = Singleton::getInstance();
    // Singleton* s2 = Singleton::getInstance();
    // cout<<(s1 == s2)<<endl;
    // Still we can create multiple object proof s1 and s2 are not equal

    // We need a thing which can control that ek hi instance banne
    // lets take a variable which will hold the instance of the Singleton, that variable will hold the pointer which points to the object in the heap memory
    // it will see that it is already created or not if create getInstance will return it only else it will create a new one

    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    cout<<(s1 == s2)<<endl;
    // Now a single object is created
}