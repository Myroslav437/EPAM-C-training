#include "src/unique_file.h"

/*
template <class T>
static void Type_Test(T a);
*/


int main() {

	{
		// all two files are closed
		mysp::unique_file my(fopen("hello1.txt", "w"));
		my.reset(fopen("hello2", "w"));
	}
}