#pragma once

#include "screen.h"
#include "clip.h"
#include "coordinate_system.h"
#include <vector>
#include <array>

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


    CoordinateSystem3D CoordinateSystem() const
    {
        return CoordinateSystem3D(
                position,
                glm::inverse(view) * glm::vec4(25.0, 0.0, 0.0, 1.0),
                glm::inverse(view) * glm::vec4(0.0, 25.0, 0.0, 1.0),
                glm::inverse(view) * glm::vec4(0.0, 0.0, 25.0, 1.0));
    }

    std::vector<glm::vec2> Capture(const std::vector<glm::vec3>& object, const Clip& clip)
    {
        std::vector<glm::vec2> capturedPoints;
        const glm::vec4 viewport(0, 0, 1.0, 1.0);
        for(const glm::vec3& point : object)
        {
            capturedPoints.push_back(
                glm::project(
                    point,
                    view,
                    clip.GetProjection(),
                    viewport)
                );
        }

        return capturedPoints;
    }

    std::vector<glm::vec2> Capture(const std::vector<std::array<double, 3>>& object, const Clip& clip)
    {
        std::vector<glm::vec2> capturedPoints;
        const glm::vec4 viewport(0, 0, 1.0, 1.0);
        for(const std::array<double, 3>& point : object)
        {
            capturedPoints.push_back(
                glm::project(
                    glm::vec3(point[0], point[1], point[2]),
                    view,
                    clip.GetProjection(),
                    viewport)
                );
        }

        return capturedPoints;
    }

private:
    glm::mat4 view;
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
};

