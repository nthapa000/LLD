#include<iostream>
#include<mutex>

using namespace std;

class Singleton{
private:
    static Singleton *instance; 
    static mutex mtx; 
    // mutex in c++ help to lock and unlock(critical section of code can be accessed by only one thread at a time and unlock when it goes out)


    Singleton(){
        cout<<"Singleton Constructor called. New object created."<<endl;
    }

public:
    static Singleton* getInstance(){
        lock_guard<mutex> lock(mtx); // lock for thread safety// now only one thread allowed to enter at a time
        if(instance == nullptr){//Now suppose there are two thread who execute this condition at the same time at that moment dono kai liye condiiton same ho jaayegi
            lock_guard<mutex> lock(mtx);
            // here lets say only one of the thread(t1) got the lock 
            // it creates the instance and leaves 
            // but now the other thread(t2) which was waiting for t1 will ge lock once it leave since now it isn't checking whether the object was created or not will create its own object 
            // hence we need to double check
            if(instance==nullptr){
                instance = new Singleton();
            }
        }
        // we prefer to avoid lock as much as possible since in any language locking and unlocking is an expensive operation
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main(){
    

    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    cout<<(s1 == s2)<<endl;
   
}