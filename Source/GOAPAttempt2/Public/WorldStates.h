#pragma once

//#include "Containers/Map.h"
//#include "Templates/Tuple.h"

#include <utility>
#include <memory>
#include <type_traits>

UENUM()
enum class WorldState
{
	IsHungry,
	IsThirsty,

	IsInDanger,
	IsDamaged,

	IsNearTree,
	IsNearBuyer,
	IsNearSeller,
	
	HaveWood,
	HaveAxe,
	HaveWater,
	HaveFood,

	HaveMoney,

	Chilling
};

//class Value final
//{
//	class ValueBase
//	{
//		template<class U>
//		class ValueModel;
//	public:
//		virtual ~ValueBase() {};
//		virtual ValueBase* Copy() = 0;
//		virtual bool IsEqual(const ValueModel<class U>* Other) = 0;
//		//virtual bool operator==(const ValueBase* rhs) const = 0;
//	};
//
//	template<class T>
//	class ValueModel final : public ValueBase
//	{
//	public:
//		ValueModel(const T& t) : Val{ t } {};
//		ValueModel(T&& t) : Val{ t } {};
//
//		virtual ValueModel* Copy() override { return new ValueModel(*this); }
//
//		virtual bool IsEqual(const ValueModel<class U>* Other) override
//		{
//			return Val == dynamic_cast<ValueModel<T>*>(Other)->Val;
//		}
//
//		//virtual bool operator==(const ValueBase* rhs) const override
//		//{
//		//	//T OtherVal = dynamic_cast<ValueModel>(rhs).Val;
//		//	//if (decltype(this->Val) == decltype(OtherVal))
//		//	if (std::is_same<T, decltype(dynamic_cast<ValueModel>(rhs).Val)>::value)
//		//		return Val == dynamic_cast<ValueModel>(rhs).Val;
//
//		//	return false;
//		//}
//
//	private:
//		T Val;
//	};
//
//public:
//	//template<class T>
//	//Value(T&& t) : pValue{ new ValueModel<std::remove_reference_t>(std::forward<T>(t)) } {};
//	template<class T>
//	Value(T&& t) : pValue{ new ValueModel<T>(std::forward<T>(t)) } {};
//
//	Value(Value&&) = default;
//	Value& operator=(Value&&) = default;
//
//	Value(const Value& other) : pValue{ other.pValue->Copy() } {};
//	Value& operator=(const Value& other)
//	{
//		pValue.reset(other.pValue->Copy());
//		return *this;
//	};
//
//	bool IsEqual(const Value& Other)
//	{
//		return pValue->IsEqual(Other.pValue.get());
//	}
//
//private:
//	std::unique_ptr<ValueBase> pValue;
//};

using Precondition = std::pair<WorldState, bool>;
using Consequence = std::pair<WorldState, bool>;
using DesiredState = std::pair<WorldState, bool>;

using ConditionalGoal = std::pair<Precondition, DesiredState>;

//using TPrecondition = std::pair<WorldState, Value>;
//using TConsequence = std::pair<WorldState, Value>;
//using TDesiredState = std::pair<WorldState, Value>;
//
//using TConditionalGoal = std::pair<TPrecondition, TDesiredState>;

class BoolIntFloatValue final
{
private:
	bool BoolValue{ false };
	int IntegerValue{ 0 };
	float FloatValue{ 0.f };

	enum class ValueType
	{
		BoolType,
		IntegerType,
		FloatType
	};
	ValueType TypeOfValue;

public:
	explicit BoolIntFloatValue(bool Value) : BoolValue{ Value }, TypeOfValue{ ValueType::BoolType } {}
	explicit BoolIntFloatValue(int Value) : IntegerValue{ Value }, TypeOfValue{ ValueType::IntegerType } {}
	explicit BoolIntFloatValue(float Value) : FloatValue{ Value }, TypeOfValue{ ValueType::FloatType } {}

private:
	template<class T>
	T Get() const
	{
		switch (TypeOfValue)
		{
		case BoolIntFloatValue::ValueType::BoolType:
			return BoolValue;
		case BoolIntFloatValue::ValueType::IntegerType:
			return IntegerValue;
		case BoolIntFloatValue::ValueType::FloatType:
			return FloatValue;
		}
	}

public:
	bool IsEqual(const BoolIntFloatValue& Other)
	{
		if (TypeOfValue == Other.TypeOfValue)
		{
			Get<bool>(); //problem here
		}
	}
};