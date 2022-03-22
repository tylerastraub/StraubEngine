#include "State.h"

void State::setGameSize(int w, int h) {
    _gameSize = {w, h};
}

void State::setNextState(State* state) {
    if(_nextState) delete _nextState;
    _nextState = state;
}

void State::setRenderer(SDL_Renderer* renderer) {
    _renderer = renderer;    
}

void State::setRenderScale(int scale) {
    _renderScale = scale;
}

void State::addSpritesheet(std::string spritesheetID, Spritesheet* spritesheet) {
    _spritesheets[spritesheetID] = spritesheet;
}

void State::addText(TextSize::TextSize size, Text* text) {
    _text[size] = text;
}

void State::setAudioPlayer(Audio* audioPlayer) {
    _audioPlayer = audioPlayer;
}

SDL_Point State::getGameSize() {
    return _gameSize;
}

State* State::getNextState() {
    return _nextState;
}

SDL_Renderer* State::getRenderer() {
    return _renderer;
}

int State::getRenderScale() {
    return _renderScale;
}

Spritesheet* State::getSpritesheet(std::string spritesheetID) {
    return _spritesheets[spritesheetID];
}

Text* State::getText(TextSize::TextSize size) {
    return _text[size];
}

Audio* State::getAudioPlayer() {
    return _audioPlayer;
}