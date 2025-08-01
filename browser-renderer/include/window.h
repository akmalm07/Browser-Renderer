#pragma once

#include "config.h"
#include "units.h"
#include "tab.h"

namespace renderer
{
	class Window
	{
	public:

		Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		Window(Window&&) = default;
		Window& operator=(Window&&) = default;

		bool should_close() const;

		void add_tab(std::vector<std::unique_ptr<BoxBase>> domElements, std::string httpPath, std::string_view title = "Untitled");

		void render();

	private:

		SharedDataFunction<std::unique_ptr<ImDrawList>> _tabBarCommands;
		
		std::vector<char> _isTabOpen;

		std::vector<std::unique_ptr<Tab>> _tabs; 

		windowing::Window _window;
	
		size_t _currentTabIndex = 0;
	};

	void search_google(const std::string& query);
}

