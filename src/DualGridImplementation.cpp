#include <vector>
#include <cmath>
#include <fstream>
// #include <algorithm>
#include "DualGridImplementation.h"
	// std::ofstream kk("log.log");
DualGridImplementer::DualGridImplementer(Features feat):
		Width(feat.Width),Height(feat.Height), SizeOfGridByCM(feat.SizeOfGridByCM), TrueNorth(feat.TrueNorth),
		WhiteSubspacePerRoom(feat.WhiteSubspacePerRoom),
		WIP_WGrid(feat.Height, std::vector<char>(feat.Width, '-')),
		WhiteSpaceList(feat.WhiteSubspacePerRoom * NUMBER_OF_ROOMS, Subspace(feat)) // 2: Bedroom & Bathroom
		{

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

double MappedScore(double min_num, double goal_num, double max_num, double status){
	// the idea is status is in a [min,max] range, and
	// MappedScore(min) = 0
	// MappedScore(max) = 0
	// MappedScore(goal) = 1
	// (because it is peaked in that point)
	// for now, the chart you can see the graph is here: https://www.desmos.com/calculator/xb4xtnndqf
	return std::min(
		(status - goal_num) / (goal_num - min_num),
		(goal_num - status) / (max_num - goal_num)) + 1;
}


uint32_t DualGridImplementer::ijCoordsto1D(uint32_t i, uint32_t j, uint32_t channel = 0, uint32_t channel_count = 1){
	// return j * Width + i;
	// if channel == 1: become the Good-old j*W+i
	return i * channel_count + j * Width * channel_count + channel;
}

// uint32_t DualGridImplementer::GridCoordsto1D();

int32_t DualGridImplementer::ImplementAndEvaluate(CSA_Char8& InputGrid,CSA_Double64& InputData, CSA_Double64& Scores){
	ImplementationCore(false, InputGrid, InputData, Scores);
	return 0;
}

int32_t DualGridImplementer::ImplementAndExport(CSA_Char8& InputGrid, CSA_Double64& InputData, CSA_Double64& Scores,
		CSA_Char8& ExportGrid){
	
	#ifdef __PEDANTIC__
		// Assert the correct size of ExportGrid
	#endif

	ExportPrototype imp = ImplementationCore(true, InputGrid, InputData, Scores);
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
	for(auto &subs: WhiteSpaceList){
		subs.Reset(Width, Height); // cleaning the whole mess
		// kk << "subs";
	}
	// for(auto subs: WhiteSpaceList){
	// 	kk << subs.MaxX <<' ';
	// }
	// kk <<std::endl;
}

DualGridImplementer::ExportPrototype DualGridImplementer::ImplementationCore(bool ForExport, CSA_Char8& InputGrid, 
		CSA_Double64& InputData, CSA_Double64& Scores){


	#ifdef __PEDANTIC__
		// assert the correct sizes of inputs
	#endif

	#ifdef __PEDANTIC__
		// assert there is some 'F' in the InputGrid
	#endif

	#ifdef __PEDANTIC__
		// assert all WSErros, CSError is 0
	#endif

	ClearSharedMemmory(); // because this is the main chockpoint for Using here
	Objectives* obj = reinterpret_cast<Objectives*>(Scores.data);
	ExportPrototype out = ExportPrototype{false};

	for(uint32_t i = 0; i < Scores.size; i++){
		Scores.data[i] = 0; // scores are 0!
	}

	// WIP_WGrid ro por mikonim
	int n = NUMBER_OF_ROOMS * WhiteSubspacePerRoom + 1; // n: whole possible types of space: (n*m)... and empty!

	#ifdef __PEDANTIC__
		// assert n < 65 (65 is 'A')
	#endif
	
	for (int i = 0; i < n - 1 ; i++){
		WhiteSpaceList[i].RoomCode = i / WhiteSubspacePerRoom + 1;
	}
	
	double free_spaces = 0;
	for (uint32_t i = 0; i < Width; i++)
		for(uint32_t j = 0; j < Height; j++){
			char ssIndex = ConvertToBase(n, InputData.data[ijCoordsto1D(i, j, 0, 2)]) - 1;
					// -1: empty shit, 0...s*2: white rooms
			if(ssIndex != -1)
				WhiteSpaceList[ssIndex].UpdateWith(i, j);
			else
				free_spaces ++;
		}
	free_spaces = free_spaces / (Height * Width); // 80% should be free!
	obj->UseCorrectAmountOfSpaceInWhitespace = MappedScore(0, 0.8, 1, free_spaces);


	// check Overlap
	uint32_t errors_in_overlap = 0, inactive_white_space = 0;
	for (int it = 0; it < n - 1; it++){
		if(WhiteSpaceList[it].MaxX != 0){
			int code = WhiteSpaceList[it].RoomCode;
			for(uint32_t i = WhiteSpaceList[it].MinX; i < WhiteSpaceList[it].MaxX; i++){
				for(uint32_t j = WhiteSpaceList[it].MinY; j < WhiteSpaceList[it].MaxY; j++){
					if(WIP_WGrid[i][j] == '-'){
						WIP_WGrid[i][j] = code; // so cute and great!
					}else if(WIP_WGrid[i][j] != code){
						// shit :// overlap with another room
						// Errors.data[ijCoordsto1D(i, j, 0, 2)]++; // ++: to show how bad is this
						errors_in_overlap ++;
					}else{
						// nothing to do: this means overlap with the same room
					}
				}
			}
		}
		else{
			inactive_white_space ++;
		}
	}
	obj->AllWhitespcaseShouldBeActive = (double)(n - 1 - inactive_white_space) / (double)(n - 1);
	obj->NoOverlapsInWhiteSpaces = (double)(errors_in_overlap) / (double)(Height * Width * (NUMBER_OF_ROOMS-1));

	if(errors_in_overlap != 0){
		// return out;
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
					// Errors.data[ijCoordsto1D(i, j, 0, 1)]++;
				}
			}
		}

	// obj->UseAllSpaces = unused_grids_count / available_grids_count;

	// for (uint32_t i = 0; i < Width; i++)
	// 	for(uint32_t j = 0; j < Height; j++){





	// vector subspace ha az roo oona update mishan!




	out.ReadyForImplementaion = true;
	return out;

}
