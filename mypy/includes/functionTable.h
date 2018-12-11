#ifndef FUNCTIONTABLE_H
#define FUNCTIONTABLE_H

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

class Node;

class FunctionTable {
  public:
    FunctionTable() : table(), formalArgs() {}
    void setValue(const std::string& name, const Node* val);
    const Node* getValue(const std::string& name) const;
    bool checkValue(const std::string& name) const;

    void setFormalArgs(const std::string& name, const std::vector<Node*>* val);
    const std::vector<Node*>* getFormalArgs(const std::string& name) const;
    bool checkFormalArgs(const std::string& name) const;

    // debug method
    void printTable() const;
  private:
    std::map<std::string, const Node*> table;
    std::map<std::string, const std::vector<Node*>*> formalArgs;
};

#endif
