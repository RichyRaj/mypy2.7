#ifndef FUNCTIONTABLE_H
#define FUNCTIONTABLE_H

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

class Node;

class FunctionTable {
  public:
    FunctionTable() : table() {}
    void setValue(const std::string& name, const Node* val);
    const Node* getValue(const std::string& name) const;
    bool checkValue(const std::string& name) const;
    // debug method
    void printTable() const;
  private:
    std::map<std::string, const Node*> table;
};

#endif
