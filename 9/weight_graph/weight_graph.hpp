#pragma once
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <vector>
#include <print>

template<typename Ty, typename Weight = size_t>
class weight_graph
{
public:
	struct Edge
	{
		std::reference_wrapper<Ty> v1;
		std::reference_wrapper<Ty> v2;
		Weight weight;
	};
public:
	weight_graph() = default;
	virtual ~weight_graph() = default;

	template<typename TyRef>
	requires std::is_same_v<Ty, std::decay_t<TyRef>>
	void add_vec(TyRef&& value)
	{
		m_adjList[std::forward<TyRef>(value)];
	}

	void add_edge(const Ty& v1, const Ty& v2, Weight weight)
	{
		auto [ itr1, itr2 ] { check_vecs(v1, v2) };
		//特别注意，这里的引用包装需要引用到键本身
		itr1->second.emplace(std::cref(itr2->first), weight);
		itr2->second.emplace(std::cref(itr1->first), weight);
	}
	
	std::vector<std::pair<Ty, Ty>> edges() const
	{
		auto m_adjListCpy { m_adjList };
		std::vector<std::pair<Ty, Ty>> ret;
		// 容器状态会发生改变，range for loop不适用
		for(auto fromItr { m_adjListCpy.begin() };
			fromItr !=  m_adjListCpy.end(); ++fromItr)
		{
			// unordered_set/map insert，erase操作都不会使现有iterator失效
			// fromItr, toItr特指外层map的iterator
			for(auto innerItr { fromItr->second.begin() };
				innerItr != fromItr->second.end(); ++innerItr)
			{
				const Ty& value = innerItr->first;
				const Weight& weight = innerItr->second;

				ret.emplace_back(fromItr->first, value, weight);
				auto toItr { m_adjListCpy.find(value) };
				assert(toItr != m_adjListCpy.end());

				if (toItr == fromItr)	//圈
					innerItr = fromItr->second.erase(innerItr);
				else
					toItr->second.erase(std::pair{ std::cref(fromItr->first), weight });
			}

		}
	}
	
	void display_dot(FILE* stream = stdout) const
	{
		std::println(stream, "graph G {{");
		
		auto theEdges { edges() };
		for (const auto& value : theEdges)
		{
		}

		std::println(stream, "}}");
	}

protected:	//impl func
	[[maybe_unused]]
	decltype(auto) check_vecs(const Ty& v1, const Ty& v2)
	{
		auto itr1 { m_adjList.find(v1) };
		auto itr2 { m_adjList.find(v2) };
		if (itr1 == m_adjList.end() || itr2 == m_adjList.end())
		{
			throw std::range_error{
				std::format("value: {} doesnot exist", itr1 == m_adjList.end() ? v1 : v2)
			};
		}

		return std::pair{ itr1, itr2 };
	}
protected: 	//constant value, type
	inline static constexpr size_t INF { std::numeric_limits<size_t>::max() };
	struct EdgeRefHash
	{
		size_t operator()(const std::pair<std::reference_wrapper<const Ty>, size_t>& ref) const
		{
			return std::hash<Ty>{}(ref.first.get()) ^
				   (std::hash<size_t>{}(ref.second) << 1);
		}
	};
	struct EdgeRefEqual
	{
		bool operator()(const std::pair<std::reference_wrapper<const Ty>, size_t>& lhs,
					    const std::pair<std::reference_wrapper<const Ty>, size_t>& rhs) const
		{
			return lhs.first.get() == rhs.first.get() &&
				   lhs.second == rhs.second;
		}
	};
protected:	//data member
	//按照正常逻辑编写，相同权值和顶点的边视为相等（可以拥有多条）
	using VecEntry = std::unordered_multiset<std::pair<std::reference_wrapper<const Ty>, Weight>,
		  									 EdgeRefHash, EdgeRefEqual>;
	std::unordered_map<Ty, VecEntry> m_adjList;
};

