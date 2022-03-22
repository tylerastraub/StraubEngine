#ifndef GAME_H
#define GAME_H

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
    const char * _gameFontPath = "res/font/Munro.ttf";

    const int GAME_WIDTH = 320;
    const int GAME_HEIGHT = 180;
    int _renderScale = 4;

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
    SDL_GameController* _controller = nullptr;

    bool _exitFlag = false;

    State* _currentState = nullptr;
    State* _nextState = nullptr;

    // Resources
    std::unordered_map<std::string, std::shared_ptr<Spritesheet>> _spritesheets;
    std::unordered_map<TextSize::TextSize, std::shared_ptr<Text>> _text;
    std::unique_ptr<Audio> _audioPlayer = nullptr;
};

#endif