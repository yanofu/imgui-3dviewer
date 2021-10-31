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

    Screen GetScreen() const { return screen_; }

    void SetCameraView(glm::vec3 eye, glm::vec3 lookat, glm::vec3 up)
    {
        eye_ = eye;
        lookat_ = lookat;
        up_ = up;
        view_ = glm::lookAt(eye_, lookat_, up_);
    }

    void SetScreen(const Screen screen)
    {
        screen_ = screen;
    }

    void SetClip(const Clip clip)
    {
        clip_ = clip;
    }

    glm::vec2 ProjectToScreen(const glm::vec3& point)
    {
        auto projected_viewport = glm::project(point, view_, clip_.GetProjection(), screen_.GetViewPort());
        auto projected_screen = glm::vec2(screen_.GetViewPortTrans() * glm::vec3(projected_viewport.x, projected_viewport.y, 1));
        return projected_screen;
    }

private:
    glm::mat4 view_;
    glm::vec3 eye_;
    glm::vec3 lookat_;
    glm::vec3 up_;
    Screen screen_;
    Clip clip_;
};

