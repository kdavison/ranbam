#pragma once

#include <GLFW/glfw3.h>

namespace GLFW
{
class library
{
public:
  library() {
    glfwInit();
  }

  ~library() {
    glfwTerminate();
  }
};



}
