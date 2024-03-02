#include "DualGridImplementation.h"

extern "C"{
	void* c_MakeDGI(Features fet);
	// void c_SetFeature(void*, Features);
	int32_t c_ImplementAndEvaluate(
		void* DGI,
		CSA_Char8 InputGrid,
		CSA_Double64 WhiteSpace,
		CSA_Double64 ColoredSpace,
		CSA_Double64 WSError, 
		CSA_Double64 CSError,
		CSA_Double64 Scores);
	int32_t c_ImplementAndExport(
		void* DGI,
		CSA_Char8 InputGrid,
		CSA_Double64 WhiteSpace,
		CSA_Double64 ColoredSpace,
		CSA_Double64 WSError, 
		CSA_Double64 CSError,
		CSA_Double64 Scores,
		CSA_Char8 ExportGrid);
	int32_t c_DeleteDGI(void*);

}

