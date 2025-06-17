// This example shows everything Abstraction, Polymorphism, Encapsulation and Inheritance
// Abstraction was about data hiding hence we made it virtual for you to accelerate car there is no need to know how it accelerate , its definition we are seeing it inside the hood
// Inheritance: ManualCar and ElecticCar are inheriting the Car object
// Encapsulation: Data security
#include <iostream>
#include <string>

using namespace std;

// Base Car class
class Car{
protected:

    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;

public:
    Car(string brand, string model){
        this->brand = brand;
        this->model = model;
        this->isEngineOn = false;
        this->currentSpeed = 0;
    }

//Common methods for all Cars
    void startEngine() {
        isEngineOn = true;
        cout<<brand<<" "<<model<<" : Engine started "<<endl;
    }

    void stopEngine(){
        isEngineOn = false;
        currentSpeed = 0;
        cout<<brand<<" "<<model<<" : Engine turned off"<<endl;
    }


    virtual void accelerate() = 0;// Abstract method for dynamic Polymorphism
    virtual void accelerate(int speed) =0;// Abstract method for static Polymorphism 
    virtual void brake() = 0;// Abstract method for dynamic Polymorphism
    virtual ~Car(){}; // Virtual Destructor
};

class ManualCar: public Car{
private:
    int currentGear; //specific to the ManualCar

public:
    ManualCar(string brand, string model):Car(brand,model){
        this->currentGear = 0;
    }

    // Specialized method for the ManualCar 
    void shiftGear(int gear){
        currentGear = gear;
        cout<<brand<<" "<<model<<": Shifted to gear "<<currentGear<<endl;
    }  

    // Overriding accelerate - Dynamic Polymorphism (Method overriding)
    void accelerate(){
        if(!isEngineOn){
            cout<<brand<<" "<<model<<" : Cannot accelerate! Engine is off." <<endl;
            return;
        }
        currentSpeed += 20;
        cout<<brand<<" "<<model<<" : Accelerating to "<<currentSpeed<<" km/h"<<endl;
    }

    // overriding and overloading accelerate at the same time.
    void accelerate(int speed){
        if(!isEngineOn){
            cout<<brand<<" "<<model<<": Cannot Accelerate! engine is off"<<endl;
            return;
        }
        currentSpeed += speed;
        cout<<brand<<" "<<model<<" : Accelerating to "<<currentSpeed<<" km/h"<<endl;
    }

    // Overriding brake - Dynamic polymorphism
    void brake(){
        currentSpeed -= 20;
        if(currentSpeed < 0) currentSpeed = 0;
        cout<<brand<<" "<<model<<": Braking! Speed is now "<<currentSpeed<<" km/h"<<endl; 
    }
};


class ElectricCar: public Car{
private:
    int batteryLevel;

public:
    ElectricCar(string brand,string model):Car(brand,model){
        this->batteryLevel = 100;
    }

    void chargeBattery(){
    // unique method for the ElecticCar
        batteryLevel = 100;
        cout<<brand<<" "<<model<<" : Battery fully charged!" <<endl;
    }

    // Overriding accelerate - Dynamic Polymorphism
    void accelerate(){
        if(!isEngineOn){
            cout<<brand<<" "<<model<<" : Cannot accelerate! Engine is off."<<endl;
            return;
        }
        if(batteryLevel<=0){
            cout<<brand<<" "<<model<<" : battery dead! Cannot Accelerate."<<endl;
            return;
        }
        batteryLevel -= 10;
        currentSpeed += 15;
        cout<<brand<<" "<<model<<" : Accelerating to "<<currentSpeed <<" km/h. Battery at "<<batteryLevel<<"%."<<endl;
    }

    // Overriding and overloading accelerate
    void accelerate(int speed){
        if(!isEngineOn){
            cout<<brand<<" "<<model<<" : Cannot accelerate! Engine is off."<<endl;
            return;
        }
        if(batteryLevel<=0){
            cout<<brand<<" "<<model<<" : battery dead! Cannot Accelerate."<<endl;
            return;
        }
        batteryLevel -= 10;
        currentSpeed += speed;
        cout<<brand<<" "<<model<<" : Accelerating to "<<currentSpeed <<" km/h. Battery at "<<batteryLevel<<"%."<<endl;
    }
    // Overriding brake - Dynamic Polymorphism
    void brake(){
        currentSpeed -= 15;
        if(currentSpeed < 0) currentSpeed = 0;
        cout<<brand<<" "<<model <<" : Regenerative braking! Speed is now "<<currentSpeed<<" km/h. Battery at "<<batteryLevel<<"%. "<<endl;
    }
};

int main(){
    
    ManualCar* myManualCar = new ManualCar("Suzuki","WagonR");
    myManualCar->startEngine();
    myManualCar->shiftGear(1);
    myManualCar->accelerate();
    myManualCar->brake();
    myManualCar->stopEngine();
    delete myManualCar;

    cout<<"**************************"<<endl;

    ElectricCar* myElectricCar = new ElectricCar("Tesla","Model 5");
    myElectricCar->chargeBattery();
    myElectricCar->startEngine();
    myElectricCar->accelerate();
    myElectricCar->accelerate(60);
    myElectricCar->brake();
    myElectricCar->stopEngine();
    delete myElectricCar;

    return 0;
}

