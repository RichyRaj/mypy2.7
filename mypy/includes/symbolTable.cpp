#include <map>
#include <algorithm>
#include "symbolTable.h"
#include "literal.h"

const Literal* SymbolTable::getValue(const std::string& name) const {
  std::map<std::string, const Literal*>::const_iterator it =
    table.find(name);
  if ( it == table.end() ) throw name+std::string(" not found");
  return it->second;
}

void SymbolTable::setValue(const std::string& name, const Literal* val) {
  table[name] = val;
}

bool SymbolTable::checkValue(const std::string& name) const {
  std::map<std::string, const Literal*>::const_iterator it =
    table.find(name);
  if (it == table.end()) {
    return false;
  }
  return true;
}

void SymbolTable::printTable() const {
  std::cout<<"=+++++++++++++++++++++++++++++++++++++++++++++++++++++++="<<std::endl;
  std::cout << "SYMBOL TABLE - SIZE : " << table.size() << std::endl;
  for(auto it = table.cbegin(); it != table.cend(); ++it)
  {
    std::cout << it->first << " --> ";
    it->second->eval()->print();
  }
  std::cout<<"=+++++++++++++++++++++++++++++++++++++++++++++++++++++++="<<std::endl;
}
