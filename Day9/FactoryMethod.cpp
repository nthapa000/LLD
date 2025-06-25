#include<iostream>

using namespace std;

class Burger{
public:
    virtual void prepare() = 0; //Pure virtual function
    virtual ~Burger() {} // Virtual Destructor
};

class BasicBurger: public Burger{
public:
    void prepare() override{
        cout<<"Preparing Basic Burger with bun, patty and ketchup!"<<endl;
    }
};

class StandardBurger: public Burger{
public:
    void prepare() override{
        cout<<"Preparing Standard Burger with bun, patty and ketchup!"<<endl;
    }
};

class PremiumBurger : public Burger{
public:
    void prepare() override{
        cout<<"Preparation of premium burger with gourment bun, premium patty ,cheese , lettuce , paneer, olive"<<endl;
    };
};


class BasicWheatBurger: public Burger{
public:
    void prepare() override{
        cout<<"Preparing Basic Wheat Burger with bun, patty and ketchup!"<<endl;
    }
};

class StandardWheatBurger: public Burger{
public:
    void prepare() override{
        cout<<"Preparing Standard Wheat Burger with bun, patty and ketchup!"<<endl;
    }
};

class PremiumWheatBurger : public Burger{
public:
    void prepare() override{
        cout<<"Preparation of premium wheat burger with gourment bun, premium patty ,cheese , lettuce , paneer, olive"<<endl;
    };
};

// Factory and its composition
class BurgerFactory{
public:
    virtual Burger* createBurger(string& type) = 0;
};

// Two type of factory where SinghBurger produce normal burgers of 3 types
class SinghBurger: public BurgerFactory{
public:
    Burger* createBurger(string& type) override{
        if(type=="basic"){
            return new BasicBurger();
        }else if(type=="standard"){
            return new StandardBurger();
        }else if(type == "premium"){
            return new PremiumBurger();
        } else{
            cout<<"Invalid burger type! "<<endl;
            return nullptr;
        }
    }
};

// King burger makes only wheat burger
class KingBurger : public BurgerFactory{
public:
    Burger* createBurger(string &type) override {
        if(type == "basic"){
            return new BasicWheatBurger();
        } else if (type == "standard"){
            return new StandardWheatBurger();
        } else if (type == "premium"){
            return new PremiumWheatBurger();
        } else{
            cout<<"Invalid burger type! "<<endl;
            return nullptr;
        }
    }
};

int main(){
    string type = "standard";
    // we wanted wheat based burger 
    BurgerFactory* myFactory = new KingBurger();
    Burger* burger = myFactory->createBurger(type);
    burger->prepare();
}
