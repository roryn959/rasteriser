#include "Model/World.h"

World::World(Paintbrush& paintbrush) :
    m_paintbrush{paintbrush},
    m_triangles{},
    m_triangleBasedPyramids{}
{
    Triangle redTriangle{ { -40, 30, 1 }, { -5, 40, 1 }, { -15, -15, 1 }, COLOUR_RED };
    Triangle blueTriangle{ { -40, 30, 3 }, { -5, 40, 1.2 }, { -15, -15, 1.2 }, COLOUR_BLUE };

    m_triangles.push_back(redTriangle);
    m_triangles.push_back(blueTriangle);

    TriangleBasedPyramid tbp1{ {-25, 0, 4}, {0, 25, 4}, {25, 0, 4}, {5, 5, 3}, COLOUR_BLUE};
    m_triangleBasedPyramids.push_back(tbp1);
}

void World::Paint() {
    for (Triangle& triangle : m_triangles) 
        m_paintbrush.PaintTriangle(triangle);

    for (TriangleBasedPyramid& triangleBasedPyramid : m_triangleBasedPyramids) {
        for (Triangle& triangle : triangleBasedPyramid.GetTriangles())
        {
            m_paintbrush.PaintTriangle(triangle);
        }
    }
}

void World::ProcessTimeTick(float dt) {
    m_triangles[0].ShiftZ(dt);
    m_triangleBasedPyramids[0].RotateOnX((M_PI / 10.0f) * dt);
    //m_triangleBasedPyramids[0].ShiftX(5 * dt);
    //m_triangleBasedPyramids[0].ShiftY(10 * dt);
}