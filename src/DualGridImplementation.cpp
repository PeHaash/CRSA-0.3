#include <vector>
#include <cmath>
// #include <algorithm>
#include "DualGrid.h"


DualGridImplementer::DualGridImplementer(Features feat):
		Width(feat.Width),Height(feat.Height), SizeOfGridByCM(feat.SizeOfGridByCM), TrueNorth(feat.TrueNorth),
		WhiteSubspacePerRoom(feat.WhiteSubspacePerRoom * 2),
		WIP_WGrid(feat.Height, std::vector<char>(feat.Width, '-')),
		WS_(feat.WhiteSubspacePerRoom * 2, Subspace(feat)) // 2: Bedroom & Bathroom
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
	// convert double N that is in range[0,1) to  an output in range [0...s]
	// return number [0,s) for N from [0,1)
	// Ensure the result is within the range [0, s-1]
	return std::min(static_cast<int>(std::floor(N * s)), s - 1);
}

DualGridImplementer::ExportPrototype DualGridImplementer::ImplementationCore(CSA_Char8& InputGrid, CSA_Double64& WhiteSpace, 
		CSA_Double64& ColoredSpace, CSA_Double64& WSError, CSA_Double64& CSError, CSA_Double64& Scores){

	#ifdef __PEDANTIC__
		// assert the correct sizes of inputs!
	#endif 


	// WIP_WGrid ro por mikonim
	int n = 2 * WhiteSubspacePerRoom + 1; // n: whole possible counts of 
	#ifdef __PEDANTIC__
		// assert n < 256
	#endif
	for (int i = 0; i < n; i++)
		WS_[i].RoomCode = i/WhiteSubspacePerRoom;

	for (uint32_t i = 0; i < Width; i++)
		for(uint32_t j = 0; j < Height; j++){
			WIP_WGrid[i][j] = ConvertToBase(n, WhiteSpace.data[i * Width + j]) - 1; // -1: empty shit, 0...s*2: rooms
			char ssIndex = WIP_WGrid[i][j];
			if(ssIndex != -1){
				// POTENTIAL FOR A NEW FUNCTION, MAKE IT CLEANER WS_[ssIndex].UpdateWith(i, j);
				WS_[ssIndex].MinX = std::min(WS_[ssIndex].MinX, i);
				WS_[ssIndex].MinY = std::min(WS_[ssIndex].MinY, j);
				WS_[ssIndex].MaxX = std::max(WS_[ssIndex].MaxX, i + 1);
				WS_[ssIndex].MaxY = std::max(WS_[ssIndex].MaxY, j + 1);
			}
		}

	for (uint32_t i = 0; i < Width; i++)
		for(uint32_t j = 0; j < Height; j++)
			WIP_WGrid[i][j] = -1;

	for (int it = 0; it < n; it++){
		if(WS_[it].MaxX != 0){
			int code = WS_[it].RoomCode;
			for(uint32_t i = WS_[it].MinX; i < WS_[it].MaxX; i++){
				for(uint32_t j = WS_[it].MinY; j < WS_[it].MaxY; j++){
					if(WIP_WGrid[i][j] == -1){
						WIP_WGrid[i][j] = code; // so cute and great!
					}else if(WIP_WGrid[i][j] != code){
						// shit :// overlap with another room
						WSError.data[i * Width + j] = 1; // (or ++, idk)
					}else{
						// nothing to do: this means overlap with the same room
					}

				}
			}


		}
	}





	// vector subspace ha az roo oona update mishan!





	return ExportPrototype();

}
