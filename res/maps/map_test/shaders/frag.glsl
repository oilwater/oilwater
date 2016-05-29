#version 110

uniform sampler2D normal_map;
uniform sampler2D colour_map;

const float far  = 150.0;
const float near = 0.3;
varying vec3 NORMAL;
varying vec2 texcord;
varying mat3 TBN;

varying vec3 POSITION;


#define MAX_LIGHTS 3
#define SPECULAR
const float shininess = 1.0;


float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
        vec3 normal = TBN * vec3(texture2D(normal_map, texcord));
        float NormalMapFactor;
        float l;
		float light = 0.0;
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
         gl_FragDepth = depth;

        for (int i=0; i < MAX_LIGHTS; i++)
            {
                NormalMapFactor = normalize(dot(normal, vec3(gl_LightSource[i].position.xyz - POSITION)));

                l = length(gl_LightSource[i].position.xyz - POSITION);
               
				 light += NormalMapFactor / l;

            }
	gl_FragColor = vec4(texture2D(colour_map, texcord).rgb * light,
                                     texture2D(colour_map, texcord).a);
}
