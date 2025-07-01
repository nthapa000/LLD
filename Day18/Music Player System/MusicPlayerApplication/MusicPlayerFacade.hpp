#pragma once
#include "core/AudioEngine.hpp"
#include "models/Playlist.hpp"
#include "models/Song.hpp"
#include "strategies/PlayStrategy.hpp"
#include "enums/DeviceType.hpp"
#include "enums/PlayStrategyType.hpp"
#include "managers/DeviceManager.hpp"
#include "managers/PlaylistManager.hpp"
#include "managers/StrategyManager.hpp"

using namespace std;

class MusicPlayerFacade {
private:
    static MusicPlayerFacade* instance;
    AudioEngine* audioEngine;
    Playlist* loadedPlaylist;
    PlayStrategy* playStrategy;

    MusicPlayerFacade() {
        loadedPlaylist = nullptr;
        playStrategy   = nullptr;
        audioEngine = new AudioEngine();
    }

public:
    static MusicPlayerFacade* getInstance() {
        if (!instance) {
            instance = new MusicPlayerFacade();
        }
        return instance;
    }

    // is type ka device connect krdo
    void connectDevice(DeviceType deviceType) {
        DeviceManager::getInstance()->connect(deviceType);
    }

    // ye wali strategy set krdo strategyManager
    void setPlayStrategy(PlayStrategyType strategyType) {
        playStrategy = StrategyManager::getInstance()->getStrategy(strategyType);
    }

    void loadPlaylist(const string& name) {
        loadedPlaylist = PlaylistManager::getInstance()->getPlaylist(name);
        if (!playStrategy) {
            throw runtime_error("Play strategy not set before loading.");
        }
        playStrategy->setPlaylist(loadedPlaylist);
    }
    
    void playSong(Song* song) {
        if (!DeviceManager::getInstance()->hasOutputDevice()) {
            throw runtime_error("No audio device connected.");
        }
        IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
        audioEngine->play(device, song);
    }

    void pauseSong(Song* song) {
        if (audioEngine->getCurrentSongTitle() != song->getTitle()) {
            throw runtime_error("Cannot pause \"" + song->getTitle() + "\"; not currently playing.");
        }
        audioEngine->pause();
    }

    void playAllTracks() {
        if (!loadedPlaylist) {
            throw runtime_error("No playlist loaded.");
        }
        // terpe next gaana hai to laake dede
        while (playStrategy->hasNext()) {
            Song* nextSong = playStrategy->next();
            IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, nextSong);
        }
        cout << "Completed playlist: " << loadedPlaylist->getPlaylistName() << "\n";
    }

    // bs next gaana play horaha
    void playNextTrack() {
        if (!loadedPlaylist) {
            throw runtime_error("No playlist loaded.");
        }
        if(playStrategy->hasNext()) {
            Song* nextSong = playStrategy->next();
            IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, nextSong);
        }
        else {
            cout << "Completed playlist: " << loadedPlaylist->getPlaylistName() << "\n";
        }
    }

    void playPreviousTrack() {
        if (!loadedPlaylist) {
            throw runtime_error("No playlist loaded.");
        }
        if(playStrategy->hasPrevious()) {
            Song* prevSong = playStrategy->previous();
            IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, prevSong);
        }
        else {
            cout << "Completed playlist: " << loadedPlaylist->getPlaylistName() << "\n";
        }
    }

    // 
    void enqueueNext(Song* song) {
        playStrategy->addToNext(song);
    }
};

MusicPlayerFacade* MusicPlayerFacade::instance = nullptr;
    