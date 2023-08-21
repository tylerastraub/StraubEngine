#pragma once

#include "State.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
// Systems
#include "InputSystem.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"

#include <memory>
#include <entt/entity/registry.hpp>

class GameState: public State {
public:
    GameState() = default;
    ~GameState() = default;

    bool init() override;
    void tick(float timescale) override;
    void render() override;
    void handleKeyboardInput(SDL_Event e) override {};
    void handleControllerButtonInput(SDL_Event e) override;
    void handleControllerAxisInput(SDL_Event e) override;
    void handleMouseInput(SDL_Event e) override;

    void initSystems();

private:
    strb::vec2f _renderOffset = {0.f, 0.f};

    entt::registry _ecs;

    entt::entity _player;

    InputSystem _inputSystem;
    RenderSystem _renderSystem;
    PhysicsSystem _physicsSystem;

};