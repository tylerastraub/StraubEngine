#include "CollisionMap.h"

#include <iostream>

CollisionMap::CollisionMap(std::vector<std::vector<int>> collisionMap) {
    _collisionMapHeight = collisionMap.size();
    _collisionMapWidth = collisionMap[0].size();
    for(int y = 0; y < _collisionMapHeight; ++y) {
        std::vector<bool> row;
        for(int x = 0; x < _collisionMapWidth; ++x) {
            row.push_back((bool) collisionMap[y][x]);
        }
        _collisionMap.push_back(row);
    }
}

void CollisionMap::allocate(int w, int h) {
    _collisionMapWidth = w;
    _collisionMapHeight = h;
    for(int y = 0; y < h; ++y) {
        std::vector<bool> row;
        for(int x = 0; x < w; ++x) {
            row.push_back(false);
        }
        _collisionMap.push_back(row);
    }
}

void CollisionMap::printCollisionMap() {
    for(int y = 0; y < _collisionMapHeight; ++y) {
        for(int x = 0; x < _collisionMapWidth; ++x) {
            std::cout << _collisionMap[y][x] << "  ";
        }
        std::cout << std::endl;
    }
}

void CollisionMap::setCollisionMapIndex(int x, int y, bool collides) {
    if(x >= 0 && x < _collisionMapWidth && y >= 0 && y < _collisionMapHeight) {
        _collisionMap[y][x] = collides;
    }
}

int CollisionMap::getCollisionMapWidth() {
    return _collisionMapWidth;
}

int CollisionMap::getCollisionMapHeight() {
    return _collisionMapHeight;
}

bool CollisionMap::getCollisionMapAt(int x, int y) {
    if(x >= 0 && x < _collisionMapWidth && y >= 0 && y < _collisionMapHeight) {
        return _collisionMap[y][x];
    }
    return true;
}