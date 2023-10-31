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

    float topHeight = height / 2.0f, bottomHeight = -topHeight, thetaStep = ew::TAU / numSegments, theta;
    ew::Vertex top, bottom, topVertex, bottomVertex;

    top.pos = ew::Vec3(0, topHeight, 0);
    mesh.vertices.push_back(top);

    for (int i = 0; i <= numSegments; i++) {
        theta = i * thetaStep;
        topVertex.pos.x = cos(theta) * radius;
        topVertex.pos.z = sin(theta) * radius;
        topVertex.pos.y = topHeight;
        mesh.vertices.push_back(topVertex);

        mesh.indices.push_back(i);
        mesh.indices.push_back(0);
        mesh.indices.push_back(i + 1);
    }

    bottom.pos = ew::Vec3(0, bottomHeight, 0);
    mesh.vertices.push_back(bottom);

    for (int i = 0; i <= numSegments; i++) {
        theta = i * thetaStep;
        bottomVertex.pos.x = cos(theta);
        bottomVertex.pos.z = sin(theta);
        bottomVertex.pos.y = bottomHeight;
        mesh.vertices.push_back(bottomVertex);

        mesh.indices.push_back(numSegments + i + 2);
        mesh.indices.push_back(numSegments + 2);
        mesh.indices.push_back(numSegments + i + 3);
    }

    for (int i = 0; i < numSegments; i++) {
        int startIndices = i + 1;

        mesh.indices.push_back(startIndices);
        mesh.indices.push_back(startIndices + 1);
        mesh.indices.push_back(startIndices + numSegments + 2);

        mesh.indices.push_back(startIndices + 1);
        mesh.indices.push_back(startIndices + numSegments + 3);
        mesh.indices.push_back(startIndices + numSegments + 2);
    }

    return mesh;
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