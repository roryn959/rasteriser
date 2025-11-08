#include "Model/TriangleBasedPyramid.h"

TriangleBasedPyramid::TriangleBasedPyramid(Point p1, Point p2, Point p3, Point p4, Colour colour) :
    m_points{p1, p2, p3, p4},
    m_centreOfMass{ 0, 0, 0 },
    m_transformedPoints{p1, p2, p3, p4},
    m_colour{colour},
    m_translation{ 0, 0, 0 },
    m_rotation{IDENTITY}
{
    for (const Point& point : m_points) {
        m_centreOfMass.m_x += point.m_x;
        m_centreOfMass.m_y += point.m_y;
        m_centreOfMass.m_z += point.m_z;
    }

    m_centreOfMass.m_x /= 4.0f;
    m_centreOfMass.m_y /= 4.0f;
    m_centreOfMass.m_z /= 4.0f;
}

std::vector<Triangle> TriangleBasedPyramid::GetTriangles() {
    std::vector<Triangle> triangles;

    triangles.push_back({ m_transformedPoints[2], m_transformedPoints[1], m_transformedPoints[0], m_colour });
    triangles.push_back({ m_transformedPoints[0], m_transformedPoints[1], m_transformedPoints[3], m_colour });
    triangles.push_back({ m_transformedPoints[1], m_transformedPoints[2], m_transformedPoints[3], m_colour });
    triangles.push_back({ m_transformedPoints[0], m_transformedPoints[2], m_transformedPoints[3], m_colour });
    return triangles;
}

void TriangleBasedPyramid::ShiftX(float dx) {
    m_translation.m_x += dx;

    m_centreOfMass.m_x += dx;
    UpdateTransformedPoints();
}

void TriangleBasedPyramid::ShiftY(float dy) {
    m_translation.m_y += dy;

    m_centreOfMass.m_y += dy;
    UpdateTransformedPoints();
}

void TriangleBasedPyramid::ShiftZ(float dz) {
    m_translation.m_z += dz;

    m_centreOfMass.m_z += dz;
    UpdateTransformedPoints();
}

void TriangleBasedPyramid::RotateOnX(float theta) {
    Matrix<float, 3, 3> Rz{
        { 1, 0, 0 },
        { 0, cos(theta), -sin(theta) },
        { 0, sin(theta), cos(theta) }
    };

    m_rotation =  Rz * m_rotation;
    UpdateTransformedPoints();

    std::cout << m_rotation;
}

void TriangleBasedPyramid::RotateOnY(float theta) {
    Matrix<float, 3, 3> Rz{
        { cos(theta), -sin(theta), 0 },
        { sin(theta), cos(theta), 0 },
        { 0, 0, 1 }
    };

    m_rotation =  Rz * m_rotation;
    UpdateTransformedPoints();
}

void TriangleBasedPyramid::RotateOnZ(float theta) {
    Matrix<float, 3, 3> Rz{
        { cos(theta), -sin(theta), 0 },
        { sin(theta), cos(theta), 0 },
        { 0, 0, 1 }
    };

    m_rotation =  Rz * m_rotation;
    UpdateTransformedPoints();
}

void TriangleBasedPyramid::UpdateTransformedPoints() {
    for (int i=0; i < 4; ++i) {
        const Point& point = m_points[i] - m_centreOfMass;
        Point translatedPoint{ point.m_x + m_translation.m_x, point.m_y + m_translation.m_y, point.m_z + m_translation.m_z };
        Point transformedPoint = m_rotation * translatedPoint;
        m_transformedPoints[i] = transformedPoint + m_centreOfMass;
    }
}