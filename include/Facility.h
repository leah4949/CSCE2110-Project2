// Author: Shirisha Thapa
// Stores information about a campus facility.

#ifndef FACILITY_H
#define FACILITY_H

#include <string>
using namespace std;

// Stores information about one campus facility
struct Facility {
    string facilityId;
    string facilityName;
    string buildingName;
    string category;
};

#endif
