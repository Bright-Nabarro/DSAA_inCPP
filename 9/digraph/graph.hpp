#pragma once
#include <unordered_set>
#include <unordered_map>
#include <print>
#include <stdexcept>
#include <limits>
#include <queue>
#include <algorithm>
#include <cassert>

template<typename Ty>
class digraph
{
public:

	virtual ~digraph() = default;
	void add_vec(const Ty& value)
	{
		if (m_adjList.find(value) != m_adjList.end())
			return;

		m_adjList[value] = {
			.sets = {},
			.inDegree = 0,
			.distence = INF,
		};
	}

	void add_edge(const Ty& u, const Ty& v)
	{
		auto [ uItr, vItr ] { check_vecs(u, v) };

		uItr->second.sets.insert(v);
		vItr->second.inDegree++;
	}

	std::vector<Ty> top_sort() 
	{
		

		std::vector<Ty> ret;	
		std::unordered_map<std::reference_wrapper<const Ty>, std::size_t, hash_t, equal_t>
			inDegreeListsCopy(0, s_kHash_fn, s_kEqual_fn);
		std::for_each(m_adjList.cbegin(), m_adjList.cend(), 
				 [&](const auto& pair) {
				 	inDegreeListsCopy[std::cref(pair.first)] = pair.second.inDegree;
				 }
			);
		
		std::queue<Ty> que;
		std::for_each(inDegreeListsCopy.cbegin(), inDegreeListsCopy.cend(),
				[&](const auto& pair) {
					if (pair.second == 0)
						que.push(pair.first);
				}
			);

		while(!que.empty())
		{
			ret.push_back(std::move(que.front()));
			que.pop();

			for(const auto& adj : m_adjList[ret.back()].sets)
			{
				if(--inDegreeListsCopy[adj] == 0)
					que.push(adj);
			}
		}

		return ret;
	}

	std::vector<Ty> bfs(const Ty& u, const Ty& v) const
	{
		check_vecs(u, v);
		std::vector<Ty> ret;
		std::unordered_map<std::reference_wrapper<const Ty>, std::reference_wrapper<const Ty>, hash_t, equal_t>
			predecessor ( 0, s_kHash_fn, s_kEqual_fn);
		std::queue<std::pair<std::reference_wrapper<const Ty>, size_t>> que;
		que.emplace(u, 0);
	
		while(!que.empty())
		{
			if (v == que.front().first)
			{
				auto itr { predecessor.find(v) };
				assert(itr != predecessor.cend());
				while(itr->second != u)
				{
					ret.push_back(itr->first);
					itr = predecessor.find(itr->second);
				}
				ret.push_back(itr->first);
				ret.push_back(itr->second);
				std::reverse(ret.begin(), ret.end());
				return ret;
			}

			for (const auto& vertex : m_adjList.find(que.front().first)->second.sets)
			{
				que.emplace(vertex, que.front().second+1);

				predecessor.emplace(std::cref(vertex) , std::cref(que.front().first));
			}

			que.pop();
		}
		return {};
	}

	void display_dot(std::FILE* stream = stdout) const
	{
		std::println(stream, "digraph G {{");
		for (const auto& [ key, value ] : m_adjList)
		{
			if (value.sets.empty())
			{
				std::println("\t\"{}\"", key);
				continue;
			}

			auto itr = value.sets.cbegin();
			for(; itr != value.sets.cend(); ++itr)
			{
				std::println("\t\"{}\" -> \"{}\"", key, *itr);
			}
		}
		std::println(stream, "}}");
	}

	void display_degree(std::FILE* stream = stdout) const
	{
		std::vector<Ty> adjListCpy;
		for (const auto& [ key, value ] : m_adjList)
			adjListCpy.push_back(key);
		std::ranges::sort(adjListCpy);
		
		for (const auto& value : adjListCpy)
			std::println(stream, "\"{}\" : \"{}\"", value,
						 m_adjList.find(value)->second.inDegree);
	}

	

private:
	[[maybe_unused]]
	decltype(auto) check_vecs(const Ty& u, const Ty& v) const
	{
		auto uItr { m_adjList.find(u) };
		auto vItr { m_adjList.find(v) };
		if (uItr == m_adjList.end() || vItr == m_adjList.end())
		{
			throw std::range_error { 
				std::format("{} doesnot in graph", 
						uItr == m_adjList.end() ? u : v)
			};
		}
		return std::pair<decltype(uItr), decltype(vItr)> { uItr, vItr };
	}

	decltype(auto) check_vecs(const Ty& u, const Ty& v)
	{
		auto uItr { m_adjList.find(u) };
		auto vItr { m_adjList.find(v) };
		if (uItr == m_adjList.end() || vItr == m_adjList.end())
		{
			throw std::range_error { 
				std::format("{} doesnot in graph", 
						uItr == m_adjList.end() ? u : v)
			};
		}
		return std::pair<decltype(uItr), decltype(vItr)> { uItr, vItr };
	}
	
	inline static const auto s_kHash_fn = [](const std::reference_wrapper<const Ty>& ref) {
		return std::hash<Ty>()(ref.get());
	};
	inline static const auto s_kEqual_fn = [](const std::reference_wrapper<const Ty>& lhs,
							  const std::reference_wrapper<const Ty>& rhs) {
		return lhs.get() == rhs.get();
	};
	using hash_t = decltype(s_kHash_fn);
	using equal_t = decltype(s_kEqual_fn);

private:
	struct VertexData
	{
		std::unordered_multiset<Ty> sets;
		std::size_t inDegree;
		std::size_t distence;
	};

	inline static const std::size_t INF { std::numeric_limits<std::size_t>::max() };
	std::unordered_map<Ty, VertexData> m_adjList;
};

