#ifndef LETTER_SPRITE_H
#define LETTER_SPRITE_H

#include "model.h"

struct res_let
{
    GLuint vertex_buffer;

    GLuint vertex_shader, fragment_shader, program;

    GLint vertex;

    GLint camera_matrix, world_matrix;

    vector<vtx4> vertex_data;

    unsigned int element_len;

    string vertex_shader_path, fragment_shader_path;
};

class Letter_sprite : public Position
{
public:
    Letter_sprite(char *path);


    res_let _res_let;

    void render();

    void init_camera(Camera *_camera);

    int type;
private:
    void parser_model(char *path);
    void calc_tangents();
    Camera *camera;
};

#endif // LETTER_SPRITE_H
