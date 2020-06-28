#pragma once

#ifdef CR_PLATFORM_WINDOWS

extern Crystal::Application* Crystal::CreateApplication();

int main(int argc, char** argv)
{
	Crystal::Log::Init();
	CR_CORE_TRACE("Welcome to Crystal Engine.");

	auto app = Crystal::CreateApplication();
	app->Run();
	delete app;
}

#endif