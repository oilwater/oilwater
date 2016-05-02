/*
 * model.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: rainautumn
 */
#include "model.h"

#include <fstream>
#include <iostream>
#include <sstream>

Model::Model(char *path)
{
	// TODO Auto-generated constructor stub

    Position();

	stringstream model_path;

	stringstream vertex_path;
	stringstream fragment_path;

	vertex_path << path << "/shaders/vert.glsl";
	fragment_path << path << "/shaders/frag.glsl";

	_res_mod.vertex_shader_path = vertex_path.str();
	_res_mod.fragment_shader_path = fragment_path.str();

	stringstream colour_path;
	stringstream normal_path;

	colour_path << path << "/textures/colour.tga";
	normal_path << path << "/textures/normal.tga";

	_res_mod.colour_map_path = colour_path.str();
	_res_mod.normal_map_path = normal_path.str();

	model_path << path << "/model.obj";

    _res_pos.position.drop();
    _res_pos.angular_position.drop();

	parser_model((char*)model_path.str().c_str());
}

Model::~Model()
{
	// TODO Auto-generated destructor stub
}

void Model::render()
{
    mtx4 world_matrix = get_position_matrix();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _res_mod.colour_map);
    glUniform1i(_res_mod.colour_uniform, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _res_mod.normal_map);
    glUniform1i(_res_mod.normal_uniform, 1);

    glUniformMatrix4fv (_res_mod.camera_matrix, 1, GL_TRUE, &camera->get_matrix().m[0][0]);
    glUniformMatrix4fv (_res_mod.world_matrix, 1, GL_TRUE, &world_matrix.m[0][0]);

    glUseProgram(_res_mod.program);

    glBindBuffer(GL_ARRAY_BUFFER, _res_mod.vertex_buffer);
    glVertexAttribPointer(_res_mod.vertex, 4, GL_FLOAT, GL_FALSE, sizeof(vtx4), (const GLvoid*)0);
    glEnableVertexAttribArray(_res_mod.vertex);

    glBindBuffer(GL_ARRAY_BUFFER, _res_mod.textur_buffer);
    glVertexAttribPointer(_res_mod.UV, 2, GL_FLOAT, GL_FALSE, sizeof(vtx2), 0);
    glEnableVertexAttribArray(_res_mod.UV);

    glBindBuffer(GL_ARRAY_BUFFER, _res_mod.normal_buffer);
    glVertexAttribPointer(_res_mod.normals, 3, GL_FLOAT, GL_FALSE, sizeof(vtx3), 0);
    glEnableVertexAttribArray(_res_mod.normals);

    glBindBuffer(GL_ARRAY_BUFFER, _res_mod.tangent_buffer);
    glVertexAttribPointer(_res_mod.tangents, 3, GL_FLOAT, GL_FALSE, sizeof(vtx3), 0);
    glEnableVertexAttribArray(_res_mod.tangents);

    glBindBuffer(GL_ARRAY_BUFFER, _res_mod.bitangent_buffer);
    glVertexAttribPointer(_res_mod.bitangents, 3, GL_FLOAT, GL_FALSE, sizeof(vtx3), 0);
    glEnableVertexAttribArray(_res_mod.bitangents);

    glDrawArrays(GL_TRIANGLES,0, _res_mod.element_len);

}

void Model::init_camera(Camera *_camera)
{
    camera = _camera;
}

void Model::parser_model(char *path)
{
	ifstream filein;

    string vert_array;
    string norm_array;
    string text_array;

    string elem_array_v;
    string elem_array_n;
    string elem_array_t;


    unsigned int num_of_vertex = 0;
    unsigned int num_of_elements = 0;
    unsigned int num_of_normal = 0;
    unsigned int num_of_texture = 0;

	filein.open(path);

	if(!filein.is_open())
		{
			cout << "Unable to open vertex file "<< path << " for reading"  << endl;
	        _res_mod.element_len = 0;
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
	    else if(key == string("vn "))
	        {
	            key = test.substr(2, test.length());
	            num_of_normal++;
	            norm_array += key;
	        }
	    else if(key == string("vt "))
	        {
	            key = test.substr(2, test.length());
	            num_of_texture++;
	            text_array += key;
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


	                oneblock = key.substr(0, key.find('/'));
	                if(oneblock != "")
	                	elem_array_t += oneblock + ' ';
	                else
	                	elem_array_t += "1 ";
	                key = key.substr(key.find('/') + 1, key.length());


	                oneblock = key.substr(0, key.find(' '));
	                if(oneblock != "")
	                	elem_array_n += oneblock + ' ';
	                else
	                	elem_array_n += "1 ";

	                if(key.find(' ') > key.length())
	                    break;
	                key = key.substr(key.find(' ') + 1, key.length());
	             }
	        }
	    }
    filein.close();

    _res_mod.element_len = num_of_elements;

    float *buf_vertex_data = new float [num_of_vertex * 4];
    float *buf_normal_data = new float [num_of_normal * 3];
    float *buf_texture_data = new float [num_of_texture * 2];

    unsigned int *buf_vertex_element = new unsigned int [num_of_elements];
    unsigned int *buf_normal_element = new unsigned int [num_of_elements];
    unsigned int *buf_texture_element = new unsigned int [num_of_elements];


    istringstream vertex_strim(vert_array);
    istringstream texture_strim(text_array);
    istringstream normal_strim(norm_array);

    istringstream element_t_strim(elem_array_t);
    istringstream element_n_strim(elem_array_n);
    istringstream element_v_strim(elem_array_v);


    //���� ���������� ���� ���������������� ������������.. ���������� �� ������������������!


    for(unsigned int k = 0; k < num_of_vertex * 4 ; k++)
    {
        vertex_strim >> buf_vertex_data[k];
    }

    for(unsigned int k = 0; k < num_of_normal * 3 ; k++)
    {
        normal_strim >> buf_normal_data[k];
    }

    for(unsigned int k = 0; k < num_of_texture * 2 ; k++)
    {
        texture_strim >> buf_texture_data[k];
    }

    for(unsigned int n = 0; n < num_of_elements ; n++)
    {
        element_v_strim >> buf_vertex_element[n];
        element_t_strim >> buf_texture_element[n];
        element_n_strim >> buf_normal_element[n];

        buf_vertex_element[n]--;
        buf_texture_element[n]--;
        buf_normal_element[n]--;

        vtx4 buf4;
        buf4.init(buf_vertex_data[buf_vertex_element[n] * 4     ],
                  buf_vertex_data[buf_vertex_element[n] * 4  + 1],
                  buf_vertex_data[buf_vertex_element[n] * 4  + 2],
                  buf_vertex_data[buf_vertex_element[n] * 4  + 3]);

        _res_mod.vertex_data.push_back(buf4);

        vtx3 buf3;
        buf3.init(buf_normal_data[buf_normal_element[n] * 3     ],
                  buf_normal_data[buf_normal_element[n] * 3  + 1],
                  buf_normal_data[buf_normal_element[n] * 3  + 2]);
        _res_mod.normal_data.push_back(buf3);

        vtx2 buf2;
        buf2.init(buf_texture_data[buf_texture_element[n] * 2    ],
                  buf_texture_data[buf_texture_element[n] * 2 + 1]);
        _res_mod.UV_data.push_back(buf2);
    }

    delete[] buf_normal_data;
    delete[] buf_normal_element;
    delete[] buf_texture_data;
    delete[] buf_texture_element;
    delete[] buf_vertex_data;
    delete[] buf_vertex_element;

    calc_tangents();

    return;
}

void Model::calc_tangents()
{
    for(unsigned int i = 0; i <_res_mod.element_len; i+=3)
    {
        vtx4 edge1 = _res_mod.vertex_data[i+1] -_res_mod.vertex_data[i];
        vtx4 edge2 = _res_mod.vertex_data[i+2] -_res_mod.vertex_data[i];

        vtx2 dUV1 = _res_mod.UV_data[i+1] - _res_mod.UV_data[i];
        vtx2 dUV2 = _res_mod.UV_data[i+2] - _res_mod.UV_data[i];

        float f = 1 / (dUV1.v[0] * dUV2.v[1] - dUV2.v[0] * dUV1.v[1]);

        vtx3 tangent_buf;
        vtx3 bitangent_buf;

        tangent_buf.init  (f * (dUV2.v[1] * edge1.v[0] - dUV1.v[1] * edge2.v[0]),
                           f * (dUV2.v[1] * edge1.v[1] - dUV1.v[1] * edge2.v[1]),
                           f * (dUV2.v[1] * edge1.v[2] - dUV1.v[1] * edge2.v[2])
                      );

        bitangent_buf.init(f * (-dUV2.v[0] * edge1.v[0] - dUV1.v[0] * edge2.v[0]),
                           f * (-dUV2.v[0] * edge1.v[1] - dUV1.v[0] * edge2.v[1]),
                           f * (-dUV2.v[0] * edge1.v[2] - dUV1.v[0] * edge2.v[2])
                      );

        for(int k = 0; k < 3; k++)
        {
            _res_mod.bitangent_data.push_back(bitangent_buf);
            _res_mod.tangent_data.push_back  (tangent_buf);
        }
    }

}

