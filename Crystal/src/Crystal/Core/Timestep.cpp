#include <crpch.h>
#include "Timestep.h"

#include <GLFW/glfw3.h>

namespace Crystal
{
	double Timestep::GetTime()
	{
		return glfwGetTime();
	}
}