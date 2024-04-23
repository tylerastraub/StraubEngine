#pragma once
#include "vec2.h"
#include "rect2.h"

#include <entt/entity/registry.hpp>

class CameraSystem {
public:
    CameraSystem() = default;
    ~CameraSystem() = default;

    void update(entt::registry& ecs, float timescale);
    void alignCameraOffsetWithGoal();

    void setCameraGoal(entt::entity goalEntity);
    void setGoalCameraOffset(strb::vec2f goalOffset);
    void setCurrentCameraOffset(strb::vec2f currentOffset);
    void setGameSize(strb::vec2i gameSize);
    void setCameraBounds(strb::rect2f cameraBounds);
    void setCameraSpeed(float cameraSpeed);

    strb::vec2f getCurrentCameraOffset();
    bool atXEdge();
    bool atYEdge();

private:
    strb::vec2f _currentCameraOffset = {0.f, 0.f};
    strb::vec2f _goalCameraOffset = {0.f, 0.f};
    entt::entity _cameraGoal = entt::null;
    
    /**
     * Percent of distance camera moves between camera and target. For instance,
     * a _cameraSpeed of 0.1f means every frame, the distance closes by 10%.
     * This should be between 0 and 1. Some notable points:
     * - 0.01f = snail pace
     * - 0.05f = slower speed
     * - 0.1f = normal speed
     * - 0.5f = very fast
     * - 1.f = no smooth camera, instantly locks onto target
     */
    float _cameraSpeed = 0.1f;

    strb::vec2i _gameSize = {0, 0}; // The size of the game window in pixels
    strb::rect2f _cameraBounds = {0.f, 0.f, 0.f, 0.f};

};