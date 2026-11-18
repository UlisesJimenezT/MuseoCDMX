#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Model;

// Salas museo
enum Room {
	ROOM_LOBBY,          
	ROOM_JUGUETES,       
	ROOM_DIA_DE_MUERTOS, 
	ROOM_GASTRONOMIA,    
	ROOM_LUCHA_LIBRE,    
	ROOM_XOCHIMILCO,
	ROOM_PANTEON,
	ROOM_TRANSPORTE
};

inline const char* RoomName(Room room) {
	switch (room) {
	case ROOM_LOBBY:          return "Lobby";
	case ROOM_JUGUETES:       return "Sala 1 - Juguetes y Tradiciones";
	case ROOM_DIA_DE_MUERTOS: return "Sala 2 - Dia de Muertos";
	case ROOM_GASTRONOMIA:    return "Sala 3 - Gastronomia";
	case ROOM_LUCHA_LIBRE:    return "Sala 4 - Lucha Libre";
	case ROOM_XOCHIMILCO:     return "Sala 5 - Xochimilco";
	case ROOM_PANTEON:        return "Panteon";
	case ROOM_TRANSPORTE:     return "Sala 6 - Transporte";
	}
	return "?";
}

// Material, Phong MP, Fresnel TM
enum MaterialType {
	MAT_MATE,         
	MAT_PLASTICO,     
	MAT_TRANSLUCIDO,  
	MAT_METALICO      
};

inline const char* MaterialName(MaterialType m) {
	switch (m) {
	case MAT_MATE:        return "Mate (Phong)";
	case MAT_PLASTICO:    return "Plastico (Phong)";
	case MAT_TRANSLUCIDO: return "Translucido (Fresnel)";
	case MAT_METALICO:    return "Metalico (Fresnel)";
	}
	return "?";
}

struct CatalogEntry {
	const char*  name;    
	const char*  file;     
	Room         room;
	glm::vec3    position; 
	glm::vec3    rotation; 
	glm::vec3    scale;
	MaterialType material; 
};

// pieza en museo
struct SceneObject {
	std::string  name;
	Model*       model = nullptr;
	glm::vec3    position = glm::vec3(0.0f);
	glm::vec3    rotation = glm::vec3(0.0f); 
	glm::vec3    scale = glm::vec3(1.0f);
	Room         room = ROOM_LOBBY;
	MaterialType material = MAT_MATE;

	// Animacion, -1 ninguna, Phase desfase entre iguales
	glm::vec3    basePosition = glm::vec3(0.0f);
	glm::vec3    baseRotation = glm::vec3(0.0f);
	glm::vec3    baseScale = glm::vec3(1.0f);
	int          animSimple = -1; 
	int          animKeyframe = -1;
	int          animProcedural = -1;
	float        animPhase = 0.0f;
	float        animTime = 0.0f;     // reloj propio de la animacion
	bool         animPaused = false;  // la tecla P la pausa o la reanuda  

	// Interaccion, off m que movio, yaw grados que giro, scale escalado, radius anillo
	bool         interactive = false;
	glm::vec3    userOffset = glm::vec3(0.0f);  
	float        userYaw = 0.0f;               
	float        userScale = 1.0f;              
	float        ringRadius = 0.0f;             
};

// Matriz de modelo
inline glm::mat4 GetModelMatrix(const SceneObject& obj) {
	glm::mat4 m = glm::mat4(1.0f);
	m = glm::translate(m, obj.position);
	m = glm::rotate(m, glm::radians(obj.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m = glm::rotate(m, glm::radians(obj.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m = glm::rotate(m, glm::radians(obj.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m = glm::scale(m, obj.scale);
	return m;
}

#endif
