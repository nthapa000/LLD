#include <iostream>
using namespace std;

// why we made so many handler 
// we could have put the logic in if else statement 
// then why so many handler 
// we want to follow open close principle 
// now suppose we have to introduce new handler we have to change the existing codee 
// but now we have to just make a new class
// we followed OCP
// Single responsibility principle ko bhi follow kiya 
// what if new notes introduced we need to verify money is authenticated or not
// 100 rupees change then we will change only hundreadRupeesHandler

// Abstract Handler (Base Class)
class MoneyHandler{
protected:
// such that child class can use it
    MoneyHandler* nextHandler;

public:
// first independently exist
    MoneyHandler(){
        this->nextHandler = nullptr;
    }

    void setNextHandler(MoneyHandler *next){
        nextHandler = next;
    }

    virtual void dispense(int amount) = 0;
};

class ThoushandHandler : public MoneyHandler{
private:
    int numNotes;
    // How many thoushand notes exist there

public:
    ThoushandHandler(int numNotes){
        this->numNotes = numNotes;
    }

    void dispense(int amount) override{
        int notesNeeded = amount / 1000; // how much notes we need

        if(notesNeeded > numNotes){ // agr no. of notes required jyada hai jitna present hai usse
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else{
            numNotes -= notesNeeded;
        }
    // actually note to dispense krta actually koi class hota jo hardware sai interact karta
        if(notesNeeded > 0)
            cout<< "Dispensing "<<notesNeeded <<" x $1000 notes. \n";

        int remainingAmount = amount - (notesNeeded*1000);
        if(remainingAmount > 0){
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else{
                // if last handler then it wont have nextHandler
                cout<<"Remaining amount of "<< remainingAmount << " cannot be fulfilled "<<endl;
            }
        }
    }
};

// Concrete Handler for  500 handler
class FiveHundredHandler : public MoneyHandler{
private:
    int numNotes;

public:
    FiveHundredHandler(int numNotes){
        this->numNotes = numNotes;
    }

    void dispense (int amount) override{
        int notesNeeded = amount / 500;
    
        if(notesNeeded > numNotes){
            notesNeeded = numNotes;
            numNotes = 0;
        }else{
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0){
            cout<<"Dispensing "<<notesNeeded <<" x $500 notes. \n";
        }

        int remainingAmount = amount - (notesNeeded * 500);
        if(remainingAmount > 0){
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else{
                cout<<"Remaining amount of "<< remainingAmount << " cannot be fulfilled "<<endl;
            }
        }
    }

};

// Concrete Handler for 200 Rs Notes
class TwoHundredHandler : public MoneyHandler {
private:
    int numNotes;

public:
    TwoHundredHandler(int numNotes) {
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 200;

        if(notesNeeded > numNotes) {
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else {
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0)
            cout << "Dispensing " << notesNeeded << " x ₹200 notes.\n";

        int remainingAmount = amount - (notesNeeded * 200);
        if(remainingAmount > 0) {
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else {
                cout << "Remaining amount of " << remainingAmount << " cannot be fulfilled (Insufficinet fund in ATM)\n";
            }
        }
    }
};

// Concrete Handler for 100 Rs Notes
class HundredHandler : public MoneyHandler {
private:
    int numNotes;

public:
    HundredHandler(int numNotes) {
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 100;

        if(notesNeeded > numNotes) {
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else {
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0)
            cout << "Dispensing " << notesNeeded << " x ₹100 notes.\n";

        int remainingAmount = amount - (notesNeeded * 100);
        if(remainingAmount > 0) {
            if(nextHandler != nullptr) nextHandler->dispense(remainingAmount);
            else {
                cout << "Remaining amount of " << remainingAmount << " cannot be fulfilled (Insufficinet fund in ATM)\n";
            }
        }
    }
};

// Client Code
int main() {
    // Creating handlers for each note type
    MoneyHandler* thousandHandler = new ThoushandHandler(3);
    MoneyHandler* fiveHundredHandler = new FiveHundredHandler(5);
    MoneyHandler* twoHundredHandler= new TwoHundredHandler(10);
    MoneyHandler* hundredHandler= new HundredHandler(20);

    // Setting up the chain of responsibility
    thousandHandler->setNextHandler(fiveHundredHandler);
    fiveHundredHandler->setNextHandler(twoHundredHandler);
    twoHundredHandler->setNextHandler(hundredHandler);

    int amountToWithdraw = 4000;

    // Initiating the chain
    cout << "\nDispensing amount: ₹" << amountToWithdraw << endl;
    thousandHandler->dispense(amountToWithdraw);

    return 0;
}