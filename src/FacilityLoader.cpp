#include "FacilityLoader.h"
#include "CampusGraph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Author: Shirisha Thapa
// Reads and validates facility records from a file.

// Removes spaces, tabs, and extra whitespace
static string trimFacilityText(const string& text) {
    size_t start = text.find_first_not_of(" \t\r\n");

    if (start == string::npos) {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

// Converts a facility ID to uppercase
static string uppercaseFacilityId(string id) {
    id = trimFacilityText(id);

    for (char& letter : id) {
        if (letter >= 'a' && letter <= 'z') {
            letter = letter - 'a' + 'A';
        }
    }

    return id;
}

// Checks that the ID is F followed by three digits
static bool checkFacilityId(const string& id) {
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

// Loads facilities from the text file
LoadStats loadFacilities(
    const string& path,
    CampusGraph& graph,
    FacilityHashTable& table
) {
    LoadStats stats;
    ifstream file(path);

    if (!file.is_open()) {
        cout << "Error: Cannot open " << path << endl;
    }
    else {
        string line;
        int lineNumber = 0;

        while (getline(file, line)) {
            lineNumber++;

            string cleanedLine = trimFacilityText(line);

            // Skip blank lines and comments
            if (cleanedLine.empty() || cleanedLine[0] == '#') {
                continue;
            }

            // Separate the four fields
            vector<string> fields;
            size_t start = 0;

            for (size_t i = 0; i <= line.length(); i++) {
                if (i == line.length() || line[i] == '|') {
                    fields.push_back(trimFacilityText(
                        line.substr(start, i - start)
                    ));
                    start = i + 1;
                }
            }

            // Check number of fields
            if (fields.size() != 4) {
                cout << "Warning: " << path
                     << ", line " << lineNumber
                     << ": Expected four fields." << endl;
                stats.rejected++;
                continue;
            }

            // Check for empty fields
            bool emptyField = false;

            for (const string& field : fields) {
                if (field.empty()) {
                    emptyField = true;
                }
            }

            if (emptyField) {
                cout << "Warning: " << path
                     << ", line " << lineNumber
                     << ": Empty required field." << endl;
                stats.rejected++;
                continue;
            }

            // Store the facility information
            Facility facility;
            facility.facilityId = uppercaseFacilityId(fields[0]);
            facility.facilityName = fields[1];
            facility.buildingName = fields[2];
            facility.category = fields[3];

            // Validate facility ID
            if (!checkFacilityId(facility.facilityId)) {
                cout << "Warning: " << path
                     << ", line " << lineNumber
                     << ": ID must be F followed by three digits."
                     << endl;
                stats.rejected++;
                continue;
            }

            // Check if the building exists
            if (!graph.hasBuilding(facility.buildingName)) {
                cout << "Warning: " << path
                     << ", line " << lineNumber
                     << ": Unknown building: "
                     << facility.buildingName << endl;
                stats.rejected++;
                continue;
            }

            // Use the original building spelling
            facility.buildingName =
                graph.getCanonicalBuildingName(facility.buildingName);

            // Check for duplicate ID
            if (table.findById(facility.facilityId) != nullptr) {
                cout << "Warning: " << path
                     << ", line " << lineNumber
                     << ": Duplicate facility ID: "
                     << facility.facilityId << endl;
                stats.rejected++;
                continue;
            }

            // Add the valid facility to the table
            if (table.insertFacility(facility)) {
                stats.accepted++;
            }
            else {
                cout << "Warning: " << path
                     << ", line " << lineNumber
                     << ": Could not insert facility."
                     << endl;
                stats.rejected++;
            }
        }
    }

    // Display file loading results
    cout << path << ": "
         << stats.accepted << " accepted, "
         << stats.rejected << " rejected"
         << " (hash capacity " << table.getCapacity()
         << ", entries " << table.getEntryCount()
         << ", collisions " << table.getCollisionCount()
         << ")" << endl;

    return stats;
}
