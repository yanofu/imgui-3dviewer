#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Screen
{
public:
    Screen(){};
    ~Screen(){};
    Screen(const glm::vec2 left_top, const glm::vec2 size)
        : left_top_(left_top), size_(size)
    {
        view_port_ = {left_top_.x, -left_top_.y, size_.x, size_.y};
        view_port_trans_ = { glm::vec3(1, 0, 0), glm::vec3{0, -1, 0}, glm::vec3{0, size_.y, 0} };
    }

    glm::vec2 GetLeftTop() const { return left_top_; }
    glm::vec2 GetSize() const { return size_; }
    glm::vec4 GetViewPort() const { return view_port_; }
    glm::mat3 GetViewPortTrans() const { return view_port_trans_; }

private:
    glm::vec2 left_top_;
    glm::vec2 size_;
    glm::vec4 view_port_;
    glm::mat3 view_port_trans_;
};