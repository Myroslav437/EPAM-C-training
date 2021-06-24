#pragma once

#include "../CObject.hpp"
#include <type_traits>
#include <exception>
#include <utility>
#include <memory>

namespace mysp {
	template <class Deleter = std::default_delete<CObject>>
	class UniquePtr {
	public:
		typedef CObject	    element_type;
		typedef Deleter     deleter_type;
		typedef UniquePtr	this_type;
		typedef CObject* pointer;

		constexpr UniquePtr() noexcept;
		constexpr UniquePtr(std::nullptr_t) noexcept;
		explicit UniquePtr(pointer p) noexcept;
		UniquePtr(this_type&& u) noexcept;

		UniquePtr(pointer p, typename std::add_lvalue_reference<const deleter_type>::type deleter) noexcept;
		UniquePtr(pointer p, typename std::remove_reference<deleter_type>::type&& deleter) noexcept;

		virtual ~UniquePtr() noexcept;

		virtual void reset(pointer ptr = pointer()) noexcept;
		virtual pointer release() noexcept;

		virtual void swap(this_type& other) noexcept;

		virtual this_type& operator=(this_type&& r) noexcept;
		virtual this_type& operator=(std::nullptr_t) noexcept;

		virtual element_type& operator*() const; //std::add_lvalue_reference<element_type>::type
		virtual pointer operator->() const noexcept;


		virtual pointer get() const noexcept;
		virtual deleter_type& get_deleter() noexcept;
		virtual const deleter_type& get_deleter() const noexcept;


		UniquePtr(const this_type&) = delete;
		UniquePtr& operator=(const this_type&) = delete;
		UniquePtr& operator=(pointer pValue) = delete;

	protected:
		pointer ptr_;
		deleter_type del_;
	};


	template<class Deleter>
	constexpr UniquePtr<Deleter>::UniquePtr() noexcept :
		ptr_(pointer()), del_(deleter_type())
	{
	}

	template <class Deleter>
	constexpr UniquePtr<Deleter>::UniquePtr(std::nullptr_t) noexcept :
		ptr_(pointer()), del_(deleter_type())
	{
	}

	template <class Deleter>
	UniquePtr<Deleter>::UniquePtr(pointer p) noexcept :
		ptr_(p), del_(deleter_type())
	{
	}

	template<class Deleter>
	UniquePtr<Deleter>::UniquePtr(pointer p, typename std::add_lvalue_reference<const deleter_type>::type deleter) noexcept :
		ptr_(p), del_(deleter)
	{
	}

	template<class Deleter>
	UniquePtr<Deleter>::UniquePtr(pointer p, typename std::remove_reference<deleter_type>::type&& deleter) noexcept :
		ptr_(p), del_(std::move(deleter))
	{
	}

	template <class Deleter>
	UniquePtr<Deleter>::UniquePtr(this_type&& u) noexcept :
		ptr_(u.release()),
		del_(std::forward<deleter_type>(u.get_deleter()))
	{
	}

	template <class Deleter>
	UniquePtr<Deleter>::~UniquePtr() noexcept {
		reset();
	}

	template <class Deleter>
	void UniquePtr<Deleter>::swap(this_type& other) noexcept {
		std::swap(ptr_, other.ptr_);
		std::swap(del_, other.del_);
	}

	template <class Deleter>
	typename UniquePtr<Deleter>::this_type& UniquePtr<Deleter>::operator=(this_type&& r) noexcept {
		reset(r.release());
		del_ = std::move(r.get_deleter()); //std::forward  ?
		return *this;
	}

	template <class Deleter>
	typename UniquePtr<Deleter>::this_type& UniquePtr<Deleter>::operator=(std::nullptr_t) noexcept {
		reset();
		return *this;
	}

	template <class Deleter>
	void UniquePtr<Deleter>::reset(pointer p) noexcept {
		if (p != ptr_) {
			const pointer old = ptr_;
			ptr_ = p;
			if (old != nullptr) {
				get_deleter()(old);
			}
		}
	}

	template <class Deleter>
	typename UniquePtr<Deleter>::pointer UniquePtr<Deleter>::release() noexcept {
		const pointer old = ptr_;
		ptr_ = pointer();
		return old;
	}

	template<class Deleter>
	typename UniquePtr<Deleter>::element_type& UniquePtr<Deleter>::operator*() const
	{
		return *ptr_;
	}

	template <class Deleter>
	typename UniquePtr<Deleter>::pointer UniquePtr<Deleter>::operator->() const noexcept {
		return ptr_;
	}

	template <class Deleter>
	typename UniquePtr<Deleter>::pointer UniquePtr<Deleter>::get() const noexcept {
		return ptr_;
	}

	template<class Deleter>
	typename UniquePtr<Deleter>::deleter_type& UniquePtr<Deleter>::get_deleter() noexcept {
		return this->del_;
	}

	template<class Deleter>
	const typename UniquePtr<Deleter>::deleter_type& UniquePtr<Deleter>::get_deleter() const noexcept
	{
		return this->del_;
	}

}