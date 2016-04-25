#version 110

attribute vec4 vertex;

attribute vec3 normals;
attribute vec3 tangents;
attribute vec3 bitangents;

attribute vec2 UV;

uniform mat4 camera_matrix;
uniform mat4 world_matrix;

varying vec2 texcord;

varying vec3 NORMAL;
varying mat3 TBN;

void main()
{
             NORMAL = (vec3(world_matrix * vec4(normals, 0)));
        vec3 TANGENT = (vec3(world_matrix * vec4(normals, 0)));
        vec3 BITANGENT = (vec3(world_matrix * vec4(normals, 0)));

        TBN = mat3(TANGENT, BITANGENT, NORMAL);

	texcord = UV;

	gl_Position = camera_matrix * world_matrix * vertex;
}
