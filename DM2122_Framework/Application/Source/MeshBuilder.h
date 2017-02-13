#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateCircle(const std::string &meshName, Color color, unsigned numSlices = 10.0f,float radius = 1.0f);
	static Mesh* GenerateRing(const std::string &meshName, Color color, unsigned numSlices = 10.0f, float outerRadius = 1.0f, float innerRadius = 0.5f);
	static Mesh* GenerateHemisphere(const std::string &meshName, Color color, unsigned numStacks = 10.f, unsigned numSlices = 10.0f, float radius = 1.0f);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numStacks = 10.f, unsigned numSlices = 36.f,  float radius = 1.0f);
	static Mesh* GenerateCylinder(const std::string &meshName, Color color, unsigned numSlices = 36.f, float radius = 1.0f, float height = 10.f);
	static Mesh* GenerateCone(const std::string &meshName, Color color, unsigned numSlices = 36.f, float radius = 1.0f, float height = 10.f);
	static Mesh* GenerateTorus(const std::string &meshName, Color color, unsigned numStacks = 10.f, unsigned numSlices = 36.f, float outerRadius = 2.f, float innerRadius = 1.f);

	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif