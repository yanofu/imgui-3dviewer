// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <iostream>
#include <string>

#include "camera.hpp"
#include "happly.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void GlmVec3Text(const std::string label, const glm::vec3 vec)
{
    ImGui::Text(label.c_str());
    for (size_t i = 0; i < vec.length(); ++i)
    {
        ImGui::Text(std::to_string(vec[i]).c_str());
        ImGui::SameLine();
    }
    ImGui::NewLine();
}

static void GlmVec2Text(const std::string label, const glm::vec2 vec)
{
    ImGui::Text(label.c_str());
    for (size_t i = 0; i < vec.length(); ++i)
    {
        ImGui::Text(std::to_string(vec[i]).c_str());
        ImGui::SameLine();
    }
    ImGui::NewLine();
}

static void GlmMat4Text(const std::string label, const glm::mat4x4 mat)
{
    ImGui::Text(label.c_str());
    for (size_t i = 0; i < 4; ++i)
    {
        ImGui::Text(std::string(std::to_string(mat[i][0]) + "\n" + std::to_string(mat[i][1]) + "\n" + std::to_string(mat[i][2]) + "\n" + std::to_string(mat[i][3])).c_str());
        ImGui::SameLine();
    }
    ImGui::NewLine();

}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    happly::PLYData plyIn("./bunny.ply");
    try
    {
        plyIn.validate();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    const std::vector<std::array<double, 3>> model_points = plyIn.getVertexPositions();

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    bool show_3d_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    Camera camera;
    camera.SetCameraView(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Camera world_camera;
    world_camera.SetCameraView({20, 20, 20}, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);
            ImGui::Checkbox("3D Window", &show_3d_window);      // Edit bools storing our window open/close state

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGuiIO& io = ImGui::GetIO();
            ImGui::Text("x: %g  y: %g", io.MousePos.x, io.MousePos.y);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        if(show_3d_window)
        {
            ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor(0.35f, 0.3f, 0.3f));
            ImGui::Begin("3D Viewer", &show_3d_window);
            if (ImGui::Button("Close Me"))
                 show_3d_window = false;
            
            static bool display_pointcloud = true;
            ImGui::Checkbox("display pointcloud", &display_pointcloud);

            static bool auto_y_rotate = false;
            ImGui::Checkbox("automatic y", &auto_y_rotate);

            static bool auto_x_rotate = false;
            ImGui::Checkbox("automatic x", &auto_x_rotate);

            float windowWidth = (float)ImGui::GetWindowWidth();
            float windowHeight = (float)ImGui::GetWindowHeight();
            ImVec2 windowsPosition = ImGui::GetWindowPos();

            static bool isDraging = false;
            ImGuiIO& io = ImGui::GetIO();
            io.ConfigWindowsMoveFromTitleBarOnly = true;
            auto isInside = ImRect(windowsPosition + ImVec2(0, 15), windowsPosition + ImGui::GetWindowSize()).Contains(io.MousePos);
            if (!isDraging && io.MouseDown[0] && isInside && (fabsf(io.MouseDelta.x) > 0.f || fabsf(io.MouseDelta.y) > 0.f))
            {
                isDraging = true;
            }
            else if ((isDraging && !io.MouseDown[0]) || !isInside)
            {
                isDraging = false;
            }

            if(isDraging || auto_x_rotate || auto_y_rotate)
            {
                GlmVec2Text("Mouse Delta", glm::vec2(io.MouseDelta.x, io.MouseDelta.y));
                {
                    const float delta_angle_x = (2 * IM_PI / windowWidth);
                    const float delta_angle_y = (IM_PI / windowHeight);
                    float mouse_delata_x = 0;
                    float mouse_delata_y = 0;
                    if (isDraging)
                    {
                        mouse_delata_x = -io.MouseDelta.x;
                        mouse_delata_y = -io.MouseDelta.y;
                    }
                    if (auto_x_rotate)
                    {
                        mouse_delata_x = 1;
                    }
                    if (auto_y_rotate)
                    {
                        mouse_delata_y = 1;
                    }
                    const float x_angle = mouse_delata_x * delta_angle_x;
                    const float y_angle = mouse_delata_y * delta_angle_y;
                    glm::vec4 position(camera.GetEye(), 1);
                    const glm::vec4 pivot(camera.GetLookAt(), 1);
                    const auto rx = glm::rotate(glm::mat4(1.0), x_angle, camera.GetUp());
                    position = rx * (position - pivot) + pivot;
                    const auto ry = glm::rotate(glm::mat4(1.0), y_angle, camera.GetRightVector());
                    position = (ry * (position - pivot)) + pivot;
                    camera.SetCameraView(position, camera.GetLookAt(), camera.GetUp());
                }
            }

            const float viewWidth = 200.f;
            const float viewHeight = viewWidth * windowHeight / windowWidth;
            camera.SetClip(Clip(viewWidth, viewHeight, 10.f, 1000.f));
            camera.SetScreen(Screen(glm::vec2(windowsPosition.x, windowsPosition.y), glm::vec2(windowWidth, windowHeight)));

            const auto origin = camera.ProjectToScreen(glm::vec3(0.0, 0.0, 0.0));
            const auto origin_x_axis = camera.ProjectToScreen(glm::vec3(50.0, 0.0, 0.0));
            const auto origin_y_axis = camera.ProjectToScreen(glm::vec3(0.0, 50.0, 0.0));
            const auto origin_z_axis = camera.ProjectToScreen(glm::vec3(0.0, 0.0, 50.0));

            ImDrawList* drawlist = ImGui::GetWindowDrawList();
            drawlist->AddCircleFilled(ImVec2(origin.x, origin.y), 5, IM_COL32(255, 255, 255, 255));
            drawlist->AddLine(ImVec2(origin.x, origin.y), ImVec2(origin_x_axis.x, origin_x_axis.y), IM_COL32(255, 0, 0, 255), 1.0f);
            drawlist->AddLine(ImVec2(origin.x, origin.y), ImVec2(origin_y_axis.x, origin_y_axis.y), IM_COL32(0, 255, 0, 255), 1.0f);
            drawlist->AddLine(ImVec2(origin.x, origin.y), ImVec2(origin_z_axis.x, origin_z_axis.y), IM_COL32(0, 0, 255, 255), 1.0f);

            if(display_pointcloud)
            {
                for (auto model_point : model_points)
                {
                    auto point = camera.ProjectToScreen(glm::vec3(model_point[0], model_point[1], model_point[2]));
                    drawlist->AddCircle(ImVec2(point.x, point.y), 1, IM_COL32(255, 0, 255, 255));
                }
            }

            ImGui::End();
            ImGui::PopStyleColor(1);
        }

        if(show_3d_window)
        {
            ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor(0.35f, 0.3f, 0.3f));
            ImGui::Begin("3D World View", &show_3d_window);
            if (ImGui::Button("Close Me"))
                 show_3d_window = false;

            GlmVec3Text("Camera Position", camera.GetEye());
            GlmMat4Text("Camera View", camera.GetViewMatrix());
            GlmMat4Text("Camera View Inverse", glm::inverse(camera.GetViewMatrix()));

            const float viewWidth = 200.f;
            const float viewHeight = viewWidth * ImGui::GetWindowHeight() / ImGui::GetWindowWidth();
            world_camera.SetClip(Clip(viewWidth, viewHeight, 10.f, 1000.f));
            world_camera.SetScreen(Screen(glm::vec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y), glm::vec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight())));

            const auto origin = world_camera.ProjectToScreen(glm::vec3(0.0, 0.0, 0.0));
            const auto origin_x_axis = world_camera.ProjectToScreen(glm::vec3(50.0, 0.0, 0.0));
            const auto origin_y_axis = world_camera.ProjectToScreen(glm::vec3(0.0, 50.0, 0.0));
            const auto origin_z_axis = world_camera.ProjectToScreen(glm::vec3(0.0, 0.0, 50.0));

            ImDrawList* drawlist = ImGui::GetWindowDrawList();
            drawlist->AddCircleFilled(ImVec2(origin.x, origin.y), 5, IM_COL32(255, 255, 255, 255));
            drawlist->AddLine(ImVec2(origin.x, origin.y), ImVec2(origin_x_axis.x, origin_x_axis.y), IM_COL32(255, 0, 0, 255), 1.0f);
            drawlist->AddLine(ImVec2(origin.x, origin.y), ImVec2(origin_y_axis.x, origin_y_axis.y), IM_COL32(0, 255, 0, 255), 1.0f);
            drawlist->AddLine(ImVec2(origin.x, origin.y), ImVec2(origin_z_axis.x, origin_z_axis.y), IM_COL32(0, 0, 255, 255), 1.0f);

            const auto camera_position = world_camera.ProjectToScreen(camera.GetEye());
            const auto camera_x_axis = world_camera.ProjectToScreen(glm::inverse(camera.GetViewMatrix()) * glm::vec4(25.0, 0.0, 0.0, 1.0));
            const auto camera_y_axis = world_camera.ProjectToScreen(glm::inverse(camera.GetViewMatrix()) * glm::vec4(0.0, 25.0, 0.0, 1.0));
            const auto camera_z_axis = world_camera.ProjectToScreen(glm::inverse(camera.GetViewMatrix()) * glm::vec4(0.0, 0.0, 25.0, 1.0));

            drawlist->AddCircleFilled(ImVec2(camera_position.x, camera_position.y), 5, IM_COL32(255, 255, 255, 255));
            drawlist->AddLine(ImVec2(origin.x, origin.y), ImVec2(camera_position.x, camera_position.y), IM_COL32(0, 255, 255, 255), 1.0f);
            drawlist->AddLine(ImVec2(camera_position.x, camera_position.y), ImVec2(camera_x_axis.x, camera_x_axis.y), IM_COL32(255, 0, 0, 255), 1.0f);
            drawlist->AddLine(ImVec2(camera_position.x, camera_position.y), ImVec2(camera_y_axis.x, camera_y_axis.y), IM_COL32(0, 255, 0, 255), 1.0f);
            drawlist->AddLine(ImVec2(camera_position.x, camera_position.y), ImVec2(camera_z_axis.x, camera_z_axis.y), IM_COL32(0, 0, 255, 255), 1.0f);

            ImGui::End();
            ImGui::PopStyleColor(1);
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
