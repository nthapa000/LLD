#include<iostream>
#include<vector>

using namespace std;

// Product class representing any item of any Ecommerce
class Product{
public:
    string name;
    double price;

    Product(string name, double price){
        this->name = name;
        this->price = price;
    }
};

// 1. ShoppingCart: only responsibe for Cart related business logic
class ShoppingCart{
private:
    vector<Product*> products; // store heap-allocated products , basically we are storing multiple products

public:
    // setter
    void addProduct(Product *p){
        products.push_back(p);
    }
    // getter
    const vector<Product*>& getProducts(){
        return products;
    }

    // Calculates total price in cart
    double calculateTotal(){
        double total = 0;
        for(auto p: products){
            total += p->price;
        }
        return total;
    }
};

// 2. ShoppingCartPrinter: Only responsible for printing invoices
class ShoppingCartPrinter{
private:
    ShoppingCart* cart;// reference of ShoppingCart
public:
    ShoppingCartPrinter(ShoppingCart* cart){
        this->cart = cart;
    }

    void printInvoice(){
        cout<<"Shopping Cart Invoice\n";
        for(auto p: cart->getProducts()){
            cout<<p->name<<" - $ "<< p->price<<endl;
        }
        cout<<"Total: $"<<cart->calculateTotal()<<endl;
    }
};

// To follow OCP
// first we have made an abstract class "Persistence" and then we made three subclass "SQLPersistence","MongoPersistence" and "FilePersistence" inheriting Persistence

// Abstract Class
class Persistence{
private:
    ShoppingCart* cart;

public:
    virtual void save(ShoppingCart* cart) = 0;// Pure virtual function
};

// SQLPersistence save in SQLDB
class SQLPersistence: public Persistence{
public:
    void save(ShoppingCart* cart) override{
        cout<<"Saving shopping cart to SQL DB.."<<endl;
    }
};

class MongoPersistence: public Persistence{
public:
    void save(ShoppingCart* cart) override{
        cout<<"Saving shopping cart to MongoDB.."<<endl;
    }
};

class FilePersistence: public Persistence{
public:
    void save(ShoppingCart* cart) override{
        cout<<"Saving shopping cart to file.."<<endl;
    }
};

int main(){
    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Laptop",1500));
    cart->addProduct(new Product("Mouse",50));

    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    // We have made three different references of Persistence 
    Persistence* db = new SQLPersistence();
    Persistence* mongo = new MongoPersistence();
    Persistence* file = new FilePersistence();

    db->save(cart);// save to SqlDB
    mongo->save(cart);
    file->save(cart);
    
    return 0;
}