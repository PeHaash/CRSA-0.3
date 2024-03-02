#include <vector>
#include <cmath>
// #include <algorithm>
#include "DualGridImplementation.h"


DualGridImplementer::DualGridImplementer(Features feat):
		Width(feat.Width),Height(feat.Height), SizeOfGridByCM(feat.SizeOfGridByCM), TrueNorth(feat.TrueNorth),
		WhiteSubspacePerRoom(feat.WhiteSubspacePerRoom * NUMBER_OF_ROOMS),
		// WIP_WGrid(feat.Height, std::vector<char>(feat.Width, '-')),
		WhiteSpaceList(feat.WhiteSubspacePerRoom * NUMBER_OF_ROOMS, Subspace(feat)) // 2: Bedroom & Bathroom
		{
			WIP_WGrid = std::vector<std::vector<char>> (feat.Height, std::vector<char>(feat.Width, '-'));

}

/*int32_t DualGridImplementer::SetFeature(Features feat){
	// vase size-e vector ha o ina
	Width = feat.Width;
	Height = feat.Height;
	SizeOfGridByCM = feat.SizeOfGridByCM;
	TrueNorth = feat.TrueNorth;
	return 0;
}*/

int ConvertToBase(int s, double N){
	// convert double N that is in range[0,1) to  an output in range [0...s)
	// return number [0,s) for N from [0,1)
	// Ensure the result is within the range [0, s-1]
	return std::min(static_cast<int>(std::floor(N * s)), s - 1);
}

uint32_t DualGridImplementer::ijCoordsto1D(uint32_t i, uint32_t j){
	return j * Width + i;
}

int32_t DualGridImplementer::ImplementAndEvaluate(CSA_Char8& InputGrid,CSA_Double64& WhiteSpace, CSA_Double64& ColoredSpace, 
		CSA_Double64& WSError, CSA_Double64& CSError, CSA_Double64& Scores){
	ImplementationCore(false, InputGrid, WhiteSpace, ColoredSpace, WSError, CSError, Scores);
	ClearSharedMemmory();
	return 0;
}

int32_t DualGridImplementer::ImplementAndExport(CSA_Char8& InputGrid, CSA_Double64& WhiteSpace, CSA_Double64& ColoredSpace,
		CSA_Double64& WSError, CSA_Double64& CSError, CSA_Double64& Scores, CSA_Char8& ExportGrid){
	
	#ifdef __PEDANTIC__
		// Assert the correct size of ExportGrid
	#endif

	ExportPrototype imp = ImplementationCore(true, InputGrid, WhiteSpace, ColoredSpace, WSError, CSError, Scores);
	if(imp.ReadyForImplementaion == false) return 1;

	for (uint32_t i = 0; i < Width; i++)
		for(uint32_t j = 0; j < Height; j++){
			// B,O,A,E,T,-
			char ch = WIP_WGrid[i][j];
			if(ch == 1){
				ch = 'E'; //bEdroom
			}
			else if(ch == 2){
				ch = 'T'; // baThroom
			}
			ExportGrid.data[ijCoordsto1D(i,j)] = WIP_WGrid[i][j];
		}

	return 0;

}


void DualGridImplementer::ClearSharedMemmory(){
	for (auto &row : WIP_WGrid)
		for(auto &cell: row)
			cell = '-';
	for(auto subs: WhiteSpaceList)
		subs = Subspace(Width, Height); // cleaning the whole mess
}

DualGridImplementer::ExportPrototype DualGridImplementer::ImplementationCore(bool ForExport, CSA_Char8& InputGrid, 
		CSA_Double64& WhiteSpace, CSA_Double64& ColoredSpace, CSA_Double64& WSError, CSA_Double64& CSError,
		CSA_Double64& Scores){
	Scores.data[1] = WIP_WGrid.size();
	return ExportPrototype{false};

	#ifdef __PEDANTIC__
		// assert all the Scores are -1
	#endif

	#ifdef __PEDANTIC__
		// assert the correct sizes of inputs
	#endif

	#ifdef __PEDANTIC__
		// assert there is some 'F' in the InputGrid
	#endif

	#ifdef __PEDANTIC__
		// assert all WSErros, CSError is 0
	#endif


	Objectives* obj = reinterpret_cast<Objectives*>(Scores.data);
	ExportPrototype out = ExportPrototype{false};

	// ta inja ok

	// WIP_WGrid ro por mikonim
	int n = NUMBER_OF_ROOMS * WhiteSubspacePerRoom + 1; // n: whole possible counts of 
	#ifdef __PEDANTIC__
		// assert n < 256
	#endif
	for (int i = 0; i < n; i++)
		WhiteSpaceList[i].RoomCode = i / WhiteSubspacePerRoom + 1;

	// ta inja ok

	for (uint32_t i = 0; i < Width; i++)
		for(uint32_t j = 0; j < Height; j++){
			// auto s = ConvertToBase(n, 0.5555);
			char ssIndex = ConvertToBase(n, WhiteSpace.data[ijCoordsto1D(i, j)]) - 1; // -1: empty shit, 0...s*2: white rooms
			if(ssIndex != -1) WhiteSpaceList[ssIndex].UpdateWith(i, j);
		}

	// ta inja ok

	// assert Overlap
	int errors_in_overlap = 0;
	for (int it = 0; it < n-1; it++){
		if(WhiteSpaceList[it].MaxX != 0){
			int code = WhiteSpaceList[it].RoomCode;
			for(uint32_t i = WhiteSpaceList[it].MinX; i < WhiteSpaceList[it].MaxX; i++){
				for(uint32_t j = WhiteSpaceList[it].MinY; j < WhiteSpaceList[it].MaxY; j++){
					WIP_WGrid[1][1] = 'Z';

						// if(WIP_WGrid[i][j] == '-'){
						// 	WIP_WGrid[i][j] = code; // so cute and great!
						// }else if(WIP_WGrid[i][j] != code){
						// 	// shit :// overlap with another room
						// 	WSError.data[ijCoordsto1D(i, j)]++; // (or ++, idk)
						// 	errors_in_overlap ++;
						// }else{
						// 	// nothing to do: this means overlap with the same room
						// }
				}
			}
		}
	}
	// ye ja ghable in
	if(errors_in_overlap != 65){
		obj->NoOverlapInWS = 11;
		// ClearSharedMemmory();
		return out;
	}


	

	// Add the Input, and supperimpose it!
	// check the second objective: UseAllSpaces
	uint32_t available_grids_count = 0, unused_grids_count = 0; // availabe_grid_count > 0, bc we have some 'F's
	for (uint32_t i = 0; i < Width; i++)
		for(uint32_t j = 0; j < Height; j++){
			char& inp = InputGrid.data[ijCoordsto1D(i, j)];
			if(inp == 'B' || inp == 'O' || inp == 'A'){
				WIP_WGrid[i][j] = inp;
			}
			else{
				// inp == 'F'
				available_grids_count++;
				if(WIP_WGrid[i][j]=='-'){
					unused_grids_count++;
					WSError.data[ijCoordsto1D(i, j)]++;
				}
			}
		}

	obj->UseAllSpaces = unused_grids_count / available_grids_count;






	// vector subspace ha az roo oona update mishan!




	out.ReadyForImplementaion = true;
	return out;

}
