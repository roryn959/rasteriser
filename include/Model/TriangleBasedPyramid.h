#pragma once

#include <cstddef>
#include <iostream>
#include <math.h>
#include <vector>

#include "Core/Colour.h"
#include "Core/Triangle.h"
#include "Core/Point.h"
#include "Model/Matrix.h"

class TriangleBasedPyramid {
public:
    TriangleBasedPyramid(Point p1, Point p2, Point p3, Point p4, Colour colour);

    inline Point operator[](size_t i) { return m_points[i]; }

    inline Colour GetColour() { return m_colour; }
    std::vector<Triangle> GetTriangles(); // Optimise this!!

    void ShiftX(float dx);
    void ShiftY(float dy);
    void ShiftZ(float dz);

    void RotateOnX(float theta);
    void RotateOnY(float theta);
    void RotateOnZ(float theta);

private:
    void UpdateTransformedPoints();

    const Point m_points[4];
    Point m_centreOfMass;
    Point m_transformedPoints[4];
    const Colour m_colour;
    Point m_translation;
    Matrix<float, 3, 3> m_rotation;
};