#pragma once

#include "config.h"

#include "box.h"
#include "units.h"
#include "shared_function.h"


namespace renderer
{

	//ImGui::GetWindowSize() .. for pixel size that is const for all screens

	class Tab
	{
	public:
		Tab() = default;

		Tab(std::vector<std::unique_ptr<BoxBase>> domElements, std::string httpPath, std::string_view title = "Untitled");

		Tab(const Tab&) = delete;
		Tab& operator=(const Tab&) = delete;
		Tab(Tab&&) = default;
		Tab& operator=(Tab&&) = default;

		std::array<char, 128>& get_search_buff();

		std::string get_title() const;

		void render();

	private:

		std::string _httpPath;
		std::string _title;

		std::array<char, 128> _searchBuff = {};

		SharedDataFunction<std::unique_ptr<ImDrawList>> _sharedDataFunctions;

		std::vector<std::unique_ptr<BoxBase>> _boxes; /// DOM elements

	};

}