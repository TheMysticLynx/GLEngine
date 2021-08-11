#pragma once
#pragma once

#include <fstream>

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/fwd.h"
#include "rapidjson/document.h"
#include "rapidjson/fwd.h"
#include <vector>
#include "Mesh.h"
#include "JSON.h"

using json = nlohmann::json;
using namespace std;

namespace GLTFImporter {

	struct GLTFExport {
		vector<Camera> cameras;
		//Lights vector<Light> lights
		vector<Mesh> meshes;
	};

	GLTFExport TransverseNode(int index, json& document, unsigned char* binData);

	//C = Cast
	template<typename T, typename C = T>
	vector<C> ProcessData(json document, int index, unsigned char* data) {
		int byteLength = document["bufferViews"][index]["byteLength"] / sizeof(T);
		int byteOffset = document["bufferViews"][index]["byteOffset"] / sizeof(T);

		T* pointer = reinterpret_cast<T*>(data);
		
		int i = 0;

		vector<C> dataVector;
		while (pointer + i != pointer + byteLength) {
			dataVector.push_back( (C)*(pointer + i));
			cout << *(pointer + i) << endl;
			i++;
		}

		return dataVector;
	}

	GLTFExport GetData(const char* filePath, const char* fileName) {
		std::fstream stream(std::string(filePath) + std::string(fileName));
		std::string jsonString;
		jsonString.assign(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());

		json Document = json::parse(jsonString);

		ifstream binFile(std::string(filePath) + (string)Document["buffers"][0]["uri"], ios::in | ios::binary);
		vector<unsigned char> dataVector(std::istreambuf_iterator<char>(binFile), {});

		TransverseNode(0, Document, dataVector.data());
		return GLTFExport();
	}

	GLTFExport TransverseNode(int index, json& document, unsigned char* binData) {
		json node = document["nodes"][index];

		vector<Camera> cameras;
		vector<Mesh> meshVector;

		if (node.find("mesh") != node.end()) {
			int MESH_INDEX = node["mesh"];

			json MeshJsonArray = document["meshes"][MESH_INDEX];

			int POSITION_INDEX = MeshJsonArray["primitives"][0]["attributes"]["POSITION"];
			int NORMAL_INDEX = MeshJsonArray["primitives"][0]["attributes"]["NORMAL"];
			int TEXCOORD_INDEX = MeshJsonArray["primitives"][0]["attributes"]["TEXCOORD_0"];
			int INDICES_INDEX = MeshJsonArray["primitives"][0]["indices"];
			int MATERIAL_INDEX = MeshJsonArray["primitives"][0]["material"];
			 
			vector<float> positions = ProcessData<float>(document, POSITION_INDEX, binData);
			vector<float> normals = ProcessData<float>(document, NORMAL_INDEX, binData);
			vector<float> texcoords = ProcessData<float>(document, TEXCOORD_INDEX, binData);
			vector<GLuint> indexes = ProcessData<float, unsigned int>(document, INDICES_INDEX, binData);
			
			vector<Vertex> vertVector;
			for (int i = 0; i < positions.size() / 3; i++) {
				vertVector.push_back(Vertex{
					//Pos Normal Color UV
						glm::vec3(positions[(i * 3) + 0], positions[(i * 3) + 1], positions[(i * 3) + 2]),
						glm::vec3(normals[(i * 3) + 0], normals[(i * 3) + 1], normals[(i * 3) + 2]),
						glm::vec3(1, 1, 1),
						glm::vec2(texcoords[(i * 2) + 0], texcoords[(i * 2) + 1])
					});
			}

			vector<Mesh>().push_back(Mesh(vector<Vertex>(), indexes, vector<Texture>()));
		}

		if (index < document["nodes"].size() - 1) {
			GLTFExport e = TransverseNode(index + 1, document, binData);

			cameras.insert(cameras.end(), e.cameras.begin(), e.cameras.end());
			meshVector.insert(meshVector.end(), e.meshes.begin(), e.meshes.end());
		}

		return GLTFExport{
			cameras,
			meshVector
		};
	}

}