#pragma once

#include "screen.h"
#include "clip.h"

class Camera
{
public:
    Camera(){};
    Camera(const glm::vec3 eye, const glm::vec3 lookat, const glm::vec3 up)
        : eye_(eye), lookat_(lookat), up_(up)
    {
        view_ = glm::lookAt(eye_, lookat_, up_);
    }

    glm::mat4 GetViewMatrix() const { return view_; }
    glm::vec3 GetEye() const { return eye_; }
    glm::vec3 GetUp() const { return up_; }
    glm::vec3 GetLookAt() const { return lookat_; }
    glm::vec3 GetViewDir() const { return -glm::transpose(view_)[2]; }
    glm::vec3 GetRightVector() const { return glm::transpose(view_)[0]; }

    void SetCameraView(glm::vec3 eye, glm::vec3 lookat, glm::vec3 up)
    {
        eye_ = eye;
        lookat_ = lookat;
        up_ = up;
        view_ = glm::lookAt(eye_, lookat_, up_);
    }

    glm::vec2 ProjectToScreen(const Screen& screen, const Clip& clip, const glm::vec3& point)
    {
        auto projected_viewport = glm::project(point, view_, clip.GetProjection(), screen.GetViewPort());
        auto projected_screen = glm::vec2(screen.GetViewPortTrans() * glm::vec3(projected_viewport.x, projected_viewport.y, 1));
        return projected_screen;
    }

private:
    glm::mat4 view_;
    glm::vec3 eye_;
    glm::vec3 lookat_;
    glm::vec3 up_;
};

