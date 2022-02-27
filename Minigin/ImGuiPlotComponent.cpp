#include "MiniginPCH.h"
#include "ImGuiPlotComponent.h"

#include <algorithm>

#include "3rdParty/imgui-1.87/imgui_plot.h"

dae::ImGuiPlotComponent::ImGuiPlotComponent(std::map<std::string, std::vector<float>> plotValues)
{
	//m_VerticalHeaders = verticalHeaders;
	//m_HorizontalHeaders = horizontalHeaders;
	m_PlotValues = plotValues;
}

void dae::ImGuiPlotComponent::Update()
{
}

void dae::ImGuiPlotComponent::Render() const
{
	//ImGui::PlotConfig conf;
	//std::vector<float> y_data{};
	//for (auto it = m_PlotValues.begin(); it != m_PlotValues.end(); ++it)
	//{
	//	y_data.insert(y_data.end(), it->second.begin(), it->second.end());
	//}


	//conf.values.ys_list = y_data.data();

	//conf.values.count = static_cast<int>( it->second.size()) + 1;
	//conf.scale.min = 0;
	//float max = *std::ranges::max_element(it->second);
	//conf.scale.max = max * 1.1f;
	//conf.tooltip.show = true;
	//conf.tooltip.format = "x=%.2f, y=%.2f";
	//conf.grid_x.show = true;
	//conf.grid_y.show = true;
	//conf.frame_size = ImVec2(400, 200);
	//conf.line_thickness = 2.f;

	//ImGui::Plot(it->first.c_str(), conf);


	//ONLY RENDERS ONE LINE TODO: use commented code above to support multiple lines
	ImGui::PlotConfig conf;

	conf.values.ys = m_PlotValues.begin()->second.data();
	conf.values.count = (int)m_PlotValues.begin()->second.size()+1;
	conf.scale.min = 0;
	float max = *std::ranges::max_element(m_PlotValues.begin()->second);
	conf.scale.max = max*1.1f;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.frame_size = ImVec2(400, 200);
	conf.line_thickness = 2.f;

	ImGui::Text(m_PlotValues.begin()->first.c_str());
	ImGui::Plot(m_PlotValues.begin()->first.c_str(), conf);
}
