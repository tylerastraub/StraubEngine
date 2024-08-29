#pragma once

#include "GUIElement.h"
#include "SpritesheetID.h"
#include "SpritesheetProperties.h"

#include <memory>

class Icon : public GUIElement {
public:
    Icon(SpritesheetID spritesheetId, SpritesheetProperties spritesheetProperties);
    ~Icon() = default;

    void render(SDL_Renderer* renderer, strb::vec2f pos) override;

private:
    SpritesheetID _spritesheetId = SpritesheetID::NOVAL;
    SpritesheetProperties _spritesheetProperties;

};