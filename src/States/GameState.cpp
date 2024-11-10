#include "GameState.h"
#include "RandomGen.h"
#include "SpritesheetRegistry.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "InputComponent.h"

#include <chrono>

std::mt19937 RandomGen::randEng{(unsigned int) std::chrono::system_clock::now().time_since_epoch().count()};

bool GameState::init() {
    initSystems();

    _player = _ecs.create();                            // pos                lastPos
    _ecs.emplace<TransformComponent>(_player, strb::vec2f{64, 64}, strb::vec2f{64, 64});
    PhysicsComponent physics;
    physics.maxVelocity = {50.f, 50.f};
    physics.frictionCoefficient = {10.f};
    physics.acceleration = {20.f, 20.f};
    _ecs.emplace<PhysicsComponent>(_player, physics);
    _ecs.emplace<RenderComponent>(_player, RenderComponent{{0, 0, 16, 16}});
    _ecs.emplace<InputComponent>(_player, InputComponent{{InputEvent::LEFT, InputEvent::RIGHT, InputEvent::UP, InputEvent::DOWN}});

    // if (_server.start(7000) == false) {
    //     return false;
    // }

    // if(_client.connect("localhost", 7000) == false) {
    //     return false;
    // }

    return true;
}

void GameState::tick(float timescale) {
    if(getKeyboard()->isKeyPressed(SDL_SCANCODE_S) && _client.isConnected() == false) {
        if(_server.isRunning() == false) {
            _server.start(7000);
        }
        else {
            _server.shutDown();
        }
    }
    if(getKeyboard()->isKeyPressed(SDL_SCANCODE_C) && _server.isRunning() == false) {
        if(_client.isConnected() == false) {
            _client.connect("localhost", 7000);
        }
        else {
            _client.disconnect();
        }
    }

    if(_server.isRunning()) _server.poll();
    if(_client.isConnected()) _client.poll();

    // Logic goes here BEFORE input updates!
    _inputSystem.update(_ecs);
    _physicsSystem.updateX(_ecs, timescale);
    _physicsSystem.updateY(_ecs, timescale);
    _renderSystem.update(_ecs, timescale);

    // Input updates
    getKeyboard()->updateInputs();
    getController()->updateInputs();
}

void GameState::render() {
    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(getRenderer());

    _renderSystem.render(getRenderer(), _ecs, _renderOffset);

    SDL_RenderPresent(getRenderer());
}

void GameState::handleControllerButtonInput(SDL_Event e) {
    getController()->updateButtonInputs(e);
}

void GameState::handleControllerAxisInput(SDL_Event e) {
    getController()->updateAxisInputs(e);
}

void GameState::handleMouseInput(SDL_Event e) {
    getMouse()->handleEvent(e, _renderOffset.x, _renderOffset.y);
}

void GameState::initSystems() {
    _inputSystem.init(getKeyboard(), getController(), getSettings());
    _renderSystem.setRenderBounds(getGameSize());
}