#include "CameraSystem.h"

void CameraSystem::update(float timescale) {
    float xOffsetDiff = _goalCameraOffset.x - _currentCameraOffset.x;
    float yOffsetDiff = _goalCameraOffset.y - _currentCameraOffset.y;
    // X Offset
    _currentCameraOffset.x = ((1 - _cameraSpeed) * _currentCameraOffset.x) + (_cameraSpeed * _goalCameraOffset.x);
    if(_currentCameraOffset.x < 0) {
        _currentCameraOffset.x = 0;
    }
    else if(_currentCameraOffset.x > _levelSize.x - _gameSize.x) {
        _currentCameraOffset.x = _levelSize.x - _gameSize.x;
    }

    // Y Offset
    _currentCameraOffset.y = (0.9f * _currentCameraOffset.y) + (0.1f * _goalCameraOffset.y);
    if(_currentCameraOffset.y < 0) {
        _currentCameraOffset.y = 0;
    }
    else if(_currentCameraOffset.y > _levelSize.y - _gameSize.y) {
        _currentCameraOffset.y = _levelSize.y - _gameSize.y;
    }
}

void CameraSystem::setGoalCameraOffset(float x, float y) {
    _goalCameraOffset = {x, y};
}

void CameraSystem::setCurrentCameraOffset(float x, float y) {
    _currentCameraOffset = {x, y};
}

void CameraSystem::setGameSize(int x, int y) {
    _gameSize = {(float) x, (float) y};
}

void CameraSystem::setLevelSize(int x, int y) {
    _levelSize = {(float) x, (float) y};
}

void CameraSystem::setCameraSpeed(float cameraSpeed) {
    _cameraSpeed = cameraSpeed;
}

strb::vec2f CameraSystem::getCurrentCameraOffset() {
    return _currentCameraOffset * -1.f;
}

bool CameraSystem::atXEdge() {
    return _goalCameraOffset.x <= 0 ||
        _goalCameraOffset.x >= _levelSize.x - _gameSize.x;
}

bool CameraSystem::atYEdge() {
    return _goalCameraOffset.y <= 0 ||
        _goalCameraOffset.y >= _levelSize.y - _gameSize.y;
}