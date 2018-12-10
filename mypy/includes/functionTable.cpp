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

void FunctionTable::printTable() const {
  std::cout<<"=+++++++++++++++++++++++++++++++++++++++++++++++++++++++="<<std::endl;
  std::cout << "Function TABLE - SIZE : " << table.size() << std::endl;
  for(auto it = table.cbegin(); it != table.cend(); ++it)
  {
    std::cout << it->first << std::endl;
  }
  std::cout<<"=+++++++++++++++++++++++++++++++++++++++++++++++++++++++="<<std::endl;
}
