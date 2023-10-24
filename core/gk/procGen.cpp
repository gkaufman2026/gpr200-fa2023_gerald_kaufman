#include "ewMath/ewMath.h"
#include "procGen.h"

ew::MeshData gk::createSphere(float radius, int numSegments) {
    ew::MeshData mesh;
    return mesh;
}

ew::MeshData gk::createCylinder(float height, float radius, int numSegments) {
    ew::MeshData mesh;
    float thetaStep = TAU / numSegments, theta;

    for (int i = 0; i <= numSegments; i++) {
        theta = i * thetaStep;
        mesh.vertices.push_back(cos(theta));
        mesh.vertices.push_back(sin(theta));
        mesh.vertices.push_back(0);
    }

    return mesh;
}

ew::MeshData gk::createPlane(float size, int subdivisions) {
    ew::MeshData mesh;
    return mesh;
}