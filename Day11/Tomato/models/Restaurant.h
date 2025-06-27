// Checks if the macro RESTAURANT_H is not defined.
// header guard — a mechanism used in C++ to prevent a header file from being included multiple times during compilation.
#ifndef RESTAURANT_H

// If it's not defined, it defines it. This ensures that the body of the header file is only included once.
#define RESTAURANT_H

// The actual content of the header file (like class declarations, includes, etc.) would go between the #define and the #endif.

#include <iostream>
#include <string>
#include <vector>
#include "MenuItem.h"

using namespace std;

// modal class
class Restaurant{
private:
// to declare it at the end with zero 
// and now whenever the new Restaurant is created we increment the RestaurantId++
// hence restaurantId are autoIncrementing we dont want anyone to manually enter the id
    static int nextRestaurantId;
    int restaurantId;
    string name;
    string location;
    vector<MenuItem> menu;

public:
    Restaurant(const string&name, const string& location){
        this->name = name;
        this->location = location;
        this->restaurantId = ++nextRestaurantId;
    }

    ~Restaurant(){
        // Optional: just for clarity or debug
        cout<<"Destroying Restaurant:" <<name<<", and clearing its menu."<<endl;
        menu.clear();
    }

    // Getters and Setters
    string getName() const {
        return name;
    }

    void setName(const string &n){
        name = n;
    }

    string getLocation() const{
        return location;
    }

    void setLocation(const string &loc){
        location = loc;
    }

    void addMenuItem(const MenuItem &item){
        menu.push_back(item);
    } 

    const vector<MenuItem>& getMenu() const{
        return menu;
    }
};


int Restaurant::nextRestaurantId = 0;

#endif //RESTAURANT_H
// This ends the conditional inclusion started by #ifndef
// Without header guards, including the same header file in multiple files can lead to multiple definition errors.