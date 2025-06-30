// we have few problem in our code: customer need to know many things 
// let out the updated code 

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


// Notification and Decorators

class INotification {
public:
    virtual string getContent() const = 0;

    virtual ~INotification() {}
};

// Concrete Notification: simple text notification
class SimpleNotification : public INotification{
private:
    string text;

public:
    SimpleNotification(const string& msg){
        text = msg;
    }

    string getContent() const override{
        return text;
    }
};

// Abstract Decorator wraps a Notfication object.
class INotificationDecorator : public INotification{
protected:
    INotification* notification;

public:
    INotificationDecorator(INotification* n){
        notification = n;
    }

    virtual ~INotificationDecorator(){
        delete notification;
    }
};

// Decorator to add a timestamp to the content.
class TimestampDecorator : public INotificationDecorator{
public:
    TimestampDecorator(INotification* n) : INotificationDecorator(n){ }

    // we can access notification directly since we made it protected 
    string getContent() const override{
        // static time
        // we can fetch it from util
        return "[2025-04-13 14:22:00]" + notification->getContent();
    }
};

// Decorator to append a signature to the content.
class SignatureDecorator : public INotificationDecorator{
private:
    string signature;

public:
    SignatureDecorator(INotification* n, const string& sig): INotificationDecorator(n){
        signature = sig;
    }

    string getContent() const override{
        return notification->getContent() + "\n---" + signature + "\n\n";
   }
};

// Observer Pattern Components

// Observer interface: each observer gets an update with a Notification pointer.
class IObserver{
public:
    virtual void update() = 0;
    virtual ~IObserver() {}
};

class IObservable{
public:
    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers() = 0;
};

// Concrete Observable
class NotificationObservable : public IObservable{
private:
    vector<IObserver*> observers;
    INotification* currentNotification;

public:
    NotificationObservable(){
        currentNotification = nullptr;
    }

    void addObserver(IObserver* obs) override{
        observers.push_back(obs);
    }

    void removeObserver(IObserver* obs) override{
        observers.erase(remove(observers.begin(),observers.end(),obs),observers.end());
    }

    void notifyObservers() override{
        for(unsigned int i = 0; i<observers.size();i++){
            // calls every obsers update function
            observers[i]->update();
        }
    }

    void setNotification(INotification* notification){
        if(currentNotification != nullptr){
            delete currentNotification;
        }
        currentNotification = notification;
        // notfication set krne ke baad will tell every observer that hey i got the notification
        notifyObservers();
    }

    INotification* getNotification(){
        return currentNotification;
    }

    string getNotificationContent(){
        return currentNotification->getContent();
    }

    ~NotificationObservable(){
        if(currentNotification != NULL){
            delete currentNotification;
        }
    }
};

// Concrete Observer 1
class Logger : public IObserver {
private:
    NotificationObservable* notificationObservable;

public:
    Logger(NotificationObservable* observable){
        this->notificationObservable = observable;
    }

    void update(){
        cout<<"Logging New Notification : \n" <<notificationObservable -> getNotificationContent();
    }
};

// Strategy Pattern Component (Concrete observer 2)

// Abstract class for different Notification Strategies

class INotificationStrategy{
public:
// push email wether it is through SMS , email or popup
    virtual void sendNotification(string content) = 0;
};

class EmailStrategy : public INotificationStrategy{
private:
    string emailId;

public:
    EmailStrategy(string emailId){
        this->emailId = emailId;
    }

    void sendNotification(string content) override{
        // Simulate the process of sending an email notification
        // representing the dispatch of messages to users via email
        cout<< "Sending the email Notification to: "<<emailId<<"\n"<<content<<endl;
    }
};

class SMSStrategy : public INotificationStrategy{
private:
    string mobileNumber;

public:
    SMSStrategy(string mobileNumber){
        this->mobileNumber = mobileNumber;
    }

    void sendNotification(string content) override{
        // Simulate the process of sending an SMS notification
        // representing the dispatch of messages to users via SMS.

        cout<<"Sending SMS Notication to: "<<mobileNumber<<"\n"<<content;
    }
};

class PopUpStrategy : public INotificationStrategy{
public:
    void sendNotification(string content) override{
        // Simulate the process of sending popup notification
        cout<<"Sending Popup Notification: \n"<<content;
    }
};

class NotificationEngine : public IObserver{
private:
    NotificationObservable* notificationObservable;
    vector<INotificationStrategy*> notificationStrategies;

public:
    NotificationEngine(NotificationObservable* observable){
        this->notificationObservable = observable;
    }

    void addNotificationStrategy(INotificationStrategy* ns){
        this->notificationStrategies.push_back(ns);
    }

    // Can have RemoveNotificationStrategy as well

    void update(){
        string notificationContent = notificationObservable->getNotificationContent();
        for(const auto notificationStrategy: notificationStrategies){
            notificationStrategy->sendNotification(notificationContent);
        }
    }
};

// Nptification Services
// The NotificationServices manage notificatios. It keeps track of notifications
// Any client code will interact with this services
// bridge between notification kaise bnti hai and kaise bhejte hai

// Singleton class
class NotificationService{
private:
// give content to it
    NotificationObservable* observable;
    // singleton class
    static NotificationService* instance;
    // store list of notification
    vector<INotification*> notifications;

    NotificationService(){
        // private constructor
        observable = new NotificationObservable();
    }

public:
// help to integrate the singleton design pattern
    static NotificationService* getInstance(){
        // we will get NotificationService instance whenever we will call this fucntion
        if(instance == nullptr){
            instance = new NotificationService();
        }
        return instance;
    }

    // Exposes the observable so observers can attach
    NotificationObservable* getObservable(){
        return observable;
    }

    // Creates a new Notification and notifies observers
    void sendNotification(INotification* notification){
        // sabse pehle notification leta hai and then push_back into the list of notification
        notifications.push_back(notification);// to maintain history
        // 
        observable->setNotification(notification);
    }

    ~NotificationService(){
        delete observable;
    }
};

// Since it is singleton
NotificationService* NotificationService::instance = nullptr;

// client code how will client interact with our notification system
int main(){
    // Create NotificationService.
    // singleton
    NotificationService* notificationService = NotificationService::getInstance();

    // Get Observable
    // we didnt want that client have to make their own NotficationObservable hence we made new object of it in Notification Service constructor itself
    // main reason for this is that we wanted our application to be plugin and play and think carefully does the client really need to know how to make the Observable object orr observers ko assign kaise karenge 
    // Client should know minimal things to integrate this
    NotificationObservable* notificationObservable = notificationService->getObservable();
   
    // Create Logger Observer
    Logger* logger = new Logger(notificationObservable);

    // Create NotificationEngine observers.
    NotificationEngine* notificationEngine = new NotificationEngine(notificationObservable);

    notificationEngine->addNotificationStrategy(new EmailStrategy("random.person@gmail.com"));
    notificationEngine->addNotificationStrategy(new SMSStrategy("+91 9876543210"));
    notificationEngine->addNotificationStrategy(new PopUpStrategy());

    // Attach these observers.
    notificationObservable->addObserver(logger);
    notificationObservable->addObserver(notificationEngine);

    // Create a notification with decorators.
    INotification* notification = new SimpleNotification("Your order has been shipped!");
    // decorate with timestamp 
    notification = new TimestampDecorator(notification);
    notification = new SignatureDecorator(notification, "Customer Care");
    
    // send all three type of notification
    notificationService->sendNotification(notification);

    delete logger;
    delete notificationEngine;
    return 0;
}