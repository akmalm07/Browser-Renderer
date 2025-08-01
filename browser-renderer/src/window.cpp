#include "headers.h"
#include "window.h"

namespace renderer
{
	Window::Window()
	{
		_window.init(800.0f, 600.0f, "Browser Renderer", true, true);

	}

	bool Window::should_close() const
	{
		return _window.get_should_close();
	}

	void Window::add_tab(std::vector<std::unique_ptr<BoxBase>> domElements, std::string httpPath, std::string_view title)
	{
		static std::vector<std::string_view> names;
		static std::vector<int> found;

		std::string titleStr(title);

		if (std::find(names.begin(), names.end(), title) != names.end())
		{
			int index = std::distance(names.begin(), std::find(names.begin(), names.end(), title));
			titleStr = std::string(title) + " " + std::to_string(++found[index]);
		}
		else
		{
			names.push_back(title);
			found.push_back(0);
		}

		_tabs.push_back(std::make_unique<Tab>(std::move(domElements), std::move(httpPath), titleStr));
		_isTabOpen.push_back(true); 
	}

	void Window::render()
	{
		_window.update();

		ImGuiViewport* viewport = ImGui::GetMainViewport();

		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::Begin("Tab Bar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus);

		ImGui::SetCursorPos(ImVec2(10.0f, 10.0f));

		if (!ImGui::BeginTabBar("Tabs"))
		{
			ImGui::End();
			return;
		}



		for (size_t i = 0; i < _tabs.size(); i++)
		{
			if (!_tabs[i])
			{
				continue;
			}

			std::string name = _tabs[i]->get_title();

			bool isOpen = (_isTabOpen[i] != 0);
			if (!isOpen)
			{
				ImGui::SetTabItemClosed(name.c_str());
				continue;
			}

			if (ImGui::BeginTabItem(name.c_str(), reinterpret_cast<bool*>(&_isTabOpen[i])))
			{
				_currentTabIndex = i;
				_tabs[i]->render();
				ImGui::EndTabItem();
			}

		}

		ImGui::EndTabBar();


		if (_isTabOpen.size() > 1)
		{
			for (size_t i = 0; i < _isTabOpen.size(); i++)
			{
				if (_isTabOpen[i] != true)
				{
					_tabs.erase(_tabs.begin() + i);
					_isTabOpen.erase(_isTabOpen.begin() + i);
					i--;
				}
			}
		}

		ImGui::SameLine();

		if (ImGui::Button("+"))
		{
			add_tab(std::vector<std::unique_ptr<BoxBase>>(), "http://example.com", "New Tab");
		}

		auto& searchBuff = _tabs[_currentTabIndex]->get_search_buff();

		if (ImGui::InputTextWithHint("Search", "Type Here ...", searchBuff.data(), searchBuff.size(), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			if (!searchBuff.empty())
			{
				std::string searchQuery(searchBuff.data());
				
				search_google(searchQuery);

				std::cout << "Search query: " << searchQuery << std::endl;
			}
			searchBuff.fill(0); // Clear the search buffer after processing
		}

		ImGui::End();
		windowing::clear_color();
		windowing::render();
	}

	void search_google(const std::string& query)
	{
		std::stringstream ss;
		ss << std::regex_replace(query, std::regex(" "), "+");
		std::string url = "https://www.google.com/search?q=" + query;
		system(("start " + url).c_str());
	}
}