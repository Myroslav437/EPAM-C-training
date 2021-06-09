#pragma once
#pragma once

#include <utility>
#include <cstring>

namespace mystl {

	// VectorBase
	//
	// Memory allocation is implemented in the VectorBase class. 
	// If an exception is thrown in the vector constructor, the destructor for 
	// VectorBase will be called automatically (and free the allocated memory).
	//
	// The C++ standard (15.2 paragraph 2): 
	//    "An object that is partially constructed or partially destroyed will
	//     have destructors executed for all its fully constructed subobjects,
	//     that is, for subobjects for which the constructor has been completed
	//     execution and the destructor has not yet begun execution."

	template <class T, class AllocT>
	class VectorBase {
	public:
		typedef AllocT              allocator_type;
		typedef std::ptrdiff_t      difference_type;
		typedef std::size_t         size_type;

		VectorBase();
		VectorBase(const allocator_type& allocator);
		VectorBase(size_type n, const allocator_type& alloc);
		~VectorBase();

		const allocator_type& get_allocator() const;
		allocator_type& get_allocator();
		void set_allocator(const allocator_type& alloc);

	protected:
		T* allocate(size_type n);
		void free(T* p, size_type n);
		size_type calcNewCapacity(size_type currentCapacity);

	protected:
		T* pBegin, * pEnd;
		T* pCapacity;
		allocator_type Allocator;

		static const size_type npos = (size_type)(-1);        // non-valid position.
		static const size_type capMaxSize = (size_type)(-2);  // -1 is reserved for 'npos'
	};


	template <class T, class AllocT>
	VectorBase<T, AllocT>::VectorBase() :
		pBegin(nullptr),
		pEnd(nullptr),
		pCapacity(nullptr),
		Allocator(allocator_type())
	{
	}

	template <class T, class AllocT>
	VectorBase<T, AllocT>::VectorBase(const allocator_type& alloc) :
		pBegin(nullptr),
		pEnd(nullptr),
		pCapacity(nullptr),
		Allocator(alloc)
	{
	}

	template <class T, class AllocT>
	VectorBase<T, AllocT>::VectorBase(size_type n, const allocator_type& alloc) :
		Allocator(alloc)
	{
		pBegin = allocate(n);
		pEnd = pBegin;
		pCapacity = pBegin + n;
	}


	template <class T, class AllocT>
	VectorBase<T, AllocT>::~VectorBase() {
		if (pBegin) {
			Allocator.deallocate(pBegin, pCapacity - pBegin);
		}
	}

	template <class T, class AllocT>
	const typename VectorBase<T, AllocT>::allocator_type&
		VectorBase<T, AllocT>::get_allocator() const {
		return Allocator;
	}


	template <class T, class AllocT>
	typename VectorBase<T, AllocT>::allocator_type&
		VectorBase<T, AllocT>::get_allocator() {
		return Allocator;
	}


	template <class T, class AllocT>
	void VectorBase<T, AllocT>::set_allocator(const allocator_type& alloc) {
		Allocator = alloc;
	}


	template <class T, class AllocT>
	T* VectorBase<T, AllocT>::allocate(size_type n) {
		if (n) {
			T* p = Allocator.allocate(n);
			return p;
		}
		else {
			return nullptr;
		}
	}


	template <class T, class AllocT>
	void VectorBase<T, AllocT>::free(T* p, size_type n) {
		if (p) {
			Allocator.deallocate(p, n);
		}
	}


	template <class T, class AllocT>
	typename VectorBase<T, AllocT>::size_type
		VectorBase<T, AllocT>::calcNewCapacity(size_type currentCapacity) {
		return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
	}
}