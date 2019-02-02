#include "main.h"

#ifndef RAFALE_H
#define RAFALE_H


class Rafale {
public:
    Rafale() {}
    Rafale(float x, float y);
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void yaw(bool right);
    void pitch(bool up);
    void roll(bool anticlockwise);
    glm::vec3 position;
private:
    VAO *object[2];
    float rotation;
    double speed;
    float yaw_ctrl;
    float pitch_ctrl;
    float roll_ctrl;
    static constexpr float width = 1.0f;
    static constexpr float height = 1.0f;
    static constexpr float depth = 3.0f;
    static constexpr float span = 3.0f;
};

#endif // RAFALE_H