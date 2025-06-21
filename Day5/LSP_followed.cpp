#include<iostream>
#include<vector>
#include<typeinfo>
#include<stdexcept>

using namespace std;

// we broke the Account abstract class hierachy into two classes DepositOnlyAccount and WithdrawableAccount , here WithdrawableAccount class inherit(extend) the DepositOnlyAccount
class DepositOnlyAccount{
public:
// single virtual deposit method
    virtual void deposit(double amount) = 0;
};

class WithdrawableAccount: public DepositOnlyAccount{
public:
// isme deposit and withdraw dono aagaye
    virtual void withdraw(double amount) = 0;
};

class SavingAccount: public WithdrawableAccount{
private:
    double balance;

public:
    SavingAccount(){
        balance = 0;
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

class CurrentAccount: public WithdrawableAccount{
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

class FixedTermAccount: public DepositOnlyAccount{
private:
    double balance;

public:
    FixedTermAccount(){
        balance=0;
    }
    
    void deposit(double amount){
        balance += amount;
        cout<<" Deposited: "<<amount<<" in Fixed Term Account. New Balance: "<<balance<<endl;
    }
};

class BankClient{
private:
// two list
    vector<WithdrawableAccount*> withdrawableAccounts;
    vector<DepositOnlyAccount*> depositOnlyAccounts;

public:
// initialized the list with the constructor
    BankClient(vector<WithdrawableAccount*> withdrawableAccounts,vector<DepositOnlyAccount*> depositOnlyAccounts){
        this->withdrawableAccounts = withdrawableAccounts;
        this->depositOnlyAccounts = depositOnlyAccounts;
    }

    void processTransactions(){
        for(WithdrawableAccount* acc: withdrawableAccounts){
            acc->deposit(1000);
            acc->withdraw(500);
        }

        for(DepositOnlyAccount* acc: depositOnlyAccounts){
            acc->deposit(500);
        }
    }
};

int main(){
    // two list made and passed some account
    vector<WithdrawableAccount*> withdrawableAccounts;
    withdrawableAccounts.push_back(new SavingAccount());
    withdrawableAccounts.push_back(new CurrentAccount());

    vector<DepositOnlyAccount*> depositOnlyAccounts;
    depositOnlyAccounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(withdrawableAccounts,depositOnlyAccounts);
    client->processTransactions();
    return 0;
}