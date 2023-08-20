#include "State.h"

void State::setGameSize(int w, int h) {
    _gameSize = {(float) w, (float) h};
}

void State::setNextState(State* state) {
    if(_nextState) delete _nextState;
    _nextState = state;
}

void State::setRenderer(SDL_Renderer* renderer) {
    _renderer = renderer;    
}

void State::setRenderScale(strb::vec2 renderScale) {
    _renderScale = renderScale;
}

void State::addText(TextSize size, std::shared_ptr<Text> text) {
    _text[size] = text;
}

void State::setAudioPlayer(std::shared_ptr<Audio> audioPlayer) {
    _audioPlayer = audioPlayer;
}

void State::setSettings(std::shared_ptr<Settings> settings) {
    _settings = settings;
}

void State::completeSettingsChange() {
    _settingsChanged = false;
}

void State::setInput(std::shared_ptr<Keyboard> keyboard, std::shared_ptr<Mouse> mouse, std::shared_ptr<Controller> controller) {
    _keyboard = keyboard;
    _mouse = mouse;
    _controller = controller;
}

strb::vec2 State::getGameSize() {
    return _gameSize;
}

State* State::getNextState() {
    return _nextState;
}

SDL_Renderer* State::getRenderer() {
    return _renderer;
}

strb::vec2 State::getRenderScale() {
    return _renderScale;
}

std::shared_ptr<Text> State::getText(TextSize size) {
    return _text[size];
}

std::shared_ptr<Audio> State::getAudioPlayer() {
    return _audioPlayer;
}

std::shared_ptr<Settings> State::getSettings() {
    return _settings;
}

bool State::settingsChanged() {
    return _settingsChanged;
}

std::shared_ptr<Keyboard> State::getKeyboard() {
    return _keyboard;
}

std::shared_ptr<Mouse> State::getMouse() {
    return _mouse;
}

std::shared_ptr<Controller> State::getController() {
    return _controller;
}