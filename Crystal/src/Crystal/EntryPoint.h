#pragma once

#ifdef CR_PLATFORM_WINDOWS

extern Crystal::Application* Crystal::CreateApplication();

int main(int argc, char** argv)
{
	Crystal::Log::Init();

	auto app = Crystal::CreateApplication();
	CR_CORE_INFO("Welcome to Crystal Engine.");
	app->Run();
	delete app;
}

#endif