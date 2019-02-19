#include "main.h"
#include "cannon.h"

#ifndef ISLAND_H
#define ISLAND_H


class Island {
public:
    Island() {}
    Island(float x, float z);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    glm::vec4 * shoot();
    bounding_box_t get_bounding_box();
    bool die(bool);
private:
    VAO *object[6];
    Cannon cannon;
    float max_height;
    static constexpr float width  = 4.0f;
    static constexpr float height = 0.4f;
};

#endif // ISLAND_H
