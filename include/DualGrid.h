/*
    we will have two grids for the input: one for Whitespaces, another one for the ColoredSpaces
    Whitespace: Doors, Walls, whole form
    ColoredSpace: specific things in the room
*/


/*
we need to define:
    Objectives (a struct) ----
    InputData (a type of CSA) ---
    Export (type of CSA)
    Features (shared struct between here & python)
    DeterministicEnvironment (main class of the code)
*/

/*
    
*/

#include <cstdint>

#include "CSharedArrays.h"

// kamel nist
struct Objectives{
    // first part:
    double NoRoomInTheBOA;  // 'B'lockec, 'O'utside, 'A'ccess
    double NoOverlapInWS;       // The most important part
    // second:
    double NoOverlapbetweenCS;  // The most important part
    double CirculationAccessAll;


};

// just guidelines
struct InputData{
    CSA_Char8 InputGrid;
    CSA_Double64 WhiteSpace, ColoredSpace;
};

struct OutputForEvaluation{
    CSA_Double64 WSError, CSError;
    CSA_Double64 Scores;
};

struct OutputForExport{
    CSA_Double64 Export;
};

struct Features{
    uint32_t Width, Height;
    double SizeOfGridByCM;  // cm: default 10
    double TrueNorth;       // radian, True north ()
};


class DualGridImplementer{
private:
    Features m_features;
public:
    DualGridImplementer(Features);

    int32_t SetFeature(Features);

    int32_t ImplementAndEvaluate(
        CSA_Char8& InputGrid,
        CSA_Double64& WhiteSpace,
        CSA_Double64& ColoredSpace,
        CSA_Double64& WSError, 
        CSA_Double64& CSError,
        CSA_Double64& Scores);

    int32_t ImplementAndExport(
        CSA_Char8& InputGrid,
        CSA_Double64& WhiteSpace,
        CSA_Double64& ColoredSpace,
        CSA_Double64& WSError, 
        CSA_Double64& CSError,
        CSA_Double64& Scores,
        CSA_Char8& ExportGrid);
private:
	struct ExportPrototype{
		bool ReadyForImplementaion = false;
	};
	ExportPrototype ImplementationCore(
		CSA_Char8& InputGrid,
        CSA_Double64& WhiteSpace,
        CSA_Double64& ColoredSpace,
        CSA_Double64& WSError, 
        CSA_Double64& CSError,
        CSA_Double64& Scores);
	// I think maybe better than keeping in the private methods of class, because ... no meaning
};


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
