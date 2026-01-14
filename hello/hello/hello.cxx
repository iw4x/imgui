#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

using namespace std;

namespace ImGui
{
  inline void
  ImplGlfwNewFrame ()
  {
    ImGui_ImplGlfw_NewFrame ();
  }

  inline void
  ImplOpenGL3NewFrame ()
  {
    ImGui_ImplOpenGL3_NewFrame ();
  }

  inline bool
  ImplOpenGL3Init (const char* glsl_version)
  {
    return ImGui_ImplOpenGL3_Init (glsl_version);
  }

  inline bool
  ImplGlfwInitForOpenGL (GLFWwindow* window, bool install_callbacks)
  {
    return ImGui_ImplGlfw_InitForOpenGL (window, install_callbacks);
  }

  inline void
  ImplOpenGL3Shutdown ()
  {
    ImGui_ImplOpenGL3_Shutdown ();
  }

  inline void
  ImplGlfwShutdown ()
  {
    ImGui_ImplGlfw_Shutdown ();
  }

  inline void
  ImplOpenGL3RenderDrawData (ImDrawData* draw_data)
  {
    ImGui_ImplOpenGL3_RenderDrawData (draw_data);
  }
}

namespace hello
{
  namespace
  {
    void
    error (const char* msg)
    {
      cerr << "error: " << msg << endl;
    }

    void
    glfw_error_callback (int error, const char* desc)
    {
      cerr << "glfw error (" << error << "): " << desc << endl;
    }

    void
    setup_imgui ()
    {
      glfwSetErrorCallback (glfw_error_callback);

      if (!glfwInit ())
        exit (1);

      glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint (GLFW_RESIZABLE, GLFW_FALSE);
      glfwWindowHint (GLFW_DECORATED, GLFW_FALSE);

      GLFWwindow* w (glfwCreateWindow (1280, 720, "Hello", nullptr, nullptr));
      if (!w)
        exit (1);

      glfwMakeContextCurrent (w);
      glfwSwapInterval (1);

      ImGui::CreateContext ();
      ImGui::ImplGlfwInitForOpenGL (w, true);
      ImGui::ImplOpenGL3Init ("#version 330");

      ImGuiIO& io (ImGui::GetIO ());
      io.IniFilename = nullptr;

      ImGuiStyle& style (ImGui::GetStyle ());
      style.WindowBorderSize = 0.0f;
      style.WindowPadding = ImVec2 (0.0f, 0.0f);
      style.WindowRounding = 0.0f;

      while (!glfwWindowShouldClose (w))
      {
        glfwPollEvents ();

        ImGui::ImplOpenGL3NewFrame ();
        ImGui::ImplGlfwNewFrame ();
        ImGui::NewFrame ();
        ImGui::SetNextWindowPos (ImVec2 (0, 0));
        ImGui::SetNextWindowSize (ImVec2 (1280, 720));
        ImGui::Begin ("##window",
                      nullptr,
                      ImGuiWindowFlags_NoTitleBar |
                      ImGuiWindowFlags_NoResize |
                      ImGuiWindowFlags_NoMove |
                      ImGuiWindowFlags_NoScrollbar |
                      ImGuiWindowFlags_NoScrollWithMouse);
        ImGui::End ();
        ImGui::Render ();
        ImGui::ImplOpenGL3RenderDrawData (ImGui::GetDrawData ());

        glfwSwapBuffers (w);
      }

      ImGui::ImplOpenGL3Shutdown ();
      ImGui::ImplGlfwShutdown ();
      ImGui::DestroyContext ();

      glfwDestroyWindow (w);
      glfwTerminate ();
    }
  }
}

int
main (int argc, char* argv [])
{
  using namespace hello;

  setup_imgui ();
}
