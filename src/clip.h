#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Clip
{
public:
    Clip(){};
    ~Clip(){};
    Clip(const float width, const float height, const float near, const float far)
        : width(width), height(height), near(near), far(far)
    {
        projection = glm::ortho(-width, width, -height, height, near, far);
    }

    Clip(const float radian, const float width, const float height, const float near, const float far)
        : radian(radian), width(width), height(height), near(near), far(far)
    {
        projection = glm::perspective(radian, width/height, near, far);
    }

    glm::mat4 GetProjection() const { return projection; }

private:
    glm::mat4 projection;
    float width;
    float height;
    float near;
    float far;
    float radian;
};