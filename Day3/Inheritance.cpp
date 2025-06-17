#include<iostream>
#include<string>

using namespace std;

class Car{
protected:
// generic to all cars will not put in ManualCar and ElecticCar, we did defined it as protected since we dont want other than child class to access this
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;

public:
    Car(string b, string m){
        this->brand = b;
        this->model = m;
        isEngineOn = false;
        currentSpeed = 0;
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

    void accelerate(){
        if(!isEngineOn){
            cout<<brand<<" "<<model<<": Cannot accelerate! Engine is off!!"<<endl;
            return; 
        }
        currentSpeed += 20;
        cout<<brand<<" "<<model<<" : Accelerating to "<<currentSpeed<<" km/h"<<endl;
    }

    void brake(){
        currentSpeed -= 20;
        if(currentSpeed<0) currentSpeed=0;
        cout<<brand<<" "<<model<<" : Braking! speed is now"<<currentSpeed<<" km/h"<<endl;
    }

    virtual ~Car(){}
};

class ManualCar: public Car{
private:
    int currentGear; //specific to the ManualCar

public:
    ManualCar(string b, string m):Car(b,m){
        currentGear = 0;
    }

    // Specialized method for the ManualCar 
    void shiftGear(int gear){
        currentGear = gear;
        cout<<brand<<" "<<model<<": Shifted to gear "<<currentGear<<endl;
    }  
};

class ElectricCar: public Car{
private:
    int batteryLevel;

public:
    ElectricCar(string b,string m):Car(b,m){
        batteryLevel = 100;
    }

    void chargeBattery(){
    // unique method for the ElecticCar
        batteryLevel = 100;
        cout<<brand<<" "<<model<<" : Battery fully charged!" <<endl;
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
    myElectricCar->accelerate();
    myElectricCar->brake();
    myElectricCar->stopEngine();
    delete myElectricCar;

    return 0;
}
