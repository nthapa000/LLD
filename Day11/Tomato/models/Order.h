#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Restaurant.h"
#include "MenuItem.h"
#include "../strategies/PaymentStrategy.h"
#include "../utils/TimeUtils.h"

using namespace std;

class Order{
protected:
    static int nextOrderId;
    int orderId;
    User* user;
    Restaurant* restaurant;
    vector<MenuItem> items;
    PaymentStrategy* paymentStrategy;
    double total;
    // order kab ke liye schedule hai basically type of order
    string scheduled;

public:
    Order(){
        user = nullptr;
        restaurant = nullptr;
        paymentStrategy = nullptr;
        total = 0.0;
        scheduled = "";
        orderId = ++nextOrderId;
    }

    virtual ~Order(){
        delete paymentStrategy;
    }

    bool processPayment(){
        if(paymentStrategy){
            // we should not know ki konsi payment strategy hai 
            // basically jo bhi payment strategy hai wahi implement hogi
            paymentStrategy->pay(total);
            return true;
        }else{
            cout<<"Please choose a payment mode first"<<endl;
            return false;
        }
    }

    virtual string getType() const = 0;
    // will be override

    // getters and setters
    int getOrderId() const {
        return orderId;
    }

    void setUser(User* u){
        user = u;
    }

    User* getUser() const {
        return user;
    }

    void setRestaurant(Restaurant *r){
        restaurant = r;
    }

    Restaurant* getRestaurant() const {
        return restaurant;
    }

    void setItems(const vector<MenuItem>& its){
        items = its;
        total = 0;
        for(auto &i: items){
            total += i.getPrice();
        }
    }

    const vector<MenuItem>& getItems() const{
        return items;
    }

    void setPaymentStrategy(PaymentStrategy* p){
        paymentStrategy = p;
    }

    void setScheduled(const string& s){
        scheduled = s;
    }

    string getScheduled() const {
        return scheduled;
    }

    double getTotal() const {
        return total;
    }

    void setTotal(int total){
        this->total = total;
    }
};

int Order::nextOrderId = 0;

#endif