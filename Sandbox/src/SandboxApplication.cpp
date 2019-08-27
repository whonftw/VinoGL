#include "VinoGL.h"
#include <memory>
class SandboxApplication : public Vino::Application
{
public:
	SandboxApplication()
	{
	}
};

std::unique_ptr<Vino::Application> CreateApplication()
{
	std::unique_ptr<SandboxApplication> ptr(new SandboxApplication());
	return std::move(ptr);
}