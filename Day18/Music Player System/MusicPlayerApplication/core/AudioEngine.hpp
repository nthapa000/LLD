// calling adapters
#pragma once
#include "../models/Song.hpp"
#include "../device/IAudioOutputDevice.hpp"
#include <string>
#include <iostream>

using namespace std;

// audioEngine was work to to talk with output device
class AudioEngine{
private:
    Song* currentSong; // reference of current song
    bool songIsPaused; // is song paused or not

public:
    AudioEngine(){
        currentSong = nullptr;
        songIsPaused = false;
    }

    string getCurrentSongTitle() const{
        if(currentSong){
            return currentSong->getTitle();
        }
        return "";
    }

    bool isPaused() const{
        return songIsPaused; //check krta hai ki song pause hai ki nhi hai
    }

    void play(IAudioOutputDevice* aod, Song* song){
        // is song present there or not 
        if(song == nullptr){
            throw runtime_error("Cannot play a null song.");
        }

        // Resume if same song was paused
        // and song should also be same
        if(songIsPaused && song == currentSong){
            songIsPaused = false;
            cout<<"Resuming song: "<<song->getTitle()<<"\n";
            aod->playAudio(song);
            return; 
        }

        currentSong = song;
        songIsPaused = false;
        cout<<"Playing song: "<<song->getTitle()<<"\n";
        aod->playAudio(song); 
    }

    void pause(){
        if(currentSong == nullptr){
            throw runtime_error("No song is currently playing to pause");
        }

        if(songIsPaused){
            throw runtime_error("Song is already paused");
        }

        songIsPaused = true;
        cout<<"Pausing song: "<<currentSong->getTitle() <<"\n";
    }
};
