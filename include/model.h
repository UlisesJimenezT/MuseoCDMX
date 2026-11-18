#ifndef MODEL_H
#define MODEL_H

#include <glm/gtx/string_cast.hpp>

#include <modelstructs.h>

#include <algorithm>

// fotos de textures partes sin textura, prefix inicio nombre mat
struct MaterialPhoto {
    const char* prefix;       
    const char* file;         
    float       repetitions;  
};
const MaterialPhoto kMaterialPhotos[] = {
    {"cuero", "cuero.bmp", 4.0f},              // botas, cinturon, maletin, resortera
    {"piel_libro", "cuero.bmp", 6.0f},         // pasta libro
    {"terciopelo", "terciopelo.bmp", 3.0f},    // arcos, coronas, canastas y florero
    {"vestido_catrina", "terciopelo.bmp", 3.0f},
    {"tela_morada", "tela.bmp", 3.0f},         // telas altar
    {"tela_naranja", "tela.bmp", 3.0f},
    {"tela_rosa", "tela.bmp", 3.0f},
    {"tela_vino", "tela.bmp", 3.0f},
    {"mantel_blanco", "tela.bmp", 3.0f},
    {"tela_toalla", "tela.bmp", 5.0f},
    {"vela_lona", "tela.bmp", 6.0f},           // vela barquito
    {"tela_faldon_ring", "tela.bmp", 3.0f},    // ring y ropa luchadores
    {"tela_esq_", "tela.bmp", 4.0f},
    {"tela_guante_", "tela.bmp", 6.0f},
    {"tela_mascara_", "tela.bmp", 8.0f},
    {"tela_mallas_", "tela.bmp", 6.0f},
    {"tela_calzon_", "tela.bmp", 6.0f},
    {"tela_bota_", "tela.bmp", 6.0f},
    {"tela_blanca", "tela.bmp", 6.0f},         // mangas protagonista
    {"caja_registradora", "madera.bmp", 2.0f},
    {"barro_negro", "barro.bmp", 3.0f},        // florero barro
    {"vidriado_verde", "barro.bmp", 3.0f},     // cazuela vidriada
    {"concha_", "pan.bmp", 6.0f},              // conchas canasta de pan
    {"galleta", "pan.bmp", 6.0f},
    {"fondo_canal", "tierra.bmp", 2.0f},       // fondo maquetas Xochi
};

// Carga foto de textures 
inline unsigned int SharedTexture(const string& file)
{
    return TextureFromFile(file.c_str(), "textures");
}

// tipo de material de una parte 
inline int MaterialTypeOf(const string& name)
{
    const char* translucent[] = { "vidrio_", "agua_", "translucido_" };
    const char* plastic[] = { "tela_plastico_", "hule_", "charol", "zapato_charol", "laca_", "tela_esmalte_",
                              "barniz_", "vidriado_", "porcelana", "talavera", "gema_" };
    for (const char* p : translucent)
        if (name.rfind(p, 0) == 0) return 2;
    if (name.rfind("metal_", 0) == 0) return 3;
    for (const char* p : plastic)
        if (name.rfind(p, 0) == 0) return 1;
    return 0;
}

class Model
{
public:
    /*  Model Data */
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

	string filename;

	/* Bones data */
	vector<Bone> bones;

	/* Scene data */
	Assimp::Importer importer;
	const aiScene* scene;
	
	map<string, unsigned int> m_BoneMapping; // maps a bone name to its index
	unsigned int m_NumBones;
	vector<BoneInfo> m_BoneInfo;
	glm::mat4 m_GlobalInverseTransform;

    /*  Functions   */
    // constructor, expects a filepath to a 3D model.
    Model(string const &path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }

    // draws the model, and thus all its meshes
    void Draw(Shader shader)
    {
        for(unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }

    // dibuja partes opacas o vidrio y agua
    void DrawParts(Shader shader, bool translucent)
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
            if (meshes[i].translucent == translucent)
                meshes[i].Draw(shader);
    }

    bool HasParts(bool translucent)
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
            if (meshes[i].translucent == translucent)
                return true;
        return false;
    }

    //refleja en X partes de esos materiales dentro de caja estantes
    void MirrorX(glm::vec3 boxMin, glm::vec3 boxMax, float planeX, const vector<string>& materials)
    {
        for (unsigned int i = 0; i < meshes.size(); i++) {
            Mesh& mesh = meshes[i];
            if (std::find(materials.begin(), materials.end(), mesh.materialName) == materials.end())
                continue;

            bool changed = false;
            for (Vertex& v : mesh.vertices) {
                glm::vec3 p = v.Position;
                if (p.x < boxMin.x || p.x > boxMax.x || p.y < boxMin.y || p.y > boxMax.y || p.z < boxMin.z || p.z > boxMax.z)
                    continue;
                v.Position.x = 2.0f * planeX - p.x;
                v.Normal.x = -v.Normal.x;
                v.Tangent.x = -v.Tangent.x;
                v.Bitangent.x = -v.Bitangent.x;
                changed = true;
            }
            if (changed)
                mesh.UploadVertices();
        }
    }

    // traslada vertices que caen dentro de la caja para cartel
    void MoveInBox(glm::vec3 boxMin, glm::vec3 boxMax, glm::vec3 offset, const vector<string>& materials)
    {
        for (unsigned int i = 0; i < meshes.size(); i++) {
            Mesh& mesh = meshes[i];
            if (std::find(materials.begin(), materials.end(), mesh.materialName) == materials.end())
                continue;

            bool changed = false;
            for (Vertex& v : mesh.vertices) {
                glm::vec3 p = v.Position;
                if (p.x < boxMin.x || p.x > boxMax.x || p.y < boxMin.y || p.y > boxMax.y || p.z < boxMin.z || p.z > boxMax.z)
                    continue;
                v.Position += offset;
                changed = true;
            }
            if (changed)
                mesh.UploadVertices();
        }
    }

    // agranda cada grupo de vertices de un material para faroles
    void ExpandGroupsXZ(const string& material, float factor)
    {
        for (unsigned int i = 0; i < meshes.size(); i++) {
            Mesh& mesh = meshes[i];
            if (mesh.materialName != material)
                continue;

            // agrupar vertices cercanos y sacar su centro
            vector<glm::vec2> sums;
            vector<int> counts;
            vector<int> groupOf(mesh.vertices.size());
            for (size_t v = 0; v < mesh.vertices.size(); v++) {
                glm::vec2 p(mesh.vertices[v].Position.x, mesh.vertices[v].Position.z);
                size_t g = 0;
                while (g < sums.size() && glm::length(sums[g] / (float)counts[g] - p) > 0.5f)
                    g++;
                if (g == sums.size()) {
                    sums.push_back(glm::vec2(0.0f));
                    counts.push_back(0);
                }
                sums[g] += p;
                counts[g]++;
                groupOf[v] = (int)g;
            }

            // alejar cada vertice del centro de su grupo
            for (size_t v = 0; v < mesh.vertices.size(); v++) {
                glm::vec2 center = sums[groupOf[v]] / (float)counts[groupOf[v]];
                glm::vec3& p = mesh.vertices[v].Position;
                p.x = center.x + (p.x - center.x) * factor;
                p.z = center.y + (p.z - center.y) * factor;
            }
            mesh.UploadVertices();
        }
    }

	// update transformations in time
	void SetPose(float time, glm::mat4 *gBones) {
		
		// processNode(scene->mRootNode, time);
		glm::mat4 n_matrix(1.0f);
		ReadNodeHierarchy(time, scene->mRootNode, n_matrix);

		for (unsigned int i = 0; i < bones.size(); i++) {
			if (i < 100) {
				
				gBones[i] = bones[i].transformation;
				// cout << "bone: " << i << " : " << bones[i].name.data << " T= " << glm::to_string(gBones[i]) << endl;
			}
		}
	}

	// Return the duration of the animation in ticks (frames)
	double getNumFrames() {

		const aiAnimation* pAnimation = scene->mAnimations[0];
		if (pAnimation == nullptr) return -1.0;


		return pAnimation->mDuration;

	}

	// return the number of ticks per second
	double getFramerate() {
		const aiAnimation* pAnimation = scene->mAnimations[0];
		if (pAnimation == nullptr) return -1.0;


		return  pAnimation->mTicksPerSecond;
	}

private:

    /*  Functions   */

	inline glm::mat4 aiMatrix4x4ToGlm(aiMatrix4x4 from)
	{
		glm::mat4 to;

		to[0][0] = (GLfloat)from.a1; to[0][1] = (GLfloat)from.b1;  to[0][2] = (GLfloat)from.c1; to[0][3] = (GLfloat)from.d1;
		to[1][0] = (GLfloat)from.a2; to[1][1] = (GLfloat)from.b2;  to[1][2] = (GLfloat)from.c2; to[1][3] = (GLfloat)from.d2;
		to[2][0] = (GLfloat)from.a3; to[2][1] = (GLfloat)from.b3;  to[2][2] = (GLfloat)from.c3; to[2][3] = (GLfloat)from.d3;
		to[3][0] = (GLfloat)from.a4; to[3][1] = (GLfloat)from.b4;  to[3][2] = (GLfloat)from.c4; to[3][3] = (GLfloat)from.d4;

		return to;
	}

    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const &path)
    {
        // read file via ASSIMP, aplica la transformacion de cada nodo a sus vertices y genera normales si faltan
		scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace |
			aiProcess_GenSmoothNormals | aiProcess_PreTransformVertices);
        // check for errors
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
            return;
        }
		filename = path;
        // retrieve the directory path of the filepath
        directory = path.substr(0, path.find_last_of('/'));

		aiMatrix4x4 inverseTransform = scene->mRootNode->mTransformation;
		inverseTransform.Inverse();
		m_GlobalInverseTransform = aiMatrix4x4ToGlm(inverseTransform);

        // process ASSIMP's root node recursively
        processNode(scene->mRootNode, scene);
    }

	void processNode(aiNode *node, float time){
		
		if (node == nullptr) return;

		glm::mat4 n_matrix(1.0f);
		ReadNodeHierarchy(time, node, n_matrix);

	}

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene)
    {
		// cout << node->mName.data << endl;
		// cout << "Meshes: " << node->mNumMeshes << endl;
        // process each mesh located at the current node
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // the node object only contains indices to index the actual objects in the scene. 
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			// cout << "Mesh: " << mesh->mName.data << endl;
            meshes.push_back(processMesh(mesh, scene));
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }

    }

    Mesh processMesh(aiMesh *mesh, const aiScene *scene)
    {
        // data to fill
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

		// cout << "NumVertices: " << mesh->mNumVertices << endl;

        // Walk through each of the mesh's vertices
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            // normals
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
            // texture coordinates
            if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x; 
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            // tangent / bitangent (Museo: solo si la malla tiene UVs)
            if (mesh->mTangents && mesh->mBitangents) {
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
            }
            else {
                vertex.Tangent = glm::vec3(0.0f);
                vertex.Bitangent = glm::vec3(0.0f);
            }
            
			// Bones
			int bcount = 0;
			for (unsigned int pb = 0; pb < MAX_NUM_BONES; pb++) {
				vertex.IDs1[pb] = 0.0f;
				vertex.IDs2[pb] = 0.0f;
				vertex.IDs3[pb] = 0.0f;
				vertex.Weights1[pb] = 0.0f;
				vertex.Weights2[pb] = 0.0f;
				vertex.Weights3[pb] = 0.0f;
			}
			m_NumBones = mesh->mNumBones;
			for (unsigned int j = 0; j < mesh->mNumBones; j++) {

				for (unsigned int k = 0; k < mesh->mBones[j]->mNumWeights; k++) {
					unsigned int VertexID = mesh->mBones[j]->mWeights[k].mVertexId;
					float Weight = (float)(mesh->mBones[j]->mWeights[k].mWeight);
					if ( VertexID == i && bcount < MAX_NUM_BONES ) {
						vertex.IDs1[bcount] = (float)j;
						vertex.Weights1[bcount] = Weight;
						bcount++;
						/*cout << "Vertex " << VertexID << ": Bone: " << j
						<< ": W = " << Weight << endl;*/
					}
					if (VertexID == i && bcount >= MAX_NUM_BONES && bcount < 2*MAX_NUM_BONES) {
						vertex.IDs2[bcount - MAX_NUM_BONES] = (float)j;
						vertex.Weights2[bcount - MAX_NUM_BONES] = Weight;
						bcount++;
						/*cout << "Vertex " << VertexID << ": Bone: " << j
							<< ": W = " << Weight << endl;*/
					}
					if (VertexID == i && bcount >= 2 * MAX_NUM_BONES && bcount < 3 * MAX_NUM_BONES) {
						vertex.IDs3[bcount - 2*MAX_NUM_BONES] = (float)j;
						vertex.Weights3[bcount - 2*MAX_NUM_BONES] = Weight;
						bcount++;
						/*cout << "Vertex " << VertexID << ": Bone: " << j
							<< ": W = " << Weight << endl;*/
					}
				}
			}
			vertices.push_back(vertex);
			//cout << "Vertex " << i << ": " << glm::to_string(vertex.IDs1) << glm::to_string(vertex.IDs2) << glm::to_string(vertex.IDs3)  << endl;
			//cout << "Vertex " << i << ": " << glm::to_string(vertex.Weights1) << glm::to_string(vertex.Weights2) << glm::to_string(vertex.Weights3) << endl;
        }
		// cout << "Vertex readed: " << vertices.size() << endl;

		// Process Bones
		// cout << "Num bones readed: " << mesh->mNumBones << endl;
		bones.clear();
		for (unsigned int i = 0; i < mesh->mNumBones; i++) {

			Bone  newBone;
			newBone.name = mesh->mBones[i]->mName;
			newBone.offsetMatrix = aiMatrix4x4ToGlm(mesh->mBones[i]->mOffsetMatrix);
			newBone.transformation = glm::mat4(1.0f);

			for (unsigned int j = 0; j < mesh->mBones[i]->mNumWeights; j++) {
				unsigned int VertexID = mesh->mBones[i]->mWeights[j].mVertexId;
				float Weight = mesh->mBones[i]->mWeights[j].mWeight;
				newBone.push( VertexID, Weight );
			}

			bones.push_back(newBone);
		}
		// cout << "NumFaces: " << mesh->mNumFaces << endl;

        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        
        // return a mesh object created from the extracted mesh data
        Mesh result(vertices, indices, textures);

        // color del material
        aiColor4D kd(1.0f, 1.0f, 1.0f, 1.0f);
        if (aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &kd) == AI_SUCCESS)
            result.diffuseColor = glm::vec4(kd.r, kd.g, kd.b, 1.0f);

        // vidrio_, agua_ y translucido_ 
        aiString materialName;
        material->Get(AI_MATKEY_NAME, materialName);
        string name = materialName.C_Str();
        if (name.rfind("vidrio_", 0) == 0) {
            result.translucent = true;
            result.diffuseColor.a = 0.25f;
        }
        else if (name.rfind("agua_", 0) == 0 || name.rfind("translucido_", 0) == 0) {
            result.translucent = true;
            result.diffuseColor.a = 0.35f;
        }

        result.materialName = name;
        result.emissive = (name.rfind("luz_", 0) == 0);
        result.materialType = MaterialTypeOf(name);

        // si parte no trae foto, se busca una por el nombre del material
        bool hasDiffuse = false;
        for (unsigned int i = 0; i < result.textures.size(); i++)
            if (result.textures[i].type == "texture_diffuse") hasDiffuse = true;
        if (!hasDiffuse) {
            for (const MaterialPhoto& photo : kMaterialPhotos) {
                if (name.rfind(photo.prefix, 0) != 0)
                    continue;
                Texture texture;
                texture.id = SharedTexture(photo.file);
                texture.type = "texture_diffuse";
                texture.path = photo.file;
                result.textures.push_back(texture);
                result.triplanar = true;
                result.triplanarScale = photo.repetitions;
                break;
            }
        }

        return result;
    }

	void ReadNodeHierarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform)
	{
		if (pNode == nullptr || scene == nullptr) return;

		string NodeName(pNode->mName.data);

		const aiAnimation* pAnimation = scene->mAnimations[0];

		//cout << NodeName << endl;
		
		if (pAnimation == nullptr) return;

		//cout << "valid animation" << endl;

		//aiMatrix4x4 NodeTransformation(pNode->mTransformation);
		aiMatrix4x4 NodeTransformation;

		const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
		
		if (pNodeAnim != nullptr) {
			aiVector3D Scaling;
			CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
			aiMatrix4x4 ScalingM;
			if (ScalingM.IsIdentity()) 
				aiMatrix4x4::Scaling(Scaling, ScalingM);

			aiQuaternion RotationQ;
			CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
			aiMatrix4x4 RotationM(RotationQ.GetMatrix());

			aiVector3D Translation;
			CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
			aiMatrix4x4 TranslationM;
			if (ScalingM.IsIdentity())
				aiMatrix4x4::Translation(Translation, TranslationM);

			// Combine the above transformations
			NodeTransformation = TranslationM * RotationM * ScalingM;

			// cout << "Compute Node Transformation: " << pNodeAnim->mNodeName.data << endl;
		}

		glm::mat4 GlobalTransformation = ParentTransform * aiMatrix4x4ToGlm(NodeTransformation);

		//cout << "GT=" << glm::to_string(GlobalTransformation) << endl;

		// cout << "Parent: " << NodeName << endl;

		// Modify bones transformation
		for (unsigned int b = 0; b < bones.size(); b++) {
			if (bones[b].name == pNode->mName) {
				bones[b].transformation =  m_GlobalInverseTransform * GlobalTransformation*bones[b].offsetMatrix;
				//cout << "bone: " << b << " : " << bones[b].name.data << " T= " << glm::to_string(bones[b].transformation) << endl;
			}
		}

		for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
			// cout << "Child: " << pNode->mChildren[i]->mName.data << ": " << i << endl;
			ReadNodeHierarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
		}
	}

	const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
	{
		for (unsigned int i = 0; i < pAnimation->mNumChannels; i++) {
			const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

			if (string(pNodeAnim->mNodeName.data) == NodeName) {
				return pNodeAnim;
			}
		}

		return nullptr;
	}

	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		if (pNodeAnim->mNumScalingKeys == 1) {
			Out = pNodeAnim->mScalingKeys[0].mValue;
			return;
		}

		unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
		unsigned int NextScalingIndex = (ScalingIndex + 1);
		assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
		float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
		float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
		const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
		aiVector3D Delta = End - Start;
		Out = Start + Factor * Delta;
	}

	unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		assert(pNodeAnim->mNumScalingKeys > 0);

		for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
			if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
				return i;
			}
		}

		assert(0);

		return 0;
	}

	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		// we need at least two values to interpolate...
		if (pNodeAnim->mNumRotationKeys == 1) {
			Out = pNodeAnim->mRotationKeys[0].mValue;
			return;
		}

		unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
		unsigned int NextRotationIndex = (RotationIndex + 1);
		assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
		float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
		float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
		const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
		aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
		Out = Out.Normalize();
	}

	unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		assert(pNodeAnim->mNumRotationKeys > 0);

		for (unsigned int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
			if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
				return i;
			}
		}

		assert(0);

		return 0;
	}

	unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
			if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
				return i;
			}
		}

		assert(0);

		return 0;
	}

	void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
	{
		if (pNodeAnim->mNumPositionKeys == 1) {
			Out = pNodeAnim->mPositionKeys[0].mValue;
			return;
		}

		unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
		unsigned int NextPositionIndex = (PositionIndex + 1);
		assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
		float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
		float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
		assert(Factor >= 0.0f && Factor <= 1.0f);
		const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
		const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
		aiVector3D Delta = End - Start;
		Out = Start + Factor * Delta;
	}

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
    {
        vector<Texture> textures;
        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for(unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if(!skip)
            {   // if texture hasn't been loaded already, load it
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), this->directory);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
    }
};

#endif
