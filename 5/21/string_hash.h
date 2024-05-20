#include <string>
#include <vector>
#include <utility>

class StrHashTable
{
public:
	StrHashTable();
	StrHashTable(size_t initalTableSize);
	bool contains(const std::string& str) const;
	void clear();
	bool insert(const std::string& str);
	bool remove(const std::string& str);
	size_t size() const noexcept { return m_size; }
private:
    enum Entry { ACTIVE, EMPTY, DELETED };
	struct HashEntry
	{
		std::string m_str;
		Entry m_condition;
		bool activity() const;
		HashEntry(): m_condition{EMPTY}{}
		HashEntry(std::string str, Entry condition):
			m_str{std::move(str)}, m_condition{condition}
			{}
	};
private:
	size_t string_hash(const std::string& str) const;
	bool check_rehash();
	void rehash();
	std::pair<Entry, size_t> find_pos(const std::string& str) const;
private:
	inline static const size_t sk_initialTableSize{53};
private:
	std::vector<HashEntry> m_table;
	size_t m_size{0};
	mutable bool hashFail{false};
};