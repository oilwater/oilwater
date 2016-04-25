/*
 * initbuff.h
 *
 *  Created on: Mar 30, 2015
 *      Author: rainautumn
 */

#ifndef INITBUFF_H_
#define INITBUFF_H_

#include "model.h"
#include <GL/glew.h>
#include <stdio.h>
#include <cstdlib>

void *file_contents(const char *filename, GLint *length);
void *read_tga(const char *filename, int *width, int *height);
void init_buffers(res_mod *_res_mod);
static GLuint make_texture(const char *filename);
GLuint make_shader(GLenum type, const char *filename);
GLuint make_program(GLuint vertex_shader, GLuint fragment_shader);

#endif /* INITBUFF_H_ */
