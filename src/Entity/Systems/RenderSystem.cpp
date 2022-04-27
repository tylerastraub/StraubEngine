#include "RenderSystem.h"
#include "EntityRegistry.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "SpritesheetPropertiesComponent.h"
#include "DirectionComponent.h"
#include "StateComponent.h"

void RenderSystem::updateRenderQuadSmoothMovement(float percent) {
    auto ecs = EntityRegistry::getInstance();
    for(auto ent : _entities) {
        if(ecs->hasComponent<TransformComponent>(ent)) {
            auto& transform = ecs->getComponent<TransformComponent>(ent);
            auto& renderComponent = ecs->getComponent<RenderComponent>(ent);
            strb::vec2f delta = (transform.position - transform.lastPosition) * 16;
            renderComponent.renderQuad.x = transform.lastPosition.x * 16 + delta.x * percent + renderComponent.renderQuadOffset.x;
            renderComponent.renderQuad.y = transform.lastPosition.y * 16 + delta.y * percent + renderComponent.renderQuadOffset.y;
        }
    }
}

void RenderSystem::render(SDL_Renderer* renderer, int renderXOffset, int renderYOffset) {
    auto ecs = EntityRegistry::getInstance();
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
    for(auto ent : _entities) {
        auto& renderComponent = ecs->getComponent<RenderComponent>(ent);
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