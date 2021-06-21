#include "unique_file.h"
#include <exception>
#include <utility>

namespace mysp {
	constexpr unique_file::unique_file() noexcept :
		ptr_(pointer())
	{
	}

	constexpr unique_file::unique_file(std::nullptr_t) noexcept :
		ptr_(pointer())
	{
	}

	unique_file::unique_file(pointer p) noexcept :
		ptr_(p)
	{
	}

	unique_file::unique_file(this_type&& u) noexcept :
		ptr_(u.release())
	{
	}

	unique_file::~unique_file() noexcept {
		reset();
	}

	void unique_file::reset(pointer p) noexcept {
		if (p != this->ptr_) {
			const pointer old = ptr_;
			closer_type::close(old);
			ptr_ = p;
		}
	}

	unique_file::pointer unique_file::release() noexcept {
		const pointer old = ptr_;
		ptr_ = pointer();
		return old;
	}

	void unique_file::swap(this_type& other) noexcept {
		std::swap(ptr_, other.ptr_);
	}

	unique_file::this_type& unique_file::operator=(this_type&& r) noexcept {
		reset(r.release());
		return *this;
	}

	unique_file::this_type& unique_file::operator=(std::nullptr_t) noexcept {
		reset();
		return *this;
	}

	// Not noexcept, because the pointer may be NULL.
	typename std::add_lvalue_reference<unique_file::element_type>::type unique_file::operator*() const {
		return *ptr_;
	}

	unique_file::pointer unique_file::operator->() const noexcept {
		return ptr_;
	}

	unique_file::pointer unique_file::get() const noexcept {
		return ptr_;
	}

	unique_file::operator bool() const noexcept {
		return ptr_;
	}



	void unique_file::default_closer::close(pointer p) noexcept {
		if (p) {
			if (std::fclose(p) == EOF) {
				//
			}
		}
	}

}