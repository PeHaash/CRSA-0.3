#include "include/french_hamlets.h"

extern "C"{
	void* c_MakeFrenchHamlets(Features);
	void c_SetFeature(void*, Features);
	void c_ImplementAndEvaluate(void*,InputData, Scores);
	void c_ImplementAndExport(void*, InputData, Scores, ExportFormat);
	void c_DeleteFrenchHamlets(void*);

}

