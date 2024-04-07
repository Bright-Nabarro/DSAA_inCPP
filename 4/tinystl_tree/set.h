#pragma once
#include "avl_tree.h"

template<typename Ty>
class set
{
public:
	//constructor
	set();
	set(const set& rhs);
	set& operator=(const set& rhs);
	set(set&& rhs) noexcept;
	set& operator=(set&& rhs) noexcept;
	//add initializer later
	virtual ~set() = default;

	void swap(set& rhs) noexcept;

public:
	using size_type = size_t;
	class const_iterator;
	class iterator;
public:
	//-capbility-----------------------------------------------
	bool empty() const noexcept;

	size_type size() const noexcept;

	size_type max_size() const noexcept;
	//---------------------------------------------------------

	//-modifier------------------------------------------------
	void clear();

	template<typename Ty_ref>
	std::pair<iterator, bool> insert(Ty_ref&& value);

	template<typename Ty_ref>
	void insert(const_iterator pos, Ty_ref&& value);

	//template<typename InputIt>
	//void insert(InputIt first, InputIt last);

	template<typename... Args>
	void emplace(Args...);

	template<typename... Args>
	void emplace_hint(const_iterator, Args...);

	iterator erase(const_iterator pos);

	iterator erase(const_iterator first, const_iterator last);

	size_type erase(const Ty& value);
	//---------------------------------------------------------

	//-lookup--------------------------------------------------
	bool contains (const Ty& value) const;

	const_iterator find(const Ty& value) const;
	//---------------------------------------------------------
private:

};