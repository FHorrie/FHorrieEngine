#pragma once
#include "Component.h"
#include "Observer.h"

namespace FH
{
	class TextureComponent;
	class CoinBagComponent;
	class LiveTextureComponent;

	class CoinBagTextureComponent : public Component, public Observer
	{
	public:
		CoinBagTextureComponent(GameObject* pOwner, CoinBagComponent* pCoinBag);
		virtual ~CoinBagTextureComponent() = default;
		CoinBagTextureComponent(const CoinBagTextureComponent& other) = delete;
		CoinBagTextureComponent(CoinBagTextureComponent&& other) = delete;
		CoinBagTextureComponent& operator=(const CoinBagTextureComponent& other) = delete;
		CoinBagTextureComponent& operator=(CoinBagTextureComponent&& other) = delete;

		void OnNotify(GameObject* go, GameEvent e) override;

	private:
		TextureComponent* m_BagIdleTex{};
		TextureComponent* m_BagFallingTex{};
		LiveTextureComponent* m_BagWiggleTex{};
		LiveTextureComponent* m_BagBrokenTex{};
	};
}
