#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<char> readFile(const std::string& path) noexcept {
	std::vector<char> vec;
	std::ifstream stream;
	stream.exceptions(std::ifstream::failbit);

	try {
		// open the file:
		stream.open(path, std::ifstream::ate);
		// get the size:
		auto sz = stream.tellg();
		// allocate memory:
		vec.reserve(static_cast<size_t>(sz));
		// read data:
		stream.seekg(0, stream.beg);
		std::copy(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>(), std::back_inserter(vec));
		// close the file:
		stream.close();
	}
	catch (std::ifstream::failure& e) {
		std::cerr << "Error while opening or reading the file: " << e.what() << std::endl;
	}
	catch (std::length_error& e) {
		std::cerr << "Error while reserving vector size: " << e.what() << std::endl;
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Error while allocating the memory: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error occured: " << std::endl;
	}

	return vec;
}

int main() {
	readFile("MyFile.txt");
	readFile("Dummy.txt");


}