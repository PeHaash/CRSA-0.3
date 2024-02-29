// shared arrays between numpy & c++, in a C format:

#include <cstdint>

struct CSA_Double64{
	uint64_t size;
	double* data;
};

struct CSA_Float32{
	uint64_t size;
	float* data;
};

struct CSA_Int32{
	uint64_t size;
	int* data;
};

struct CSA_Char8{
	uint64_t size;
	char* data;
};

// etc...