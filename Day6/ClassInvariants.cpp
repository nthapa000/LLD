#include<iostream>
using namespace std;

// Class Invariant of a parent class Object should not be broken by child class Object.
// Hence child class can either maintain or strengthen the invariant but never narrows it down.

// Invariant: Balance cannot be negative
// Its my responsibility to follow this rule in the parent class
class BankAccount{
protected:
    double balance;

public:
    BankAccount(double b){// whenever balance ata hai 
        if(b<0) throw invalid_argument("Balance cant be negative");
        balance = b;
    }

    virtual void withdraw(double amount){ // withdraw karne ke time check krte ki balance- amount negative na ho 
        if(balance - amount < 0 ) throw runtime_error("Insufficient funds");
        balance -= amount;
        cout<<"Amount withdrawn. Remaining balance is "<<balance<<endl;
    }
};

// Child class has the responsibility to follow this rule 
// Brakes Invariant: should not be allowed
class CheatAccount: public BankAccount{
public:
    CheatAccount(double b):BankAccount(b){
    
    }

    void withdraw(double amount) override{
        balance -= amount;//LSP! breaks Negative balance allowed
        cout<<"Amount withdrawn. Remaining balance is "<<balance<<endl;
    }
};

int main(){
    BankAccount* bankAccount = new BankAccount(100);
    bankAccount->withdraw(100);
}