#include "../ew/ewMath/ewMath.h"
#include "procGen.h"

ew::MeshData gk::createSphere(float radius, int numSegments) {
    ew::MeshData mesh;
    float thetaStep = ew::TAU / numSegments, phiStep = ew::PI / numSegments, phi, theta;
    int row, col, i, poleStart, sideStart;

    for (row = 0; row <= numSegments; row++) {
        phi = row * phiStep;
        for (col = 0; col <= numSegments; col++) {
            theta = col * thetaStep;
            ew::Vertex vertex;

            vertex.pos.x = radius * cos(theta) * sin(phi);
            vertex.pos.y = radius * cos(phi);
            vertex.pos.z = radius * sin(theta) * sin(phi);

            vertex.normal = ew::Normalize(vertex.pos - ew::Vec3(0, 0, 0));

            vertex.uv.x = theta / ew::TAU;
            vertex.uv.y = 1 - (phi / ew::PI);

            mesh.vertices.push_back(vertex);
        }
    }

    poleStart = 0;
    sideStart = numSegments + 1;

    for (i = 0; i < numSegments; i++) {
        mesh.indices.push_back(sideStart + i);
        mesh.indices.push_back(poleStart + i);
        mesh.indices.push_back(sideStart + i + 1);
    }

    int columns = numSegments + 1, start;
    for (row = 1; row < numSegments - 1; row++) {
        for (col = 0; col < numSegments; col++) {
            start = row * columns + col;

            mesh.indices.push_back(start);
            mesh.indices.push_back(start + 1);
            mesh.indices.push_back(start + columns);
            mesh.indices.push_back(start + columns);
            mesh.indices.push_back(start + 1);
            mesh.indices.push_back(start + columns + 1);
        }
    }

    poleStart = mesh.vertices.size() - numSegments - 1;
    sideStart = poleStart - numSegments - 1;

    for (i = 0; i < numSegments; i++) {
        mesh.indices.push_back(sideStart + i);
        mesh.indices.push_back(sideStart + i + 1);
        mesh.indices.push_back(poleStart + i);
    }

    return mesh;
}

ew::MeshData gk::createCylinder(float height, float radius, int numSegments) {
    ew::MeshData mesh;

    float topHeight = height / 2.0f, bottomHeight = -topHeight;
    ew::Vertex top, bottom;
    int i;

    top.pos = ew::Vec3(0, topHeight, 0);
    mesh.vertices.push_back(top);

    bottom.pos = ew::Vec3(0, bottomHeight, 0);
    mesh.vertices.push_back(bottom);

    return mesh;
}

void createCylinderRingTOBFace(ew::MeshData& meshData, ew::Vec3 normal, float yPos, float radius, int segments) {
    float thetaStep = ew::TAU / segments, theta;
    int i;
    for (i = 0; i <= segments; i++) {
        theta = i * thetaStep;
        ew::Vertex vertex;

        vertex.pos.x = cos(theta) * radius;
        vertex.pos.z = sin(theta) * radius;
        vertex.pos.y = yPos;
        vertex.normal = normal;
        vertex.uv = ew::Vec2((cos(theta) + 1) * 0.5, (sin(theta) + 1) * 0.5);
        meshData.vertices.push_back(vertex);
    }
}

void createCylinderRingSideFace(ew::MeshData& meshData, float yPos, float radius, float uv, int segments) {
    float thetaStep = ew::TAU / segments, theta;
    int i;
    for (i = 0; i <= segments; i++) {
        theta = i * thetaStep;
        ew::Vertex vertex;

        vertex.pos.x = cos(theta) * radius;
        vertex.pos.z = sin(theta) * radius;
        vertex.pos.y = yPos;
        vertex.normal = ew::Normalize(ew::Vec3(cos(theta), 0, sin(theta)));
        vertex.uv = ew::Vec2((cos(theta) + 1) * 0.5, uv);
        meshData.vertices.push_back(vertex);
    }
}

ew::MeshData gk::createPlane(float size, int subdivisions) {
    ew::MeshData mesh;
    int row, col, columns = subdivisions + 1, start;

    for (row = 0; row <= subdivisions; row++) {
        for (col = 0; col <= subdivisions; col++) {
            ew::Vertex vertex;

            vertex.pos.x = size * static_cast<float>(col) / subdivisions;
            vertex.pos.z = -size * static_cast<float>(row) / subdivisions;

            vertex.uv.x = (static_cast<float>(col) / subdivisions);
            vertex.uv.y = (static_cast<float>(row) / subdivisions);

            vertex.normal = ew::Vec3(0.0, 1.0, 0.0);
            mesh.vertices.push_back(vertex);
        }
    }
    
    for (row = 0; row < subdivisions; row++) {
        for (col = 0; col < subdivisions; col++) {
            start = row * columns + col;

            mesh.indices.push_back(start);
            mesh.indices.push_back(start + 1);
            mesh.indices.push_back(start + columns + 1);

            mesh.indices.push_back(start + columns + 1);
            mesh.indices.push_back(start + columns);
            mesh.indices.push_back(start);
        }
    }

    return mesh;
}