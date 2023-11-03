#pragma once
#include "../ew/mesh.h"

namespace gk {
	ew::MeshData createSphere(float radius, int numSegments);
	ew::MeshData createCylinder(float height, float radius, int numSegments);
	ew::MeshData createPlane(float size, int subdivisions);
	void createCylinderRingTOBFace(ew::MeshData &meshData, ew::Vec3 normal, float yPos, float radius, int segments);
	void createCylinderRingSideFace(ew::MeshData &meshData, float yPos, float radius, float uv, int segments);
}
