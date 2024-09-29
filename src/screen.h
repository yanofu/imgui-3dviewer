#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Screen
{
public:
    Screen(){};
    ~Screen(){};
    Screen(const glm::vec2 leftTopInWindow, const glm::vec2 windowSize)
        : leftTopInWindow(leftTopInWindow), windowSize(windowSize)
    {
    }

    glm::mat3 ToTransform() const
    {
        return {
            glm::vec3(windowSize.x, 0, 0),
            glm::vec3(0, windowSize.y, 0),
            glm::vec3(leftTopInWindow.x, leftTopInWindow.y, 1)};
    }
    
    glm::vec4 ToTransformVector() const
    {
         return {windowSize.x, windowSize.y, leftTopInWindow.x, leftTopInWindow.y};
    }

    glm::vec4 ToFixedScaleTransformVector() const
    {
         return {windowSize.x, windowSize.x, leftTopInWindow.x, leftTopInWindow.y};
    }

private:
    glm::vec2 leftTopInWindow;
    glm::vec2 windowSize;
};