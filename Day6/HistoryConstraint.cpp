#include<iostream>

using namespace std;

// Sub class methods should not be allowed state changes What
// Base class never allowed

class BankAccount{
protected:
    double balance;

public:
    BankAccount(double b){
        if(b<0) throw invalid_argument("Balance can't be negative");
        balance = b;
    }

    // History constraint: withraw should be allowed
    virtual void withdraw(double amount){
        if(balance - amount < 0) throw runtime_error("Insufficient funds");
        balance -= amount;
        cout<<"Amount withdrawn. Remaining balance is "<<balance<<endl;
    }
};

class FixedDepositAccount: public BankAccount{
public:
    FixedDepositAccount(double b): BankAccount(b){}

    //LSP break! History constraint is broke!
    // Parent class behavior change: Now withdraw is not allowed
    // This class will brake client code that relies on withdraw.
    void withdraw(double amount) override{
        throw runtime_error("Withdraw not allowed in Fixed deposit");
        // But we had to maintain the History constraint in the subclass for the class to be substitutable sub class acc to LSP
    } 
};

int main(){
    BankAccount* bankAccount = new BankAccount(100);
    // Here main is client and it was expecting that it can withdraw when possible
    bankAccount->withdraw(1000);
}