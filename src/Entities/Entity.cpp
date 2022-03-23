#include "Entity.h"

Entity::Entity() {
    entityIdProvider++;
    _entityId = entityIdProvider;
}

void Entity::setPos(float x, float y) {
    _pos = {x, y};
}

void Entity::setTextureRect(SDL_Rect rect) {
    _textureRect = rect;
}

void Entity::setCollisionRect(SDL_Rect rect) {
    _collisionRect = rect;
}

void Entity::setHitbox(SDL_Rect rect) {
    _hitbox = rect;
}

void Entity::setHurtbox(SDL_Rect rect) {
    _hurtbox = rect;
}

void Entity::setMaxSpeed(float maxSpeed) {
    _maxSpeed = maxSpeed;
}

void Entity::setAcceleration(float acceleration) {
    _acceleration = acceleration;
}

void Entity::setFriction(float friction) {
    _friction = friction;
}

void Entity::setAirAcceleration(float airAcceleration) {
    _airAcceleration = airAcceleration;
}

void Entity::setAirFriction(float airFriction) {
    _airFriciton = airFriction;
}

void Entity::setJumpPower(float jumpPower) {
    _jumpPower = jumpPower;
}

void Entity::setSpritesheet(Spritesheet* spritesheet) {
    _spritesheet = spritesheet;
}

void Entity::setKeyboard(Keyboard* keyboard) {
    _keyboard = keyboard;
}

void Entity::setMouse(Mouse* mouse) {
    _mouse = mouse;
}

void Entity::setController(Controller* controller) {
    _controller = controller;
}

void Entity::setAudioPlayer(Audio* audioPlayer) {
    _audioPlayer = audioPlayer;
}

const SDL_FPoint Entity::getPos() {
    return _pos;
}

const SDL_Rect Entity::getTextureRect() {
    return _textureRect;
}

const SDL_Rect Entity::getCollisionRect() {
    return _collisionRect;
}

const SDL_Rect Entity::getHitbox() {
    return _hitbox;
}

const SDL_Rect Entity::getHurtbox() {
    return _hurtbox;
}

const float Entity::getMaxSpeed() {
    return _maxSpeed;
}

const float Entity::getAcceleration() {
    return _acceleration;
}

const float Entity::getFriction() {
    return _friction;
}

const float Entity::getAirAcceleration() {
    return _airAcceleration;
}

const float Entity::getAirFriction() {
    return _airFriciton;
}

const float Entity::getJumpPower() {
    return _jumpPower;
}

const Spritesheet* Entity::getSpritesheet() {
    return _spritesheet;
}

const Keyboard* Entity::getKeyboard() {
    return _keyboard;
}

const Mouse* Entity::getMouse() {
    return _mouse;
}

const Controller* Entity::getController() {
    return _controller;
}

const Audio* Entity::getAudioPlayer() {
    return _audioPlayer;
}