#include "headers.h"
#include "window.h"


int main()
{
	using namespace renderer;

	Window window;

	window.add_tab(std::vector<std::unique_ptr<BoxBase>>(), "http://example.com");
	window.add_tab(std::vector<std::unique_ptr<BoxBase>>(), "http://example.com");
	window.add_tab(std::vector<std::unique_ptr<BoxBase>>(), "http://example.com");
	window.add_tab(std::vector<std::unique_ptr<BoxBase>>(), "http://example.com");
	window.add_tab(std::vector<std::unique_ptr<BoxBase>>(), "http://example.com");
	window.add_tab(std::vector<std::unique_ptr<BoxBase>>(), "http://example.com");
	window.add_tab(std::vector<std::unique_ptr<BoxBase>>(), "http://example.com");
	window.add_tab(std::vector<std::unique_ptr<BoxBase>>(), "http://example.com");
	window.add_tab(std::vector<std::unique_ptr<BoxBase>>(), "http://example.com");
	
	while (!window.should_close())
	{
		window.render();
	}
}