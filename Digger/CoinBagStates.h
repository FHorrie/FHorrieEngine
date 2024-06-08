#pragma once

namespace FH
{
	//FWD
	class CoinBagComponent;
	struct Cell;

	class CoinBagState abstract
	{
	public:
		virtual ~CoinBagState() = default;
		virtual void Update(CoinBagComponent* component) = 0;
	};


	class IdleBagState : public CoinBagState
	{
	public:
		IdleBagState() = default;
		virtual ~IdleBagState() = default;
		virtual void Update(CoinBagComponent* component) override;
	};

	class MovingBagState : public CoinBagState
	{
	public:
		MovingBagState(int prevCol, CoinBagComponent* component);
		virtual ~MovingBagState() = default;
		virtual void Update(CoinBagComponent* component) override;
	};

	class FallingBagState : public CoinBagState
	{
	public:
		FallingBagState(CoinBagComponent* component);
		virtual ~FallingBagState() = default;
		virtual void Update(CoinBagComponent* component) override;

	private:
		float m_FallTime{1.2f};
		float m_AccuFallTime{};

		bool m_Notified{};
	};

	class ExposedBagState : public CoinBagState
	{
	public:
		ExposedBagState(CoinBagComponent* component);
		virtual ~ExposedBagState() = default;
		virtual void Update(CoinBagComponent* component) override;

	private:
		Cell* m_pCurrentCell{};
	};

	class CollectedBagState : public CoinBagState
	{
	public:
		CollectedBagState(CoinBagComponent* component);
		virtual ~CollectedBagState() = default;
		virtual void Update(CoinBagComponent* component) override { component; }
	};
}