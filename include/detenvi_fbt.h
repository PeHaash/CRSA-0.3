 /*
 start from a set of N subspace, with N-1 merger
 subspace has Xpower, Ypower, ...
 merger is H or V



 */



/*
  rules of spaces (decleared in the gird):
    B: blocked - not accessible to us, outside walls, other rooms, etc...
    O: Outside - not accessible to us, but we can put windows to them
    A: Access - not accessible to build, but we can put Doors to them
    F: Free - Free for us to work on
*/

// -1: unscored
// 0: worst possible
// 1: great!
struct Objectives{
  double NoRoomInTheBOA; // blocked, 
  double HasEntrance;
  double HasOnlyOneEntrance;
  double AllSpacesAreConnected;
};
// make a pointer of objective, points at the array came from python



// #include <cstdint>
