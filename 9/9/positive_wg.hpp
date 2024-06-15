#include <stdexcept>
#include <cassert>
#include <algorithm>
#include "weight_graph.hpp"
#include "binary_heap.hpp"

template<typename Ty, typename Weight = size_t>
class positive_wg: public virtual weight_graph<Ty, Weight>
{
public:
	using weight_graph<Ty, Weight>::weight_graph;

	void add_edge(const Ty& v1, const Ty& v2, Weight weight) override
	{
		if (weight < 0)
			throw std::range_error("positive_wg weight of edge cannot be negative");
		weight_graph<Ty, Weight>::add_edge(v1, v2, weight);
	}

	[[nodiscard]]
	std::vector<std::vector<Ty>> dijkstra(const Ty& v) const
	{
		std::vector<std::vector<Ty>> result;
		
		std::unordered_map<std::reference_wrapper<const Ty>, Entry,
						   KTyRefHash, KTyRefEqual> table;
		for (const auto& [ key, value ] : weight_graph<Ty, Weight>::m_adjList)
		{
			Weight dv { weight_graph<Ty, Weight>::INF };
			if (key == v)
				dv = 0;

			table.emplace(
				std::cref(key),
				Entry{ .known = false, .dv = dv, .pv = std::nullopt }
			);
		}
		
		binary_heap<PrityEntry, PrityCpr> priorityQue;
		std::unordered_map<std::reference_wrapper<const PrityEntry>, Activity,
						   KPrityEntryRefHash, KPrityEntryRefEqual> queActivity;
		//初始化队列(INF不进行插入)
		auto [ fKey, fValue ] { *table.find(v) };
		PrityEntry firstValue { &(fKey.get()), fValue };
		priorityQue.push(firstValue);
		queActivity.emplace(std::cref(firstValue), Activity::VALID);

		while(!priorityQue.empty())
		{
			while(!priorityQue.empty() &&
				  queActivity.find(priorityQue.top())->second == Activity::INVALID)
				priorityQue.pop();
			assert(!priorityQue.empty());
			const auto& [ Typ, entryV ] { priorityQue.top() };
			priorityQue.pop();
			//known标记为true时无需入队
			table.find(std::cref(*Typ))->second.known = true;
			const auto& [ tyv, vecEntry ] { *weight_graph<Ty, Weight>::m_adjList.find(*Typ) };
			//遍历相邻节点
			for (const auto& [ adjTyr, weight ] : vecEntry)
			{
				auto& entry { table.find(adjTyr)->second };
				PrityEntry queEntryOld { &(adjTyr.get()), entry };
				if ( auto actyItr { queActivity.find(queEntryOld) }; actyItr != queActivity.end())
					actyItr->second = Activity::INVALID;

				if (entry.known || entry.dv < weight)
					continue;
				
				assert(entry.known == false);
				entry.dv = weight;
				entry.pv.emplace(*Typ);
				PrityEntry queEntryNew { &(adjTyr.get()), entry };
				queActivity.emplace( std::cref(queEntryNew), Activity::VALID );
				priorityQue.push(queEntryNew);
			}
		}

		for (const auto& [ key, value ] : table)
		{
			std::vector<Ty> line;
			line.push_back(key.get());
			if (v == key.get())
			{
				result.push_back(line);
				continue;
			}

			while(value.pv.value() != v)
			{
				line.push_back(value.pv.value().get());
			}
			line.push_back(v);
			std::ranges::reverse(line);
			result.push_back(line);
		}
		
		std::ranges::sort(result, std::less<>{}, [](const auto& vec){ return vec.back(); });
		return result;
	}

private:
	struct Entry
	{
		bool known;
		Weight dv;
		std::optional<std::reference_wrapper<const Ty>> pv;
	};

	using PrityEntry = std::pair<const Ty*, Entry>;

	struct KTyRefHash
	{
		size_t operator()(const std::reference_wrapper<const Ty>& value) const
		{
			return std::hash<Ty>{}(value.get());
		}
	};

	struct KTyRefEqual
	{
		bool operator()(const std::reference_wrapper<const Ty>& lhs,
						const std::reference_wrapper<const Ty>& rhs) const
		{
			return lhs.get() == rhs.get();
		}
	};

	struct PrityCpr
	{
		bool operator()(const PrityEntry& lhs, const PrityEntry& rhs) const
		{
			return lhs.second.dv < rhs.second.dv;
		}
	};

	struct PrityEntryHash
	{
		size_t operator()(const PrityEntry& value) const
		{
			return {
				std::hash<const Ty*>{}(value.first) ^
				(std::hash<bool>{}(value.second.known) << 1 ) ^
				(std::hash<Weight>{}(value.second.dv) << 2 ) ^
				(value.second.pv.has_value() ? (
					KTyRefHash{}(
						value.second.pv.value()) << 3
					) : 0
				)
			};
		}
	};

	struct PrityEntryEqual
	{
		bool operator()(const PrityEntry& lhs, const PrityEntry& rhs) const
		{
			//在操作逻辑中能保证每个key都不相同
			//return false;
			return lhs.first == rhs.first
				&& lhs.second.known == rhs.second.known
				&& lhs.second.dv == rhs.second.dv
				&& lhs.second.pv == rhs.second.pv;
				
		}
	};

	struct KPrityEntryRefHash
	{
		size_t operator()(const std::reference_wrapper<const PrityEntry>& value) const
		{
			return PrityEntryHash{}(value.get());
		}
	};

	struct KPrityEntryRefEqual
	{
		bool operator()(const std::reference_wrapper<const PrityEntry>& lhs,
						const std::reference_wrapper<const PrityEntry>& rhs) const
		{
			return PrityEntryEqual{}(lhs.get(), rhs.get());
		}

	};

	enum class Activity{
		VALID, INVALID
	};
};

