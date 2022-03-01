#pragma once
#include <map>

#include "BaseComponent.h"
namespace dae
{
    class ImGuiPlotComponent final :public BaseComponent
    {
    public:
	    ImGuiPlotComponent(std::map<std::string, std::vector<float>> plotValues);
	    //ImGuiPlotComponent() = delete;
	    ~ImGuiPlotComponent() override = default;
	    ImGuiPlotComponent(const ImGuiPlotComponent& other) = delete;
	    ImGuiPlotComponent(ImGuiPlotComponent&& other) noexcept = delete;
	    ImGuiPlotComponent& operator=(const ImGuiPlotComponent& other) = delete;
	    ImGuiPlotComponent& operator=(ImGuiPlotComponent&& other) noexcept = delete;

	    void Update() override;
	    void Render() const override;
    private:
		std::map<std::string, std::vector<float>> m_PlotValues;

	    //std::vector<float> m_HorizontalHeaders;
		//std::vector<float> m_VerticalHeaders;
		int* m_NrOfSamples = new int(10);
    };
}

