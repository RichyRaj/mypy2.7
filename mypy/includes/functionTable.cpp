#include <map>
#include <algorithm>
#include "functionTable.h"
// #include "ast.h"

const Node* FunctionTable::getValue(const std::string& name) const {
  std::map<std::string, const Node*>::const_iterator it =
    table.find(name);
  if (it == table.end()) throw std::string("Function ") + name + std::string(" not found");
  return it->second;
}

void FunctionTable::setValue(const std::string& name, const Node* val) {
  table[name] = val;
}

bool FunctionTable::checkValue(const std::string& name) const {
  std::map<std::string, const Node*>::const_iterator it =
    table.find(name);
  if (it == table.end()) {
    return false;
  }
  return true;
}

const std::vector<Node*>* FunctionTable::getFormalArgs(const std::string& name) const {
  // std::map<std::string, std::vector<Node*>*>::const_iterator it =
  //   formalArgs.find(name);
  // if (it == formalArgs.end()) throw std::string("Function ") + name + std::string(" not found");
  // return it->second;
}

void FunctionTable::setFormalArgs(const std::string& name, const std::vector<Node*>* val) {
  formalArgs[name] = val;
}

bool FunctionTable::checkFormalArgs(const std::string& name) const {
  std::map<std::string, const std::vector<Node*>*>::const_iterator it =
    formalArgs.find(name);
    if (it == formalArgs.end()) {
      return false;
    }
    return true;
}

void FunctionTable::printTable() const {
  std::cout<<"=+++++++++++++++++++++++++++++++++++++++++++++++++++++++="<<std::endl;
  std::cout << "Function TABLE - SIZE : " << table.size() << std::endl;
  for(auto it = table.cbegin(); it != table.cend(); ++it)
  {
    std::cout << it->first << std::endl;
  }
  std::cout << "Function TABLE Formal Parameters - SIZE : " << formalArgs.size() << std::endl;
  for(auto it = formalArgs.cbegin(); it != formalArgs.cend(); ++it)
  {
    std::cout << it->first << std::endl;
  }
  std::cout<<"=+++++++++++++++++++++++++++++++++++++++++++++++++++++++="<<std::endl;
}
