#pragma once
#include "imgui.h"
#include <glm/glm.hpp>

struct CoordinateSystem
{
    CoordinateSystem(glm::vec2 origin, glm::vec2 axisX, glm::vec2 axisY, glm::vec2 axisZ)
    : origin(ImVec2(origin.x, origin.y)),
    axisX(ImVec2(axisX.x, axisX.y)),
    axisY(ImVec2(axisY.x, axisY.y)),
    axisZ(ImVec2(axisZ.x, axisZ.y))
    {
    }
    
    ImVec2 origin;
    ImVec2 axisX;
    ImVec2 axisY;
    ImVec2 axisZ;
};