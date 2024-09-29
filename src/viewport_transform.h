#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "screen.h"

class ViewportTransform
{
public:
    ViewportTransform(const Screen& screen)
        : screen(screen)
    {
    }

    ~ViewportTransform()
    {
    }

    static ViewportTransform Create(const glm::vec2 leftTopInWindow, const glm::vec2 windowSize)
    {
        return ViewportTransform(Screen(leftTopInWindow, windowSize));
    }

    std::vector<glm::vec2> Transform(const std::vector<glm::vec2>& pointsInClip) const
    {
        const auto& transform = screen.ToFixedScaleTransformVector();
        std::vector<glm::vec2> pointsInScreen;
        for(auto pointInClip : pointsInClip)
        {
            pointsInScreen.emplace_back(
                glm::vec2{
                    transform[0] * pointInClip.x + transform[2],
                    transform[1] * pointInClip.y + transform[3],
                }
            );
        }
        return pointsInScreen;
    }

private:
    Screen screen;

};