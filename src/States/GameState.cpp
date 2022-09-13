#include "GameState.h"
#include "RandomGen.h"
#include "SpritesheetRegistry.h"

#include <chrono>

std::mt19937 RandomGen::randEng{(unsigned int) std::chrono::system_clock::now().time_since_epoch().count()};

bool GameState::init() {
    _keyboard = std::make_unique<Keyboard>();
    _mouse = std::make_unique<Mouse>(getRenderScale(), getRenderScale());
    _controller = std::make_unique<Controller>();

    _dialogueBox.setText(getText(TextSize::TINY));
    _dialogueBox.setIsEnabled(true);
    _dialogueBox.setReadSpeed(ReadSpeed::VERY_SLOW);
    _dialogueBox.setString("Hi! This is a test to see if the dialogue box works. Should wrap correctly!");

    return true;
}

void GameState::tick(float timescale) {
    // Logic goes here BEFORE input updates!
    if(_keyboard->isKeyPressed(SDL_SCANCODE_Z)) _dialogueBox.setTextFullyDisplayed(true);
    _dialogueBox.tick(timescale);

    // Input updates
    _keyboard->updateInputs();
    _controller->updateInputs();
}

void GameState::render() {
    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(getRenderer());

    _dialogueBox.render(0, getGameSize().y - 32);

    SDL_RenderPresent(getRenderer());
}

void GameState::handleControllerButtonInput(SDL_Event e) {
    _controller->updateButtonInputs(e);
}

void GameState::handleControllerAxisInput(SDL_Event e) {
    _controller->updateAxisInputs(e);
}

void GameState::handleMouseInput(SDL_Event e) {
    _mouse->updateInput(e, _renderOffset.x, _renderOffset.y);
}