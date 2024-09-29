#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "imgui.h"

template<typename T, typename U>
class VecConverter
{
public:
    static T Convert(const U& vec)
    {
        static_assert(sizeof(T) == 0, "Unsupported conversion");
        return {};
    }
};

template<>
glm::vec2 VecConverter<glm::vec2, ImVec2>::Convert(const ImVec2& vec)
{
    return {vec.x, vec.y};
}

template<>
glm::vec4 VecConverter<glm::vec4, ImVec4>::Convert(const ImVec4& vec) 
{
    return {vec.x, vec.y, vec.z, vec.w};
}

template<>
ImVec2 VecConverter<ImVec2, glm::vec2>::Convert(const glm::vec2& vec)
{
    return {vec.x, vec.y};
}

template<>
ImVec4 VecConverter<ImVec4, glm::vec4>::Convert(const glm::vec4& vec)
{
    return {vec.x, vec.y, vec.z, vec.w};
}