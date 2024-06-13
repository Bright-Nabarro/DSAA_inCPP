#pragma once
#include "weight_graph.hpp"
#include "binary_heap.hpp"


template<typename Ty, typename Weight = size_t>
class weight_graph_mst : public weight_graph<Ty, Weight>
{
	struct PrimData;
	struct KTyRefHash;
	struct KTyRefEqual;
	using PrimTable = std::unordered_map<std::reference_wrapper<const Ty>,
		  			  	   PrimData, KTyRefHash, KTyRefEqual>;
	using PrimEntry = std::pair<const Ty*, PrimData>;
	struct PrimCpr;

	const std::unordered_map<Ty, typename weight_graph<Ty, Weight>::VecEntry>&
	m_adjList { weight_graph<Ty, Weight>::m_adjList };

public:
	using weight_graph<Ty, Weight>::weight_graph;
	//未完成，需要优先队列拥有一种能够让一个外部指针传入
	[[deprecated]]
	weight_graph<Ty, Weight> prim_alg() const
	{
		PrimTable table;
		//初始化表
		for (const auto& [ key, value ] : m_adjList)
		{
			table[std::cref(key)] = {
				.known 	= false,
				.dv 	= weight_graph<Ty, Weight>::INF,
				.pv		= std::nullopt,
			};
		}

		if (table.empty())
			return {};
		
		binary_heap<PrimEntry, PrimCpr> priorityQue;
		//选取map中第一个顶点初始化prioirtyQue
		//注意，primEntry的first是指针，避免reference_wrapper无默认构造问题
		table.begin()->second = { .known = true, .dv = 0, .pv = std::nullopt };
		priorityQue.push(PrimEntry{&table.begin()->first.get(), table.begin()->second});

		while(!priorityQue.empty())
		{
			//pTy == Ty*, primData = { .known, .dv, .pv(opt) }
			const auto& [ pTy, primData ] { priorityQue.top() };
			priorityQue.pop();
			//adjList == set{ vec(Ty), weight }
			const auto& adjList { m_adjList.find(*pTy)->second }; 
			for(const auto& [ vec, weight ] : adjList)
			{
				if (weight < table[vec].dv)
				{
					table[vec].dv = weight;
					table[vec].pv.value() = std::cref(*pTy);
				}
			}
		}

		return construct_graph(table);
	}

	//未完成，需要泛型不相交集
	weight_graph<Ty, Weight> kruskal_alg() const
	{
	}

private:
	weight_graph<Ty, Weight> construct_graph(const PrimTable& map) const
	{
		return{};
	}

private:
	struct PrimData
	{
		bool known;
		Weight dv;
		std::optional<std::reference_wrapper<const Ty>> pv;
	};

	struct KTyRefHash
	{
		size_t operator()(const std::reference_wrapper<const Ty>& ref) const
		{
			return std::hash<Ty>{}(ref.get());
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

	struct PrimCpr
	{
		bool operator()(const PrimEntry& lhs, const PrimEntry& rhs) const
		{
			return lhs.second.dv < rhs.second.dv;
		}
	};
};

