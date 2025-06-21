#include<iostream>
#include<vector>

using namespace std;

// Here the interface is Account and this will be known to client(is basically a person, software or application which uses our object)
// Abstract class hai isko inherit and override krna padega
class Account{
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

class SavingAccount : public Account{
private:
    double balance;

public:
    SavingAccount(){
        balance=0;
    }

    void deposit(double amount){
        balance += amount;
        cout<<"Deposited: "<<amount<< " in Savings Account. New Balance: "<< balance<<endl;
    }

    void withdraw(double amount){
        if(balance>= amount){
            balance -= amount;
            cout<<"Withdrawn "<<amount<<" from Savings Account. New Balance:"<<balance<<endl;
        }else{
            cout<<" Insufficient funds in the Savings account! \n"<<endl;
        }
    }
};

class CurrentAccount: public Account{
private:
    double balance;

public:
    CurrentAccount(){
        balance=0;
    }

    void deposit(double amount){
        balance += amount;
        cout<<"Deposited: "<<amount<< " in Current Account. New Balance: "<< balance<<endl;
    }

    void withdraw(double amount){
        if(balance>= amount){
            balance -= amount;
            cout<<"Withdrawn "<<amount<<" from Current Account. New Balance:"<<balance<<endl;
        }else{
            cout<<" Insufficient funds in the Current account! \n"<<endl;
        }
    }
};

class FixedTermAccount: public Account{
private:
    double balance;

public:
    FixedTermAccount(){
        balance = 0;
    }

    void deposit(double amount){
        balance += amount;
        cout<<"Deposited: "<<amount <<" in Fixed Term Account. New Balance: "<<balance<<endl;
    }

    void withdraw(double amount){
        // since it was the fixed deposit account and it didn't allow withdraw so it didnt have any way to handle the withdraw hence it throws the exception
        throw logic_error("Withdrawal not allowed in Fixed Term Account!");
    }
};

// in this solution we made client aware of the types of account hence we made the client closely coupled by using this set of codes
class BankClient{
private:
    vector<Account*> accounts;
    // gave list of accounts to the client

public:
    BankClient(vector<Account*> accounts){
        this->accounts = accounts;
    }

    // Here we have violated the OCP because to add new feature we have modified the existing class
    void processTransactions(){
        // loop krta hai accounts list mai and then call deposit and withdrawl of that account
        for(Account* acc: accounts){
            acc->deposit(1000); // Alll accounts allow deposits 

            // checking account type explicitly
            if(typeid(*acc)== typeid(FixedTermAccount)){
                cout<<"Skipping withdrawl for Fixed Term Account. \n";
            }else{
                try{
                    acc->withdraw(500);
                }catch(const logic_error& e){
                    cout<<"Exception: "<<e.what()<<endl;
                }
            }
        
        }
    }
};

int main(){
    vector<Account*> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(accounts);
    client->processTransactions();
    // Throws exception when withdrawing from FixedTermAccount

}