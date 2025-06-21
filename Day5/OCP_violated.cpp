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

// 3. ShoppingCartStorage: Only responsible for saving cart to DB
class ShoppingCartStorage{
private:
    ShoppingCart* cart;

public:
    ShoppingCartStorage(ShoppingCart* cart){
        this->cart = cart;
    }

    void saveToSQLDatabase(){
        cout<<"Saving shopping cart to SQL database.. "<<endl;
    }

    // violate OCP because to introduce new feature we have modified on the existing class
    void saveToMongoDatabase(){
        cout<<"Saving shopping cart to Mongo DB.. "<<endl;
    }

    void saveToFile(){
        cout<<"Saving shopping cart to File.."<<endl;
    }
};

int main(){
    // cart ka object banaya
    ShoppingCart* cart = new ShoppingCart();
    // cart mai two item add kr diya
    cart->addProduct(new Product("Laptop",1500));
    cart->addProduct(new Product("Mouse",50));

    // ShoppingCartPrinter ka object banaya and usme cart ko pass kr diya
    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    ShoppingCartStorage* db = new ShoppingCartStorage(cart);
    db->saveToSQLDatabase();
}