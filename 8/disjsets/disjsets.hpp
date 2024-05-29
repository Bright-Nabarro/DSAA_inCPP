#include <vector>

class disjsets
{
public:
	explicit disjsets(int numElements);
	int find(int x) const;
	int find(int x);
	void union_sets(int root1, int root2);
private:

	std::vector<int> m_arr;
};
