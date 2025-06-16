#include<iostream>
#include<string>

using namespace std;

// There are two main points for the Encapsulation
// first data and behaviors should be encapsulated inside a class 
// data security: some data need not to be available to the public

// class kai behaviors and methods should be encapsulated hence they are in class SportsCar
class SportsCar{
    // public: using public access modifire is not good idea hence it can be access by everyone from outside 
    // for example we can directly set the speed of the sportCar 500 from outside 
    // in main function
    // myCar->currentSpeed = 500
    // we want to change the currentSpeed we want them to go through a function
    // hence we need to make this access modifier private 

private:
    // characters
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed;
        int currentGear;

        // for tyre character we will need both getter and setter function
        string tyre;
// myCar->currentSpeed = 500
// now this line of code will raise error 
// "currentSpeed" is a private member of "SportsCar"

// we will make all our methods public since to interact with the object SportsCar we need to
public:
// constructor
        SportsCar(string b, string m){
            this->brand = b;
            this->model = m;
            isEngineOn = false;
            currentSpeed = 0;
            currentGear = 0; // neutral
            tyre= "MRF";
        }

// lets say we want users to see there speed
// getters and setters
//  variable ya characteristic ki value ko get ya set krne ke liye , this method is public
// this method can access since it is inside the class
        int getCurrentSpeed(){
            return this->currentSpeed;
        }

        string getTyre(){
            return this->tyre;
        }
        // Here we may think we have given both setter and getter for the tyre then why is there need for tyre to private access modifier
        string setTyre(string tyre){
            // when we set using setter function then we can have some validation before setting the tyre character 
            this->tyre = tyre;
        }

// methods --> behavior
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
    SportsCar * myCar = new SportsCar("Ford","Mustang");
    // now in this car we can implement all the functions;

    myCar->startEngine();
    myCar->shiftGear(1);
    myCar->accelerate();
    myCar->shiftGear(2);
    myCar->accelerate();
    cout<<myCar->getCurrentSpeed()<<" "<<endl;
    myCar->accelerate();
    myCar->brake();
    myCar->stopEngine(); 
}