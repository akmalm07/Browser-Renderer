#include "headers.h"
#include "tab.h"


namespace renderer
{
	Tab::Tab(std::vector<std::unique_ptr<BoxBase>> domElements, std::string httpPath, std::string_view title)
	{
		_httpPath = std::move(httpPath);
		_title = title;

		_searchBuff.fill(0); 

		_boxes.reserve(100);

		_sharedDataFunctions.add_function([this](std::shared_ptr<std::unique_ptr<ImDrawList>> state) {
			ImGuiViewport* viewport = ImGui::GetMainViewport();

			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);

			ImGuiWindowFlags windowFlags =
				ImGuiWindowFlags_NoDecoration |
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoBringToFrontOnFocus |
				ImGuiWindowFlags_NoNavFocus;

			ImGui::Begin(_title.c_str(), nullptr, windowFlags);


			ImGui::End();
			});
	}

	std::array<char, 128>& Tab::get_search_buff() { return _searchBuff; }
	
	std::string Tab::get_title() const { return _title; }


	void Tab::render()
	{
		_sharedDataFunctions.call_all();
	}
}