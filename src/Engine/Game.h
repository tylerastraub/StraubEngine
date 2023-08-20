#pragma once

#include "State.h"
#include "GameState.h"

class Game {
public:
    Game(const char * windowTitle);
    ~Game();

    bool init();
    bool loadResources();
    void startGameLoop();
    void exit();

private:
    const char * _windowTitle;
    const char * _tinyTextFontPath = "res/font/04b03.ttf";
    const char * _smallTextFontPath = "res/font/edit-undo.brk.ttf";
    const char * _mediumTextFontPath = "res/font/MunroSmall.ttf";
    const char * _largeTextFontPath = "res/font/edit-undo.brk.ttf"; // temp

    const int GAME_WIDTH = 320;
    const int GAME_HEIGHT = 180;
    strb::vec2f _renderScale = {1.f, 1.f};

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
    SDL_GameController* _gameController = nullptr;

    bool _exitFlag = false;

    State* _currentState = nullptr;
    State* _nextState = nullptr;

    // Resources
    std::unordered_map<TextSize, std::shared_ptr<Text>> _text;
    std::shared_ptr<Audio> _audioPlayer = nullptr;
    std::shared_ptr<Settings> _settings = nullptr;
    
    std::shared_ptr<Keyboard> _keyboard = nullptr;
    std::shared_ptr<Mouse> _mouse = nullptr;
    std::shared_ptr<Controller> _controller = nullptr;
};