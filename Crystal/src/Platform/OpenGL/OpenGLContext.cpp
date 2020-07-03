#include <crpch.h>

#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Crystal
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CR_CORE_ASSERT(windowHandle, "Window handle is null.");
	}

	void OpenGLContext::Init()
	{
		CR_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CR_CORE_ASSERT(status, "Failed to initialize Glad.");

		CR_CORE_INFO("OpenGL Info:");
		CR_CORE_INFO("  Vendor:\t{0}", glGetString(GL_VENDOR));
		CR_CORE_INFO("  Renderer:\t{0}", glGetString(GL_RENDERER));
		CR_CORE_INFO("  Version:\t{0}", glGetString(GL_VERSION));

		#ifdef CR_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			CR_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Crystal requires at least OpenGL 4.5.");
		#endif

	}

	void OpenGLContext::SwapBuffers()
	{
		CR_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}