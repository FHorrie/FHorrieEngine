#define _CRT_SECURE_NO_WARNINGS

#include <array>
#include <chrono>

#include "CacheTestComponent.h"
#include "imgui_plot.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdl2.cpp"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_opengl3.cpp"

using std::chrono::high_resolution_clock;
using namespace dae;

CacheTestComponent::CacheTestComponent(GameObject* pOwner)
	: Component(pOwner)
{}

void CacheTestComponent::RenderUI()
{
	ShowTrashCacheWindow();
}

void CacheTestComponent::ShowTrashCacheWindow(bool* p_open)
{
	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing Dear ImGui context. Refer to examples app!");

	ImGuiWindowFlags window_flags{};

	const ImGuiViewport* main_viewport{ ImGui::GetMainViewport() };
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 20, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Trash the Cache", p_open, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	static int sampleCount = 10;
	ImGui::InputInt("nr of samples", &sampleCount);
	ImGui::Spacing();

	if (ImGui::Button("Trash the cache with int"))
	{ 
		m_CacheTrashedInt = true;
		m_AvgIntTimingMax = 0;
		m_PlottedInt = false;
	}
	if (m_CacheTrashedInt == true)
		MeasureCacheTime(sampleCount);

	if (ImGui::Button("Trash the cache with GameObject3D"))
	{ 
		m_CacheTrashed3D = true;
		m_Avg3DTimingMax = 0;
		m_Plotted3D = false;
	}
	if (m_CacheTrashed3D == true)
		MeasureCacheTime3D(sampleCount);

	if (ImGui::Button("Trash the cache with GameObject3DAlt")) 
	{ 
		m_CacheTrashed3DAlt = true;
		m_Avg3DAltTimingMax = 0;
		m_Plotted3DAlt = false;
	}
	if (m_CacheTrashed3DAlt == true)
		MeasureCacheTime3DAlt(sampleCount);

	ImGui::PopItemWidth();
	ImGui::End();
}

void CacheTestComponent::MeasureCacheTime(int sampleCount)
{
	if (!m_PlottedInt)
	{
		std::vector<std::vector<float>> timings{};
		auto buffer{ new std::array<int, 1000>{} };
		for (int idx{}; idx < sampleCount; idx++)
		{
			timings.push_back(std::vector<float>{});

			for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
			{
				auto start = high_resolution_clock::now();
				for (size_t i{}; i < buffer->size(); i += stepSize)
				{
					buffer->data()[i] *= 2;
				}
				auto end = high_resolution_clock::now();
				auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				timings[idx].push_back(float(delta.count()));
			}
		}

		for (int idx{}; idx < int(m_Steps.size()); idx++)
		{
			float sum{};
			for (int sampleIdx{}; sampleIdx < sampleCount; sampleIdx++)
			{
				sum += timings[sampleIdx][idx];
			}
			m_AvgIntTimings.push_back(sum / sampleCount);
		}

		m_AvgIntTimingMax = *std::ranges::max_element(m_AvgIntTimings);
		delete buffer;
		m_PlottedInt = true;
	}

	static ImU32 color{ ImColor(0, 200, 255) };

	ImGui::PlotConfig conf;

	conf.values.xs = m_Steps.data();
	conf.values.ys = m_AvgIntTimings.data();
	conf.values.count = int(m_Steps.size());
	conf.values.color = color;
	conf.tooltip.show = true;
	conf.scale.min = 0;
	conf.scale.max = m_AvgIntTimingMax;
	conf.frame_size = ImVec2(300, 200);

	ImGui::Plot("Cache timings", conf);
}

void CacheTestComponent::MeasureCacheTime3D(int sampleCount)
{
	if (!m_Plotted3D)
	{
		std::vector<std::vector<float>> timings{};
		auto buffer{ new std::array<GameObject3D, 2000>{} };
		for (int idx{}; idx < sampleCount; idx++)
		{
			timings.push_back(std::vector<float>{});

			for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
			{
				auto start = high_resolution_clock::now();
				for (size_t i{}; i < buffer->size(); i += stepSize)
				{
					buffer->data()[i].id *= 2;
				}
				auto end = high_resolution_clock::now();
				auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				timings[idx].push_back(float(delta.count()));
			}
		}

		for (int idx{}; idx < int(m_Steps.size()); idx++)
		{
			float sum{};
			for (int sampleIdx{}; sampleIdx < sampleCount; sampleIdx++)
			{
				sum += timings[sampleIdx][idx];
			}
			m_Avg3DTimings.push_back(sum / sampleCount);
		}

		m_Avg3DTimingMax = *std::ranges::max_element(m_Avg3DTimings);
		delete buffer;
		m_Plotted3D = true;
	}

	static ImU32 color{ ImColor(100, 255, 100) };

	ImGui::PlotConfig conf;

	conf.values.xs = m_Steps.data();
	conf.values.ys = m_Avg3DTimings.data();
	conf.values.count = int(m_Steps.size());
	conf.values.color = color;
	conf.tooltip.show = true;
	conf.scale.min = 0;
	conf.scale.max = m_Avg3DTimingMax;
	conf.frame_size = ImVec2(300, 200);

	ImGui::Plot("3D cache timings", conf);
}

void CacheTestComponent::MeasureCacheTime3DAlt(int sampleCount)
{
	if (!m_Plotted3DAlt)
	{
		std::vector<std::vector<float>> altTimings{};
		auto buffer{ new std::array<GameObject3DAlt, 2000>{} };
		for (int idx{}; idx < sampleCount; idx++)
		{
			altTimings.push_back(std::vector<float>{});

			for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
			{
				auto start = high_resolution_clock::now();
				for (size_t i{}; i < buffer->size(); i += stepSize)
				{
					buffer->data()[i].id *= 2;
				}
				auto end = high_resolution_clock::now();
				auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				altTimings[idx].push_back(float(delta.count()));
			}
		}

		for (int idx{}; idx < int(m_Steps.size()); idx++)
		{
			float sum{};
			for (int sampleIdx{}; sampleIdx < sampleCount; sampleIdx++)
			{
				sum += altTimings[sampleIdx][idx];
			}
			m_Avg3DAltTimings.push_back(sum / sampleCount);
		}

		m_Avg3DAltTimingMax = *std::ranges::max_element(m_Avg3DAltTimings);
		delete buffer;
		m_Plotted3DAlt = true;
	}

	static ImU32 color{ ImColor(255, 10, 10) };

	ImGui::PlotConfig conf;

	conf.values.xs = m_Steps.data();
	conf.values.ys = m_Avg3DAltTimings.data();
	conf.values.count = int(m_Steps.size());
	conf.values.color = color;
	conf.tooltip.show = true;
	conf.scale.min = 0;
	conf.scale.max = m_Avg3DAltTimingMax;
	conf.frame_size = ImVec2(300, 200);

	ImGui::Plot("Alt cache timings", conf);
}