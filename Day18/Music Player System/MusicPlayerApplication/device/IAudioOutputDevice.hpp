#pragma once
#include "../models/Song.hpp"

// Interface / Abstract class
class IAudioOutputDevice{
public:
    virtual ~IAudioOutputDevice(){}
    virtual void playAudio(Song *song) = 0;
};

