/*
 * initbuff.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: rainautumn
 */

#include "initbuff.hpp"
#include <iostream>
#include <string>

using namespace std;

static GLuint make_texture(const char *filename)
{
    int width, height;
    void *pixels = read_tga(filename, &width, &height);
    GLuint texture;

    if (!pixels)
        return 0;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    glTexImage2D(
        GL_TEXTURE_2D, 0,
        GL_RGBA8,
        width, height, 0,
        GL_BGRA, GL_UNSIGNED_BYTE,
        pixels
    );
    free(pixels);
    return texture;
}

GLuint make_shader(GLenum type, const char *filename)
{
    GLint length;
    GLchar *source = (GLchar*)file_contents(filename, &length);
    GLuint shader;
    GLint shader_ok;

    if (!source)
        return 0;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)&source, &length);
    delete source;
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok) {
        cout << "Failed to compile " << filename << endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint make_program(GLuint vertex_shader, GLuint fragment_shader)
{
    GLint program_ok;
    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
    if (!program_ok) {
        cout << "Failed to link shader program\n";
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

static short le_short(unsigned char *bytes)
{
    return bytes[0] | ((char)bytes[1] << 8);
}

void *read_tga(const char *filename, int *width, int *height)
{
    struct tga_header {
       char  id_length;
       char  color_map_type;
       char  data_type_code;
       unsigned char  color_map_origin[2];
       unsigned char  color_map_length[2];
       char  color_map_depth;
       unsigned char  x_origin[2];
       unsigned char  y_origin[2];
       unsigned char  width[2];
       unsigned char  height[2];
       char  bits_per_pixel;
       char  image_descriptor;
    } header;
    int i, color_map_size, pixels_size;
    FILE *f;
    size_t read;
    void *pixels;

    f = fopen(filename, "rb");

    if (!f) {
        fprintf(stderr, "Unable to open %s for reading\n", filename);
        return NULL;
    }

    read = fread(&header, 1, sizeof(header), f);

    if (read != sizeof(header)) {
        fprintf(stderr, "%s has incomplete tga header\n", filename);
        fclose(f);
        return NULL;
    }

    for (i = 0; i < header.id_length; ++i)
        if (getc(f) == EOF) {
            fprintf(stderr, "%s has incomplete id string\n", filename);
            fclose(f);
            return NULL;
        }

    color_map_size = le_short(header.color_map_length) * (header.color_map_depth/8);
    for (i = 0; i < color_map_size; ++i)
        if (getc(f) == EOF) {
            fprintf(stderr, "%s has incomplete color map\n", filename);
            fclose(f);
            return NULL;
        }

    *width = le_short(header.width); *height = le_short(header.height);
    pixels_size = *width * *height * (header.bits_per_pixel/8);
    pixels = malloc(pixels_size);

    read = fread(pixels, 1, pixels_size, f);

    if (read != pixels_size) {
        fprintf(stderr, "%s has incomplete image\n", filename);
        fclose(f);
        free(pixels);
        return NULL;
    }

    return pixels;
}

void *file_contents(const char *filename, GLint *length)
{
    FILE *f = fopen(filename, "r");
    void *buffer;

    if (!f) {
        fprintf(stderr, "Unable to open %s for reading\n", filename);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    *length = ftell(f);
    fseek(f, 0, SEEK_SET);

    buffer = malloc(*length+1);
    *length = fread(buffer, 1, *length, f);
    fclose(f);
    ((char*)buffer)[*length] = '\0';

    return buffer;
}

GLuint make_buffer(
    GLenum target,
    const void *buffer_data,
    GLsizei buffer_size
) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, buffer_size, buffer_data, GL_STATIC_DRAW);
    return buffer;
}

void init_buffers(res_mod *_res_mod)
{
	_res_mod->vertex_buffer =
		make_buffer(GL_ARRAY_BUFFER,
                    &_res_mod->vertex_data[0],
                    sizeof(vtx4) * _res_mod->vertex_data.size()
		);

	_res_mod->normal_buffer =
		make_buffer(GL_ARRAY_BUFFER,
                    &_res_mod->normal_data[0],
					sizeof(vtx3) * _res_mod->normal_data.size()
        );

	_res_mod->textur_buffer =
			make_buffer(GL_ARRAY_BUFFER,
                    &_res_mod->UV_data[0],
                    sizeof(vtx2) * _res_mod->UV_data.size()
        );

    _res_mod->tangent_buffer =
            make_buffer(GL_ARRAY_BUFFER,
                    &_res_mod->tangent_data[0],
                    sizeof(vtx3) * _res_mod->tangent_data.size()
        );

    _res_mod->bitangent_buffer =
            make_buffer(GL_ARRAY_BUFFER,
                    &_res_mod->bitangent_data[0],
                    sizeof(vtx3) * _res_mod->bitangent_data.size()
        );

	_res_mod->vertex_shader =
			make_shader(GL_VERTEX_SHADER,
					_res_mod->vertex_shader_path.c_str()
    );

	_res_mod->fragment_shader =
			make_shader(GL_FRAGMENT_SHADER,
					_res_mod->fragment_shader_path.c_str()
    );

	_res_mod->program
        = make_program(_res_mod->vertex_shader, _res_mod->fragment_shader);

	_res_mod->camera_matrix
        = glGetUniformLocation(_res_mod->program, "camera_matrix");

	_res_mod->world_matrix
        = glGetUniformLocation(_res_mod->program, "world_matrix");

	_res_mod->vertex =
			glGetAttribLocation(_res_mod->program, "vertex");

	_res_mod->normals =
			glGetAttribLocation(_res_mod->program, "normals");

    _res_mod->tangents =
            glGetAttribLocation(_res_mod->program, "tangents");

    _res_mod->bitangents =
            glGetAttribLocation(_res_mod->program, "bitangents");

	_res_mod->UV =
			glGetAttribLocation(_res_mod->program, "UV");

    _res_mod->normal_map = make_texture(_res_mod->normal_map_path.c_str());
    _res_mod->normal_uniform =
            glGetUniformLocation(_res_mod->program, "normal_map");

    _res_mod->colour_map = make_texture(_res_mod->colour_map_path.c_str());
    _res_mod->colour_uniform =
            glGetUniformLocation(_res_mod->program, "colour_map");




}
