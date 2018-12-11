// This is a singleton class that acts as a wrapper for the symbol and function tables
// Every component/Node will can create symbol tables and function tables
// However, communication has to go through this manager

#ifndef TABLEMANAGER__H
#define TABLEMANAGER__H

#include <string>
#include <algorithm>
#include "symbolTable.h"
#include "functionTable.h"

class Literal;
class Node;

class TableManager {
  public:
    static TableManager& getInstance();

    // ------------------ Methods for the symbol table ------------------
    const Literal* getSymbol(const std::string& name) const;
    void setSymbol(const std::string& name, const Literal* val);
    bool checkSymbol(const std::string& name) const;
    bool checkSymbolInCurrentScope(const std::string& name) const;

    // ------------------ Methods for the function table ------------------
    const Node* getFunction(const std::string& name) const;
    void setFunction(const std::string& name, const Node* val);
    bool checkFunction(const std::string& name) const;

    const std::vector<Node*>* getFormalArgs(const std::string& name) const;
    void setFormalArgs(const std::string& name, const std::vector<Node*>*);
    bool checkFormalArgs(const std::string& name) const;

    // ------------------ Methods for Scope Maintenance ------------------
    // For the sake of simplicity, we have to vectors as scope stack
    // One for functions and other for variables
    void pushScope();
    void popScope();

    // helper methods
    void printScopeStack();

  private:
    int currentScope = 0;
    std::vector<SymbolTable> sTables; // There can be multiple symbol tables
    std::vector<FunctionTable> fTables; // There can be multiple function tables
    TableManager(): sTables(), fTables() {
      // Start the global scope
      addNewScope();
    }
    // helper methods
    void addNewScope();
    void increaseTOS(); // Top of stack
};

#endif
