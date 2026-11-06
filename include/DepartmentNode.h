#ifndef DEPARTMENT_NODE_H
#define DEPARTMENT_NODE_H

#inclide <string>
#include <vector>

using namespace std:
//Represents one department in the general tree
struct DepartmentNode {
      string departmentName;
      DepartmentNode* parent;
      vector<DepartmentNode*> children;

      // Constructor
      DepartmentNode(string name, DepartmentNode* parentNode = nullptr) {
          departmentNode(string name, DepartmentNode* parentNode = nullptr)
          parent = parentNode;
      }
};
#endif


