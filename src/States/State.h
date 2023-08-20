#pragma once

#include "Text.h"
#include "Spritesheet.h"
#include "Audio.h"
#include "Settings.h"
#include "vec2.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"

#include <SDL.h>
#include <unordered_map>
#include <vector>
#include <memory>

enum class TextSize {
    TINY = 0,
    SMALL = 1,
    MEDIUM = 2,
    LARGE = 3,
};

class State {
public:
    State() = default;
    virtual ~State() = default;

    // Virtual methods
    virtual bool init() = 0;
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
    void setRenderScale(strb::vec2f renderScale);
    void addText(TextSize size, std::shared_ptr<Text> text);
    void setAudioPlayer(std::shared_ptr<Audio> audioPlayer);
    void setSettings(std::shared_ptr<Settings> settings);
    void completeSettingsChange();
    void setInput(std::shared_ptr<Keyboard> keyboard, std::shared_ptr<Mouse> mouse, std::shared_ptr<Controller> controller);
    
    strb::vec2i getGameSize();
    State* getNextState();
    SDL_Renderer* getRenderer();
    strb::vec2f getRenderScale();
    std::shared_ptr<Text> getText(TextSize size);
    std::shared_ptr<Audio> getAudioPlayer();
    std::shared_ptr<Settings> getSettings();
    bool settingsChanged();
    std::shared_ptr<Keyboard> getKeyboard();
    std::shared_ptr<Mouse> getMouse();
    std::shared_ptr<Controller> getController();

protected:
    bool _settingsChanged = false;

private:
    strb::vec2i _gameSize = {0, 0};
    State* _nextState = nullptr;
    SDL_Renderer* _renderer = nullptr;
    strb::vec2f _renderScale = {1.f, 1.f};
    std::unordered_map<TextSize, std::shared_ptr<Text>> _text;
    std::shared_ptr<Audio> _audioPlayer = nullptr;
    std::shared_ptr<Settings> _settings = nullptr;
    std::shared_ptr<Keyboard> _keyboard = nullptr;
    std::shared_ptr<Mouse> _mouse = nullptr;
    std::shared_ptr<Controller> _controller = nullptr;
};