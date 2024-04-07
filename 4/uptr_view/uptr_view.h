#pragma once
#include <memory>
#include <utility>

template<typename Ty>
class uptr_view final
{
public:
	uptr_view() noexcept: mp_uptr {nullptr}{}
	uptr_view(std::unique_ptr<Ty>& uptr) noexcept: 
		mp_uptr{&uptr}{}
	uptr_view(const std::unique_ptr<Ty>& uptr) noexcept: 
		mp_uptr{&uptr}{}
	uptr_view(std::nullptr_t) noexcept: 
		mp_uptr {nullptr}{}
	uptr_view& operator=(std::unique_ptr<Ty>& ptr) noexcept
	{
		mp_uptr = &ptr;
		return *this;
	}
	uptr_view& operator=(const std::unique_ptr<Ty>& ptr) noexcept
	{
		mp_uptr = &ptr;
		return *this;
	}

	bool operator==(const uptr_view& rhs) const noexcept
	{	return mp_uptr == rhs.mp_uptr; }
	bool operator!=(const uptr_view& rhs) const noexcept
	{	return !(*this == rhs); 	}
	bool operator==(std::nullptr_t) const noexcept
	{ 	return mp_uptr == nullptr || *mp_uptr == nullptr; }
	bool operator!=(std::nullptr_t) const noexcept
	{	return !(*this == nullptr); }
	bool is_reference(const std::unique_ptr<Ty>& uptr)
	{	return mp_uptr == &uptr;	}

	explicit operator bool const ()
	{ return *this != nullptr; }
	const Ty& operator*() const noexcept
	{ return **mp_uptr; }
	const Ty* operator->() const noexcept
	{ return mp_uptr->get(); }
	const Ty* get() const noexcept
	{ return mp_uptr->get(); }

	Ty& operator*() noexcept
	{ return const_cast<Ty&>(std::as_const(*this).operator*());}
	Ty* operator->() noexcept
	{ return const_cast<Ty*>(std::as_const(*this).operator->());}
	Ty* get() noexcept
	{ return const_cast<Ty*>(std::as_const(*this).get());}

	std::unique_ptr<Ty>& release()	noexcept
	{
		auto* result = mp_uptr;
		mp_uptr = nullptr;
		return const_cast<std::unique_ptr<Ty>&>(*result);
	}
private:
	const std::unique_ptr<Ty>* mp_uptr;
};