#version 330 core
layout (location = 0) in vec3  aPos;
layout (location = 1) in vec3  aNormal;
layout (location = 2) in vec2  aTexCoords;
layout (location = 3) in vec3  tangent;
layout (location = 4) in vec3  bitangent;
layout (location = 5) in vec4  boneIds;      // protagonista: 4 huesos por vértice
layout (location = 8) in vec4  boneWeights;

out vec2 TexCoords;
out vec3 ex_N;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 eye;

uniform bool useBones;
uniform mat4 gBones[100];

out vec3 vertexPosition_cameraspace;
out vec3 Normal_cameraspace;
out vec3 LocalPos;   // proyección triplanar
out vec3 worldPosition;   // Fresnel
out vec3 worldNormal;

void main()
{

    // Huesos: cada vértice se mueve con el promedio de sus huesos
    mat4 skin = mat4(1.0);
    if (useBones)
        skin = gBones[int(boneIds.x)] * boneWeights.x + gBones[int(boneIds.y)] * boneWeights.y +
               gBones[int(boneIds.z)] * boneWeights.z + gBones[int(boneIds.w)] * boneWeights.w;
    vec3 N = mat3(skin) * aNormal;

    vec4 PosL = skin * vec4(aPos, 1.0f);

    gl_Position = projection * view * model * PosL;

    TexCoords = aTexCoords;

    vertexPosition_cameraspace = ( view * model * PosL).xyz;

    Normal_cameraspace = ( view * model * vec4(N,0)).xyz;

    ex_N = N;
    LocalPos = aPos;
    worldPosition = (model * PosL).xyz;
    worldNormal = mat3(model) * N;
}