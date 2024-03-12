/*
	we will have two grids for the input: one for Whitespaces, another one for the ColoredSpaces
	Whitespace: Doors, Walls, whole form
	ColoredSpace: specific things in the room
*/




/*
	
*/

#include <cstdint>
#include <vector>

#include "CSharedArrays.h"

// consts:
const uint32_t NUMBER_OF_ROOMS = 3;


// kamel nist
struct Objectives{
		// intrinsit Objectives:						// 
	double UseCorrectAmountOfSpaceInWhitespace;			// [x] To make overlaps less common, ~80% should be free
	double NoOverlapsInWhiteSpaces;						// [x]
	double AllWhitespcaseShouldBeActive;				// [x] Every part, so 
	// double UseAllSpaces;								// [ ] Spaces should be all used, for when the inputs are obstructed
	double AllWhitespacesOfSameRoomAreConnected;		// [ ] rooms are connected in the same room 
	double WholePlanShouldBeConnected;					// [ ] 
	double NoOverlapsInColoredSpaces;					// [ ] ...
	double ColoreSpacesInTheCorrectRespectiveRoom;		// [ ] be in the correct room!

	// // first part:
	// double NoRoomInTheBOA;  // 'B'lockec, 'O'utside, 'A'ccess
	// double NoOverlapInWS;       // The most important part
	// // second:
	// double NoOverlapbetweenCS;  // The most important part
	// double CirculationAccessAll;
};



struct Features{
	uint32_t Width, Height;
	double SizeOfGridByCM;  // cm: default 10
	double TrueNorth;       // radian, True north ()

	uint32_t WhiteSubspacePerRoom; // subspace per WS
};


class DualGridImplementer{
private:
	// features
	uint32_t Width, Height;
	double SizeOfGridByCM;  // cm: default 10
	double TrueNorth;       // radian, True north ()
	uint32_t WhiteSubspacePerRoom;

public:
	DualGridImplementer(Features);

	// int32_t SetFeature(Features); // NO SET FEATURES IN THE CURRENT ARCHITECTURE
	/*
		Inputdata: a tensor, X,Y,channel
		[:,:,0]: whiteSpaces
		[:,:,1]: coloredSpaces

	
	*/
	int32_t ImplementAndEvaluate(
		CSA_Char8& InputGrid,
		CSA_Double64& InputData,
		CSA_Double64& Scores);

	int32_t ImplementAndExport(
		CSA_Char8& InputGrid,
		CSA_Double64& InputData,
		CSA_Double64& Scores,
		CSA_Char8& ExportGrid);
private:
	struct ExportPrototype{
		bool ReadyForImplementaion = false;
	};
	ExportPrototype ImplementationCore(
		bool ForExport,
		CSA_Char8& InputGrid,
		CSA_Double64& InputData,
		CSA_Double64& Scores);
	// I think maybe better than keeping in the private methods of class, because ... no meaning


	// other definitions:
	struct Subspace{
		uint32_t MinX, MinY, MaxX, MaxY;
		int RoomCode; // in WhiteSpaceList: 1. Bedroom, 2. Bathroom, etc.. 
		int SubspaceCode; // Internal Code to count them
		Subspace(const Features& feat){
			MaxX = 0; MaxY = 0; // 0: omran be kar bian!!! aslan nemish 0 beshe hichvaght
			MinX = feat.Width + 3;
			MinY = feat.Height + 3;
			RoomCode = -1;
			SubspaceCode = -1;
		}
		Subspace(uint32_t w, uint32_t h){
			MaxX = 0; MaxY = 0; // 0: omran be kar bian!!! aslan nemish 0 beshe hichvaght
			MinX = w + 3;
			MinY = h + 3;
			RoomCode = -1;
			SubspaceCode = -1;
		}
		void Reset(uint32_t w, uint32_t h){ 
				// just a way to reset, instead of constructor
			MaxX = 0; MaxY = 0; // 0: omran be kar bian!!! aslan nemish 0 beshe hichvaght
			MinX = w + 3;
			MinY = h + 3;
			RoomCode = -1;
			SubspaceCode = -1;
		}
		void UpdateWith(uint32_t i, uint32_t j){
			MinX = std::min(MinX, i);
			MinY = std::min(MinY, j);
			MaxX = std::max(MaxX, i + 1);
			MaxY = std::max(MaxY, j + 1);
		}
	};
	// Big data parts of the code:
	void ClearSharedMemmory();
	uint32_t ijCoordsto1D(uint32_t, uint32_t,uint32_t, uint32_t); // i,j,k, & channel count: 1: 2d, other numbers, 3d
	std::vector<std::vector<char>> WIP_WGrid;
	std::vector<Subspace> WhiteSpaceList;
		// in WhiteSpaceList: .RoomCode: 1: bedroom, 2: Bathroom
	std::vector<Subspace> CS_;
};

// The helpfile:
/*
		ExportPrototype OneWayOfImplementing::ImplementationCore(InputData& input, Scores& output,  bool ForExport){
			 // it has the core logic of implementation, and evaluation. but it may have not all the logic of export.
		}

		void OneWayOfImplementing::ImplementAndEvaluate(InputData& input, Scores& output){
			ImplementationCore(input, output,  false);
		}


		void OneWayOfImplementing::ImplementAndExport(InputData& input, ExportFormat& output){
			ExportPrototype ep = ImplementationCore(input, dummyscore,  true);
			if(ep.NotReadyForImplementaion){
				// return: we can not do it :/
			}
			// Make it from ExportPrototype
			// edit output to put in final type.
			// return output;
		}
*/


