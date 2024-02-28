// ok for now
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <vector>
#include <numeric>			// for std::accumulate
#include <algorithm>		// for std::max_element


class DisjointSet{
	private:
		std::vector<int> Par;
		int NumberOfSets;
		int NumberOfElements;
	public:
		DisjointSet() = default;  // vase in ke betoonam alaki tarifesh konam ke ba'dan kamel she
		DisjointSet(int n);
		int FindParent(int p);
		void Join(int a, int b);
		int GetNumOfSets();
		int GetDisjointnessOfElements(std::vector<int> indexes);
		int GetDisjointness();
};

#endif