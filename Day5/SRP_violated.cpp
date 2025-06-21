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

// Violating SRP: ShoppingCart is handling multiple responsibilities
class ShoppingCart{
private:
// multiple product inside ShoppingCart hence has-a relation
    vector<Product*> products;

public:
    void addProduct(Product* p){
        products.push_back(p);
    }

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

    // Violating SRP - Prints Invoice ( should be in separate class)
    void printInvoice(){
        cout<<"Shopping Cart Invoice:\n";
        for(auto p: products){
            cout<<p->name<<" - $"<<p->price<<endl;
        }
        cout<<"Total: $"<<calculateTotal()<<endl;
    }

    // Violating SRP - Saves to DB (should be in a separate class)
    void saveToDatabase(){
        cout<<"Saving shopping cart to database..."<<endl;
        // logic different basis on how we connect to the database and all
    }
};

int main(){
    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Laptop",1500));
    cart->addProduct(new Product("Mouse",50));
    cart->printInvoice();
    cart->saveToDatabase();   
    return 0;
}