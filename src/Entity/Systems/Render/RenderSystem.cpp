#include "RenderSystem.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "SpritesheetPropertiesComponent.h"
#include "DirectionComponent.h"
#include "StateComponent.h"
#include "AnimationComponent.h"
#include "rect2.h"

void RenderSystem::update(entt::registry& ecs, float timescale) {
    auto entities = ecs.view<AnimationComponent>();
    for(auto ent : entities) {
        auto& animationComponent = ecs.get<AnimationComponent>(ent);
        animationComponent.msSinceAnimationStart += timescale * 1000.f;
    }
}

void RenderSystem::render(SDL_Renderer* renderer, entt::registry& ecs, strb::vec2f renderOffset) {
    auto entities = ecs.view<RenderComponent, TransformComponent>();
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
    for(auto ent : entities) {
        auto& renderComponent = ecs.get<RenderComponent>(ent);
        auto& transform = ecs.get<TransformComponent>(ent);
        renderComponent.renderQuad.x = transform.position.x + renderComponent.renderQuadOffset.x;
        renderComponent.renderQuad.y = transform.position.y + renderComponent.renderQuadOffset.y;
        SDL_FRect quad = {
            renderComponent.renderQuad.x,
            renderComponent.renderQuad.y,
            renderComponent.renderQuad.w,
            renderComponent.renderQuad.h
        };
        quad.x += renderOffset.x;
        quad.y += renderOffset.y;
        // bounds check before rendering
        if(quad.x + quad.w > 0 && quad.x < _renderBounds.x &&
           quad.y + quad.h > 0 && quad.y < _renderBounds.y) {
            // if entity has spritesheet + required helper components
            if(ecs.all_of<SpritesheetPropertiesComponent>(ent) &&
               ecs.all_of<StateComponent>(ent) &&
               ecs.all_of<DirectionComponent>(ent)) {
                auto& propsComponent = ecs.get<SpritesheetPropertiesComponent>(ent);
                auto& state = ecs.get<StateComponent>(ent).state;
                auto& direction = ecs.get<DirectionComponent>(ent).direction;
                SpritesheetProperties props = propsComponent.getSpritesheetProperties(state, direction);
                propsComponent.spritesheet->setIsAnimated(props.isAnimated);
                propsComponent.spritesheet->setIsLooped(props.isLooped);
                propsComponent.spritesheet->setMsBetweenFrames(props.msBetweenFrames);
                propsComponent.spritesheet->setNumOfFrames(props.numOfFrames);
                if(props.isAnimated) {
                    auto& animationComponent = ecs.get<AnimationComponent>(ent);
                    auto& state = ecs.get<StateComponent>(ent);
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
                    if(ecs.all_of<StateComponent>(ent) &&
                        ecs.all_of<DirectionComponent>(ent)) {
                        auto& state = ecs.get<StateComponent>(ent).state;
                        auto& direction = ecs.get<DirectionComponent>(ent).direction;
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
            else if(ecs.all_of<SpritesheetPropertiesComponent>(ent)) {
                auto& propsComponent = ecs.get<SpritesheetPropertiesComponent>(ent);
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
                SDL_RenderFillRectF(renderer, &quad);
            }
        }
    }
}

void RenderSystem::setRenderBounds(strb::vec2i renderBounds) {
    _renderBounds = renderBounds;
}