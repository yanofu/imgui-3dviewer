#pragma once

#include "screen.h"
#include "clip.h"

class Camera
{
public:
    Camera(){};
    Camera(const glm::vec3 eye, const glm::vec3 lookat, const glm::vec3 up)
        : eye(eye), lookat(lookat), up(up)
    {
        view = glm::lookAt(eye, lookat, up);
    }

    static Camera CreateWorldCamera()
    {
        const auto initialEye = glm::vec3(20, 20, 20);
        const auto initialLookat = glm::vec3(0.0f, 0.0f, 0.0f);
        const auto initialUp = glm::vec3(0.0f, 1.0f, 0.0f);
        return Camera(initialEye, initialLookat, initialUp);
    }

    glm::mat4 GetViewMatrix() const { return view; }
    glm::vec3 GetEye() const { return eye; }
    glm::vec3 GetUp() const { return up; }
    glm::vec3 GetLookAt() const { return lookat; }
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
    glm::vec3 eye;
    glm::vec3 lookat;
    glm::vec3 up;
};

