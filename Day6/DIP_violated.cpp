#include<iostream>
using namespace std;

// low level modules
class MySQLDatabase{
public:
    void saveToSQL(string data){
        cout<<"Executing SQL Query: INSERT INTO users VALUES('"<<data<<"');"<<endl;
    }
};

// low level modules
class MongoDBDatabase{
public:
    void saveToMongo(string data){
        // kuch mongoDB function execute krta hai and mongoDB mai store kr deta hai
        cout<<"Executing MongoDB Function: db.users.insert({name: '"<<data<<"'})"<<endl;
    }
};

// Now if we want to introduce CassandraDB and remove MongoDB then we have to make changes in UserService class like changing storeUserToMongo or introduce storeUserToCassandra function and hence violating the OCP 
// Its solution will be Decision independent principle
class UserService{ // High level module (Tightly coupled)
private:
    MySQLDatabase sqlDb; // Direct dependency on MySQL
    MongoDBDatabase mongoDb; // Direct dependency on MongoDB

public:
    void storeUserToSQL(string user){
        // MySQL-specific code
        sqlDb.saveToSQL(user);
    }

    void storeUserToMongo(string user){
        // MongoDB-specific code
        mongoDb.saveToMongo(user);
    }   
};

int main(){
    UserService service;
    service.storeUserToSQL("Nishant");
    service.storeUserToMongo("Thapa");
}
