#pragma once

#include "screen.h"
#include "clip.h"

class Camera
{
public:
    Camera(){};
    Camera(const glm::vec3 position, const glm::vec3 target, const glm::vec3 up)
        : position(position), target(target), up(up)
    {
        view = glm::lookAt(position, target, up);
    }

    static Camera CreateWorldCamera()
    {
        const auto initialPosition = glm::vec3(20, 20, 20);
        const auto initialTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        const auto initialUp = glm::vec3(0.0f, 1.0f, 0.0f);
        return Camera(initialPosition, initialTarget, initialUp);
    }

    glm::mat4 GetViewMatrix() const { return view; }
    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetUp() const { return up; }
    glm::vec3 GetTarget() const { return target; }
    glm::vec3 GetViewDir() const { return -glm::transpose(view)[2]; }
    glm::vec3 GetRightVector() const { return glm::transpose(view)[0]; }

    glm::vec2 ProjectToScreen(const Screen& screen, const Clip& clip, const glm::vec3& point)
    {
        auto projectedViewport = glm::project(point, view, clip.GetProjection(), screen.GetViewPort());
        auto projectedScreen = glm::vec2(screen.GetViewPortTrans() * glm::vec3(projectedViewport.x, projectedViewport.y, 1));
        return projectedScreen;
    }

private:
    glm::mat4 view;
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
};

