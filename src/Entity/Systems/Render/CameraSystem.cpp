#include "CameraSystem.h"

#include "RenderComponent.h"

void CameraSystem::update(entt::registry& ecs, float timescale) {
    if(_cameraGoal != entt::null) {
        auto eRender = ecs.get<RenderComponent>(_cameraGoal);
        _goalCameraOffset = {eRender.renderQuad.x + eRender.renderQuad.w / 2 - _gameSize.x / 2,
            eRender.renderQuad.y + eRender.renderQuad.h / 2 - _gameSize.y / 2};
    }
    
    // keep camera goal in bounds (and allow smooth movement when at level borders)
    if(_goalCameraOffset.x < _cameraBounds.x) {
        _goalCameraOffset.x = _cameraBounds.x;
    }
    else if(_goalCameraOffset.x > _cameraBounds.x + _cameraBounds.w - _gameSize.x) {
        _goalCameraOffset.x = _cameraBounds.x + _cameraBounds.w - _gameSize.x;
    }
    if(_goalCameraOffset.y < _cameraBounds.y) {
        _goalCameraOffset.y = _cameraBounds.y;
    }
    else if(_goalCameraOffset.y > _cameraBounds.y + _cameraBounds.h - _gameSize.y) {
        _goalCameraOffset.y = _cameraBounds.y + _cameraBounds.h - _gameSize.y;
    }

    float xOffsetDiff = _goalCameraOffset.x - _currentCameraOffset.x;
    float yOffsetDiff = _goalCameraOffset.y - _currentCameraOffset.y;
    
    _currentCameraOffset.x = ((1 - _cameraSpeed) * _currentCameraOffset.x) + (_cameraSpeed * _goalCameraOffset.x);
    _currentCameraOffset.y = (0.9f * _currentCameraOffset.y) + (0.1f * _goalCameraOffset.y);
}

void CameraSystem::alignCameraOffsetWithGoal() {
    _currentCameraOffset = _goalCameraOffset;
}

void CameraSystem::setCameraGoal(entt::entity goalEntity) {
    _cameraGoal = goalEntity;
}

void CameraSystem::setGoalCameraOffset(strb::vec2f goalOffset) {
    _goalCameraOffset = goalOffset;
}

void CameraSystem::setCurrentCameraOffset(strb::vec2f currentOffset) {
    _currentCameraOffset = currentOffset;
}

void CameraSystem::setGameSize(strb::vec2i gameSize) {
    _gameSize = gameSize;
}

void CameraSystem::setCameraBounds(strb::rect2f cameraBounds) {
    _cameraBounds = cameraBounds;
}

void CameraSystem::setCameraSpeed(float cameraSpeed) {
    _cameraSpeed = cameraSpeed;
}

strb::vec2f CameraSystem::getCurrentCameraOffset() {
    return _currentCameraOffset * -1.f;
}

bool CameraSystem::atXEdge() {
    return _goalCameraOffset.x <= 0 ||
        _goalCameraOffset.x >= _cameraBounds.x + _cameraBounds.w - _gameSize.x;
}

bool CameraSystem::atYEdge() {
    return _goalCameraOffset.y <= 0 ||
        _goalCameraOffset.y >= _cameraBounds.y + _cameraBounds.h - _gameSize.y;
}