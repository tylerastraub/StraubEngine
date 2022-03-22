#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "Keyboard.h"
#include "Mouse.h"

class GameState: public State {
public:
    GameState() = default;
    ~GameState() = default;

    void init() override;
    void tick(float timescale) override;
    void render() override;
    void handleKeyboardInput(SDL_Event e) override {};
    void handleControllerButtonInput(SDL_Event e) override;
    void handleControllerAxisInput(SDL_Event e) override;
    void handleMouseInput(SDL_Event e) override;

private:
    std::unique_ptr<Keyboard> _keyboard = nullptr;
    std::unique_ptr<Mouse> _mouse = nullptr;

    SDL_FPoint _renderOffset = {0.f, 0.f};
};

#endif