#include "Wrapper.h"

void* c_MakeDGI(Features fet){
	DualGridImplementer* m = new DualGridImplementer(fet);
	return static_cast<void*> (m);
}

// void c_SetFeature(void* p, Features fet){
// 	(static_cast<FrenchHamlets*>(p))->SetFeature(fet);
// }


int32_t c_ImplementAndEvaluate(void* DGI, CSA_Char8& InputGrid, CSA_Double64& WhiteSpace, CSA_Double64& ColoredSpace,
		CSA_Double64& WSError, CSA_Double64& CSError, CSA_Double64& Scores){

	InputGrid.data[0] = 'S';
	return 5;

	return (static_cast<DualGridImplementer*>(DGI))->ImplementAndEvaluate(InputGrid, WhiteSpace, ColoredSpace, WSError,
			CSError, Scores);
}

int32_t c_ImplementAndExport(void* DGI, CSA_Char8& InputGrid, CSA_Double64& WhiteSpace, CSA_Double64& ColoredSpace,
		CSA_Double64& WSError, CSA_Double64& CSError, CSA_Double64& Scores, CSA_Char8& ExportGrid){
	return (static_cast<DualGridImplementer*>(DGI))->ImplementAndExport(InputGrid, WhiteSpace, ColoredSpace, WSError, CSError,
			Scores, ExportGrid);
}

int32_t c_DeleteDGI(void* p){
	if (p == nullptr)
		return 1;
	delete static_cast<DualGridImplementer*>(p);
	return 0;
}
