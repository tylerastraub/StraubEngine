#include "AudioSound.h"
#include "cute_sound.h"

#include <list>
#include <iostream>

class AudioPool {
public:
    AudioPool(cs_context_t* context) : _context(context) {
        for(size_t i = 0; i < _maxPoolSize; ++i) {
            _pool.push_back(cs_playing_sound_t());
        }
    }
    ~AudioPool() = default;

    void addPlayingSound(cs_loaded_sound_t* loadedAudio, float volume, bool looping) {
        for(auto it = _pool.begin(); it != _pool.end(); ++it) {
            if(!it->active) {
                it = _pool.erase(it);
                it = _pool.insert(it, cs_make_playing_sound(loadedAudio));
                it->volume0 = volume;
                it->volume1 = volume;
                it->looped = looping;
                cs_insert_sound(_context, &*it);
                return;
            }
        }
        std::cout << "Error: playing pool full! Consider increasing playing pool size." << std::endl;
    }

    void stopSound() {
        cs_lock(_context);
        for(auto it = _pool.begin(); it != _pool.end(); ++it) {
            cs_stop_sound(&*it);
        }
        cs_unlock(_context);
    }

    void setPoolSize(int poolSize) {
        if(poolSize < _maxPoolSize) {
            for(int i = 0; i < _maxPoolSize - poolSize; ++i) {
                _pool.push_back(cs_playing_sound_t());
            }
        }
        else if(poolSize > _maxPoolSize) {
            int index = _maxPoolSize - 1;
            auto it = _pool.end();
            --it;
            for(; it != _pool.begin(); --it) {
                if(index >= poolSize) {
                    _pool.erase(it);
                }
                else {
                    return;
                }
                --index;
            }
        }
    }

    bool isPlaying() {
        if(_pool.empty()) return false;
        cs_lock(_context);
        for(auto s : _pool) {
            if(s.active) {
                cs_unlock(_context);
                return true;
            }
        }
        cs_unlock(_context);
        return false;
    }

private:
    cs_context_t* _context = nullptr;
    // How many instance of a sound can be playing at one time
    int _maxPoolSize = 8;
    std::list<cs_playing_sound_t> _pool;
};