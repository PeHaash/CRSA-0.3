#include <vector>

#include "DualGrid.h"


DualGridImplementer::DualGridImplementer(Features feat):
		Width(feat.Width),Height(feat.Height), SizeOfGridByCM(feat.SizeOfGridByCM), TrueNorth(feat.TrueNorth),
		WIP_Grid(feat.Height, std::vector<char>(feat.Width, '-')){

	// width is Cols, Height is rows, we start from top/left
	// std::vector<std::vector<char>> Grid(Height, std::vector<char>(Width, '-'));

// int main() {
//     int rows = 5; // Number of rows
//     int cols = 4; // Number of columns
//     int defaultValue = 0;
//     std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, defaultValue));
    
//     return 0;
// }



}

int32_t DualGridImplementer::SetFeature(Features feat){
	Width = feat.Width;
	Height = feat.Height;
	SizeOfGridByCM = feat.SizeOfGridByCM;
	TrueNorth = feat.TrueNorth;
	return 0;
}


DualGridImplementer::ExportPrototype DualGridImplementer::ImplementationCore(CSA_Char8& InputGrid, CSA_Double64& WhiteSpace, 
		CSA_Double64& ColoredSpace, CSA_Double64& WSError, CSA_Double64& CSError, CSA_Double64& Scores){

	#ifdef __PEDANTIC__
		// assert the correct sizes of inputs!
	#endif 



	// To do:
	// 1. Implement Whitespace, with the wrong doings



	return ExportPrototype();

}
