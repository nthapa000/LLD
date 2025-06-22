// if you want to follow OCP then you must have to follow the Dependency Inversion principle
// if OCP is target then DIP is solution
// company CEO , developers QA, work on the low level, CEO wont directly talk with developers , he will have managers in the same way if the developers want to convey some kind of message to the CEO he will do through the managers
// ola uber user object can book ride cancel ride 
// now if we change the application its behavior changes , if its swiggy 
// since in real world user show different different behavior on different different occasion same is the case with in programming
// if only want those functionlity which we want to use it in application
// very hard to follow all SOLID principles
// there is always tradeoff that for bussiness logic we sacrifice with some of the SOLID design principle 
// more we follow SOLID principle more scalable and more expandable the code will be

#include<iostream>
using namespace std;

// Abstraction (Interface)
class Database{
public:
    virtual void save(string data)= 0; // pure virtual function
};

// MySQL implementation (low level module)
class MySQLDatabase : public Database{
public:
    void save(string data) override {
        cout<<"Executing SQL Query: INSERT INTO users VALUES ('"<<data<<"');"<<endl;
    }
};

// MongoDB Implementation (low level module )
class MongoDBDatabase: public Database{
public:
    void save(string data) override{
        // kuch mongoDB function execute krta hai and mongoDB mai store kr deta hai
        cout<<"Executing MongoDB Function: db.users.insert({name: '"<<data<<"'})"<<endl;
    }
};

// High-level module (now loosely coupled)
class UserService{
private:
    // object pass as a variable basically is called dependency injection
    Database* db; // dependency injection

public:
    UserService(Database* database){
        db = database;
    }

    void storeUser(string user){
        db->save(user);
    }
};

int main(){
    MySQLDatabase mysql;
    MongoDBDatabase mongodb;

    UserService service1(&mysql);
    service1.storeUser("Aditya");

    UserService service2(&mongodb);
    service2.storeUser("Raj");    
}