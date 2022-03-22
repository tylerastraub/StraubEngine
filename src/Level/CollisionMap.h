#ifndef COLLISION_MAP_H
#define COLLISION_MAP_H

#include <vector>

class CollisionMap {
public:
    CollisionMap() = default;
    CollisionMap(std::vector<std::vector<int>> collisionMap);
    ~CollisionMap() = default;

    void allocate(int w, int h);
    void printCollisionMap();

    void setCollisionMapIndex(int x, int y, bool collides);

    int getCollisionMapWidth();
    int getCollisionMapHeight();
    bool getCollisionMapAt(int x, int y);

private:
    std::vector<std::vector<bool>> _collisionMap;
    int _collisionMapWidth = 0;
    int _collisionMapHeight = 0;
    int _tileSize = 0;

};

#endif