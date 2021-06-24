#pragma once

#include "../CObject.hpp"
#include <type_traits>
#include <exception>
#include <utility>
#include <memory>

namespace mysp {
	template <class Deleter = std::default_delete<CObject>>
	class SharedPtr {
	public:
		typedef CObject	    element_type;
		typedef CObject* pointer;
		typedef Deleter     deleter_type;
		typedef SharedPtr	this_type;

		constexpr SharedPtr();
		constexpr SharedPtr(std::nullptr_t);
		explicit SharedPtr(pointer p);
		SharedPtr(const this_type&) noexcept;
		SharedPtr(this_type&& u) noexcept;
		SharedPtr(pointer p, typename std::add_lvalue_reference<const deleter_type>::type deleter);
		SharedPtr(pointer p, typename std::remove_reference<deleter_type>::type&& deleter);


		virtual ~SharedPtr() noexcept;

		// virtual pointer release() noexcept;

		virtual void swap(this_type& other) noexcept;

		virtual this_type& operator=(const this_type&) noexcept;
		virtual this_type& operator=(this_type&& r) noexcept;
		virtual this_type& operator=(std::nullptr_t) noexcept;

		virtual element_type& operator*() const; //std::add_lvalue_reference<element_type>::type
		virtual pointer operator->() const noexcept;


		virtual pointer get() const noexcept;
		virtual deleter_type& get_deleter() noexcept;
		virtual const deleter_type& get_deleter() const noexcept;


		this_type& operator=(pointer pValue) = delete;

	protected:
		class ControlBlock {
		public:
			ControlBlock() noexcept : amount(0) {};
			ControlBlock(int init) noexcept : amount(init) {};
			ControlBlock(ControlBlock& t) noexcept : amount(t.amount) {};
			ControlBlock(ControlBlock&& t) noexcept : amount(std::move(t.amount)) { t.amount = 0; };

			void inc() { ++amount; };
			void dec() { --amount; };

			bool is_valid() const { return amount > 0; };
			void invalidate() { amount = 0; }

		private:
			int amount;
		};

	protected:
		ControlBlock* get_cntrlBlock();
		ControlBlock* get_cntrlBlock() const;
		virtual void reset() noexcept;

		pointer ptr_;
		deleter_type del_;
		ControlBlock* ctrl_ = nullptr;
	};


	template<class Deleter>
	constexpr SharedPtr<Deleter>::SharedPtr() :
		ptr_(pointer()), del_(deleter_type()), ctrl_(nullptr)
	{
	}

	template <class Deleter>
	constexpr SharedPtr<Deleter>::SharedPtr(std::nullptr_t) :
		ptr_(pointer()), del_(deleter_type()), ctrl_(nullptr)
	{
	}


	template <class Deleter>
	SharedPtr<Deleter>::SharedPtr(pointer p) :
		ptr_(p), del_(deleter_type())
	{
		try {
			ctrl_ = new ControlBlock();
			ctrl_->inc();
		}
		catch (...) {
			reset(); // free allocated memory
			throw;
		}
	}

	template<class Deleter>
	SharedPtr<Deleter>::SharedPtr(pointer p, typename std::add_lvalue_reference<const deleter_type>::type deleter) :
		ptr_(p), del_(deleter)
	{
		try {
			ctrl_ = new ControlBlock();
			ctrl_->inc();
		}
		catch (...) {
			reset(); // free allocated memory
			throw;
		}
	}

	template<class Deleter>
	SharedPtr<Deleter>::SharedPtr(pointer p, typename std::remove_reference<deleter_type>::type&& deleter) :
		ptr_(p), del_(std::move(deleter))
	{
		try {
			ctrl_ = new ControlBlock();
			ctrl_->inc();
		}
		catch (...) {
			reset(); // free allocated memory
			throw;
		}
	}

	template <class Deleter>
	SharedPtr<Deleter>::SharedPtr(const this_type& u) noexcept :
		ptr_(u.get()),
		del_(u.get_deleter()),
		ctrl_(u.get_cntrlBlock())
	{
		if (ctrl_ != nullptr)
			ctrl_->inc();
	}

	template <class Deleter>
	SharedPtr<Deleter>::SharedPtr(this_type&& u) noexcept {
		u.swap(*this);
	}

	template <class Deleter>
	SharedPtr<Deleter>::~SharedPtr() noexcept {
		reset();
	}

	template <class Deleter>
	void SharedPtr<Deleter>::swap(this_type& other) noexcept {
		std::swap(ptr_, other.ptr_);
		std::swap(del_, other.del_);
		std::swap(ctrl_, other.ctrl_);
	}

	template<class Deleter>
	typename SharedPtr<Deleter>::this_type& mysp::SharedPtr<Deleter>::operator=(const this_type& t) noexcept {
		SharedPtr tmp(t);
		tmp.swap(*this);

		return *this;
	}

	template <class Deleter>
	typename SharedPtr<Deleter>::this_type& SharedPtr<Deleter>::operator=(this_type&& r) noexcept {
		r.swap(*this);
		return *this;
	}

	template <class Deleter>
	typename SharedPtr<Deleter>::this_type& SharedPtr<Deleter>::operator=(std::nullptr_t) noexcept {
		reset();
		ptr_ = nullptr;
		ctrl_ = nullptr;
		return *this;
	}

	template <class Deleter>
	void SharedPtr<Deleter>::reset() noexcept {
		if (ctrl_ == nullptr) {
			return;
		}

		ctrl_->dec();
		if (!ctrl_->is_valid()) {
			if (ptr_ != nullptr) {
				get_deleter()(ptr_);
				ptr_ = nullptr;
			}
			delete ctrl_;
			ctrl_ = nullptr;
		}
	}

	//template <class Deleter>
	//typename SharedPtr<Deleter>::pointer SharedPtr<Deleter>::release() noexcept {
	//	ctrl_->dec();
	//	if (!ctrl_->is_valid()) {
	//		ctrl_->invalidate();
	//	}
	//	const pointer old = ptr_;
	//	ptr_ = pointer();
	//	return old;
	//}

	template<class Deleter>
	typename SharedPtr<Deleter>::element_type& SharedPtr<Deleter>::operator*() const
	{
		return *ptr_;
	}

	template <class Deleter>
	typename SharedPtr<Deleter>::pointer SharedPtr<Deleter>::operator->() const noexcept {
		return ptr_;
	}

	template <class Deleter>
	typename SharedPtr<Deleter>::pointer SharedPtr<Deleter>::get() const noexcept {
		return ptr_;
	}

	template<class Deleter>
	typename SharedPtr<Deleter>::deleter_type& SharedPtr<Deleter>::get_deleter() noexcept {
		return this->del_;
	}

	template<class Deleter>
	const typename SharedPtr<Deleter>::deleter_type& SharedPtr<Deleter>::get_deleter() const noexcept
	{
		return this->del_;
	}

	template<class Deleter>
	typename SharedPtr<Deleter>::ControlBlock* SharedPtr<Deleter>::get_cntrlBlock() {
		return ctrl_;
	}

	template<class Deleter>
	typename SharedPtr<Deleter>::ControlBlock* SharedPtr<Deleter>::get_cntrlBlock() const {
		return ctrl_;
	}
}