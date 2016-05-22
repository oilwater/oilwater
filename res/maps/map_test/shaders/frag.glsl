#version 110

uniform sampler2D normal_map;
uniform sampler2D colour_map;

float far  = 150.0;
float near = 0.3;
varying vec3 NORMAL;
varying vec2 texcord;
varying mat3 TBN;

varying vec3 POSITION;


#define MAX_LIGHTS 4


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
        gl_FragColor = vec4(0);
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
         gl_FragDepth = depth;


        for (int i=0; i < MAX_LIGHTS; i++)
            {
                NormalMapFactor = clamp(dot(normal, vec3(gl_LightSource[i].position.xyz - POSITION)), 0.0, 1.0);
                l = length(gl_LightSource[i].position.xyz - POSITION);

                gl_FragColor += vec4(vec3(NormalMapFactor * texture2D(colour_map, texcord)) / l +
                                     vec3(NormalMapFactor * gl_LightSource[i].diffuse.rgb) / l,
                                     texture2D(colour_map, texcord).a);
            }

}
