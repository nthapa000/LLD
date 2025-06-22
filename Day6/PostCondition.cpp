#include<iostream>

using namespace std;

// A postcondition must be satisfied after a method is executed.
// Sub classes can strengthen the Postcondition but cannot weaken it.

class Car{
protected:
    int speed;

public:
    Car(){
        speed = 0;
    }

    void accelerate(){
        cout<<"Accelerating "<<endl;
        speed += 20;
    }

    // PostCondition: speed must reduce after brake
    virtual void brake(){
        cout<<"Applying brakes"<<endl;
        speed -= 20;
    }
};

// Subclass can strengthen postcondition - Does not violate LSP
class HybridCar: public Car{
private:
    int charge;

public:
    HybridCar(): Car(){
        charge = 0;
    }

    // Post condition: Speed must reduce after brake
    // Post condition: Charge must increase

    void brake(){
        cout<<"Applying brake"<<endl;
        speed -= 20;
        charge += 10;
    }
};

int main(){
    Car* hybridCar = new HybridCar();
    hybridCar->brake();// Works fine: HybridCar reduces speed and also increases charge
    // Client: feels no difference in substituting Hybrid car in place of Car
    return 0;
}
