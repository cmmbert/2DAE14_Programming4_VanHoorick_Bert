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
	//ONLY RENDERS ONE LINE TODO: support multiple lines
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

	ImGui::InputInt("# samples", m_NrOfSamples.get());
	ImGui::Text(m_PlotValues.begin()->first.c_str());
	ImGui::Plot(m_PlotValues.begin()->first.c_str(), conf);
}
