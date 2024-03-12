#include "Wrapper.h"
// Havaset bashe: Wrapper ha ba reference nemigiran!!!!


void* c_MakeDGI(Features fet){
	DualGridImplementer* m = new DualGridImplementer(fet);
	return static_cast<void*> (m);
}

// void c_SetFeature(void* p, Features fet){
// 	(static_cast<FrenchHamlets*>(p))->SetFeature(fet);
// }


int32_t c_ImplementAndEvaluate(void* DGI, CSA_Char8 InputGrid, CSA_Double64 InputData, CSA_Double64 Scores){

	return (static_cast<DualGridImplementer*>(DGI))->ImplementAndEvaluate(InputGrid, InputData, Scores);
}

int32_t c_ImplementAndExport(void* DGI, CSA_Char8 InputGrid, CSA_Double64 InputData, CSA_Double64 Scores, CSA_Char8 ExportGrid){
	return (static_cast<DualGridImplementer*>(DGI))->ImplementAndExport(InputGrid, InputData, Scores, ExportGrid);
}

int32_t c_DeleteDGI(void* p){
	if (p == nullptr)
		return 1;
	delete static_cast<DualGridImplementer*>(p);
	return 0;
}
