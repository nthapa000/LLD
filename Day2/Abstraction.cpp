#include<iostream>
#include<string>

using namespace std;

// denotes a real life car blueprint to make a real car we need to make object
// this is an abstract class since it has virtual keyword hence in C++ we can't directly instantiate nhi kr skte we need to define the child class which will define the abstract methods
class Car{
    // we don't need to know how the car works internally we just need to know how the car behaves or different function it has
    public:
        // virtual : says that this method is just declared here the responsibility of defining it is on the child class whoever will extend it /inherit it
        virtual void startEngine() = 0;
        virtual void shiftGear(int gear) = 0;
        virtual void accelerate() = 0;
        virtual void brake() = 0;
        virtual void stopEngine() = 0;
        virtual ~Car() {}
};
// Parent class Car was acting like an interface

// actual car 
// 
class SportsCar: public Car{
    public:
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed;
        int currentGear;

        SportsCar(string b, string m){
            this->brand = b;
            this->model = m;
            isEngineOn = false;
            currentSpeed = 0;
            currentGear = 0; // neutral
        }

        // we will now see how an actual car will implement all the function of the car 
        void startEngine() {
            isEngineOn = true;
            cout<<brand<<" "<<model<<" : Engine stars with a roar!! "<<endl;
        }

        void shiftGear(int gear){
            if(!isEngineOn){
                cout<<brand<<" "<<model<<" : Engine is off!! Cannot shift gear"<<endl;
                return; 
            }
            currentGear = gear;
            cout<<brand<<" "<<model<<" is shifted to the gear"<<currentGear<<endl;
        }

        void accelerate(){
            if(!isEngineOn){
                cout<<brand<<" "<<model<<" : Engine is off!! Cannot accelerate"<<endl;
                return; 
            }
            currentSpeed += 20;
            cout<<brand<<" "<<model<< " : Accelerating to "<< currentSpeed<<" km/h" <<endl;
        }

        void brake(){
            currentSpeed -= 20;
            if(currentSpeed<0) currentSpeed=0;
            cout<<brand<<" "<<model<<" : Braking! Speed is now "<< currentSpeed<< " km/h" <<endl;
        }

// declares all the variables again
        void stopEngine(){
            isEngineOn = false;
            currentGear = 0;
            currentSpeed = 0;
            cout<<brand<<" "<< model<<" : Engine is turned off"<<endl;
        }

};

int main(){

    // in OOPS in c++ parent class object can point to the child class object
    Car * myCar = new SportsCar("Ford","Mustang");
    // now in this car we can implement all the functions;

    myCar->startEngine();
    myCar->shiftGear(1);
    myCar->accelerate();
    myCar->shiftGear(2);
    myCar->accelerate();
    myCar->brake();
    myCar->stopEngine(); 
}