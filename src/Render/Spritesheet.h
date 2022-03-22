#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <string>
#include <SDL.h>

class Spritesheet {
public:
    Spritesheet() = default;
    ~Spritesheet();

    // Deallocates texture. Automatically called in destructor but can also
    // be called manually.
    void free();
    bool load(SDL_Renderer* renderer, std::string path);
    void render(int x, int y, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0, SDL_Point center = {-1, -1});

    int getWidth();
    int getHeight();
    int getTileWidth();
    int getTileHeight();
    bool isAnimated();
    bool isLooped();
    int getNumOfFrames();
    int getMsBetweenFrames();

    void setTileIndex(int x, int y);
    void setTileWidth(int w);
    void setTileHeight(int h);
    void setRenderWidth(int w);
    void setRenderHeight(int h);
    void setIsAnimated(bool isAnimated);
    void setIsLooped(bool isLooped);
    void setNumOfFrames(int frames);
    void setMsBetweenFrames(int ms);

private:
    const int INDEX_SIZE = 16;
    // Size of source rectangle in spritesheet
    SDL_Point _tileSize = {16, 16};
    // Size of destination rectangle for rendering spritesheet
    SDL_Point _renderSize = {16, 16};
    // Actual size of spritesheet file in pixels
    SDL_Point _size = {0, 0};
    SDL_Renderer* _renderer = nullptr;
    SDL_Texture* _texture = nullptr;

    SDL_Point _tileIndex = {0, 0};
    bool _isAnimated = false;
    bool _isLooped = false;
    // If animated, number of frames the spritesheet has.
    int _numOfFrames = 1;
    // Number of milliseconds between each frame of animation
    int _msBetweenFrames = 79;

};

#endif