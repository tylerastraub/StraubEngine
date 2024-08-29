#include "Icon.h"
#include "SpritesheetRegistry.h"

Icon::Icon(SpritesheetID spritesheetId, SpritesheetProperties spritesheetProperties) : _spritesheetId(spritesheetId), _spritesheetProperties(spritesheetProperties) {
    _type = ElementType::ICON;
}

void Icon::render(SDL_Renderer* renderer, strb::vec2f pos) {
    Spritesheet* ss = SpritesheetRegistry::getSpritesheet(_spritesheetId);

    ss->setTileIndex(_spritesheetProperties.xTileIndex, _spritesheetProperties.yTileIndex);
    ss->render(
        pos.x,
        pos.y,
        ss->getTileWidth(),
        ss->getTileHeight(),
        _spritesheetProperties.flip,
        _spritesheetProperties.angle,
        _spritesheetProperties.center
    );
}