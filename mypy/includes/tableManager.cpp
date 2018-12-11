#include "literal.h"
#include "symbolTable.h"
#include "functionTable.h"
#include "tableManager.h"

TableManager& TableManager::getInstance() {
  static TableManager instance;
  return instance;
}

// ------------------ Methods for the symbol table ------------------
const Literal*  TableManager::getSymbol(const std::string& name) const {
  // 0th index in the vector of tables will be the global scope;
  // SymbolTable sTable = sTables[0];

  // Debug
  // sTables[0].printTable();

  // Start from the tos and go until stack empty
  int tos = currentScope;
  while (tos >= 0) {
    if (sTables[tos].checkValue(name)) {
      return sTables[tos].getValue(name);
    }
    tos -= 1;
  }
  throw std::string(name + " not found ");
  return nullptr;
}

void TableManager::setSymbol(const std::string& name, const Literal* val) {
  // 0th index in the vector of tables will be the global scope
  // SymbolTable sTable = sTables[0];
  int tos = currentScope;
  sTables[tos].setValue(name, val);
  // Debug
  // sTables[0].printTable();
}

bool TableManager::checkSymbol(const std::string& name) const {
  // 0th index in the vector of tables will be the global scope
  // SymbolTable sTable = sTables[0];
  int tos = currentScope;
  while (tos >= 0) {
    if (sTables[tos].checkValue(name)) {
      return true;
    }
    tos -= 1;
  }
  return false;
}

bool TableManager::checkSymbolInCurrentScope(const std::string& name) const {
  // 0th index in the vector of tables will be the global scope
  // SymbolTable sTable = sTables[0];
  int tos = currentScope;
  if (sTables[tos].checkValue(name)) {
    return true;
  }
  return false;
}

// ------------------ Methods for the function table ------------------
const Node*  TableManager::getFunction(const std::string& name) const {
  // 0th index in the vector of tables will be the global scope;

  // Debug
  // fTables[0].printTable();

  int tos = currentScope;
  while (tos >= 0) {
    if (fTables[tos].checkValue(name)) {
      return fTables[tos].getValue(name);
    }
    tos -= 1;
  }
  throw std::string("Function " +  name + " not found ");
  return nullptr;
}

void TableManager::setFunction(const std::string& name, const Node* val) {
  // 0th index in the vector of tables will be the global scope
  int tos = currentScope;
  fTables[tos].setValue(name, val);
  // Debug
  // fTables[0].printTable();
}
bool TableManager::checkFunction(const std::string& name) const {
  // 0th index in the vector of tables will be the global scope
  int tos = currentScope;
  while (tos >= 0) {
    if (fTables[tos].checkValue(name)) {
      return true;
    }
    tos -= 1;
  }
  return false;
}

const std::vector<Node*>* TableManager::getFormalArgs(const std::string& name) const {
  int tos = currentScope;
  while (tos >= 0) {
    if (fTables[tos].checkFormalArgs(name)) {
      // return fTables[tos].getValue(name);
      return nullptr;
    }
    tos -= 1;
  }
  throw std::string("Function " +  name + " not found ");
  return nullptr;
}

void TableManager::setFormalArgs(const std::string& name, const std::vector<Node*>* list) {
  // 0th index in the vector of tables will be the global scope
  int tos = currentScope;
  std::cout<<"Setting Formal Args for ..."<<name<<std::endl;
  fTables[tos].setFormalArgs(name, list);
  // Debug
  // fTables[0].printTable();
}

bool TableManager::checkFormalArgs(const std::string& name) const {
  int tos = currentScope;
  while (tos >= 0) {
    if (fTables[tos].checkFormalArgs(name)) {
      return true;
    }
    tos -= 1;
  }
  return false;
}


// ------------------ Methods for Scope Maintenance ------------------
void TableManager::pushScope() {
  addNewScope();
  increaseTOS();
}
void TableManager::popScope() {
  if (currentScope > 0) {
    sTables.pop_back();
    fTables.pop_back();
    currentScope -= 1;
  }
}

// ------------------ Helper Methods ------------------
void TableManager::addNewScope() {
  // Once a scope is created, it becomes the top of stack
  sTables.push_back(SymbolTable());
  fTables.push_back(FunctionTable());
}
void TableManager::increaseTOS() {
  currentScope += 1;
}
void TableManager::printScopeStack() {
  int tos = currentScope;
  while (tos >= 0) {
    std::cout<<"+===================StackFrame "<< tos << "- BEGIN========================"<<std::endl;
    sTables[tos].printTable();
    fTables[tos].printTable();
    std::cout<<"+===================StackFrame "<< tos << "- END========================"<<std::endl;
    tos =- 1;
  }
}
