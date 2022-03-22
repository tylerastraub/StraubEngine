#ifndef STATE_H
#define STATE_H

#include "Text.h"
#include "Spritesheet.h"
#include "Audio.h"

#include <SDL.h>
#include <unordered_map>
#include <vector>

namespace TextSize {
    enum TextSize {
        TINY = 0,
        SMALL = 1,
        MEDIUM = 2,
        LARGE = 3,
    };
};

class State {
public:
    State() = default;
    virtual ~State() = default;

    // Virtual methods
    virtual void init() = 0;
    virtual void tick(float timescale) = 0;
    virtual void render() = 0;
    // Note that if you are using the keyboard class, it is recommended to call the updateInputs() method in tick() instead
    virtual void handleKeyboardInput(SDL_Event e) {};
    virtual void handleControllerButtonInput(SDL_Event e) {};
    virtual void handleControllerAxisInput(SDL_Event e) {};
    virtual void handleMouseInput(SDL_Event e) {};

    void setGameSize(int w, int h);
    void setNextState(State* state);
    void setRenderer(SDL_Renderer* renderer);
    void setRenderScale(int scale);
    void addSpritesheet(std::string spritesheetID, Spritesheet* spritesheet);
    void addText(TextSize::TextSize size, Text* text);
    void setAudioPlayer(Audio* audioPlayer);
    
    SDL_Point getGameSize();
    State* getNextState();
    SDL_Renderer* getRenderer();
    int getRenderScale();
    Spritesheet* getSpritesheet(std::string spritesheetID);
    Text* getText(TextSize::TextSize size);
    Audio* getAudioPlayer();

private:
    SDL_Point _gameSize = {0, 0};
    State* _nextState = nullptr;
    SDL_Renderer* _renderer = nullptr;
    int _renderScale = 1;
    std::unordered_map<std::string, Spritesheet*> _spritesheets;
    std::unordered_map<TextSize::TextSize, Text*> _text;
    Audio* _audioPlayer = nullptr;
};

#endif