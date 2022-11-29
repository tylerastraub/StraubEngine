#include "RenderSystem.h"
#include "EntityRegistry.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "SpritesheetPropertiesComponent.h"
#include "DirectionComponent.h"
#include "StateComponent.h"
#include "AnimationComponent.h"

void RenderSystem::update(float timescale) {
    auto ecs = EntityRegistry::getInstance();
    for(auto ent : _entities) {
        if(ecs->hasComponent<AnimationComponent>(ent)) {
            auto& animationComponent = ecs->getComponent<AnimationComponent>(ent);
            animationComponent.msSinceAnimationStart += timescale * 1000.f;
        }
    }
}

void RenderSystem::render(SDL_Renderer* renderer, int renderXOffset, int renderYOffset) {
    auto ecs = EntityRegistry::getInstance();
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
    for(auto ent : _entities) {
        auto& renderComponent = ecs->getComponent<RenderComponent>(ent);
        auto& transform = ecs->getComponent<TransformComponent>(ent);
        renderComponent.renderQuad.x = transform.position.x + renderComponent.renderQuadOffset.x;
        renderComponent.renderQuad.y = transform.position.y + renderComponent.renderQuadOffset.y;
        SDL_Rect quad = renderComponent.renderQuad;
        quad.x += renderXOffset;
        quad.y += renderYOffset;
        // bounds check before rendering
        if(quad.x + quad.w > 0 && quad.x < _renderBounds.x &&
           quad.y + quad.h > 0 && quad.y < _renderBounds.y) {
            // if entity has spritesheet + required helper components
            if(ecs->hasComponent<SpritesheetPropertiesComponent>(ent) &&
               ecs->hasComponent<StateComponent>(ent) &&
               ecs->hasComponent<DirectionComponent>(ent)) {
                auto& propsComponent = ecs->getComponent<SpritesheetPropertiesComponent>(ent);
                auto& state = ecs->getComponent<StateComponent>(ent).state;
                auto& direction = ecs->getComponent<DirectionComponent>(ent).direction;
                SpritesheetProperties props = propsComponent.getSpritesheetProperties(state, direction);
                propsComponent.spritesheet->setIsAnimated(props.isAnimated);
                propsComponent.spritesheet->setIsLooped(props.isLooped);
                propsComponent.spritesheet->setMsBetweenFrames(props.msBetweenFrames);
                propsComponent.spritesheet->setNumOfFrames(props.numOfFrames);
                if(props.isAnimated) {
                    auto& animationComponent = ecs->getComponent<AnimationComponent>(ent);
                    auto& state = ecs->getComponent<StateComponent>(ent);
                    // check for change in y index to restart animation counter
                    if(state.state != animationComponent.lastState) {
                        animationComponent.msSinceAnimationStart = 0;
                    }
                    if(props.isLooped) {
                        animationComponent.xIndex = animationComponent.msSinceAnimationStart / props.msBetweenFrames % props.numOfFrames;
                    }
                    else {
                        animationComponent.xIndex = animationComponent.msSinceAnimationStart / props.msBetweenFrames;
                        if(animationComponent.xIndex >= props.numOfFrames) animationComponent.xIndex = props.numOfFrames - 1;
                    }
                    propsComponent.spritesheet->setTileIndex(animationComponent.xIndex, props.yTileIndex);
                    animationComponent.lastState = state.state;
                    if(ecs->hasComponent<StateComponent>(ent) &&
                        ecs->hasComponent<DirectionComponent>(ent)) {
                        auto& state = ecs->getComponent<StateComponent>(ent).state;
                        auto& direction = ecs->getComponent<DirectionComponent>(ent).direction;
                        propsComponent.addSpritesheetProperties(state, direction, props);
                    }
                }
                else {
                    propsComponent.spritesheet->setTileIndex(props.xTileIndex, props.yTileIndex);
                }
                propsComponent.spritesheet->render(
                    quad.x,
                    quad.y,
                    quad.w,
                    quad.h,
                    props.flip,
                    props.angle,
                    props.center
                );
            }
            // else if entity has spritesheet at all
            else if(ecs->hasComponent<SpritesheetPropertiesComponent>(ent)) {
                auto& propsComponent = ecs->getComponent<SpritesheetPropertiesComponent>(ent);
                SpritesheetProperties props = propsComponent.getPrimarySpritesheetProperties();
                propsComponent.spritesheet->setIsAnimated(props.isAnimated);
                propsComponent.spritesheet->setIsLooped(props.isLooped);
                propsComponent.spritesheet->setMsBetweenFrames(props.msBetweenFrames);
                propsComponent.spritesheet->setNumOfFrames(props.numOfFrames);
                if(props.isAnimated) {
                    propsComponent.spritesheet->setTileIndex(propsComponent.spritesheet->getTileIndex().x, props.yTileIndex);
                }
                else {
                    propsComponent.spritesheet->setTileIndex(props.xTileIndex, props.yTileIndex);
                }
                propsComponent.spritesheet->render(
                    quad.x,
                    quad.y,
                    quad.w,
                    quad.h,
                    props.flip,
                    props.angle,
                    props.center
                );
            }
            else {
                // no spritesheet set, default quad rendered
                SDL_RenderFillRect(renderer, &quad);
            }
        }
    }
}

void RenderSystem::setRenderBounds(strb::vec2 renderBounds) {
    _renderBounds = renderBounds;
}