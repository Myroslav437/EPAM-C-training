#include "src/UniquePtr.hpp"
#include "src/SharedPtr.hpp"
#include <iostream>
#include <array>

using namespace std;

// Simple memory tracker:
constexpr int tracker_size = 100000;
array<void*, 100000> alloc_pointers;
array<size_t, 100000> alloc_sizes;
int alloc_indx = 0;
int alloc_sum = 0;

void* operator new(size_t size) {
	void* p = malloc(size);
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
class CustomDeleter {
public:
	void operator() (T* ptr) {
		std::clog << "Custom deleter invoked. ";
		delete ptr;
	}
};


int main() {
	{				/* UniquePtr */
		{	// Ctor - dtor test
			mysp::UniquePtr p1;
			mysp::UniquePtr p2(nullptr);
			mysp::UniquePtr p3(new mysp::CObject);
			mysp::UniquePtr p4(new mysp::CObject);
			mysp::UniquePtr p5(std::move(p4));

			CustomDeleter<mysp::CObject> a;
			mysp::UniquePtr<CustomDeleter<mysp::CObject>> p6(new mysp::CObject, a);
			mysp::UniquePtr<CustomDeleter<mysp::CObject>> p7(new mysp::CObject, CustomDeleter<mysp::CObject>());
		}

		{
			mysp::UniquePtr p2(nullptr);
			mysp::UniquePtr p3(new mysp::CObject);
			mysp::UniquePtr<CustomDeleter<mysp::CObject>> p4(new mysp::CObject, CustomDeleter<mysp::CObject>());
			p2.swap(p3);
			// p2.swap(p4); /* error */
			// p2 = std::move(p4); /* error */

			p3 = std::move(p2);
			p4 = nullptr;
		}
	}


	{				/* SharedPtr */
		{	// Ctor - dtor test
			mysp::SharedPtr p1;
			mysp::SharedPtr p2(nullptr);
			mysp::SharedPtr p3(new mysp::CObject);
			mysp::SharedPtr p4(new mysp::CObject); //

			p1 = p3;
			p3 = p4;
			p2.swap(p4);
			p4 = p1;

			mysp::SharedPtr p5(std::move(p4));
			mysp::SharedPtr p6(p5);

			p4 = std::move(p5);
			p3 = std::move(p4);

			CustomDeleter<mysp::CObject> a;
			mysp::SharedPtr<CustomDeleter<mysp::CObject>> p7(new mysp::CObject, a);
			mysp::SharedPtr<CustomDeleter<mysp::CObject>> p8(new mysp::CObject, CustomDeleter<mysp::CObject>());
		}

		{
			mysp::SharedPtr p2(nullptr);
			mysp::SharedPtr p3(new mysp::CObject);
			mysp::SharedPtr<CustomDeleter<mysp::CObject>> p4(new mysp::CObject, CustomDeleter<mysp::CObject>());
			mysp::SharedPtr<CustomDeleter<mysp::CObject>> p5(new mysp::CObject, CustomDeleter<mysp::CObject>());
			mysp::SharedPtr<CustomDeleter<mysp::CObject>> p6(nullptr, CustomDeleter<mysp::CObject>());
			p5 = p4;
			p4 = nullptr;
			p6 = p4;
			p6 = p5;
			p5 = nullptr;
			p6 = nullptr;

			p2.swap(p3);
			// p2.swap(p4); /* error */
			// p2 = std::move(p4); /* error */

		}

	}

}