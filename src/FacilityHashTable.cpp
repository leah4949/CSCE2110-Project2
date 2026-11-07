#include "FacilityHashTable.h"
#include <iostream>
using namespace std;

// Author: Shirisha Thapa
// Implements the custom hash table for campus facilities.

// Removes extra spaces and converts an ID to uppercase
static string cleanId(string id) {
    while (!id.empty() &&
           (id[0] == ' ' || id[0] == '\t' || id[0] == '\r')) {
        id.erase(0, 1);
    }

    while (!id.empty() &&
           (id.back() == ' ' || id.back() == '\t' || id.back() == '\r')) {
        id.pop_back();
    }

    for (char& letter : id) {
        if (letter >= 'a' && letter <= 'z') {
            letter = letter - 'a' + 'A';
        }
    }

    return id;
}

// Checks if an ID follows the F001 format
static bool validId(const string& id) {
    if (id.length() != 4 || id[0] != 'F') {
        return false;
    }

    for (int i = 1; i < 4; i++) {
        if (id[i] < '0' || id[i] > '9') {
            return false;
        }
    }

    return true;
}

// Creates a hash table with the given capacity
FacilityHashTable::FacilityHashTable(size_t capacity)
    : buckets(capacity == 0 ? 17 : capacity), collisionCount(0) {
}

// Calculates the index for a facility ID
size_t FacilityHashTable::hashFunction(const string& facilityId) const {
    size_t hashValue = 0;

    for (char letter : facilityId) {
        hashValue = (hashValue * 31 + letter) % buckets.size();
    }

    return hashValue;
}

// Inserts a facility into the hash table
bool FacilityHashTable::insertFacility(const Facility& facility) {
    Facility newFacility = facility;
    newFacility.facilityId = cleanId(facility.facilityId);

    if (!validId(newFacility.facilityId)) {
        return false;
    }

    size_t index = hashFunction(newFacility.facilityId);

    // Check for duplicate IDs
    for (const Facility& current : buckets[index]) {
        if (current.facilityId == newFacility.facilityId) {
            return false;
        }
    }

    // Count a collision if the bucket is not empty
    if (!buckets[index].empty()) {
        collisionCount++;
    }

    buckets[index].push_back(newFacility);
    facilities.push_back(newFacility);

    return true;
}

// Searches for a facility by ID
const Facility* FacilityHashTable::findById(const string& facilityId) const {
    string id = cleanId(facilityId);

    if (!validId(id)) {
        return nullptr;
    }

    size_t index = hashFunction(id);

    for (const Facility& facility : buckets[index]) {
        if (facility.facilityId == id) {
            return &facility;
        }
    }

    return nullptr;
}

// Displays all facilities in file order
void FacilityHashTable::displayFacilities() const {
    if (facilities.empty()) {
        cout << "No facilities available." << endl;
        cout << "Total facilities: 0" << endl;
        return;
    }

    for (const Facility& facility : facilities) {
        cout << facility.facilityId << " | "
             << facility.facilityName << " | "
             << facility.buildingName << " | "
             << facility.category << endl;
    }

    cout << "Total facilities: " << facilities.size() << endl;
}

// Returns the hash table capacity
size_t FacilityHashTable::getCapacity() const {
    return buckets.size();
}

// Returns the number of stored facilities
size_t FacilityHashTable::getEntryCount() const {
    return facilities.size();
}

// Returns the number of collisions
size_t FacilityHashTable::getCollisionCount() const {
    return collisionCount;
}
