#include<iostream>
#include<string>

using namespace std;

class ManualCar{

private:
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;
    int currentGear;

public:
    ManualCar(string brand, string model){
        this->brand = brand;
        this->model = model;
        this->isEngineOn = false;
        this->currentSpeed = 0;
        this->currentGear = 0;
    }

    void startEngine(){
        isEngineOn = true;
        cout<<brand<<" "<<model<<" : Engine Started. "<<endl;
    }

    void stopEngine(){
        isEngineOn = false;
        currentSpeed = 0;
        cout<<brand<<" "<<model<<" : Engine turned off."<<endl;
    }

    // Overloading accelerate - Static Polymorphism
    void accelerate(){
        if(!isEngineOn){
            cout<<brand<<" "<<model<<" : Cannot accelerate! Engine is off." <<endl;
            return;
        }
        currentSpeed += 20;
        cout<<brand<<" "<<model<<" : Accelerating to "<<currentSpeed<<" km/h"<<endl;
    }

    void accelerate(int speed){
        if(!isEngineOn){
            cout<<brand<<" "<<model<<" : Cannot accelerate! Engine is off." <<endl;
            return;
        }
        currentSpeed += speed;
        cout<<brand<<" "<<model<<" : Accelerating to "<<currentSpeed<<" km/h"<<endl;
    }
    
    void brake(){
        currentSpeed -= 20;
        if(currentSpeed < 0) currentSpeed = 0;
        cout<<brand<<" "<<model<<": Braking! Speed is now "<<currentSpeed<<" km/h"<<endl; 
    }

    void shiftGear(int gear){
        currentGear = gear;
        cout<<brand<<" "<<model<<": Shifted to gear "<<currentGear<<endl;
    }  
};

int main(){
    ManualCar* myManualCar = new ManualCar("Suzuki","WagonR");
    myManualCar->startEngine();
    myManualCar->accelerate();
    myManualCar->accelerate(40);
    myManualCar->brake();
    myManualCar->stopEngine();

    delete myManualCar;
    return 0;
}

