#include "main.h"

#ifndef TOWER_H
#define TOWER_H


class Tower {
public:
    Tower() {}
    Tower(float x, float y);
    void draw(glm::mat4 VP);
    glm::vec3 get_position();
private:
    VAO *object;
    glm::vec3 position;
    static constexpr float width = 2.0f;
    static constexpr float height = 8.0f;
    static constexpr float depth = 2.0f;
};

#endif // TOWER_H