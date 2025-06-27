#ifndef MENUITEM_H
#define MENUITEM_H

#include<string>
using namespace std;

class MenuItem{
private:
    string code;
    string name;
    int price;

public:
    MenuItem(const string& code, const string& name,int price){
        this->code = code;
        this->name = name;
        this->price = price;
    }

    // Getters and Setters
    string getCode() const {
        return code;
    }

    void setCode(const string &c){
        code = c;
    }

    // The const at the end of the function means that this member function will not modify the object — that is, it won’t change any member variables of the class.
    string getName() const {
        return name;
    }

    void setName(const string &n){
        name = n;
    }

    int getPrice() const{
        return price;
    }

    void setPrice(int p){
        price = p;
    }
};

#endif