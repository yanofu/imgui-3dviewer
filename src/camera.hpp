#pragma once

#include "screen.h"
#include "clip.h"
#include "coordinate_system.h"
#include <vector>
#include <array>

#include <glm/gtx/string_cast.hpp>

class Camera
{
public:
    Camera(){};
    Camera(const glm::vec3 position, const glm::vec3 target, const glm::vec3 up, const Clip& clip)
        : position(position), target(target), up(up), clip(clip)
    {
        view = glm::lookAt(position, target, up);
    }

    static Camera CreateCamera(const glm::vec3 position, const glm::vec3 target, const glm::vec3 up)
    {
        const auto clip = Clip(200.0f, 200.0f, 10.f, 1000.f);
        return Camera(position, target, up, clip);
    }

    static Camera CreateDefaultCamera()
    {
        const auto initialPosition = glm::vec3(0, 0, 100);
        const auto initialTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        const auto initialUp = glm::vec3(0.0f, 1.0f, 0.0f);
        const auto clip = Clip(200.0f, 200.0f, 10.f, 1000.f);
        return Camera(initialPosition, initialTarget, initialUp, clip);
    }

    static Camera CreateWorldCamera()
    {
        const auto initialPosition = glm::vec3(20, 20, 20);
        const auto initialTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        const auto initialUp = glm::vec3(0.0f, 1.0f, 0.0f);
        const auto clip = Clip(200.0f, 200.0f, 10.f, 1000.f);
        return Camera(initialPosition, initialTarget, initialUp, clip);
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

    std::vector<glm::vec2> Capture(const std::vector<glm::vec3>& object) const
    {
        std::vector<glm::vec2> capturedPoints;
        const glm::vec4 viewport(0, 1, 1.0, -1.0);
        for(const auto& point : object)
        {
            capturedPoints.emplace_back(
                glm::project(
                    point,
                    view,
                    clip.GetProjection(),
                    viewport)
                );
        }

        return capturedPoints;
    }

    std::vector<glm::vec2> Capture(const std::vector<std::array<double, 3>>& object) const
    {
        std::vector<glm::vec2> capturedPoints;
        const glm::vec4 viewport(0, 1, 1.0, -1.0);
        for(const auto& point : object)
        {
            // Local Space(3D) -[view]-> Camera View Space(3D)
            // Camera View Space(3D) -[clip.GetProjection]-> Clip Space(2D): -1 <= x <= 1, -1 <= y <= 1, origin is center
            // Clip Space(2D) -[in glm::project]-> Normailzed Clip Space(2D): 0 <= x <= 1, 0 <= y <= 1, origin is bottom-left
            // Normailzed Clip Space(2D) -[viewport]-> Normalized Screen Space(2D): 0 <= x <= 1, 0 <= y <= 1, origin is top-left, invert y-axis, move +1 y-axis
            capturedPoints.emplace_back(
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
    Clip clip;
};

