#version 110

uniform sampler2D normal_map;
uniform sampler2D colour_map;

const float far  = 150.0;
const float near = 0.3;
varying vec3 NORMAL;
varying vec2 texcord;
varying mat3 TBN;

varying vec3 POSITION;


#define MAX_LIGHTS 4
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
        gl_FragColor = vec4(0);
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
         gl_FragDepth = depth;
         vec4 Ispec;
         vec3 L, R;
         vec3 E = normalize(-POSITION);

        for (int i=0; i < MAX_LIGHTS; i++)
            {
                NormalMapFactor = normalize(dot(normal, vec3(gl_LightSource[i].position.xyz - POSITION)));

                l = length(gl_LightSource[i].position.xyz - POSITION);

                L = normalize(gl_LightSource[i].position.xyz - POSITION);
                R = normalize(-reflect(L, normal));

                gl_FragColor += vec4(vec3(NormalMapFactor * gl_LightSource[i].diffuse.rgb) / l +
                                     #ifdef SPECULAR
                                     gl_LightSource[i].specular.rgb * pow(max(dot(R, E), 0.0), shininess) +
                                     #endif
                                     vec3(NormalMapFactor * texture2D(colour_map, texcord).rgb * gl_LightSource[i].ambient.rgb),
                                     texture2D(colour_map, texcord).a);
            }

}
