#pragma once

#include <cute_sound.h>
#include <unordered_map>

#include "AudioSound.h"
#include "AudioPool.h"

class Audio {
public:
    Audio();
    ~Audio();

    bool addAudio(AudioSound soundName, const char * filepath);
    void playAudio(int parentId, AudioSound audio, float volume = 0.5, bool looping = false);
    void stopAudio(int parentId, AudioSound audio);
    void stopAllAudioById(int id);
    void stopAllAudio();

    bool isPlaying(int parentId, AudioSound soundName);
    
private:
    cs_context_t* _context = nullptr;
    std::unordered_map<AudioSound, cs_loaded_sound_t*> _loadedAudio;
    // 2D map using entity ID as key. This allows each entity to have its own playing sounds so that it can freely stop them as well. Use -1 for ID if no entity is playing the audio
    std::unordered_map<int, std::unordered_map<AudioSound, AudioPool*>> _playingAudio;
};