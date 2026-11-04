//File: CampusGraph.h
//Author: Leah Rodriguez
//Purpose: Declare CampusGraph class for storing running BFS, buildings, and walkways.

#ifndef CAMPUS_GRAPH_H
#define CAMPUS_GRAPH_H

#include <string>
#include <vector>

using namespace std;

struct BuildingNode{
  string name;
  vector<int> neighbors;
};

class CampusGraph{

private:
  vector<BuildingNode> buildings;
  int totalConnections;

  string trim(string str) const;
  string toLower(string str) const;
  bool splitFields(string line, vector<string>& fields) const;
  bool hasEdge(int u, int v) const;

public:
  CampusGraph();

  void loadBuildings(string filepath);
  void loadConnections(string filepath);

  int findBuildingIndex(string name) const;
  string getCanonicalBuildingName(string name) const;

  void displayGraph() const;
  void displayCountsAndDegrees() const;
  void bfsReachability(string startBuildingName) const;

  int getBuildingCount() const;
  int getConnectionCount() const;
};

#endif
