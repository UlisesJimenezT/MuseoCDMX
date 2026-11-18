#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 ex_N;

in vec3 vertexPosition_cameraspace;
in vec3 Normal_cameraspace;

uniform mat4 view;

uniform sampler2D texture_diffuse1;

// color material
uniform int  hasDiffuseTexture;
uniform vec4 MeshDiffuseColor;

uniform int   emissive;
uniform int   triplanar;
uniform float triplanarScale;   // repeticiones foto 
in vec3 LocalPos;

vec4 TriplanarSample() {
    vec3 w = pow(abs(normalize(ex_N)), vec3(4.0));
    w /= (w.x + w.y + w.z + 1e-5);
    vec3 p = LocalPos * triplanarScale;
    return texture(texture_diffuse1, p.zy) * w.x + texture(texture_diffuse1, p.xz) * w.y + texture(texture_diffuse1, p.xy) * w.z;
}

uniform vec4 MaterialAmbientColor;
uniform vec4 MaterialDiffuseColor;
uniform vec4 MaterialSpecularColor;
uniform float transparency;

#define MAX_LIGHTS 40
uniform int numLights;

uniform struct Light {
   vec3  Position;
   vec3  Direction;
   vec4  Color;
   vec4  Power;
   int   alphaIndex;
   float distance; 
} allLights[MAX_LIGHTS];

// luz luna 
uniform vec3 moonDirection;   
uniform vec3 moonColor;
uniform vec3 nightAmbient;

// materiales
uniform int materialType;
// cielo y cámara
uniform samplerCube cubetex;
uniform vec3 eye;
in vec3 worldPosition;
in vec3 worldNormal;

//brillo 
vec3  matSpecular;     // color
float matShininess;    
vec3  specularSum;     // brillo de todas las luces

vec4 ApplyLight(Light light, vec3 N, vec3 L, vec3 E, float d) {

    float r = light.distance;
    float attenuation = pow(max(1.0 - d / r, 0.0), 2.0);

    // componente ambiental
    vec4 K_a = MaterialAmbientColor * light.Color;

    // componente difusa
    float cosTheta = clamp( dot( N,L ), 0,1 );
    vec4 K_d = MaterialDiffuseColor * light.Color * cosTheta;

    // componente especular 
    vec3 R = reflect(-L,N);
    float cosAlpha = clamp( dot( E,R ), 0,1 );
    specularSum += matSpecular * light.Color.rgb * pow(cosAlpha, matShininess) * light.Power.rgb * attenuation;

    vec4 l_contribution = (K_a + K_d) * light.Power * attenuation;

    return l_contribution;
}

//coeficiente Fresnel 
float FresnelCoefficient(vec3 I, vec3 N, float bias, float scale, float power) {
    return clamp(bias + scale * pow(1.0 + dot(I, N), power), 0.0, 1.0);
}

void main()
{
    // componente difusa
    vec3 n = normalize( Normal_cameraspace );

    if (dot(n, -vertexPosition_cameraspace) < 0.0)
        n = -n;

    vec4 texel = MeshDiffuseColor;
    if (hasDiffuseTexture == 1) {
        vec4 t = (triplanar == 1) ? TriplanarSample() : texture(texture_diffuse1, TexCoords);
        if (t.a < 0.12)
            discard;
        texel = vec4(t.rgb * MeshDiffuseColor.rgb, t.a * MeshDiffuseColor.a);
    }

    if (emissive == 1) {
        FragColor = vec4(texel.rgb, texel.a);
        return;
    }

    // Phong según material
    if (materialType == 1) {          // plástico
        matSpecular = vec3(0.6);  matShininess = 64.0;
    } else if (materialType == 2) {   // translúcido
        matSpecular = vec3(0.8);  matShininess = 96.0;
    } else if (materialType == 3) {   // metálico
        matSpecular = texel.rgb;  matShininess = 96.0;
    } else {                          // mate
        matSpecular = vec3(0.05); matShininess = 8.0;
    }
    specularSum = vec3(0.0);

    vec4 ex_color = vec4(0.0f);

    for(int i = 0; i < numLights; ++i){

        vec3 EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;
        vec3 LightPosition_cameraspace = ( view * vec4(allLights[i].Position,1)).xyz;
        vec3 LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
        vec3 e = normalize(EyeDirection_cameraspace);
        vec3 l = normalize( LightDirection_cameraspace );
        float d = length( LightDirection_cameraspace );
        ex_color += ApplyLight(allLights[i], n, l, e, d);
    }

    // luna 
    vec3 moonL = normalize( (view * vec4(-moonDirection, 0.0)).xyz );
    ex_color.rgb += nightAmbient + MaterialDiffuseColor.rgb * moonColor * clamp(dot(n, moonL), 0.0, 1.0);

    // Phong mate y plástico
    vec3  color = texel.rgb * ex_color.rgb + specularSum;
    float alpha = texel.a * transparency;

    // Fresnel translúcido y metálico
    if (materialType == 2 || materialType == 3) {
        vec3 I = normalize(worldPosition - eye);
        vec3 N = normalize(worldNormal);
        if (dot(N, -I) < 0.0)
            N = -N;
        vec3 reflected = texture(cubetex, reflect(I, N)).rgb;

        if (materialType == 3) {
            // Metal
            float coef = FresnelCoefficient(I, N, 0.6, 0.4, 3.0);
            vec3 reflection = (reflected * 0.8 + ex_color.rgb * 0.6) * texel.rgb;
            color = mix(texel.rgb * ex_color.rgb * 0.35, reflection, coef) + specularSum;
        } else {
            // Vidrio y agua
            float coef = FresnelCoefficient(I, N, 0.05, 0.95, 5.0);
            color += reflected * coef;
            alpha = mix(alpha, 1.0, coef);
        }
    }

    FragColor = vec4(color, alpha);
}
