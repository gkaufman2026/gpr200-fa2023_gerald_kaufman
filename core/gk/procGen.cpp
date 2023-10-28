#include "../ew/ewMath/ewMath.h"
#include "procGen.h"

ew::MeshData gk::createSphere(float radius, int numSegments) {
    ew::MeshData mesh;
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

ew::MeshData gk::createPlane(float width, float height, int subdivisions) {
    ew::MeshData mesh;
    int indices, columns = subdivisions + 1;
    for (int row = 0; row <= subdivisions; row++) {
        for (int col = 0; col <= subdivisions; col++) {
            ew::Vertex vertex;
            vertex.pos.x =  width * col / (float)subdivisions;
            vertex.pos.y = height * row / (float)subdivisions;

            vertex.normal = ew::Vec3(0.0f, 0.0f, -1.0f);
            vertex.uv = ew::Vec2(width * (float) col / subdivisions), height * ((float) row / subdivisions);

            mesh.vertices.push_back(vertex);

            indices = row * subdivisions + col;

            mesh.indices.push_back(indices);
            mesh.indices.push_back(indices + 1);
            mesh.indices.push_back(indices + columns + 1);

            //mesh.indices.push_back(indices + 3 + subdivisions);
            //mesh.indices.push_back(indices + 2 + subdivisions);
            //mesh.indices.push_back(indices + 1);
        }
    }

    return mesh;
}