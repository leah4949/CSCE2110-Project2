#ifndef FACILITY_LOADER_H
#define FACILITY_LOADER_H

#include <string>
#include "FacilityHashTable.h"
#include "LoadStats.h"

using namespace std;

class CampusGraph;

// Author: Shirisha Thapa
// Loads facility information from a text file.

LoadStats loadFacilities(
    const string& path,
    CampusGraph& graph,
    FacilityHashTable& table
);

#endif
