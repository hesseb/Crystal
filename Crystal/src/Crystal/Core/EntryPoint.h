#pragma once

#ifdef CR_PLATFORM_WINDOWS

extern Crystal::Application* Crystal::CreateApplication();

int main(int argc, char** argv)
{
	Crystal::Log::Init();
	CR_CORE_TRACE("Welcome to Crystal Engine.");

	CR_PROFILE_BEGIN_SESSION("Startup", "CrystalProfile-Startup.json");
	auto app = Crystal::CreateApplication();
	CR_PROFILE_END_SESSION();

	CR_PROFILE_BEGIN_SESSION("Runtime", "CrystalProfile-Runtime.json");
	app->Run();
	CR_PROFILE_END_SESSION();

	CR_PROFILE_BEGIN_SESSION("Shutdown", "CrystalProfile-Shutdown.json");
	delete app;
	CR_PROFILE_END_SESSION();
}

#endif