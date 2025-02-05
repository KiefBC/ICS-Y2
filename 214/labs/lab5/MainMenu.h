#ifndef MAINMENU_H
#define MAINMENU_H

// The MainMenu (.h & .cpp) file contains the function declarations used to
// Present a main menu which allows a user to view, add, and remove employees.
// The list of employees is implemented with a linked list, and most of the
// processing functions get passed a pointer to the first element of the
// list (Employee* pHead).

#include <string>

// A command set of operations that can be used with our Menu.
enum class Command {
  invalid,
  viewEmployees,
  addEmployee,
  removeEmployee,
  removeAllEmployees,  // Add this new command
  exit
};
// a struct to represent an Employee (each instance forms a node of a linked
// list used to store employees.
struct Employee {
  int id;
  std::string name;
  Employee* pNext;
};

// A struct used to return multiple return values from the getNodeInfo()
// function. getNodeInfo() traverses the list looking for a target node (and its
// parent node). NodeInfo contains info needed to facilitate node insertion &
// deletion in the list.
struct NodeInfo {
  Employee* pNode;    // a pointer to the "target" node.
  Employee* pParent;  // a pointer to the node prior to pNode (nullptr if node
                      // is at the front)
};

// Clear any characters from the (keyboard) input buffer
void ignoreLine();

// Read and return an int from the console. Keep trying until an int is
// returned.
int getIntFromUser();

// display the main menu
void displayMainMenu();

// fetch and return a menu command from user input
Command getMenuCommand();

// Given a Command, this will determine the appropriate function to call.
// - param 1: (given) a pointer to the front of the list of employees (passed by
// reference)
// - param 2: a Command (enum) representing the action to be taken.
void handleMenuInput(Employee*& pHead, Command command);

// Display the list of employees
void viewEmployees(Employee* pHead);

// Create a new employee node
Employee* createEmployee(const std::string&);

// Add an employee to the list
void addNewEmployee(Employee*& pHead, const std::string&);

// Remove an employee from the list
void removeEmployee(Employee*& pHead, int);

// Get the node info for a target node in the list.
// - param 1: a pointer to the front of the list of employees
// - param 2: the id of the target node
// - return: a NodeInfo struct containing the target node and its parent node.
NodeInfo getNodeInfo(Employee* pHead, int);

void removeAllEmployees(Employee*& pHead);

#endif
