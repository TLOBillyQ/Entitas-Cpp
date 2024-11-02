// Copyright (c) 2020 Juan Delgado (JuDelCo)
// License: MIT License
// MIT License web page: https://opensource.org/licenses/MIT

#pragma once

#include "Entity.hpp"

namespace EntitasPP
{
class Matcher;
struct TriggerOnEvent;
typedef std::vector<Matcher> MatcherList;

class Matcher
{
	public:
		Matcher() = default;
		static auto AllOf(const ComponentIdList indices) -> const Matcher;
		static auto AnyOf(const ComponentIdList indices) -> const Matcher;
		static auto NoneOf(const ComponentIdList indices) -> const Matcher;

		auto WithAllOf(ComponentIdList indices) -> Matcher;
		auto WithAnyOf(ComponentIdList indices) -> Matcher;
		auto WithNoneOf(ComponentIdList indices) -> Matcher;

		bool IsEmpty() const;
		bool Matches(const EntityPtr& entity);
		auto GetIndices() -> const ComponentIdList;
		auto GetAllOfIndices() const -> const ComponentIdList;
		auto GetAnyOfIndices() const -> const ComponentIdList;
		auto GetNoneOfIndices() const -> const ComponentIdList;

		auto GetHashCode() const -> unsigned int;
		bool CompareIndices(const Matcher& matcher) const;

		auto OnEntityAdded() -> const TriggerOnEvent*;
		auto OnEntityRemoved() -> const TriggerOnEvent*;
		auto OnEntityAddedOrRemoved() -> const TriggerOnEvent*;

		bool operator ==(const Matcher right) const;

	protected:
		void CalculateHash();

		ComponentIdList mIndices;
		ComponentIdList mAllOfIndices;
		ComponentIdList mAnyOfIndices;
		ComponentIdList mNoneOfIndices;

	private:
		auto ApplyHash(unsigned int hash, const ComponentIdList indices, int i1, int i2) const -> unsigned int;
		auto MergeIndices() const -> ComponentIdList;
		static auto MergeIndices(MatcherList matchers) -> ComponentIdList;
		static auto DistinctIndices(ComponentIdList indices) -> ComponentIdList;

		unsigned int mCachedHash{0};
};
}

namespace std
{
template <>
struct hash<EntitasPP::Matcher>
{
	std::size_t operator()(const EntitasPP::Matcher& matcher) const
	{
		return hash<unsigned int>()(matcher.GetHashCode());
	}
};
}

namespace
{
#define COMPONENT_GET_TYPE_ID(COMPONENT_CLASS) EntitasPP::ComponentTypeId::Get<COMPONENT_CLASS>()

#define Matcher_AllOf(C1) \
((EntitasPP::Matcher)EntitasPP::Matcher::AllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1) })))
#define Matcher_AllOf2(C1, C2) \
((EntitasPP::Matcher)EntitasPP::Matcher::AllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2) })))
#define Matcher_AllOf3(C1, C2, C3) \
((EntitasPP::Matcher)EntitasPP::Matcher::AllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3) })))
#define Matcher_AllOf4(C1, C2, C3, C4) \
((EntitasPP::Matcher)EntitasPP::Matcher::AllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4) })))
#define Matcher_AllOf5(C1, C2, C3, C4, C5) \
((EntitasPP::Matcher)EntitasPP::Matcher::AllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5) })))
#define Matcher_AllOf6(C1, C2, C3, C4, C5, C6) \
((EntitasPP::Matcher)EntitasPP::Matcher::AllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5), COMPONENT_GET_TYPE_ID(C6) })))

#define Matcher_AnyOf(C1) \
((EntitasPP::Matcher)EntitasPP::Matcher::AnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1) })))
#define Matcher_AnyOf2(C1, C2) \
((EntitasPP::Matcher)EntitasPP::Matcher::AnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2) })))
#define Matcher_AnyOf3(C1, C2, C3) \
((EntitasPP::Matcher)EntitasPP::Matcher::AnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3) })))
#define Matcher_AnyOf4(C1, C2, C3, C4) \
((EntitasPP::Matcher)EntitasPP::Matcher::AnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4) })))
#define Matcher_AnyOf5(C1, C2, C3, C4, C5) \
((EntitasPP::Matcher)EntitasPP::Matcher::AnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5) })))
#define Matcher_AnyOf6(C1, C2, C3, C4, C5, C6) \
((EntitasPP::Matcher)EntitasPP::Matcher::AnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5), COMPONENT_GET_TYPE_ID(C6) })))

#define Matcher_NoneOf(C1) \
((EntitasPP::Matcher)EntitasPP::Matcher::NoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1) })))
#define Matcher_NoneOf2(C1, C2) \
((EntitasPP::Matcher)EntitasPP::Matcher::NoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2) })))
#define Matcher_NoneOf3(C1, C2, C3) \
((EntitasPP::Matcher)EntitasPP::Matcher::NoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3) })))
#define Matcher_NoneOf4(C1, C2, C3, C4) \
((EntitasPP::Matcher)EntitasPP::Matcher::NoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4) })))
#define Matcher_NoneOf5(C1, C2, C3, C4, C5) \
((EntitasPP::Matcher)EntitasPP::Matcher::NoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5) })))
#define Matcher_NoneOf6(C1, C2, C3, C4, C5, C6) \
((EntitasPP::Matcher)EntitasPP::Matcher::NoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5), COMPONENT_GET_TYPE_ID(C6) })))

#define With_AllOf(C1) \
WithAllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1) }))
#define With_AllOf2(C1, C2) \
WithAllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2) }))
#define With_AllOf3(C1, C2, C3) \
WithAllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3) }))
#define With_AllOf4(C1, C2, C3, C4) \
WithAllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4) }))
#define With_AllOf5(C1, C2, C3, C4, C5) \
WithAllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5) }))
#define With_All6(C1, C2, C3, C4, C5, C6) \
WithAllOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5), COMPONENT_GET_TYPE_ID(C6) }))

#define With_AnyOf(C1) \
WithAnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1) }))
#define With_AnyOf2(C1, C2) \
WithAnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2) }))
#define With_AnyOf3(C1, C2, C3) \
WithAnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3) }))
#define With_AnyOf4(C1, C2, C3, C4) \
WithAnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4) }))
#define With_AnyOf5(C1, C2, C3, C4, C5) \
WithAnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5) }))
#define With_AnyOf6(C1, C2, C3, C4, C5, C6) \
WithAnyOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5), COMPONENT_GET_TYPE_ID(C6) }))

#define With_NoneOf(C1) \
WithNoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1) }))
#define With_NoneOf2(C1, C2) \
WithNoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2) }))
#define With_NoneOf3(C1, C2, C3) \
WithNoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3) }))
#define With_NoneOf4(C1, C2, C3, C4) \
WithNoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4) }))
#define With_NoneOf5(C1, C2, C3, C4, C5) \
WithNoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5) }))
#define With_NoneOf6(C1, C2, C3, C4, C5, C6) \
WithNoneOf(std::vector<EntitasPP::ComponentId>({ COMPONENT_GET_TYPE_ID(C1), COMPONENT_GET_TYPE_ID(C2), COMPONENT_GET_TYPE_ID(C3), COMPONENT_GET_TYPE_ID(C4), COMPONENT_GET_TYPE_ID(C5), COMPONENT_GET_TYPE_ID(C6) }))

}
