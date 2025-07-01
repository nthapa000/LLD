#pragma once
#include "../models/Song.hpp"
#include "IAudioOutputDevice.hpp"
#include "../external/WiredSpeakerAPI.hpp"

using namespace std;

class WiredSpeakerAdapter : public IAudioOutputDevice{
private:
    WiredSpeakerAPI* wiredApi;
public:
    WiredSpeakerAdapter(WiredSpeakerAPI* api){
        wiredApi = api;
    }

// wiredApi ka reference leta hai and then usse call krta hai
    void playAudio(Song* song) override {
        string payload = song->getTitle() + " by " + song->getArtist();
        wiredApi->playSoundViaCable(payload);
    }
};

