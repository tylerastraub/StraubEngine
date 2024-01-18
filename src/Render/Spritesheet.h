#pragma once

#include "vec2.h"

#include <string>
#include <SDL.h>

/**
 * @brief Allows user to render animated textures using a spritesheet. Spritesheets should make use of
 * uniform dimensions throughout to make calculations easier.
 */
class Spritesheet {
public:
    Spritesheet() = default;
    ~Spritesheet();

    /**
     * @brief Deallocates texture. Automatically called in destructor but can also
     * be called manually.
     */
    void free();
    /**
     * @brief Loads a spritesheet based on the relative path to the executable.
     * 
     * @param renderer The SDL_Renderer being used for the project.
     * @param path The relative path of the image to be loaded.
     * @return true The image was loaded successfully.
     * @return false The image was not loaded successfully.
     */
    bool load(SDL_Renderer* renderer, std::string path);
    /**
     * @brief Renders the spritesheet.
     * 
     * @param x The absolute X position on the screen to render the sprite.
     * @param y The absolute Y position on the screen to render the sprite.
     * @param w The width of the quad to render to
     * @param h The height of the quad to render to
     * @param flip Flag to determine whether or not the flip the sprite. Set to SDL_FLIP_NONE by default.
     * @param angle The angle to rotate the sprite. Set to 0.0 by default.
     * @param center The center of the sprite for rotating. Uses the center of the sprite by default.
     */
    void render(float x, float y, float w, float h, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0, strb::vec2f center = {-1.f, -1.f});

    SDL_Texture* getTexture();
    strb::vec2i getTileIndex();
    int getWidth();
    int getHeight();
    int getTileWidth();
    int getTileHeight();
    bool isAnimated();
    bool isLooped();
    int getNumOfFrames();
    int getMsBetweenFrames();

    /**
     * @brief Set the tile index of the spritesheet. Note that this is relative to the current tile size.
     * 
     * @param x The X coordinate of the tile index
     * @param y The y coordinate of the tile index
     */
    void setTileIndex(int x, int y);
    /**
     * @brief Set the width of the srcRect in the spritesheet.
     * 
     * @param w The tile width in pixels.
     */
    void setTileWidth(int w);
    /**
     * @brief Set the height of the srcRect in the spritesheet.
     * 
     * @param h The tile height in pixels
     */
    void setTileHeight(int h);
    /**
     * @brief Set the isAnimated flag. Enabling this will result in the spritesheet automatically updating
     * its X tile index based on the below fields.
     * 
     * @param isAnimated Whether or not the spritesheet is animated.
     */
    void setIsAnimated(bool isAnimated);
    /**
     * @brief Set the isLooped flag. Only used if isAnimated is set to true.
     * 
     * @param isLooped Whether or not the spritesheet is looped.
     */
    void setIsLooped(bool isLooped);
    /**
     * @brief Set the numOfFrames member. Only used if isAnimated is set to true.
     * 
     * @param frames How many frames the spritesheet animation has.
     */
    void setNumOfFrames(int frames);
    /**
     * @brief Set the msBetweenFrames member. Only used if isAnimated is set to true.
     * 
     * @param ms The number of milliseconds between each animated frame.
     */
    void setMsBetweenFrames(int ms);

private:
    // Size of source rectangle in spritesheet
    strb::vec2i _tileSize = {32, 32};
    // Actual size of spritesheet file in pixels
    strb::vec2i _size = {0, 0};
    SDL_Renderer* _renderer = nullptr;
    SDL_Texture* _texture = nullptr;

    strb::vec2i _tileIndex = {0, 0};
    bool _isAnimated = false;
    bool _isLooped = false;
    // If animated, number of frames the spritesheet has.
    int _numOfFrames = 1;
    // Number of milliseconds between each frame of animation
    int _msBetweenFrames = 79;

};