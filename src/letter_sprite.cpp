#include "letter_sprite.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Letter_sprite::Letter_sprite(char *path)
{
    Position();

    type = MODEL;

    stringstream model_path;

    stringstream vertex_path;
    stringstream fragment_path;

    vertex_path << path << "/shaders/vert.glsl";
    fragment_path << path << "/shaders/frag.glsl";

    _res_let.vertex_shader_path = vertex_path.str();
    _res_let.fragment_shader_path = fragment_path.str();

    model_path << path << "/model.obj";

    parser_model((char*)model_path.str().c_str());
}

void Letter_sprite::render()
{
    mtx4 world_matrix;
    glUseProgram(_res_let.program);

    switch (type) {
    case MODEL:
            world_matrix = get_position_matrix();
            glUniformMatrix4fv (_res_let.camera_matrix, 1, GL_TRUE, &camera->get_matrix().m[0][0]);
        break;
    case MODEL_SPRITE:
            _res_pos.angular_position.init(0, -camera->_res_pos.angular_position.v[1],0);
            world_matrix = get_position_matrix_sprite();
            glUniformMatrix4fv (_res_let.camera_matrix, 1, GL_TRUE, &camera->get_matrix_sprite().m[0][0]);
        break;
    case MODEL_SPRITE_HP:
            world_matrix = get_position_matrix();
            glUniformMatrix4fv (_res_let.camera_matrix, 1, GL_TRUE, &camera->get_matrix_hp().m[0][0]);
        break;
    default:
        break;
    }

    glUniformMatrix4fv (_res_let.world_matrix, 1, GL_TRUE, &world_matrix.m[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, _res_let.vertex_buffer);
    glVertexAttribPointer(_res_let.vertex, 4, GL_FLOAT, GL_FALSE, sizeof(vtx4), (const GLvoid*)0);
    glEnableVertexAttribArray(_res_let.vertex);

    glDrawArrays(GL_TRIANGLES,0, _res_let.element_len);

}

void Letter_sprite::parser_model(char *path)
{
    ifstream filein;

    string vert_array;

    string elem_array_v;

    unsigned int num_of_vertex = 0;
    unsigned int num_of_elements = 0;

    filein.open(path);

    if(!filein.is_open())
        {
            cout << "Unable to open vertex file "<< path << " for reading"  << endl;
            _res_let.element_len = 0;
            return;
        }
    for(string test; getline(filein, test); )
        {
        string key = test.substr(0, test.find(' ')+1);
        if(key == string("v "))
            {
                key = test.substr(2, test.length());
                num_of_vertex++;
                vert_array += key + " 1.0 ";
            }
        else if(key == string("f "))
            {
                key = test.substr(2, test.length());
                while(1)
                {
                    num_of_elements++;

                    string oneblock = key.substr(0, key.find('/'));
                    elem_array_v += oneblock + ' ';
                    key = key.substr(key.find('/') + 1, key.length());



                    key = key.substr(key.find('/') + 1, key.length());


                    oneblock = key.substr(0, key.find(' '));
                    if(key.find(' ') > key.length())
                        break;
                    key = key.substr(key.find(' ') + 1, key.length());
                 }
            }
        }
    filein.close();

    _res_let.element_len = num_of_elements;

    float *buf_vertex_data = new float [num_of_vertex * 4];
    unsigned int *buf_vertex_element = new unsigned int [num_of_elements];


    istringstream vertex_strim(vert_array);

    istringstream element_v_strim(elem_array_v);


    for(unsigned int k = 0; k < num_of_vertex * 4 ; k++)
    {
        vertex_strim >> buf_vertex_data[k];
    }

    for(unsigned int n = 0; n < num_of_elements ; n++)
    {
        element_v_strim >> buf_vertex_element[n];

        buf_vertex_element[n]--;

        vtx4 buf4;
        buf4.init(buf_vertex_data[buf_vertex_element[n] * 4     ],
                  buf_vertex_data[buf_vertex_element[n] * 4  + 1],
                  buf_vertex_data[buf_vertex_element[n] * 4  + 2],
                  buf_vertex_data[buf_vertex_element[n] * 4  + 3]);

        _res_let.vertex_data.push_back(buf4);

    }

    delete[] buf_vertex_data;
    delete[] buf_vertex_element;

    return;
}
