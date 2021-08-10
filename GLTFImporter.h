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

	GLTFExport TransverseNode(int index, json& document);

	GLTFExport GetData(const char* filePath, const char* fileName) {
		std::fstream stream(std::string(filePath) + std::string(fileName));

		std::string jsonString;
		jsonString.assign(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());

		json Document = json::parse(jsonString);

		TransverseNode(0, Document);
		return GLTFExport();
	}

	GLTFExport TransverseNode(int index, json& document) {
		json node = document["nodes"][index];

		vector<Camera> cameras;
		vector<Mesh> meshes;

		if (node.find("mesh") != node.end()) {
			//Load Mesh
			 
		}

		if (index < document["nodes"].size() - 1) {
			GLTFExport e = TransverseNode(index + 1, document);

			cameras.insert(cameras.end(), e.cameras.begin(), e.cameras.end());
			meshes.insert(meshes.end(), e.meshes.begin(), e.meshes.end());
		}

		return GLTFExport{
			cameras,
			meshes
		};
	}

}