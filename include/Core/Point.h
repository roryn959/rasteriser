#pragma once

struct Point {
    float m_x;
    float m_y;
    float m_z;

    Point operator+(const Point& rhs) const {
        return Point{ m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z };
    }

    Point operator-(const Point& rhs) const {
        return Point{ m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z };
    }
};