#pragma once
#include <iostream>
#include "../device/IAudioOutputDevice.hpp"
#include "../enums/DeviceType.hpp"
#include "../factories/DeviceFactory.hpp"

using namespace std;

class DeviceManager{
private:
    static DeviceManager* instance;
    IAudioOutputDevice* currentOutputDevice;
    DeviceManager(){
        currentOutputDevice = nullptr;
    }

public:
    static DeviceManager* getInstance(){
        if(instance == nullptr){
            instance = new DeviceManager();
        }
        return instance;
    }

    void connect(DeviceType deviceType){
        // already if some output device is connected, disconnect it first
        if(currentOutputDevice){
            delete currentOutputDevice;
        }

        currentOutputDevice = DeviceFactory::createDevice(deviceType);

        switch(deviceType){
            case DeviceType::BLUETOOTH:
                cout<<"Bluetooth device connected \n";
            
            case DeviceType::WIRED:
                cout<<"Wired device connected \n";
                break;
            
            case DeviceType::HEADPHONES:
                cout<<"Headphones connected \n";
        }
    }

    IAudioOutputDevice* getOutputDevice(){
        if(!currentOutputDevice){
            throw runtime_error("No output device is connected");
        }
        return currentOutputDevice;
    }

    bool hasOutputDevice(){
        return currentOutputDevice != nullptr;
    }
};

DeviceManager* DeviceManager:: instance = nullptr;