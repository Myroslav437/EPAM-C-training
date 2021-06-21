#pragma once

#include <cstdio>
#include <type_traits>

namespace mysp {
	class unique_file {
	public:
		typedef std::FILE		element_type;
		typedef std::FILE* pointer;
		typedef unique_file			this_type;

		constexpr unique_file() noexcept;
		constexpr unique_file(std::nullptr_t) noexcept;
		explicit unique_file(pointer p) noexcept;
		unique_file(this_type&& u) noexcept;

		virtual ~unique_file() noexcept;

		virtual void reset(pointer ptr = pointer()) noexcept;
		virtual pointer release() noexcept;

		virtual void swap(this_type& other) noexcept;

		virtual this_type& operator=(this_type&& r) noexcept;
		virtual this_type& operator=(std::nullptr_t) noexcept;

		virtual typename std::add_lvalue_reference<element_type>::type operator*() const;
		virtual pointer operator->() const noexcept;

		virtual pointer get() const noexcept;
		virtual explicit operator bool() const noexcept;


		unique_file(const this_type&) = delete;
		unique_file& operator=(const this_type&) = delete;
		unique_file& operator=(pointer pValue) = delete;

	protected:
		typedef struct default_closer {
			typedef std::FILE	type;
			typedef std::FILE* pointer;

			static void close(pointer p) noexcept;
		}	closer_type;

	private:
		pointer ptr_;
	};
}