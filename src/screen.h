#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Screen
{
public:
    Screen(){};
    ~Screen(){};
    Screen(const glm::vec2 leftTop, const glm::vec2 size)
        : leftTop(leftTop), size(size)
    {
        viewPort = {leftTop.x, -leftTop.y, size.x, size.y};
        viewPortTrans = { glm::vec3(1, 0, 0), glm::vec3{0, -1, 0}, glm::vec3{0, size.y, 0} };
    }

    glm::vec2 GetLeftTop() const { return leftTop; }
    glm::vec2 GetSize() const { return size; }
    glm::vec4 GetViewPort() const { return viewPort; }
    glm::mat3 GetViewPortTrans() const { return viewPortTrans; }

private:
    glm::vec2 leftTop;
    glm::vec2 size;
    glm::vec4 viewPort;
    glm::mat3 viewPortTrans;
};