#include "vector/vector.hpp"
#include <iostream>
#include <array>
#include <exception>

using namespace std;

constexpr int tracker_size = 100000;
array<void*, 100000> alloc_pointers;
array<size_t, 100000> alloc_sizes;
int alloc_indx = 0;
int alloc_sum = 0;

void* operator new(size_t size) {
	void * p = malloc(size);
	if (p == NULL) {
		throw std::bad_alloc();
	}

	//make a log
	if (alloc_indx < tracker_size) {
		alloc_pointers.at(alloc_indx) = p;
		alloc_sizes.at(alloc_indx) = size;
		alloc_sum += size;
		++alloc_indx;
	}

	cout << "Allocating " << size << " bytes" << "\t" << "sum: " << alloc_sum << endl;

	return p;
}

void operator delete(void* p) {
	int size;
	auto end = alloc_pointers.begin() + alloc_indx;
	auto it = std::find(alloc_pointers.begin(), end, p);
	if (it != end) {
		int idx = std::distance(alloc_pointers.begin(), it);
		size = alloc_sizes.at(idx);
		for (int i = idx; i < alloc_indx - 1; ++i) {
			alloc_sizes.at(i) = alloc_sizes.at(i + 1);
			alloc_pointers.at(i) = alloc_pointers.at(i + 1);
		}
		--alloc_indx;
		alloc_sizes.at(alloc_indx) = 0;
		alloc_pointers.at(alloc_indx) = 0;

		alloc_sum -= size;

		cout << "Deleting " << size << " bytes" << "\t" << "sum: " << alloc_sum << endl;
	}

	free(p);
}

template <class T>
void print(mystl::vector<T>& a) {
	std::cout << "\t" << "Size/Cap: " << a.size() << "/" << a.capacity() << ", ";
	for (int i = 0; i < a.size(); ++i) {
		std::cout << a.at(i) << ", ";
	}
	std::cout << std::endl;
}

int main() {
	cout << "Allocation / dealocation test : " << endl;
	{
		mystl::vector<int> vec1; print(vec1);
		mystl::vector<int> vec2(10, 1); print(vec2);
		mystl::vector<int> vec3(vec2); print(vec3);
		mystl::vector<int> vec4({1, 2, 3, 4, 5, 6}); print(vec4);

		mystl::vector<int> vec5(vec4); print(vec5);
		mystl::vector<int> vec6(std::move(vec5)); print(vec6); print(vec5);
	}

	cout << endl << endl;
	cout << "push_back, pop_back test : " << endl;
	{
		mystl::vector<int> vec4({ 1, 2, 3, 4, 5, 6 }); print(vec4);
		for (int i = 0; i < 10; ++i) {
			vec4.push_back(i);
			print(vec4);
		}

		for (int i = 0; i < 10; ++i) {
			vec4.pop_back();
			print(vec4);
		}
	}

	cout << endl << endl;
	cout << "insert/erase test : " << endl;
	{
		mystl::vector<int> vec4({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }); print(vec4);
		for (int i = 0; i < vec4.size(); ++i) { // delete all even:
			vec4.erase(vec4.begin() + i); 
			print(vec4);
		}

		for (int i = 0; i < vec4.size(); i+=2) { // delete all even:
			vec4.insert(vec4.begin() + i, i+1);
			print(vec4);
		}
		vec4.insert(vec4.end(), 15);
		print(vec4);

		for (int i = 0; i < vec4.size(); i += 2) { // delete all even:
			vec4.insert(vec4.begin() + i, -i);
			print(vec4);
		}

		vec4.erase(vec4.begin() + 1, vec4.begin() + 5);
		print(vec4);

		std::array<int, 5> a({ 0,0,0,0,0 }) ;
		vec4.insert(vec4.begin() + 2, a.begin(), a.end());
		print(vec4);
	}

	cout << "swap test : " << endl;
	{
		mystl::vector<int> vec4({ 1, 2, 3, 4, 5}); print(vec4);
		mystl::vector<int> vec5({6, 7, 8, 9, 10}); print(vec5);
		vec4.swap(vec5);

		print(vec4);
		print(vec5);
	}
}