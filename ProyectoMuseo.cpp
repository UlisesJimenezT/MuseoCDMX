/*
 Proyecto Final - Museo interactivo de la Ciudad de Mexico
 Escobar Diaz Victor Manuel
 Hernandez Rubio Josue
 Jimenez Torres Edgar Ulises
 Reyes Vazquez Fernando
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <cmath>

// ubicar la carpeta del .exe en windows
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// OpenGL (GLAD), ventana (GLFW) y matemáticas (GLM)
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Clases
#include <shader_m.h>
#include <camera.h>
#include <model.h>
#include <animatedmodel.h>
#include <material.h>
#include <light.h>
#include <cubemap.h>

// Museo
#include <sceneobject.h>
#include <catalogo_museo.h>
#include <animaciones_museo.h>
#include <interacciones_museo.h>

// Funciones
bool Start();
bool Update();
void Render();

// Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// Museo
void LoadMuseum();
void LoadPlayer();
Model* LoadModelCached(const std::string& path);
void DrawSceneObject(const SceneObject& obj, Shader* shader, bool translucent);
void ToggleFullscreen();
void UpdateWindowTitle();
void DrawPlayer(Shader* shader);
void MovePlayer(GLFWwindow* window);
void MoveFreeCamera(GLFWwindow* window);
void UpdateCameras();
void SetCameraMode(int mode);
void AssignAnimations();
void UpdateAnimations();
void AssignInteractions();
SceneObject* FindSelectablePiece();
void UpdateInteraction(GLFWwindow* window);
void ApplyInteractions();
void DrawInteractionRings(Shader* shader);

// Globales
GLFWwindow* window;

// Tamaño ventana
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// Tamaño actual
int  windowWidth = SCR_WIDTH;
int  windowHeight = SCR_HEIGHT;
bool fullscreen = false;
bool fullscreenKeyDown = false;
int  windowedX = 100, windowedY = 100; 

// Cámaras 
// F1 1a persona, F2 3a persona, F3 libre
enum CameraMode {
	CAM_PRIMERA_PERSONA,
	CAM_TERCERA_PERSONA,
	CAM_LIBRE
};
int activeCamera = CAM_PRIMERA_PERSONA;

Camera camera;      
Camera camera3rd;   
Camera cameraFree;  

const float EYE_HEIGHT = 1.25f;        
float       trdpersonDistance = 3.0f;  
const float TRD_TARGET_HEIGHT = 1.0f;  
const float FREE_CAMERA_SPEED = 6.0f;  

// Mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Tiempo entre cuadros
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//  Protagonista 
struct Player {
	glm::vec3 position = MUSEUM_SPAWN_POSITION;  
	float     rotation = 180.0f;                 
	float     walkSpeed = 2.0f;                  
	float     runSpeed = 4.0f;                   
	AnimatedModel* body = nullptr;               

	// Caminata
	float     walkPhase = 0.0f;                  
	float     walkBlend = 0.0f;                  
	float     strideLength = 1.2f;               
};
Player player;

// Animaciones 
float animationTime = 0.0f;  

// Interacción 
SceneObject* selectedPiece = nullptr;  
SceneObject* carriedPiece = nullptr;    
bool         carryKeyDown = false;
Mesh*        interactRing = nullptr;    

// Shaders
Shader *mLightsShader;
Shader *cubemapShader;

// Museo 
SceneObject                    museumArchitecture;  
SceneObject                    museumRoof;          
bool                           showRoof = true;   
bool                           roofKeyDown = false;
std::vector<SceneObject>       sceneObjects;        
std::map<std::string, Model*>  modelCache;          

// Cubemap
CubeMap *mainCubeMap;

// Luces
std::vector<Light> gLights;
std::vector<float> gLightBasePower;  
std::vector<float> gLightFlicker;
bool lightsOn = true;                  // L prende o apaga las luces
bool lightsKeyDown = false;
int  lightColorMode = 0;               // K cambia el color de las luces
bool colorKeyDown = false;
std::vector<glm::vec4> gLightBaseColor;
SceneObject* animatedPiece = nullptr;  // pieza animada mas cercana (P)
bool pauseKeyDown = false;
AnimatedModel* mariachi = nullptr;     // personaje con huesos
AnimatedModel* munecaBaile = nullptr;  // animacion hecha en Blender
AnimatedModel* cablebusAnimado = nullptr;  // maqueta animada en Blender
AnimatedModel* ecobiciAnimada = nullptr;   // maqueta animada en Blender
    

// Materiales
Material material01;

// Usa  carpeta del .exe para encontrar models/, shaders/ y textures/
void SetWorkingDirectoryToExe() {
	char exePath[MAX_PATH];
	DWORD length = GetModuleFileNameA(NULL, exePath, MAX_PATH);
	if (length == 0 || length == MAX_PATH)
		return;

	std::string folder(exePath, length);
	folder = folder.substr(0, folder.find_last_of("\\/"));

	std::string binFolder = folder + "\\bin";
	if (GetFileAttributesA((binFolder + "\\shaders").c_str()) != INVALID_FILE_ATTRIBUTES) {
		folder = binFolder;
		SetDllDirectoryA(folder.c_str());  // assimp se carga desde bin/
	}
	SetCurrentDirectoryA(folder.c_str());
}

int main(int argc, char** argv)
{
	SetWorkingDirectoryToExe();

	if (!Start())
		return -1;

	// reloj  animaciones 
	lastFrame = (float)glfwGetTime();

	// Ciclo principal
	while (!glfwWindowShouldClose(window))
	{
		if (!Update())
			break;
	}

	glfwTerminate();
	return 0;

}

bool Start() {
	// Ventana

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Museo CDMX", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Cursor oculto
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Funciones de OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// Profundidad
	glEnable(GL_DEPTH_TEST);

	// Shaders
	mLightsShader = new Shader("shaders/museo_phong.vs", "shaders/museo_phong.fs");
	cubemapShader = new Shader("shaders/10_vertex_cubemap.vs", "shaders/10_fragment_cubemap.fs");

	// Arquitectura, piezas y protagonista
	LoadMuseum();
	LoadPlayer();

	GLenum glError = glGetError();
	if (glError != GL_NO_ERROR)
		std::cout << "[OpenGL] Error despues de cargar: 0x" << std::hex << glError << std::dec << std::endl;

	// Cubemap
	const std::string CUBEMAP_DIR = "textures/cubemap/02/";
	const std::string CUBEMAP_EXT = ".jpg";
	vector<std::string> faces
	{
		CUBEMAP_DIR + "posx" + CUBEMAP_EXT,
		CUBEMAP_DIR + "negx" + CUBEMAP_EXT,
		CUBEMAP_DIR + "posy" + CUBEMAP_EXT,
		CUBEMAP_DIR + "negy" + CUBEMAP_EXT,
		CUBEMAP_DIR + "posz" + CUBEMAP_EXT,
		CUBEMAP_DIR + "negz" + CUBEMAP_EXT
	};
	mainCubeMap = new CubeMap();
	mainCubeMap->loadCubemap(faces);

	// Luces de la noche 
	for (const LightEntry& entry : kLucesMuseo) {
		Light light;
		light.Position = entry.position;
		light.Color = glm::vec4(entry.color, 1.0f);
		light.Power = glm::vec4(entry.power, entry.power, entry.power, 1.0f);
		light.distance = entry.range;
		gLights.push_back(light);

		// parpadeo luces velas y candil 
		gLightBasePower.push_back(entry.power);
		gLightBaseColor.push_back(light.Color);
		if (strncmp(entry.name, "Velas", 5) == 0)
			gLightFlicker.push_back(0.25f);
		else if (strncmp(entry.name, "Candil", 6) == 0)
			gLightFlicker.push_back(0.07f);
		else
			gLightFlicker.push_back(0.0f);
	}

	// Luz de relleno
	Light fillLight;
	fillLight.Color = glm::vec4(1.0f, 0.95f, 0.9f, 1.0f);
	fillLight.Power = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
	fillLight.distance = 3.0f;
	gLights.push_back(fillLight);

	// Material general 
	material01.specular = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

	SetCameraMode(CAM_PRIMERA_PERSONA);
	UpdateCameras();

	std::cout << "Controles: WASD=caminar  Shift=correr  mouse=mirar" << std::endl;
	std::cout << "  F1=1a persona  F2=3a persona  F3=camara libre (Q/E bajar/subir)" << std::endl;
	std::cout << "  F11=pantalla completa  ESC=salir" << std::endl;
	std::cout << "Interacciones: F=tomar  R=girar  flechas=mover  2/1=subir/bajar  Z/X=tamano" << std::endl;
	std::cout << "  L=apagar/prender luces  K=color de luces  P=pausar/reanudar animacion" << std::endl;

	return true;
}

//  Carga museo 

Model* LoadModelCached(const std::string& path) {
	std::map<std::string, Model*>::iterator it = modelCache.find(path);
	if (it != modelCache.end())
		return it->second;

	std::ifstream probe(path);
	if (!probe.good()) {
		std::cout << "[Museo] No se encontro " << path << std::endl;
		return nullptr;
	}

	Model* model = new Model(path);
	modelCache[path] = model;
	return model;
}

void LoadMuseum() {
	// Edificio
	museumArchitecture.name = "Arquitectura";
	museumArchitecture.model = LoadModelCached(std::string(MUSEUM_MODELS_DIR) + MUSEUM_ARCHITECTURE_FILE);
	museumArchitecture.room = ROOM_LOBBY;

	// Corrección estantes 
	if (museumArchitecture.model != nullptr) {
		const vector<string> shelfMaterials = { "madera", "madera_oscura", "barro", "costal" };
		museumArchitecture.model->MirrorX(glm::vec3(21.6f, 0.4f, 13.7f), glm::vec3(22.12f, 2.25f, 15.8f), 21.90f, shelfMaterials);
		museumArchitecture.model->MirrorX(glm::vec3(21.6f, 0.4f, -12.2f), glm::vec3(22.12f, 2.25f, -10.1f), 21.90f, shelfMaterials);

		// Corrección vidrio luminoso de faroles
		museumArchitecture.model->ExpandGroupsXZ("luz_farol", 1.25f);

		// Corrección cartel lucha libre 
		museumArchitecture.model->MoveInBox(glm::vec3(20.70f, 1.40f, -20.80f), glm::vec3(20.85f, 2.80f, -19.80f),
			glm::vec3(0.0f, 0.0f, 1.05f), { "cartel_lucha" });
	}

	museumRoof.name = "Techos";
	museumRoof.model = LoadModelCached(std::string(MUSEUM_MODELS_DIR) + MUSEUM_ROOF_FILE);
	museumRoof.room = ROOM_LOBBY;

	// Piezas del catálogo
	int pending = 0;
	for (const CatalogEntry& entry : kCatalogoMuseo) {
		if (entry.file[0] == '\0') {
			pending++;
			continue;
		}

		SceneObject obj;
		obj.name = entry.name;
		obj.model = LoadModelCached(std::string(MUSEUM_MODELS_DIR) + entry.file);
		obj.position = entry.position;
		obj.rotation = entry.rotation;
		obj.scale = entry.scale;
		obj.room = entry.room;
		obj.material = entry.material;
		obj.basePosition = entry.position;
		obj.baseRotation = entry.rotation;
		obj.baseScale = entry.scale;

		if (obj.model != nullptr)
			sceneObjects.push_back(obj);
	}
	AssignAnimations();
	AssignInteractions();
}

void LoadPlayer() {
	player.body = new AnimatedModel(PLAYER_MODEL_FILE);
	mariachi = new AnimatedModel(MARIACHI_MODEL_FILE);
	munecaBaile = new AnimatedModel(MUNECA_BAILE_FILE);

	// Maquetas de transporte animadas en Blender, con brillo de plastico como las demas
	cablebusAnimado = new AnimatedModel(CABLEBUS_ANIM_FILE);
	ecobiciAnimada = new AnimatedModel(ECOBICI_ANIM_FILE);
	for (Mesh& m : cablebusAnimado->meshes) m.materialType = MAT_PLASTICO;
	for (Mesh& m : ecobiciAnimada->meshes) m.materialType = MAT_PLASTICO;
}

// Animaciones 

// Busca animación
void AssignAnimations() {
	int simple = 0, keyframe = 0, procedural = 0;
	int countPerKind[8] = {};  

	for (SceneObject& obj : sceneObjects) {
		for (int i = 0; i < (int)(sizeof(kAnimacionesSimples) / sizeof(kAnimacionesSimples[0])); i++)
			if (obj.name == kAnimacionesSimples[i].piece) { obj.animSimple = i; simple++; }

		for (int i = 0; i < (int)(sizeof(kAnimacionesKeyframes) / sizeof(kAnimacionesKeyframes[0])); i++)
			if (obj.name == kAnimacionesKeyframes[i].piece) { obj.animKeyframe = i; keyframe++; }

		for (int i = 0; i < (int)(sizeof(kAnimacionesProcedurales) / sizeof(kAnimacionesProcedurales[0])); i++) {
			const char* prefix = kAnimacionesProcedurales[i].prefix;
			if (obj.name.compare(0, strlen(prefix), prefix) == 0) {
				obj.animProcedural = i;
				obj.animPhase = countPerKind[i] * 2.0f * PI_F / 7.0f;  
				countPerKind[i]++;
				procedural++;
			}
		}
	}
}

// Mueve piezas animadas y hace parpadear flamas
void UpdateAnimations() {
	float t = animationTime;
	for (SceneObject& obj : sceneObjects) {
		if (!obj.animPaused)
			obj.animTime += deltaTime;
		float t = obj.animTime;

		obj.position = obj.basePosition;
		obj.rotation = obj.baseRotation;
		obj.scale = obj.baseScale;

		if (obj.animSimple >= 0)
			ApplySimpleAnimation(obj, kAnimacionesSimples[obj.animSimple], t);

		if (obj.animKeyframe >= 0) {
			const KeyframeAnimation& anim = kAnimacionesKeyframes[obj.animKeyframe];
			glm::vec3 offsetPosition, offsetRotation;
			InterpolateKeyframes(anim.keys, anim.numKeys, t, offsetPosition, offsetRotation);
			obj.position = obj.basePosition + offsetPosition;
			obj.rotation = obj.baseRotation + offsetRotation;
		}

		if (obj.animProcedural >= 0)
			// catrin mira a  protagonista o cámara libre
			ApplyProceduralAnimation(obj, kAnimacionesProcedurales[obj.animProcedural].kind, t,
				activeCamera == CAM_LIBRE ? cameraFree.Position : player.position);
	}

	const glm::vec4 tonos[3] = { glm::vec4(1.0f), glm::vec4(0.75f, 0.35f, 1.0f, 1.0f), glm::vec4(0.55f, 0.75f, 1.0f, 1.0f) };
	for (size_t i = 0; i < gLightFlicker.size(); i++) {
		float power = gLightBasePower[i];
		if (gLightFlicker[i] > 0.0f)
			power *= FlameFlicker(gLightFlicker[i], t, (float)i);
		if (!lightsOn)
			power = 0.0f;
		gLights[i].Color = (lightColorMode == 0) ? gLightBaseColor[i] : tonos[lightColorMode];
		gLights[i].Power = glm::vec4(power, power, power, 1.0f);
	}
}

// Interacción 

// Marca las piezas
void AssignInteractions() {
	int count = 0;
	for (SceneObject& obj : sceneObjects) {
		for (const char* name : kPiezasInteractivas) {
			if (obj.name != name)
				continue;
			obj.interactive = true;
			count++;
			
			for (const Mesh& mesh : obj.model->meshes)
				for (const Vertex& v : mesh.vertices)
					obj.ringRadius = glm::max(obj.ringRadius, glm::length(glm::vec2(v.Position.x, v.Position.z)) * obj.baseScale.x);
			obj.ringRadius += 0.05f;
		}
	}

	// Anillo plano radio 1
	const int SEGMENTS = 48;
	const float INNER = 0.88f;  
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	for (int i = 0; i <= SEGMENTS; i++) {
		float a = 2.0f * PI_F * i / SEGMENTS;
		Vertex outer = {}, inner = {};
		outer.Position = glm::vec3(std::cos(a), 0.0f, std::sin(a));
		inner.Position = outer.Position * INNER;
		outer.Normal = inner.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
		vertices.push_back(outer);
		vertices.push_back(inner);
	}
	for (unsigned int i = 0; i < SEGMENTS; i++) {
		unsigned int o0 = 2 * i, i0 = 2 * i + 1, o1 = 2 * i + 2, i1 = 2 * i + 3;
		indices.insert(indices.end(), { o0, i0, o1, o1, i0, i1 });
	}
	interactRing = new Mesh(vertices, indices, vector<Texture>());
	interactRing->emissive = true;
}

// Dibuja anillo  
void DrawInteractionRings(Shader* shader) {
	if (interactRing == nullptr)
		return;
	for (const SceneObject& obj : sceneObjects) {
		if (!obj.interactive || &obj == carriedPiece)
			continue;
		bool selected = (&obj == selectedPiece);
		float radius = obj.ringRadius * obj.userScale * (selected ? 1.1f : 1.0f);
		glm::mat4 m = glm::translate(glm::mat4(1.0f), obj.position + glm::vec3(0.0f, 0.02f, 0.0f));
		m = glm::scale(m, glm::vec3(radius, 1.0f, radius));
		shader->setMat4("model", m);
		interactRing->diffuseColor = selected ? glm::vec4(1.0f, 0.95f, 0.45f, 1.0f) : glm::vec4(0.85f, 0.68f, 0.12f, 1.0f);
		interactRing->Draw(*shader);
	}
}

// Pieza interactiva cercana
SceneObject* FindSelectablePiece() {
	glm::vec3 origin = (activeCamera == CAM_LIBRE) ? cameraFree.Position : player.position;
	glm::vec3 front = (activeCamera == CAM_LIBRE) ? cameraFree.Front : camera.Front;
	glm::vec2 forward(front.x, front.z);
	if (glm::length(forward) < 0.01f)
		return nullptr;  
	forward = glm::normalize(forward);

	SceneObject* best = nullptr;
	float bestDistance = INTERACT_DISTANCE;
	for (SceneObject& obj : sceneObjects) {
		if (!obj.interactive)
			continue;
		glm::vec2 toPiece(obj.position.x - origin.x, obj.position.z - origin.z);
		float distance = glm::length(toPiece);
		if (distance > bestDistance)
			continue;
		if (distance > 0.3f && glm::dot(toPiece / distance, forward) < 0.5f)
			continue;  
		best = &obj;
		bestDistance = distance;
	}
	return best;
}

// Pieza animada cercana, para pausarla con P
SceneObject* FindAnimatedPiece() {
	glm::vec3 origin = (activeCamera == CAM_LIBRE) ? cameraFree.Position : player.position;
	glm::vec3 front = (activeCamera == CAM_LIBRE) ? cameraFree.Front : camera.Front;
	glm::vec2 forward(front.x, front.z);
	if (glm::length(forward) < 0.01f)
		return nullptr;
	forward = glm::normalize(forward);

	SceneObject* best = nullptr;
	float bestDistance = 4.0f;
	for (SceneObject& obj : sceneObjects) {
		if (obj.animSimple < 0 && obj.animKeyframe < 0 && obj.animProcedural < 0)
			continue;
		glm::vec2 toPiece(obj.position.x - origin.x, obj.position.z - origin.z);
		float distance = glm::length(toPiece);
		if (distance > bestDistance)
			continue;
		if (distance > 0.3f && glm::dot(toPiece / distance, forward) < 0.5f)
			continue;
		best = &obj;
		bestDistance = distance;
	}
	return best;
}

// Teclas interacción 
void UpdateInteraction(GLFWwindow* window) {
	if (carriedPiece == nullptr)
		selectedPiece = FindSelectablePiece();

	// F tomar o soltar
	bool carryKey = glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS;
	if (carryKey && !carryKeyDown && activeCamera != CAM_LIBRE) {
		if (carriedPiece != nullptr)
			carriedPiece = nullptr;
		else if (selectedPiece != nullptr)
			carriedPiece = selectedPiece;
	}
	carryKeyDown = carryKey;

	if (selectedPiece == nullptr)
		return;
	SceneObject& piece = *selectedPiece;

	// 2/1 subir y bajar
	glm::vec3 front = (activeCamera == CAM_LIBRE) ? cameraFree.Front : camera.Front;
	glm::vec3 forward = glm::normalize(glm::vec3(front.x, 0.0f, front.z) + glm::vec3(0.0f, 0.0f, 1e-4f));
	glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	float move = INTERACT_MOVE_SPEED * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)        piece.userOffset += forward * move;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)      piece.userOffset -= forward * move;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)     piece.userOffset += right * move;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)      piece.userOffset -= right * move;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)         piece.userOffset.y += move;
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)         piece.userOffset.y -= move;

	// R rotar, Z/X escalar
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		piece.userYaw = std::fmod(piece.userYaw + INTERACT_ROTATE_SPEED * deltaTime, 360.0f);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		piece.userScale = glm::max(INTERACT_MIN_SCALE, piece.userScale - INTERACT_SCALE_SPEED * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		piece.userScale = glm::min(INTERACT_MAX_SCALE, piece.userScale + INTERACT_SCALE_SPEED * deltaTime);

	// pieza regresa
	if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
		piece.userOffset = glm::vec3(0.0f);
		piece.userYaw = 0.0f;
		piece.userScale = 1.0f;
		carriedPiece = nullptr;
	}
}

// Suma cambios interaccion
void ApplyInteractions() {
	for (SceneObject& obj : sceneObjects) {
		if (!obj.interactive)
			continue;

		if (&obj == carriedPiece) {
			
			glm::vec3 forward = glm::normalize(glm::vec3(camera.Front.x, 0.0f, camera.Front.z) + glm::vec3(0.0f, 0.0f, 1e-4f));
			obj.position = player.position + forward * 0.6f + glm::vec3(0.0f, 1.0f, 0.0f);
		}
		else {
			obj.position += obj.userOffset;
		}
		obj.rotation.y += obj.userYaw;
		obj.scale *= obj.userScale;
	}
}

// Dibujar piezas
// translucent true solo vidrio y agua
void DrawSceneObject(const SceneObject& obj, Shader* shader, bool translucent) {
	if (obj.model == nullptr || !obj.model->HasParts(translucent))
		return;

	shader->setMat4("model", GetModelMatrix(obj));
	obj.model->DrawParts(*shader, translucent);
}

// Dibuja un modelo con huesos en el cuadro indicado
void DrawSkinned(Shader* shader, AnimatedModel* body, float frame, const glm::mat4& model) {
	glm::mat4 pose[MAX_RIGGING_BONES];
	body->SetPose(frame, pose);
	for (unsigned int i = 0; i < body->bones.size() && i < MAX_RIGGING_BONES; i++)
		shader->SetBoneTransform(i, pose[i]);
	shader->setMat4("model", model);
	shader->setInt("useBones", 1);
	body->Draw(*shader);
	shader->setInt("useBones", 0);
}

// Mariachi camina por el vestibulo y la muneca baila en la tienda
void DrawCharacters(Shader* shader) {
	float t = animationTime;

	// Mariachi: caminata de Meshy (huesos) y recorrido de ida y vuelta calculado aqui
	const float L = 7.0f, v = 1.0f, Tw = L / v, Tt = 1.0f, T = 2.0f * (Tw + Tt);
	float u = std::fmod(t, T), x, yaw;
	if (u < Tw)               { x = -L / 2 + v * u;            yaw = 90.0f; }
	else if (u < Tw + Tt)     { x = L / 2;                     yaw = 90.0f + 180.0f * (u - Tw) / Tt; }
	else if (u < 2 * Tw + Tt) { x = L / 2 - v * (u - Tw - Tt); yaw = 270.0f; }
	else                      { x = -L / 2;                    yaw = 270.0f + 180.0f * (u - 2 * Tw - Tt) / Tt; }
	glm::mat4 m = glm::translate(glm::mat4(1.0f), MARIACHI_POSITION + glm::vec3(x, 0.0f, 0.0f));
	m = glm::rotate(m, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	DrawSkinned(shader, mariachi, std::fmod(t * MARIACHI_FPS, MARIACHI_FRAMES), m);

	// Muneca: baile hecho con keyframes en Blender
	glm::mat4 d = glm::translate(glm::mat4(1.0f), MUNECA_BAILE_POSITION);
	d = glm::rotate(d, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));   // mira hacia la entrada de la tienda
	d = glm::scale(d, glm::vec3(0.75f));
	d = glm::rotate(d, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));   // el esqueleto de Blender usa Z hacia arriba
	DrawSkinned(shader, munecaBaile, std::fmod(t * MUNECA_BAILE_FPS, MUNECA_BAILE_FRAMES), d);

	// Cablebus: la cabina recorre su cable (animacion de Blender)
	glm::mat4 c = glm::translate(glm::mat4(1.0f), CABLEBUS_ANIM_POSITION);
	c = glm::rotate(c, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	c = glm::scale(c, glm::vec3(1.15f));
	c = glm::rotate(c, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));   // Blender usa Z hacia arriba
	DrawSkinned(shader, cablebusAnimado, std::fmod(t * CABLEBUS_ANIM_FPS, CABLEBUS_ANIM_FRAMES), c);

	// Ecobici: giran las ruedas (animacion de Blender)
	glm::mat4 e = glm::translate(glm::mat4(1.0f), ECOBICI_ANIM_POSITION);
	e = glm::scale(e, glm::vec3(0.8f));
	e = glm::rotate(e, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));   // Blender usa Z hacia arriba
	DrawSkinned(shader, ecobiciAnimada, std::fmod(t * ECOBICI_ANIM_FPS, ECOBICI_ANIM_FRAMES), e);
}

// Dibujar protagonista
void DrawPlayer(Shader* shader) {
	// Pose huesos 
	glm::mat4 walk[MAX_RIGGING_BONES], rest[MAX_RIGGING_BONES];
	player.body->SetPose(player.walkPhase * PLAYER_WALK_FRAMES, walk);
	player.body->SetPose(PLAYER_REST_FRAME, rest);
	for (unsigned int i = 0; i < player.body->bones.size() && i < MAX_RIGGING_BONES; i++)
		shader->SetBoneTransform(i, rest[i] + (walk[i] - rest[i]) * player.walkBlend);

	glm::mat4 model = glm::translate(glm::mat4(1.0f), player.position);
	model = glm::rotate(model, glm::radians(player.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	shader->setMat4("model", model);
	shader->setInt("useBones", 1);
	player.body->Draw(*shader);
	shader->setInt("useBones", 0);
}

void SetLightUniformInt(Shader* shader, const char* propertyName, size_t lightIndex, int value) {
	std::ostringstream ss;
	ss << "allLights[" << lightIndex << "]." << propertyName;
	std::string uniformName = ss.str();

	shader->setInt(uniformName.c_str(), value);
}
void SetLightUniformFloat(Shader* shader, const char* propertyName, size_t lightIndex, float value) {
	std::ostringstream ss;
	ss << "allLights[" << lightIndex << "]." << propertyName;
	std::string uniformName = ss.str();

	shader->setFloat(uniformName.c_str(), value);
}
void SetLightUniformVec4(Shader* shader, const char* propertyName, size_t lightIndex, glm::vec4 value) {
	std::ostringstream ss;
	ss << "allLights[" << lightIndex << "]." << propertyName;
	std::string uniformName = ss.str();

	shader->setVec4(uniformName.c_str(), value);
}
void SetLightUniformVec3(Shader* shader, const char* propertyName, size_t lightIndex, glm::vec3 value) {
	std::ostringstream ss;
	ss << "allLights[" << lightIndex << "]." << propertyName;
	std::string uniformName = ss.str();

	shader->setVec3(uniformName.c_str(), value);
}

bool Update() {
	// Tiempo cuadro
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Teclado, mouse y camaras
	processInput(window);
	UpdateCameras();

	// Animaciones e interaccion
	animationTime += deltaTime;
	UpdateAnimations();
	UpdateInteraction(window);
	ApplyInteractions();

	// Título ventana
	static float lastTitleUpdate = 0.0f;
	if (currentFrame - lastTitleUpdate > 0.25f) {
		UpdateWindowTitle();
		lastTitleUpdate = currentFrame;
	}

	Render();

	// Muestra imagen
	glfwSwapBuffers(window);
	glfwPollEvents();

	return true;
}

// Dibuja un cuadro con la cámara activa
void Render() {
	// Limpia pantalla
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camara activa
	Camera& activeCam = (activeCamera == CAM_PRIMERA_PERSONA) ? camera :
	                    (activeCamera == CAM_TERCERA_PERSONA) ? camera3rd : cameraFree;
	float aspect = (windowHeight > 0) ? (float)windowWidth / (float)windowHeight : 1.0f;
	glm::mat4 projection = glm::perspective(glm::radians(activeCam.Zoom), aspect, 0.1f, 10000.0f);
	glm::mat4 view = activeCam.GetViewMatrix();

	// Luz relleno sigue camara
	gLights.back().Position = activeCam.Position;

	// Cielo
	{
		mainCubeMap->drawCubeMap(*cubemapShader, projection, view);
	}

	// Museo con el shader de Phong
	{
		mLightsShader->use();

		// Transparencia
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mLightsShader->setMat4("projection", projection);
		mLightsShader->setMat4("view", view);

		// Luces
		mLightsShader->setInt("numLights", (int)gLights.size());
		for (size_t i = 0; i < gLights.size(); ++i) {
			SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
			SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
			SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
			SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
			SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
			SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
		}

		mLightsShader->setVec3("eye", activeCam.Position);
		mLightsShader->setVec3("moonDirection", MOON_DIRECTION);
		mLightsShader->setVec3("moonColor", MOON_COLOR);
		mLightsShader->setVec3("nightAmbient", NIGHT_AMBIENT);

		// Cielo reflejos Fresnel
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mainCubeMap->textureID);
		mLightsShader->setInt("cubetex", 5);
		glActiveTexture(GL_TEXTURE0);

		// Material general
		mLightsShader->setVec4("MaterialAmbientColor", material01.ambient);
		mLightsShader->setVec4("MaterialDiffuseColor", material01.diffuse);
		mLightsShader->setVec4("MaterialSpecularColor", material01.specular);
		mLightsShader->setFloat("transparency", material01.transparency);

		// 1 partes opacas, 2 vidrio y agua
		for (int pass = 0; pass < 2; pass++) {
			bool translucent = (pass == 1);
			if (translucent)
				glDepthMask(GL_FALSE);

			DrawSceneObject(museumArchitecture, mLightsShader, translucent);

			// Techos
			if (showRoof) {
				glEnable(GL_CULL_FACE);
				DrawSceneObject(museumRoof, mLightsShader, translucent);
				glDisable(GL_CULL_FACE);
			}

			for (const SceneObject& obj : sceneObjects)
				DrawSceneObject(obj, mLightsShader, translucent);

			if (!translucent)
				DrawInteractionRings(mLightsShader);

			// 1a persona sin cuerpo
			if (!translucent && activeCamera != CAM_PRIMERA_PERSONA)
				DrawPlayer(mLightsShader);

			// Mariachi y muneca bailarina
			if (!translucent)
				DrawCharacters(mLightsShader);

			glDepthMask(GL_TRUE);
		}
	}

	glUseProgram(0);
}

// camaras 1a y 3a persona
void UpdateCameras() {
	// 1a en ojos
	camera.Position = player.position + glm::vec3(0.0f, EYE_HEIGHT, 0.0f);

	// 3a detrás
	glm::vec3 target = player.position + glm::vec3(0.0f, TRD_TARGET_HEIGHT, 0.0f);
	camera3rd.Position = target - camera.Front * trdpersonDistance;
	if (camera3rd.Position.y < 0.3f)
		camera3rd.Position.y = 0.3f;  // evita traspasar piso
	camera3rd.Front = glm::normalize(target - camera3rd.Position);
}

void SetCameraMode(int mode) {
	// empezar camara libre donde se quedaron las otras dos
	if (mode == CAM_LIBRE && activeCamera != CAM_LIBRE) {
		Camera& from = (activeCamera == CAM_TERCERA_PERSONA) ? camera3rd : camera;
		cameraFree = Camera(from.Position, glm::vec3(0.0f, 1.0f, 0.0f), camera.Yaw, camera.Pitch);
		cameraFree.MovementSpeed = FREE_CAMERA_SPEED;
	}
	activeCamera = mode;
	UpdateWindowTitle();
}

// Info ventana, camara o  pieza
void UpdateWindowTitle() {
	const char* modes[] = { "Primera persona (F1)", "Tercera persona (F2)", "Camara libre (F3)" };
	char title[256];
	if (selectedPiece != nullptr)
		snprintf(title, sizeof(title), "%s: %s - F tomar, R girar, flechas mover, 2/1 subir/bajar, Z/X tamano",
			selectedPiece == carriedPiece ? "Llevas" : "Interactiva", selectedPiece->name.c_str());
	else if (animatedPiece != nullptr)
		snprintf(title, sizeof(title), "Animada: %s - P %s su animacion", animatedPiece->name.c_str(),
			animatedPiece->animPaused ? "reanuda" : "pausa");
	else
		snprintf(title, sizeof(title), "Museo CDMX - %s - L luces, K color de luces", modes[activeCamera]);
	glfwSetWindowTitle(window, title);
}

// WASD mueve a la protagonista hacia donde mira camara
void MovePlayer(GLFWwindow* window) {
	glm::vec3 forward = glm::normalize(glm::vec3(camera.Front.x, 0.0f, camera.Front.z));
	glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

	glm::vec3 direction(0.0f);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) direction += forward;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) direction -= forward;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) direction += right;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) direction -= right;

	// Suavizar cambio caminata
	bool moving = glm::length(direction) >= 0.01f;
	player.walkBlend = glm::clamp(player.walkBlend + (moving ? 5.0f : -5.0f) * deltaTime, 0.0f, 1.0f);
	if (!moving)
		return;

	direction = glm::normalize(direction);
	bool running = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
	float speed = running ? player.runSpeed : player.walkSpeed;
	player.position += direction * speed * deltaTime;

	// El paso avanza con la distancia recorrida
	player.walkPhase = std::fmod(player.walkPhase + speed * deltaTime / player.strideLength, 1.0f);

	// Suavizar giro
	float desired = glm::degrees(std::atan2(direction.x, direction.z));
	float diff = std::fmod(desired - player.rotation + 540.0f, 360.0f) - 180.0f;
	float step = 600.0f * deltaTime;
	player.rotation += glm::clamp(diff, -step, step);
}

// Vuelo de cámara libre
void MoveFreeCamera(GLFWwindow* window) {
	float velocity = cameraFree.MovementSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		velocity *= 3.0f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraFree.Position += cameraFree.Front * velocity;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraFree.Position -= cameraFree.Front * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cameraFree.Position += cameraFree.Right * velocity;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cameraFree.Position -= cameraFree.Right * velocity;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) cameraFree.Position.y += velocity;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) cameraFree.Position.y -= velocity;
}

// Teclado
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Cambio de camara
	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS && activeCamera != CAM_PRIMERA_PERSONA)
		SetCameraMode(CAM_PRIMERA_PERSONA);
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS && activeCamera != CAM_TERCERA_PERSONA)
		SetCameraMode(CAM_TERCERA_PERSONA);
	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS && activeCamera != CAM_LIBRE)
		SetCameraMode(CAM_LIBRE);

	// Pantalla completa
	bool fullscreenKey = glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS;
	if (fullscreenKey && !fullscreenKeyDown)
		ToggleFullscreen();
	fullscreenKeyDown = fullscreenKey;

	// Mostrar u ocultar techos
	bool roofKey = glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS;
	if (roofKey && !roofKeyDown)
		showRoof = !showRoof;
	roofKeyDown = roofKey;

	// L prende o apaga las luces, K cambia su color
	bool lightsKey = glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS;
	if (lightsKey && !lightsKeyDown)
		lightsOn = !lightsOn;
	lightsKeyDown = lightsKey;
	bool colorKey = glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS;
	if (colorKey && !colorKeyDown)
		lightColorMode = (lightColorMode + 1) % 3;
	colorKeyDown = colorKey;

	// P pausa o reanuda la animacion de la pieza animada mas cercana
	animatedPiece = FindAnimatedPiece();
	bool pauseKey = glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS;
	if (pauseKey && !pauseKeyDown && animatedPiece != nullptr)
		animatedPiece->animPaused = !animatedPiece->animPaused;
	pauseKeyDown = pauseKey;

	// Mallas
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) { glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); glPointSize(3.0f); }
	if (activeCamera == CAM_LIBRE)
		MoveFreeCamera(window);
	else
		MovePlayer(window);
}

// Ajusta imagen a ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	windowWidth = width;    // evitar deformar
	windowHeight = height;
}

// pantalla completa o ventana
void ToggleFullscreen() {
	if (!fullscreen) {
		glfwGetWindowPos(window, &windowedX, &windowedY);
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else {
		glfwSetWindowMonitor(window, NULL, windowedX, windowedY, SCR_WIDTH, SCR_HEIGHT, 0);
	}
	fullscreen = !fullscreen;
	firstMouse = true;  // evita salto de vista al cambiar tamaño
}

// Movimiento de vista
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos;

	lastX = (float)xpos;
	lastY = (float)ypos;

	if (activeCamera == CAM_LIBRE)
		cameraFree.ProcessMouseMovement(xoffset, yoffset);
	else
		camera.ProcessMouseMovement(xoffset, yoffset);  // misma vista para 1a y 3a persona
}

// distancia en 3a persona o zoom
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (activeCamera == CAM_TERCERA_PERSONA)
		trdpersonDistance = glm::clamp(trdpersonDistance - (float)yoffset * 0.3f, 1.5f, 6.0f);
	else if (activeCamera == CAM_LIBRE)
		cameraFree.ProcessMouseScroll((float)yoffset);
	else
		camera.ProcessMouseScroll((float)yoffset);
}
