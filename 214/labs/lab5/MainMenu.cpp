// See comments in MainMenu.h for general details on what each functin does.
#include <iostream>
#include <limits>

#include "MainMenu.h"

// clear any characters from the (keyboard) input buffer
void ignoreLine() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// read and return an int from the console.  Keep trying if invalid until an int
// is returned.
int getIntFromUser() {
  while (true) {
    int guess;
    std::cin >> guess;

    if (std::cin.fail()) {
      std::cin.clear();
      ignoreLine();
      std::cerr
          << "Invalid input. Input must be a valid int.  Please try again.\n";
    } else {
      ignoreLine();
      return guess;
    }
  }
}

// output the menu choices to the console.
void displayMainMenu() {
  std::cout << "\n";
  std::cout << "--- MENU ---\n";
  std::cout << "1) View Employees\n";
  std::cout << "2) Add Employee\n";
  std::cout << "3) Remove Employee\n";
  std::cout << "4) Remove All Employees\n";  // New option
  std::cout << "0) Exit\n";
  std::cout << "-------------\n";
  std::cout << "Select: ";
}

// Attempt to read an int from the keyboard.
// If there was a failure, clear the buffer and return -1.
Command getMenuCommand() {
  int input{-1};  // default
  std::cin >> input;
  if (std::cin.fail()) {
    std::cin.clear();  // clear the failure
    input = -1;        // indicate an error
  }
  ignoreLine();  // ignore any extra input

  Command command = Command::invalid;  // default
  // match input with specific commands
  switch (input) {
    case 1:
      command = Command::viewEmployees;
      break;
    case 2:
      command = Command::addEmployee;
      break;
    case 3:
      command = Command::removeEmployee;
      break;
    case 4:  // New case for removing all employees
      command = Command::removeAllEmployees;
      break;
    case 0:
      command = Command::exit;
      break;
  }
  return command;
}

// This function is called when a user picks a selection from the menu.
// It determines what action to take depending on the menuItemSelected,
// and calls the appropriate function.
// Returns true the selection was a request to exit menu, false otherwise.
void handleMenuInput(Employee*& pHead, Command command) {
  switch (command) {
    case Command::viewEmployees:
      std::cout << ">> View Employees:\n";
      viewEmployees(pHead);
      break;
    case Command::addEmployee: {
      std::cout << ">> Add Employee:\n";
      std::cout << "Enter name:";
      std::string name;
      std::getline(std::cin, name);
      addNewEmployee(pHead, name);
    } break;
    case Command::removeEmployee:
      std::cout << ">> Remove Employee:\n";
      std::cout << "Enter id:";
      removeEmployee(pHead, getIntFromUser());
      break;
    case Command::exit:
      std::cout << "Exiting\n";
      break;
    default:
      std::cout << "Invalid input.\n";
      break;
  }
}

// =============================================================================
// Implement the functions below by following the given directions:
// As you implement these, you will have to add forward declarations for
// each one in MainMenu.h
// The function name has been given.
// In some cases, the first parameter has been given.
// =============================================================================

// Output a list of all employees to the console.
// If the list is empty (nullptr), print "empty list.\n"
// If it isn't empty, print each employee's id and name to the console:
//    eg: [id: 5, name: Mary]\n
// Create a pointer to traverse the list, point it at the front of the list,
// process the node (output as shown above), and advance the pointer through the
// list.  Repeat until you process the last node.
// -param 1: (given) a pointer to an Employee struct (representing the front
//			 of the list of employees.
// return: nothing
// TODO ------------------------------------------------------------------------
// viewEmployees(Employee* pHead);
void viewEmployees(Employee* pHead) {
  if (pHead == nullptr) {
    std::cout << "Empty List" << std::endl;
    return;
  }

  Employee* pCurrent = pHead;
  while (pCurrent != nullptr) {
    std::cout << pCurrent->id << " " << pCurrent->name << std::endl;
    pCurrent = pCurrent->pNext;
  }
}

// Create a new employee struct on the heap.
// Use a static local variable to generate unique employee id's with (initialize
// it and then increment it every time this function is called).
// Dynamically allocate memory for an employee struct from the heap.
//		 Initialize it with:
//				-the unique id,
//				-the name passed in as a paramter,
//				-nullptr.
// - param 1: a string - the employee's name.
// - return: a pointer to the dynamically allocated Employee struct
// TODO ------------------------------------------------------------------------
// createEmployee();
Employee* createEmployee(const std::string& employeeName) {
  static int uniqueID = 0;
  Employee* pEmployee = new Employee;

  pEmployee->id = uniqueID++;
  pEmployee->name = employeeName;
  pEmployee->pNext = nullptr;

  return pEmployee;
}

// Create a new employee node, then add it to the list
// Use createEmployee() for node creation.
// Insert the new employee node at the front of the linked list
// It will help to draw this out!
// - param 1: (given) a pointer to the front of the list of employees (passed
//            by reference)
// - param 2: a string - the employee's name.
// - return: nothing
// TODO ------------------------------------------------------------------------
// addNewEmployee(Employee*& pHead);
void addNewEmployee(Employee*& pHead, const std::string& employeeName) {
  Employee* pEmployee = createEmployee(employeeName);
  pEmployee->pNext = pHead;
  pHead = pEmployee;
}

// Search through the list for a node with the given id.
// Tip: Use a pointer to iterate through the linked list and another
//      pointer to track the parent.
// - param 1: (given) a pointer to an Employee struct (representing the front
//			  of the list of employees
// - param 2: an int (the id of the employee we're searching for).
// - return: a NodeInfo struct. It contains a pointer to the node that matches
//			 the id passed in and a pointer to that node's parent.
//           If node not found, pointers inside NodeInfo should both be nullptr.
//           If node is first in the list, NodeInfo.pParent should be nullptr.
// TODO ------------------------------------------------------------------------
// getNodeInfo(Employee* pHead);
NodeInfo getNodeInfo(Employee* pHead, const int id) {
  NodeInfo nodeInfo{nullptr, nullptr};
  Employee* pCurrent = pHead;
  Employee* pParent = nullptr;

  while (pCurrent != nullptr) {
    if (pCurrent->id == id) {
      nodeInfo.pNode = pCurrent;
      nodeInfo.pParent = pParent;
      return nodeInfo;
    }
    pParent = pCurrent;
    pCurrent = pCurrent->pNext;
  }

  return nodeInfo;
}

// Removes an employee node with the given id from the list.
// Try to find a node with the given id (use getNodeInfo()).
//	1) If node not found, output "Error: employee id:# not found\n".
//  2) If node found, but parent is nullptr, the node is first in the list:
//			-Set the pHead to point to the second node in the list.
//			-Output "removed id:# \n" to the console
//			-Deallocate the node (return it to the heap)
//  3) otherwise the node was found and a parent exists
//			-Set the parent's next pointer to the next pointer of
//the
// node we want to delete 			-Output a "removed id: #n" message to
// the console 			-Deallocate the node (return it to the heap).
// - param 1: (given) a pointer to the front of the list of employees (passed by
// reference)
// - param 2: an int (the id of the employee we're searching for).
// - return: nothing
// TODO ------------------------------------------------------------------------
// removeEmployee(Employee*& pHead);
void removeEmployee(Employee*& pHead, const int id) {
  const NodeInfo nodeInfo = getNodeInfo(pHead, id);

  if (nodeInfo.pNode == nullptr) {
    std::cout << "Error: employee id:" << id << " not found\n";
    return;
  }

  if (nodeInfo.pParent == nullptr) {
    pHead = nodeInfo.pNode->pNext;
    std::cout << "removed id (first if block):" << id << std::endl;
    delete nodeInfo.pNode;
  } else {
    nodeInfo.pParent->pNext = nodeInfo.pNode->pNext;
    std::cout << "removed id:" << id << std::endl;
    delete nodeInfo.pNode;
  }
}
