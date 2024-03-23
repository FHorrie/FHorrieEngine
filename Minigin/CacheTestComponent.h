#pragma once
#include "Component.h"

namespace FH
{
	class CacheTestComponent final : public Component
	{
	public:
		void RenderUI() override;

		void ShowTrashCacheWindow(bool* p_open = NULL);

		void MeasureCacheTime(int sampleCount);
		void MeasureCacheTime3D(int sampleCount);
		void MeasureCacheTime3DAlt(int sampleCount);

		CacheTestComponent(GameObject* pOwner);
		virtual ~CacheTestComponent() = default;
		CacheTestComponent(const CacheTestComponent& other) = delete;
		CacheTestComponent(CacheTestComponent&& other) = delete;
		CacheTestComponent& operator=(const CacheTestComponent& other) = delete;
		CacheTestComponent& operator=(CacheTestComponent&& other) = delete;

	private:
		//step sizes
		const std::array<float, 11> m_Steps{ 1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f, 512.f, 1024.f };

		/////////////////////////////////
		//Int cache variables
		bool m_CacheTrashedInt{};
		bool m_PlottedInt{};
		std::vector<float> m_AvgIntTimings{};
		float m_AvgIntTimingMax{};

		/////////////////////////////////
		//GameObject3D cache variables
		bool m_CacheTrashed3D{};
		bool m_Plotted3D{};
		std::vector<float> m_Avg3DTimings{};
		float m_Avg3DTimingMax{};

		/////////////////////////////////
		//GameObject3DAlt cache variables
		bool m_CacheTrashed3DAlt{};
		bool m_Plotted3DAlt{};
		std::vector<float> m_Avg3DAltTimings{};
		float m_Avg3DAltTimingMax{};

		/////////////////////////////////


	};

	//////////////////
	//Data for plots
	//////////////////

	struct Transform3D
	{
		float matrix[16]
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
	};

	class GameObject3D
	{
		Transform3D local;
	public:
		int id;
	};

	class GameObject3DAlt
	{
		Transform3D* local;
	public:
		int id;
	};

	//////////////////
}