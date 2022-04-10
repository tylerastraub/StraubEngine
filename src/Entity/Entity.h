#ifndef ENTITY_H
#define ENTITY_H

#include "Keyboard.h"
#include "Mouse.h"
#include "Controller.h"
#include "Spritesheet.h"
#include "Audio.h"

#include <SDL.h>

class Entity {
public:
    Entity();
    ~Entity() = default;

    virtual void tick(float timescale) = 0;
    virtual void render(int xOffset, int yOffset) = 0;

    void setPos(float x, float y);
    void setTextureRect(SDL_Rect rect);
    void setCollisionRect(SDL_Rect rect);
    void setHitbox(SDL_Rect rect);
    void setHurtbox(SDL_Rect rect);

    void setMaxSpeed(float maxSpeed);
    void setAcceleration(float acceleration);
    void setFriction(float friction);
    void setAirAcceleration(float airAcceleration);
    void setAirFriction(float airFriction);
    void setJumpPower(float jumpPower);

    void setSpritesheet(Spritesheet* spritesheet);
    
    void setKeyboard(Keyboard* keyboard);
    void setMouse(Mouse* mouse);
    void setController(Controller* controller);

    void setAudioPlayer(Audio* audioPlayer);
    
    const SDL_FPoint getPos();
    const SDL_Rect getTextureRect();
    const SDL_Rect getCollisionRect();
    const SDL_Rect getHitbox();
    const SDL_Rect getHurtbox();

    const float getMaxSpeed();
    const float getAcceleration();
    const float getFriction();
    const float getAirAcceleration();
    const float getAirFriction();
    const float getJumpPower();

    const Spritesheet* getSpritesheet();

    const Keyboard* getKeyboard();
    const Mouse* getMouse();
    const Controller* getController();

    const Audio* getAudioPlayer();

private:
    static int entityIdProvider;
    int _entityId;

    // The entity's aboslute world position
    SDL_FPoint _pos = {0, 0};
    // Used for mapping the texture to the entity
    SDL_Rect _textureRect = {0, 0, 0, 0};
    // Used for level collision detection
    SDL_Rect _collisionRect = {0, 0, 0, 0};
    // Used for hurting other entities
    SDL_Rect _hitbox = {0, 0, 0, 0};
    // Used for getting hurt by other entities
    SDL_Rect _hurtbox = {0, 0, 0, 0};

    // Physics and platforming. Everything is in units per second
    float _maxSpeed = 50.f;
    float _acceleration = 10.f;
    float _friction = 10.f;
    float _airAcceleration = 5.f;
    float _airFriciton = 2.f;
    float _jumpPower = 120.f;

    // Render
    Spritesheet* _spritesheet = nullptr;

    // Input
    Keyboard* _keyboard = nullptr;
    Mouse* _mouse = nullptr;
    Controller* _controller = nullptr;

    // Other
    Audio* _audioPlayer = nullptr;
};

#endif