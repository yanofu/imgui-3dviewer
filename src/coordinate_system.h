#pragma once
#include "imgui.h"
#include <glm/glm.hpp>

class CoordinateSystem3D
{
public:
    CoordinateSystem3D(glm::vec3 origin, glm::vec3 axisX, glm::vec3 axisY, glm::vec3 axisZ)
    : origin(origin),
    axisX(axisX),
    axisY(axisY),
    axisZ(axisZ)
    {
    }
    
    ~CoordinateSystem3D()
    {
    }

    static CoordinateSystem3D Create()
    {
        return CoordinateSystem3D(
                glm::vec3(0.0, 0.0, 0.0),
                glm::vec3(50.0, 0.0, 0.0),
                glm::vec3(0.0, 50.0, 0.0),
                glm::vec3(0.0, 0.0, 50.0));
    }

    std::vector<glm::vec3> ToArray() const
    {
        return std::vector<glm::vec3>{
            origin,
            axisX,
            axisY,
            axisZ};
    }

private:
    glm::vec3 origin;
    glm::vec3 axisX;
    glm::vec3 axisY;
    glm::vec3 axisZ;
};


class CoordinateSystem2D
{
public:
    CoordinateSystem2D(glm::vec2 origin, glm::vec2 axisX, glm::vec2 axisY, glm::vec2 axisZ)
    : origin(origin),
    axisX(axisX),
    axisY(axisY),
    axisZ(axisZ)
    {
    }
    
    ~CoordinateSystem2D()
    {
    }

    static CoordinateSystem2D FromArray(const std::vector<glm::vec2>& array)
    {
        return CoordinateSystem2D(
            array[0],
            array[1],
            array[2],
            array[3]
        );
    }

    ImVec2 Origin() const
    {
        return ImVec2(origin.x, origin.y);
    }

    ImVec2 AxisX() const
    {
        return ImVec2(axisX.x, axisX.y);
    }

    ImVec2 AxisY() const
    {
        return ImVec2(axisY.x, axisY.y);
    }

    ImVec2 AxisZ() const
    {
        return ImVec2(axisZ.x, axisZ.y);
    }

private:
    glm::vec2 origin;
    glm::vec2 axisX;
    glm::vec2 axisY;
    glm::vec2 axisZ;
};