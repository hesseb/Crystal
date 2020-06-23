#pragma once

#ifdef CR_PLATFORM_WINDOWS

extern Crystal::Application* Crystal::CreateApplication();

int main(int argc, char** argv)
{
	Crystal::Log::Init();

	int a = 6;
	CR_ERROR("This is an ERROR. This is a variable = {0}", a);
	CR_CORE_INFO("This is FATAL");
	CR_CORE_WARN("This is a warning");
	CR_CORE_TRACE("This is just stuff");

	auto app = Crystal::CreateApplication();
	app->Run();
	delete app;
}

#endif