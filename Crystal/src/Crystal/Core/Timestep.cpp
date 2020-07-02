#include <crpch.h>
#include "Crystal/Core/Timestep.h"

#include <GLFW/glfw3.h>

namespace Crystal
{
	double Timestep::GetTime()
	{
		return glfwGetTime();
	}
}