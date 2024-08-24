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
        : width_(width), height_(height), near_(near), far_(far)
    {
        projection_ = glm::ortho(-width_, width_, -height_, height_, near_, far_);
    }

    Clip(const float radian, const float width, const float height, const float near, const float far)
        : radian_(radian), width_(width), height_(height), near_(near), far_(far)
    {
        projection_ = glm::perspective(radian_, width_/height_, near_, far_);
    }

    glm::mat4 GetProjection() const { return projection_; }

private:
    glm::mat4 projection_;
    float width_;
    float height_;
    float near_;
    float far_;
    float radian_;
};