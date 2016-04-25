/*
 * model.h
 *
 *  Created on: Mar 30, 2015
 *      Author: rainautumn
 */
#ifndef MODEL_H_
#define MODEL_H_

#include <string>
#include "glmath.hpp"
#include "position.h"
#include <GL/glew.h>
#include <vector>
#include "camera.h"

using namespace std;

struct res_mod
{
	GLuint vertex_buffer;
    GLuint normal_buffer, tangent_buffer, bitangent_buffer;
    GLuint textur_buffer, colour_buffer;

	GLuint vertex_shader, fragment_shader, program;

	GLint vertex;
    GLint normals, tangents, bitangents;
	GLint UV;
    GLint colour_map, normal_map;

    GLint colour_uniform, normal_uniform;
    GLint camera_matrix, world_matrix;

	vector<vtx4> vertex_data;
    vector<vtx3> normal_data, tangent_data, bitangent_data;
    vector<vtx2> UV_data;

    unsigned int element_len;

    string vertex_shader_path, fragment_shader_path;
    string colour_map_path, normal_map_path;
};

class Model : public Position
{
public:
    Model(char *path);
    virtual ~Model();

	res_mod _res_mod;

	void render();

    void init_camera(Camera *_camera);
private:
	void parser_model(char *path);
    void calc_tangents();
    Camera *camera;
};

#endif /* MODEL_H_ */
