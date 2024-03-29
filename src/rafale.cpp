#include "rafale.h"
#include "main.h"

Rafale::Rafale(float x, float y) {
    this->position = glm::vec3(x, y + height, 0);
    this->rotation = 0;
    this->counter = 0;
    this->fuel = MAX_FUEL;
    this->speed = 0.25f;
    this->yaw_ctrl = 0;
    this->pitch_ctrl = 0;
    this->health = MAX_HEALTH;
    this->roll_ctrl = 0;
    this->loop_ctrl = 0;
    this->barral_roll_ctrl = 0;
    this->rotation_matrix = glm::rotate(0.0f, glm::vec3(1, 0, 0));

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
            -width, -height,  -depth, // triangle 1 : begin
            -width, -height,   depth,
            -width,  height,   depth, // triangle 1 : end
             width,  height,  -depth, // triangle 2 : begin
            -width, -height,  -depth,
            -width,  height,  -depth, // triangle 2 : end
             width, -height,   depth,
            -width, -height,  -depth,
             width, -height,  -depth,
             width,  height,  -depth,
             width, -height,  -depth,
            -width, -height,  -depth,
            -width, -height,  -depth,
            -width,  height,   depth,
            -width,  height,  -depth,
             width, -height,   depth,
            -width, -height,   depth,
            -width, -height,  -depth,
            -width,  height,   depth,
            -width, -height,   depth,
             width, -height,   depth,
             width,  height,   depth,
             width, -height,  -depth,
             width,  height,  -depth,
             width, -height,  -depth,
             width,  height,   depth,
             width, -height,   depth,
             width,  height,   depth,
             width,  height,  -depth,
            -width,  height,  -depth,
             width,  height,   depth,
            -width,  height,  -depth,
            -width,  height,   depth,
             width,  height,   depth,
            -width,  height,   depth,
             width, -height,   depth
        };
    static const GLfloat vertex_buffer_data_2[] = {
            //fin 1
            -width,   0.0f,  -depth/8, // triangle 1 : begin
            -width,   0.01f, 7*depth/8,
       -span-width,   0.0f,   depth/2, // triangle 1 : end
            -width,   0.0f,-7*depth/8, // triangle 2 : begin
            -width,   0.01f,  -depth/4,
     -span/2-width,   0.0f,  -depth/2, // triangle 2 : end
            // fin 2
             width,   0.0f, 7*depth/8, // triangle 1 : begin
             width,   0.01f,  -depth/8,
        span+width,   0.0f,   depth/2, // triangle 1 : end
             width,   0.0f,-7*depth/8, // triangle 2 : begin
             width,   0.01f,  -depth/4,
      span/2+width,   0.0f,  -depth/2, // triangle 2 : end
            // fin 3
             -0.01f,span/2+height,   depth, // triangle 1 : begin
              0.0f,       height,   depth/2,
             -0.01f,       height,   depth, // triangle 1 : end
            // fin 4
              0.01f,span/2+height,   depth, // triangle 1 : begin
              0.0f,        height,   depth/2,
              0.01f,       height,   depth, // triangle 1 : end
          // Nose
              0.0f,      0.0f,   -depth-3*span/4,
             width,    height,   -depth,
            -width,    height,   -depth,
              0.0f,      0.0f,   -depth-3*span/4,
            -width,    height,   -depth,
            -width,   -height,   -depth,
              0.0f,      0.0f,   -depth-3*span/4,
            -width,   -height,   -depth,
             width,   -height,   -depth,
              0.0f,      0.0f,   -depth-3*span/4,
             width,   -height,   -depth,
             width,    height,   -depth
        };
    static const GLfloat vertex_buffer_data_3[] = {
            width/2, span/4+height,  -depth/4,
            width/2,        height,  -depth/4,
               0.0f,        height,-7*depth/8,
           -width/2, span/4+height,  -depth/4,
           -width/2,        height,  -depth/4,
               0.0f,        height,-7*depth/8,
            width/2, span/4+height,  -depth/4,
           -width/2, span/4+height,  -depth/4,
               0.0f,        height,-7*depth/8,
           -width/2, span/4+height,  -depth/4,
           -width/2,        height,  -depth/4,
            width/2, span/4+height,  -depth/4,
            width/2,        height,  -depth/4,
            width/2, span/4+height,  -depth/4,
           -width/2,        height,  -depth/4
        };

    // Aim arrows
    static const GLfloat vertex_buffer_data_4[] = {

    };

    this->object[0] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data , COLOR_ORANGE, GL_LINES);
    this->object[1] = create3DObject(GL_TRIANGLES,  10*3, vertex_buffer_data_2, COLOR_GREEN, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES,  5*3, vertex_buffer_data_3, COLOR_BLUE, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES,  5*3, vertex_buffer_data_4, COLOR_GREY, GL_FILL);
}

void Rafale::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // glm::mat4 rotate = this->rotation_matrix;
    rotate *= glm::rotate((float) (this->yaw_ctrl * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate *= glm::rotate((float) (this->pitch_ctrl * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate *= glm::rotate((float) (this->roll_ctrl * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
}

void Rafale::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rafale::tick() {
    // Move in direction of nose to origin
    this->position.y += sin(this->pitch_ctrl * M_PI/180.0f) * this->speed;
    this->position.x -= sin(this->yaw_ctrl   * M_PI/180.0f) * cos(this->pitch_ctrl * M_PI/180.0f) * this->speed;
    this->position.z -= cos(this->yaw_ctrl * M_PI/180.0f) * cos(this->pitch_ctrl * M_PI/180.0f) * this->speed;

    if(this->barral_roll_ctrl)
        this->roll_ctrl = this->barral_roll_ctrl--;
    if(this->loop_ctrl)
        this->pitch_ctrl = 360 - this->loop_ctrl--;
    this->fuel -= 1.0f;
    if(this->fuel < 0){
        exit(1);
    }
    this->health += 0.0625f;
    if(this->health > MAX_HEALTH)
        this->health = MAX_HEALTH;
    // printf("%f %f %f %f %f\n", this->position.x ,this->position.y, this->position.z, this->yaw_ctrl, this->pitch_ctrl);
}
glm::vec3 Rafale::orientation() {
    return glm::vec3(this->yaw_ctrl, this->pitch_ctrl, this->roll_ctrl);
}

void Rafale::yaw(bool right) {
    if(barral_roll_ctrl || loop_ctrl)
        return;
    if(right)
        this->yaw_ctrl -= 1;
    else
        this->yaw_ctrl += 1;
}

void Rafale::pitch(bool up) {
    if(barral_roll_ctrl || loop_ctrl)
        return;
    if(up)
        this->pitch_ctrl += 0.75f;
    else
        this->pitch_ctrl -= 0.75f;
}

void Rafale::roll(bool anticlockwise) {
    if(barral_roll_ctrl || loop_ctrl)
        return;
    if(anticlockwise)
        this->roll_ctrl += 1;
    else
        this->roll_ctrl -= 1;
}

void Rafale::barral_roll() {
    if(barral_roll_ctrl || loop_ctrl)
        return;
    this->barral_roll_ctrl = 360;
    this->roll_ctrl = 0;
}

void Rafale::loop() {
    if(barral_roll_ctrl || loop_ctrl)
        return;
    this->loop_ctrl = 360;
    this->pitch_ctrl = 0;
}

bounding_box_t Rafale::get_bounding_box() {
    bounding_box_t box = {
        this->position.x,    //x-coordinate
        this->position.y,    //y-coordinate
        this->position.z,    //z-coordinate
        width*2,             //main body width
        height*2,            //main body height
        depth*2,             //main body depth
    };
    return box;
}

glm::vec3 Rafale::unit_vector(){
    glm::vec3 temp;
    temp.y = sin(this->pitch_ctrl * M_PI/180.0f);
    temp.x = -sin(this->yaw_ctrl   * M_PI/180.0f) * cos(this->pitch_ctrl * M_PI/180.0f);
    temp.z = -cos(this->yaw_ctrl * M_PI/180.0f) * cos(this->pitch_ctrl * M_PI/180.0f);
    temp = glm::normalize(temp);
    return temp;
}

float Rafale::fuel_fill(bool up) {
    //up =1 increase fuel
    if(up)
        this->fuel = MAX_FUEL;
    //up = 0 return current fuel in normalized;
    // return 2*(this->fuel/MAX_FUEL-0.5);
    return this->fuel/MAX_FUEL;
}

void Rafale::speed_up(bool up) {
    //up =1 increase spped
    if(up)
    {
        this->speed += 0.05;
        if(this->speed > MAX_SPEED)
            this->speed = MAX_SPEED;
    }
    else{
        this->speed -= 0.05;
        if(this->speed < 0)
            this->speed = 0;
    }
}

float Rafale::speed_fill() {
    return this->speed/MAX_SPEED;
}

float Rafale::health_fill() {
    return this->health/MAX_HEALTH;
}


glm::vec3 Rafale::get_position() {
    return this->position;
}

void Rafale::die(int sick) {
    this->health -= sick * 2 * this->speed;
    if(this->health <= 0){
        exit(1);
    }
}
