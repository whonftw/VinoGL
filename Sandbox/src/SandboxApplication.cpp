#include "VinoGL.h"

class SandboxApplication : public Vino::Application
{
};

std::unique_ptr<Vino::Application> CreateApplication()
{
	std::unique_ptr<SandboxApplication> ptr(new SandboxApplication());
	return std::move(ptr);
}