#include "MiniginPCH.h"
#include "ImGuiPlotComponent.h"

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
	ImGui::PlotConfig conf;
	conf.values.ys = m_PlotValues.begin()->second.data();
	conf.values.count = (int)m_PlotValues.begin()->second.size();
	conf.scale.min = 0;
	conf.scale.max = 2500;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.frame_size = ImVec2(400, 400);
	conf.line_thickness = 2.f;

	ImGui::Plot(m_PlotValues.begin()->first.c_str(), conf);
	//ImGui::PlotLines(m_PlotValues.begin()->first.c_str(), m_PlotValues.begin()->second.data(), (int)m_PlotValues.begin()->second.size());
	//ImGui::ShowDemoWindow();
}
