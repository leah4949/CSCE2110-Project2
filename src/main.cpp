// CSCE 2110 - Project 2
// Smart Campus Navigation and Facility Analytics System
//File: main.cpp
//Author: Leah, Sirisha, Aanchal
//Purpose: Milestone 1 menu

#include <iostream>
#include <string>
#include <cstdlib>
#include "../include/CampusGraph.h"

using namespace std;

string trimInput(string str){
  int start = 0;
  int len = (int)str.length();

  while(start < len && (str[start] == ' ' || str[start] == '\t' || str[start] == '\r' || str[start] == '\n')){
    start++;
  }

  int end = len - 1;
  while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\r' || str[end] == '\n')){
    end--;
  }

  if(start > end){
    return "";
  }
  return str.substr(start, end - start + 1);
}

void printMenu(){
  cout << "\n--- Smart Campus Navigation System ---\n";
  cout << "1. View all faculities\n";
  cout << "2. Search facility by ID\n";
  cout << "3. View campus graph\n";
  cout << "4. Display graph counts and degrees\n";
  cout << "5. Find reachable buildings(BFS)\n";
  cout << "6. Add department\n";
  cout << "7. Search department\n";
  cout << "8. Display department hierarchy\n";
  cout << "9. Run preorder traversal\n";
  cout << "10. Exit\n";
  cout << "Enter choice: ";
}

int main(int argc, char* argv[]){
  cout << "Smart Campus Navigation System" << endl;

  string dataDirectory = "data";
  if(argc >= 2){
    dataDirectory = argv[1];
  }

  CampusGraph campusGraph;

  loadBuildings(dataDirectory + "/buildings.txt", campusGraph);
  loadConnections(dataDirectory + "/connections.txt", campusGraph);

  bool running = true;
  while(running){
    printMenu();

    string userInput;
    if(!getline(cin, userInput)){
      break;
    }
    string cleanInput = trimInput(userInput);

    if(cleanInput == ""){
      cout << "Error: Please enter a number from 1 to 10(or 0 to exit).\n";
      continue;
    }
    bool isAllDigits = true;
    for (int i = 0; i < (int)cleanInput.length(); i++){
      if(cleanInput[i] < '0' || cleanInput[i] > '9'){
      isAllDigits = false;
      break;
      }
    }
    if(!isAllDigits || cleanInput.length() > 4){
      cout << "Error: Invalid menu input '" << cleanInput << "'. Please enter a valid option number.\n";
      continue;
    }

    int choice = atoi(cleanInput.c_str());

    if(choice == 1){
      cout << "[Siri: displayFacilities()]\n";
    }
    else if(choice == 2){
      cout << "Enter facility ID: ";
      string facilityId;
      getline(cin, facilityId);
      if(trimInput(facilityId) == ""){
        cout << "Error: Facility ID cannot be blank\n";
      }else{
      facilityTable.findById(facilityId);
      }
    }
    else if (choice == 3){
      campusGraph.displayGraph();
    }
    else if(choice == 4){
      campusGraph.displayCountsAndDegrees();
    }
    else if (choice == 5){
      cout << "Enter starting building name: ";
      string buildingName;
      getline(cin, buildingName);
      if(trimInput(buildingName) == ""){
        cout << "Error: Building name cannot be blank.\n";
      }else{
        campusGraph.findReachableBuildings(buildingName);
      }
    }
    else if(choice == 6){
      cout << "addDepartment\n";
    }
    else if(choice == 7){
      cout << "Enter department name: ";
      string departmentName;
      getline(cin, departmentName);
      if(trimInput(departmentName) == ""){
        cout << "Error: Department name cannot be blank.\n";
      }else{
      }
    }
    else if(choice == 8){
    
      
      
        


