#ifndef ANIMACIONES_MUSEO_H
#define ANIMACIONES_MUSEO_H

#include <cmath>
#include <cstring>

#include <glm/glm.hpp>

#include <sceneobject.h>

// Animaciones 

const float PI_F = 3.14159265f;

// Simples

enum SimpleAnimKind { ANIM_GIRO, ANIM_BALANCEO, ANIM_SALTO };
//piece nombre, amount grados/metros
struct SimpleAnimation {
	const char*    piece;   
	SimpleAnimKind kind;
	glm::vec3      axis;
	float          amount; 
	float          speed;   
};

const SimpleAnimation kAnimacionesSimples[] = {
	{ "Trompo",               ANIM_GIRO,     {0.0f, 1.0f, 0.0f},  0.0f,  540.0f },  
	{ "Pirinola",             ANIM_GIRO,     {0.0f, 1.0f, 0.0f},  0.0f,  360.0f },
	{ "Pinata",               ANIM_BALANCEO, {0.0f, 0.0f, 1.0f}, 12.0f,    1.6f },  
	{ "Yoyo",                 ANIM_SALTO,    {0.0f, 1.0f, 0.0f},  0.30f,   2.5f },
	{ "Reflector",            ANIM_BALANCEO, {0.0f, 1.0f, 0.0f}, 35.0f,    0.6f },  
	{ "Canoa",                ANIM_BALANCEO, {1.0f, 0.0f, 0.0f},  4.0f,    1.3f },  
	{ "Caballito de madera",  ANIM_BALANCEO, {0.0f, 0.0f, 1.0f},  8.0f,    2.0f }, 
	{ "Rana de Xochimilco",   ANIM_SALTO,    {0.0f, 1.0f, 0.0f},  0.12f,   3.0f },
	{ "Papel picado",         ANIM_BALANCEO, {1.0f, 0.0f, 0.0f},  6.0f,    1.1f }, 
	{ "Sonaja de calavera",   ANIM_BALANCEO, {0.0f, 0.0f, 1.0f}, 15.0f,    9.0f },
	{ "Matracas",             ANIM_GIRO,     {0.0f, 1.0f, 0.0f},  0.0f,  300.0f },
	{ "Campana de difuntos",  ANIM_BALANCEO, {0.0f, 0.0f, 1.0f}, 15.0f,    1.5f },
};

inline void ApplySimpleAnimation(SceneObject& obj, const SimpleAnimation& anim, float t) {
	switch (anim.kind) {
	case ANIM_GIRO:
		obj.rotation = obj.baseRotation + anim.axis * std::fmod(anim.speed * t, 360.0f);
		break;
	case ANIM_BALANCEO:
		obj.rotation = obj.baseRotation + anim.axis * anim.amount * std::sin(anim.speed * t);
		break;
	case ANIM_SALTO:
		obj.position = obj.basePosition + anim.axis * anim.amount * std::fabs(std::sin(anim.speed * t));
		break;
	}
}

// Keyframes
struct Keyframe {
	float     time;      
	glm::vec3 position;  
	glm::vec3 rotation;  
};

// Xolo recorre pasillo
const Keyframe kKeysXolo[] = {
	{  0.0f, {0.0f, 0.0f, 0.0f}, {0.0f, -90.0f, 0.0f} },
	{  5.5f, {0.0f, 0.0f, 8.0f}, {0.0f, -90.0f, 0.0f} },
	{  6.3f, {0.0f, 0.0f, 8.0f}, {0.0f,  90.0f, 0.0f} },
	{ 11.8f, {0.0f, 0.0f, 0.0f}, {0.0f,  90.0f, 0.0f} },
	{ 12.6f, {0.0f, 0.0f, 0.0f}, {0.0f, 270.0f, 0.0f} },
};

// Luchador salta 
const Keyframe kKeysLuchadorTecnico[] = {
	{ 0.0f, { 0.00f, 0.0f, 0.0f}, { 0.0f, 0.0f, 0.0f} },
	{ 1.0f, {-1.20f, 0.0f, 0.0f}, { 0.0f, 0.0f, 0.0f} },
	{ 2.5f, {-0.40f, 0.9f, 0.0f}, {25.0f, 0.0f, 0.0f} },
	{ 3.1f, { 0.25f, 0.0f, 0.0f}, {20.0f, 0.0f, 0.0f} },
	{ 4.0f, { 0.00f, 0.0f, 0.0f}, { 0.0f, 0.0f, 0.0f} },
	{ 8.0f, { 0.00f, 0.0f, 0.0f}, { 0.0f, 0.0f, 0.0f} },
};

// Luchador cae 
const Keyframe kKeysLuchadorRudo[] = {
	{ 0.0f, {0.0f, 0.00f, 0.0f}, { 0.0f, 0.0f,  0.0f} },
	{ 3.0f, {0.0f, 0.00f, 0.0f}, { 0.0f, 0.0f,  0.0f} },
	{ 3.9f, {0.3f, 0.12f, 0.0f}, { 0.0f, 0.0f, 85.0f} },
	{ 5.8f, {0.3f, 0.12f, 0.0f}, { 0.0f, 0.0f, 85.0f} },
	{ 7.0f, {0.0f, 0.00f, 0.0f}, { 0.0f, 0.0f,  0.0f} },
	{ 8.0f, {0.0f, 0.00f, 0.0f}, { 0.0f, 0.0f,  0.0f} },
};

// Trajinera avanza y regresa
const Keyframe kKeysTrajinera[] = {
	{  0.0f, { 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
	{  6.0f, {-2.2f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
	{  9.0f, {-2.2f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
	{ 15.0f, { 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
};

// Garza gira y picotea 
const Keyframe kKeysGarza[] = {
	{ 0.0f, {0.0f, 0.0f, 0.0f}, { 0.0f,  0.0f, 0.0f} },
	{ 1.0f, {0.0f, 0.0f, 0.0f}, { 0.0f, 40.0f, 0.0f} },
	{ 1.6f, {0.0f, 0.0f, 0.0f}, {35.0f, 40.0f, 0.0f} },
	{ 2.4f, {0.0f, 0.0f, 0.0f}, { 0.0f, 40.0f, 0.0f} },
	{ 4.0f, {0.0f, 0.0f, 0.0f}, { 0.0f,  0.0f, 0.0f} },
};

// Catrina reverencia
const Keyframe kKeysCatrina[] = {
	{ 0.0f, {0.0f, 0.0f, 0.0f}, { 0.0f,  0.0f, 0.0f} },
	{ 1.5f, {0.0f, 0.0f, 0.0f}, { 0.0f, 30.0f, 0.0f} },
	{ 2.5f, {0.0f, 0.0f, 0.0f}, {20.0f, 30.0f, 0.0f} },
	{ 4.0f, {0.0f, 0.0f, 0.0f}, { 0.0f,  0.0f, 0.0f} },
	{ 6.0f, {0.0f, 0.0f, 0.0f}, { 0.0f,  0.0f, 0.0f} },
};

// Tecolote voltea a los lados
const Keyframe kKeysTecolote[] = {
	{ 0.0f, {0.0f, 0.0f, 0.0f}, {0.0f,   0.0f, 0.0f} },
	{ 1.0f, {0.0f, 0.0f, 0.0f}, {0.0f,  50.0f, 0.0f} },
	{ 2.5f, {0.0f, 0.0f, 0.0f}, {0.0f,  50.0f, 0.0f} },
	{ 3.5f, {0.0f, 0.0f, 0.0f}, {0.0f, -50.0f, 0.0f} },
	{ 5.0f, {0.0f, 0.0f, 0.0f}, {0.0f, -50.0f, 0.0f} },
	{ 6.0f, {0.0f, 0.0f, 0.0f}, {0.0f,   0.0f, 0.0f} },
};

struct KeyframeAnimation {
	const char*     piece;
	const Keyframe* keys;
	int             numKeys;
};

#define KEYS(k) k, (int)(sizeof(k) / sizeof(k[0]))
const KeyframeAnimation kAnimacionesKeyframes[] = {
	{ "Xoloitzcuintle",        KEYS(kKeysXolo) },
	{ "Luchador 1 (tecnico)",  KEYS(kKeysLuchadorTecnico) },
	{ "Luchador 2 (rudo)",     KEYS(kKeysLuchadorRudo) },
	{ "Trajinera",             KEYS(kKeysTrajinera) },
	{ "Garza",                 KEYS(kKeysGarza) },
	{ "Catrina",               KEYS(kKeysCatrina) },
	{ "Tecolote alebrije",     KEYS(kKeysTecolote) },
};
#undef KEYS

inline void InterpolateKeyframes(const Keyframe* keys, int numKeys, float t, glm::vec3& position, glm::vec3& rotation) {
	float duration = keys[numKeys - 1].time;
	t = std::fmod(t, duration);
	for (int i = 0; i < numKeys - 1; i++) {
		if (t <= keys[i + 1].time) {
			float f = (t - keys[i].time) / (keys[i + 1].time - keys[i].time);
			position = glm::mix(keys[i].position, keys[i + 1].position, f);
			rotation = glm::mix(keys[i].rotation, keys[i + 1].rotation, f);
			return;
		}
	}
	position = keys[numKeys - 1].position;
	rotation = keys[numKeys - 1].rotation;
}

// Procedurales
enum ProceduralKind { PROC_MARIPOSA, PROC_CARPA, PROC_AVION, PROC_CATRIN, PROC_MARIONETA,
                      PROC_NENUFARES, PROC_BARQUITO };

struct ProceduralAnimation {
	const char*    prefix;
	ProceduralKind kind;
};

const ProceduralAnimation kAnimacionesProcedurales[] = {
	{ "Mariposa monarca",  PROC_MARIPOSA },
	{ "Carpa",             PROC_CARPA },
	{ "Avion de juguete",  PROC_AVION },
	{ "Catrin de levita",  PROC_CATRIN },
	{ "Marioneta",         PROC_MARIONETA },
	{ "Nenufares",         PROC_NENUFARES },
	{ "Barquito de juguete", PROC_BARQUITO },
};

inline float HeadingDegrees(float dx, float dz) {
	return glm::degrees(std::atan2(dx, dz));
}

// Mariposas vuelo
inline void AnimateButterfly(SceneObject& obj, float t) {
	float angle = obj.animPhase + 0.35f * t;
	obj.position.x = 4.0f * std::cos(angle);
	obj.position.z = -4.0f * std::sin(angle);
	obj.position.y = obj.basePosition.y + 0.3f * std::sin(1.7f * t);// mira hacia donde vuela
	obj.rotation.y = glm::degrees(angle);
	obj.scale.x = obj.baseScale.x * (0.25f + 0.75f * std::fabs(std::cos(12.0f * t)));
}

// Carpa nado
inline void AnimateFish(SceneObject& obj, float t) {
	float angle = 0.8f * t;
	obj.position.x = obj.basePosition.x + 0.35f * std::cos(angle);
	obj.position.z = obj.basePosition.z - 0.35f * std::sin(angle);
	obj.rotation.y = glm::degrees(angle) - 180.0f + 15.0f * std::sin(8.0f * t);
}

// Avion giro
inline void AnimateToyPlane(SceneObject& obj, float t) {
	obj.rotation.y = obj.baseRotation.y - std::fmod(250.0f * t, 360.0f);
	obj.rotation.x = obj.baseRotation.x + 23.0f;
}

// Catrin voltea
inline void AnimateCatrin(SceneObject& obj, const glm::vec3& visitor) {
	glm::vec3 d = visitor - obj.basePosition;
	float target = 0.0f;
	if (glm::length(glm::vec2(d.x, d.z)) < 6.0f) {
		float diff = HeadingDegrees(d.x, d.z) - obj.baseRotation.y;
		diff = std::fmod(diff + 540.0f, 360.0f) - 180.0f;  
		target = glm::clamp(diff, -60.0f, 60.0f);
	}
	obj.rotation.y = obj.baseRotation.y + target;
}

// Marioneta columpia
inline void AnimatePuppet(SceneObject& obj, float t) {
	obj.rotation.z = obj.baseRotation.z + 18.0f * std::sin(3.7f * t);
}

// Nenufares flotan
inline void AnimateLilies(SceneObject& obj, float t) {
	obj.rotation.y = obj.baseRotation.y + 25.0f * std::sin(0.2f * t);
}

// Movimiento barquito 
inline void AnimateToyBoat(SceneObject& obj, float t) {
	obj.rotation.z = obj.baseRotation.z + 6.0f * std::sin(1.3f * t);
}

inline void ApplyProceduralAnimation(SceneObject& obj, ProceduralKind kind, float t, const glm::vec3& visitor) {
	switch (kind) {
	case PROC_MARIPOSA:   AnimateButterfly(obj, t); break;
	case PROC_CARPA:      AnimateFish(obj, t); break;
	case PROC_AVION:      AnimateToyPlane(obj, t); break;
	case PROC_CATRIN:     AnimateCatrin(obj, visitor); break;
	case PROC_MARIONETA:  AnimatePuppet(obj, t); break;
	case PROC_NENUFARES:  AnimateLilies(obj, t); break;
	case PROC_BARQUITO:   AnimateToyBoat(obj, t); break;
	}
}

// Parpadeo flamas
inline float FlameFlicker(float amplitude, float t, float phase) {
	return 1.0f + amplitude * std::sin(9.7f * t + phase);
}

#endif
