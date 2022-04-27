#include "Audio.h"

#include <iostream>
#include <SDL.h>

Audio::Audio() {
    _context = cs_make_context(NULL, 44100, 1024, 0, NULL);
    cs_spawn_mix_thread(_context);
    if(cs_error_reason) {
        std::cout << "Error creating cute_sound context! cs_error_reason: " << cs_error_reason << std::endl;
        return;
    }
}

Audio::~Audio() {
    stopAllAudio();
    for(auto it : _playingAudio) {
        for(auto jt : it.second) {
            if(jt.second) delete jt.second;
            jt.second = nullptr;
        }
    }
    for(auto it : _loadedAudio) {
        cs_free_sound(it.second);
        it.second = nullptr;
    }
}

bool Audio::addAudio(AudioSound soundName, const char * filepath) {
    std::string fullPath;
    fullPath += SDL_GetBasePath();
    fullPath += filepath;
    cs_loaded_sound_t* sound = new cs_loaded_sound_t(cs_load_wav(fullPath.c_str()));
    if(cs_error_reason) {
        std::cout << "Error loading '" << filepath << "'! cs_error_reason: " << cs_error_reason << std::endl;
        return false;
    }
    _loadedAudio[soundName] = sound;
    return true;
}

void Audio::playAudio(int parentId, AudioSound audio, float volume, bool looping) {
    if(!_playingAudio[parentId][audio]) _playingAudio[parentId][audio] = new AudioPool(_context);
    _playingAudio[parentId][audio]->addPlayingSound(_loadedAudio[audio], volume, looping);
}

void Audio::stopAudio(int parentId, AudioSound audio) {
    if(_playingAudio[parentId][audio]) _playingAudio[parentId][audio]->stopSound();
}

void Audio::stopAllAudioById(int id) {
    for(auto it : _playingAudio[id]) {
        if(it.second) it.second->stopSound();
    }
}

void Audio::stopAllAudio() {
    for(auto e : _playingAudio) {
        for(auto s : e.second) {
            if(s.second) s.second->stopSound();
        }
    }
}

bool Audio::isPlaying(int parentId, AudioSound soundName) {
    if(_playingAudio[parentId][soundName]) return _playingAudio[parentId][soundName]->isPlaying();
    return false;
}