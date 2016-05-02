#version 110

uniform sampler2D normal_map;
uniform sampler2D colour_map;

float far  = 150.0; 
float near = 1.0; 

varying vec3 NORMAL;
varying vec2 texcord;
varying mat3 TBN;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
        vec3 normal = TBN * vec3(texture2D(normal_map, texcord));
        float NormalMapFactor = dot(normal, vec3(0.3, 0.1, -0.6));
	float depth = LinearizeDepth(gl_FragCoord.z) / far; 
            gl_FragDepth = depth;

            gl_FragColor = vec4(vec3(NormalMapFactor * texture2D(colour_map, texcord)),  texture2D(colour_map, texcord).a);
}
