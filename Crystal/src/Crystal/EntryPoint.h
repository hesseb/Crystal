#pragma once

#ifdef CR_PLATFORM_WINDOWS

extern Crystal::Application* Crystal::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Crystal::CreateApplication();
	app->Run();
	delete app;
}

#endif