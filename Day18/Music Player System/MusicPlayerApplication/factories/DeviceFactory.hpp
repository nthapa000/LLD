#pragma once
#include<iostream>
#include "../device/IAudioOutputDevice.hpp"
#include "../device/BluetoothSpeakerAdapter.hpp"
#include "../device/WiredSpeakerAdapter.hpp"
#include "../device/HeadphonesAdapter.hpp"
#include "../enums/DeviceType.hpp"

using namespace std;

class DeviceFactory{
public:
    static IAudioOutputDevice* createDevice(DeviceType deviceType){
        if(deviceType == DeviceType::BLUETOOTH){
            return new  BluetoothSpeakerAdapter(new BluetoothSpeakerAPI());
        } else if(deviceType == DeviceType::WIRED){
            return new WiredSpeakerAdapter(new WiredSpeakerAPI());
        } else{
            // HEADPHONES then gives reference of Headphone
            // adapter ke saath hi external library ka reference de diya
            return new HeadphonesAdapter(new HeadphonesAPI());
        }
    }
};