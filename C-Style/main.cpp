#include <cstdio>
#include <memory>
#include <cerrno>

char* readFile(const char* path) {
	FILE* inFile;

	// open the file:
	inFile = fopen(path, "r");
	if (inFile == NULL) {
		printf("Error while opening the file: %s\n", strerror(errno));	fflush(stdout);
		return NULL;
	}
	// get file size:

	if (fseek(inFile, 0, SEEK_END)) {
		printf("Error while reading the file size: %s\n", strerror(errno));	fflush(stdout);
		fclose(inFile);

		return NULL;
	}

	long int sz = ftell(inFile) * sizeof(char);
	if (sz == 1L) {
		printf("Error while determining the file size: %s\n", strerror(errno));	fflush(stdout);
		fclose(inFile);

		return NULL;
	}

	if (fseek(inFile, 0, SEEK_SET)) {
		printf("Error while reading the file size: %s\n", strerror(errno));	fflush(stdout);
		fclose(inFile);

		return NULL;
	}

	// allocate the memory:
	char* dest = (char*)calloc(sz + 1, sizeof(char));
	if (dest == NULL) {
		printf("Error while allocating the memory: %s\n", strerror(errno));	fflush(stdout);
		fclose(inFile);

		return NULL;
	}
	// read the file:
	size_t r = fread(dest, sizeof(char), sz, inFile);
	if (r < sz) {
		printf("Error while reading the file: %s\n", strerror(errno));	fflush(stdout);
		fclose(inFile);
		free(dest);

		return NULL;
	}
	// close the file:
	if (fclose(inFile) == EOF) {
		printf("Error while closing the file: %s\n", strerror(errno));	fflush(stdout);
		free(dest);

		return NULL;
	}

	return dest;
}


int main() {
	char* a = readFile("MyFile.txt");
	if (a != NULL) {
		printf("%s\n", a);
		free(a);
	}

	char* b = readFile("Dummy.txt");
	if (b != NULL) {
		printf("%s\n", b);
		free(b);
	}

}