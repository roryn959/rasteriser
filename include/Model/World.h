#pragma once

#include <vector>

#include "Core/Triangle.h"
#include "TriangleBasedPyramid.h"
#include "View/Paintbrush.h"

#define WORLD_SPEED 1.0
#define LOOK_SENSITIVITY 2.0

class World {
public:
    World(Paintbrush& paintbrush);

    void Paint();

    void MovePovX(float dx);
    void MovePovY(float dy);
    void MovePovZ(float dz);

    void RotatePovX(float theta);
    void RotatePovY(float theta);

    void ProcessTimeTick(float dt);

    void MoveRight();
    void MoveLeft();
    void MoveForward();
    void MoveBackward();
    void MoveUp();
    void MoveDown();

    void UnMoveRight();
    void UnMoveLeft();
    void UnMoveForward();
    void UnMoveBackward();
    void UnMoveUp();
    void UnMoveDown();

    void RotateUp();
    void RotateDown();
    void RotateRight();
    void RotateLeft();

    void UnRotateUp();
    void UnRotateDown();
    void UnRotateRight();
    void UnRotateLeft();

private:
    Paintbrush&                         m_paintbrush;

    std::vector<Triangle>               m_triangles;
    std::vector<TriangleBasedPyramid>   m_triangleBasedPyramids;

    float                               m_xVelocity;
    float                               m_yVelocity;
    float                               m_zVelocity;    

    float                               m_xRotationVelocity;
    float                               m_yRotationVelocity;

};