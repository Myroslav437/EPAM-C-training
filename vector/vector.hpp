#pragma once 

#include <algorithm>
#include <stdexcept>
#include <initializer_list>
#include <iterator>
#include <memory>

#include "VectorBase.hpp"

// to remove in later lersions
#include <array>


namespace mystl {
	template <class T, class AllocT = std::allocator<T>>
	class vector : public VectorBase<T, AllocT> {
	public:
		typedef VectorBase<T, AllocT>					base_type;
		typedef vector<T, AllocT>						this_type;
		typedef T										value_type;
		typedef T*										pointer;
		typedef const T*								const_pointer;
		typedef T&										reference;
		typedef const T&								const_reference;
		typedef T*										iterator;
		typedef const T*								const_iterator; 
		typedef typename base_type::size_type           size_type;
		typedef typename base_type::allocator_type      allocator_type;

	private:
		using base_type::pBegin;
		using base_type::pEnd;
		using base_type::pCapacity;
		using base_type::Allocator;
		using base_type::allocate;
		using base_type::calcNewCapacity;
		using base_type::free;
		using base_type::npos;

	public:
		explicit vector(const allocator_type& allocator = allocator_type());
		explicit vector(size_type n, const allocator_type& allocator = allocator_type());
		vector(size_type n, const value_type& value, const allocator_type& allocator = allocator_type());
		vector(const this_type& x);
		vector(const this_type& x, const allocator_type& allocator);
		vector(this_type&& x);
		vector(std::initializer_list<value_type> ilist, const allocator_type& allocator = allocator_type());

	   ~vector();

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

		bool empty() const;
		size_type size() const;
		size_type capacity() const;

		pointer data();
		const_pointer data() const;

		reference operator[](size_type n);
		const_reference operator[](size_type n) const;
		reference at(size_type n);
		const_reference at(size_type n) const;

		void clear();
		void pop_back();

		iterator erase(const_iterator first, const_iterator last);
		iterator erase(const_iterator position);
		
		iterator insert(const_iterator position, const value_type& value);
		iterator insert(const_iterator position, value_type& value);

		template <typename InputIterator>
		iterator insert(const_iterator position, InputIterator first, InputIterator last);


		this_type& operator=(const this_type& x);
		this_type& operator=(this_type&& x);

		void swap(this_type& x);
		void push_back(const value_type& value);

	protected:
		template <typename BidirectionalIterator>
		void DoInsertFromIterator(const_iterator position, BidirectionalIterator first, BidirectionalIterator last);

		template <typename InputIterator>
		void DoAssignFromIterator(InputIterator first, InputIterator last);

		pointer DoCopy_n(const_pointer sbegin, const_pointer send, pointer dbegin);

		void DoFill_n(pointer p, size_type n, const value_type&  value);

		void DoSwap(this_type& x);

		void DoClearCapacity();

		template <typename ForwardIterator>

		void DoInitFromIterator(ForwardIterator first, ForwardIterator last);
	}; 

	template <class T, class AllocT>
	vector<T, AllocT>::vector(const allocator_type& allocator) :
		base_type(allocator)
	{
	}

	template <class T, class AllocT>
	vector<T, AllocT>::vector(size_type n, const allocator_type& allocator) :
		base_type(n, allocator)
	{
		DoFill_n(pBegin, n, T());
		pEnd = pBegin + n;
	}

	template <class T, class AllocT>
	vector<T, AllocT>::vector(size_type n, const value_type& value, const allocator_type& allocator) :
		base_type(n, allocator)
	{
		DoFill_n(pBegin, n, value);
		pEnd = pBegin + n;
	}

	template <class T, class AllocT>
	vector<T, AllocT>::vector(const this_type& x) :
		base_type(x.size(), x.Allocator)
	{
		pEnd = DoCopy_n(x.pBegin, x.pEnd, pBegin);
	}

	template <class T, class AllocT>
	vector<T, AllocT>::vector(const this_type& x, const allocator_type& allocator) :
		base_type(x.size(), allocator)
	{
		pEnd = DoCopy_n(x.pBegin, x.pEnd, pBegin);
	}

	template <class T, class AllocT>
	vector<T, AllocT>::vector(this_type&& x) :
		base_type()
	{
		DoSwap(x);
	}

	template <class T, class AllocT>
	vector<T, AllocT>::vector(std::initializer_list<value_type> ilist, const allocator_type& allocator)	: 
		base_type(allocator)
	{
		DoInitFromIterator(ilist.begin(), ilist.end());
	}

	template <class T, class AllocT>
	vector<T, AllocT>::~vector()
	{
		//Call destructor for the values. Parent class will free the memory.
		std::destroy(pBegin, pEnd);
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::iterator
		vector<T, AllocT>::begin()
	{
		return pBegin;
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::const_iterator
		vector<T, AllocT>::begin() const
	{
		return pBegin;
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::iterator
		vector<T, AllocT>::end()
	{
		return pEnd;
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::const_iterator
		vector<T, AllocT>::end() const
	{
		return pEnd;
	}

	template <class T, class AllocT>
	bool vector<T, AllocT>::empty() const
	{
		return (pBegin == pEnd);
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::size_type
		vector<T, AllocT>::size() const
	{
		return (size_type)(pEnd - pBegin);
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::size_type
		vector<T, AllocT>::capacity() const
	{
		return (size_type)(pCapacity - pBegin);
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::pointer
		vector<T, AllocT>::data()
	{
		return pBegin;
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::const_pointer
		vector<T, AllocT>::data() const
	{
		return pBegin;
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::reference
		vector<T, AllocT>::operator[](size_type n)
	{
		return *(pBegin + n);
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::const_reference
		vector<T, AllocT>::operator[](size_type n) const
	{
		return *(pBegin + n);
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::reference
		vector<T, AllocT>::at(size_type n)
	{
		if (n >= static_cast<size_type>(pEnd - pBegin)) {
			throw std::out_of_range("vector::at -- out of range");
		}

		return *(pBegin + n);
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::const_reference
		vector<T, AllocT>::at(size_type n) const
	{
		if (n >= static_cast<size_type>(pEnd - pBegin)) {
			throw std::out_of_range("vector::at -- out of range");
		}

		return *(pBegin + n);
	}

	template <class T, class AllocT>
	void vector<T, AllocT>::clear()
	{
		std::destroy(pBegin, pEnd);
		pEnd = pBegin;
	}

	template <class T, class AllocT>
	void vector<T, AllocT>::pop_back()
	{
		if (static_cast<size_type>(pEnd - pBegin) <= 0) {
			throw std::out_of_range("vector::pop_back -- out of range");
		}

		--pEnd;
		pEnd->~value_type();
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::iterator
		vector<T, AllocT>::erase(const_iterator position)
	{
		if ((position < pBegin) || (position >= pEnd)) {
			throw std::out_of_range("vector::erase -- invalid position");
		}

		iterator dst = const_cast<value_type*>(position);
		std::destroy_at(dst);

		if ((dst + 1) < pEnd) {
			iterator next = dst + 1;
			std::memmove(dst, next, size_type(pEnd - next) * sizeof(value_type));
		}
		--pEnd;
		return dst;
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::iterator
		vector<T, AllocT>::erase(const_iterator first, const_iterator last)
	{
		if ((first < pBegin) || (first > pEnd) || (last < pBegin) || (last > pEnd) || (last < first)) {
			throw std::out_of_range("vector::erase -- invalid position");
		}

		if (first != last)
		{
			iterator dstF = const_cast<value_type*>(first);
			iterator dstL = const_cast<value_type*>(last);
			std::destroy(dstF, dstL);
			std::memmove(dstF, dstL, static_cast<size_type>(pEnd - dstL) * sizeof(value_type));
			pEnd -= (dstL - dstF);
		}

		return const_cast<value_type*>(first);
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::iterator
		vector<T, AllocT>::insert(const_iterator position, const value_type& value) {

		std::array<std::reference_wrapper<value_type>, 1> temp({ const_cast<value_type&>(value) });
		DoInsertFromIterator(position, temp.begin(), temp.end());
		return begin() + operator[](position - begin());
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::iterator
		vector<T, AllocT>::insert(const_iterator position, value_type& value) {

		std::array<std::reference_wrapper<value_type>, 1> temp({ value });
		DoInsertFromIterator(position, temp.begin(), temp.end());
		return begin() + operator[](position - begin());
	}

	template <class T, class AllocT>
	template <class Iterator>
	typename vector<T, AllocT>::iterator
		vector<T, AllocT>::insert(const_iterator position, Iterator first, Iterator last) {
		DoInsertFromIterator(position, first, last);
		return begin() + operator[](position - begin());
	}

	template <class T, class AllocT>
	template <class Iterator>
	void vector<T, AllocT>::DoInsertFromIterator(const_iterator position, Iterator first, Iterator last)
	{
		if ((position < pBegin) || (position > pEnd)) {
			throw std::out_of_range("vector::insert -- invalid position");
		}

		iterator destPosition = const_cast<value_type*>(position);

		if (first != last) {
			const size_type n = std::distance(first, last);  // n is the number of elements we are inserting.

			if (n <= size_type(pCapacity - pEnd)) { // If n fits within the existing capacity...
				std::memmove(destPosition + n, destPosition, size_type(pEnd - destPosition) * sizeof(value_type));
				std::copy(first, last, destPosition);
				pEnd += n;
			}
			else { // else we need to expand our capacity.
				const size_type nPrevSize = size_type(pEnd - pBegin);
				const size_type nLeftSize = size_type(position - pBegin);
				const size_type nRightSize = size_type(pEnd - position);
				const size_type nGrowSize = calcNewCapacity(nPrevSize);
				const size_type nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
				pointer const pNewData = allocate(nNewSize);

				pointer pNewEnd = pNewData;
				try {
					std::memmove(pNewData, pBegin, nLeftSize * sizeof(value_type));
					pNewEnd += nLeftSize;
					std::copy(first, last, pNewEnd);
					pNewEnd += n;
					std::memmove(pNewEnd, pBegin + nLeftSize, nRightSize * sizeof(value_type));
					pNewEnd += nRightSize;
				}
				catch (...) {
					std::destroy(pNewData, pNewEnd);
					free(pNewData, nNewSize);
					throw;
				}

				std::destroy(pBegin, pEnd);
				free(pBegin, (size_type)(pCapacity - pBegin));

				pBegin = pNewData;
				pEnd = pNewEnd;
				pCapacity = pNewData + nNewSize;
			}
		}
	}

	template <class T, class AllocT>
	template <class Iterator>
	void vector<T, AllocT>::DoAssignFromIterator(Iterator first, Iterator last) {
		iterator position(pBegin);

		while ((position != pEnd) && (first != last)) {
			*position = *first;
			++first;
			++position;
		}
		if (first == last) {
			erase(position, pEnd);
		}
		else
			insert(pEnd, first, last);
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::this_type&
		vector<T, AllocT>::operator=(const this_type& x) {
		if (this != &x) {
			DoAssignFromIterator(x.begin(), x.end());
		}
		return *this;
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::this_type&
		vector<T, AllocT>::operator=(this_type&& x)  //Memory leak?
	{
		if (this != &x) {
			DoClearCapacity();
			swap(x);
		}
		return *this;
	}

	template <class T, class AllocT>
	void vector<T, AllocT>::swap(this_type& x) {
		if (Allocator == x.Allocator) { 
			DoSwap(x);
		}
		else {
			const this_type temp(*this);
			*this = x;
			x = temp;
		}
	}

	template <class T, class AllocT>
	void vector<T, AllocT>::push_back(const value_type& value)
	{
		if (pEnd < pCapacity) {
			::new((void*)pEnd++) value_type(value);
		}
		else {
			std::array<std::reference_wrapper<value_type>, 1> temp({const_cast<value_type&>(value)});
			DoInsertFromIterator(pEnd, temp.begin(), temp.end());
		}
	}

	template <class T, class AllocT>
	void vector<T, AllocT>::DoClearCapacity()
	{ 
		auto sz = size();
		clear();
		free(pBegin, sz);
	}

	template <class T, class AllocT>
	void vector<T, AllocT>::DoFill_n(pointer p, size_type n, const value_type& value) {
		for (int i = 0; i < n; ++i) {
			new(p + i) T(value);
		}
	}

	template <class T, class AllocT>
	typename vector<T, AllocT>::pointer 
		vector<T, AllocT>::DoCopy_n(const_pointer sbegin, const_pointer send, pointer dbegin)
	{
		size_type sz = static_cast<size_type>(send - sbegin);
		for (int i = 0; i < sz; ++i) 
		{
			new(dbegin + i) T(*(sbegin + i));
		}

		return dbegin + sz;
	}

	template <class T, class AllocT>
	void vector<T, AllocT>::DoSwap(this_type& x) {
		std::swap(pBegin, x.pBegin);
		std::swap(pEnd, x.pEnd);
		std::swap(pCapacity, x.pCapacity);
		std::swap(Allocator, x.Allocator);
	}

	template <class T, class AllocT>
	template <class Iterator>
	inline void vector<T, AllocT>::DoInitFromIterator(Iterator first, Iterator last)
	{
		const size_type n = (size_type)std::distance(first, last);
		pBegin = allocate(n);
		pCapacity = pBegin + n;
		pEnd = pCapacity;

		DoCopy_n(first, last, pBegin);
	}
}

