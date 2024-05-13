#pragma once

namespace FH
{
	//FWD
	class MoneyBagComponent;

	class MoneyBagState abstract
	{
	public:
		virtual ~MoneyBagState() = default;
		virtual void Update(MoneyBagComponent* component) = 0;
	};


	class IdleBagState : public MoneyBagState
	{
	public:
		IdleBagState() = default;
		virtual ~IdleBagState() = default;
		virtual void Update(MoneyBagComponent* component) override;
	};

	class MovingBagState : public MoneyBagState
	{
	public:
		MovingBagState(int col, MoneyBagComponent* component);
		virtual ~MovingBagState() = default;
		virtual void Update(MoneyBagComponent* component) override;

	private:
		int m_PrevPlayerCol{};
	};

	class FallingBagState : public MoneyBagState
	{
	public:
		FallingBagState() = default;
		virtual ~FallingBagState() = default;
		virtual void Update(MoneyBagComponent* component) override;

	private:
		float m_FallTime{1.5f};
		float m_AccuFallTime{};
	};

	class ExposedBagState : public MoneyBagState
	{
	public:
		ExposedBagState() = default;
		virtual ~ExposedBagState() = default;
		virtual void Update(MoneyBagComponent* component) override;
	};
}