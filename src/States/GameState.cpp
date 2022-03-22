#include "GameState.h"
#include "RandomGen.h"

#include <chrono>

std::mt19937 RandomGen::randEng{(unsigned int) std::chrono::system_clock::now().time_since_epoch().count()};

void GameState::init() {
    _keyboard = std::make_unique<Keyboard>();
    _mouse = std::make_unique<Mouse>(getRenderScale(), getRenderScale());
}

void GameState::tick(float timescale) {
    _keyboard->updateInputs();
}

void GameState::render() {
    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(getRenderer());

    SDL_RenderPresent(getRenderer());
}

void GameState::handleControllerButtonInput(SDL_Event e) {
    
}

void GameState::handleControllerAxisInput(SDL_Event e) {
    
}

void GameState::handleMouseInput(SDL_Event e) {
    _mouse->updateInput(e, _renderOffset.x, _renderOffset.y);
}