#include <iostream>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "ast.h"
#include "tableManager.h"

// ============== Classes related to the implementaion of functions ============
const Literal* SuiteNode::eval() const {
  // So the suite node will be a list of statements in a vector
  // Loop thru the vector and eval them all !
  int canExec = 1;
  for(const Node* n: *fnStatements) {
    if (!n) {
        throw std::string("Invalid Function Statement");
    }
    if (canExec) {
      n->eval();
    }
    if (TableManager::getInstance().checkSymbolInCurrentScope("__RETURN__")) {
      // std::cout<<"Yeah Found....."<<std::endl;
      canExec = 0;
    }
  }
  // TODO: BE CAREFUL !
  return nullptr;
}

const Literal* FunctionNode::eval() const {
  // On definition, store in the function table
  TableManager::getInstance().setFunction(fnName, fnStatements);

  // Test code : TODO: Remove
  if (formalArgs != nullptr) {
    std::cout<<"====================================================="<<std::endl;
    std::cout<<"The function has the following formal parameters"<<std::endl;
    for (const Node* n : *formalArgs) {
      const std::string argName = static_cast<const IdentNode*>(n)->getIdent();
      std::cout<<argName<<std::endl;
    }
    TableManager::getInstance().setFormalArgs(fnName, formalArgs);
    TableManager::getInstance().printScopeStack();
    std::cout<<"====================================================="<<std::endl;
  } else {
    std::cout<<"Nope, there are no params..."<<std::endl;
  }

  bool yes = TableManager::getInstance().checkFormalArgs(fnName);
  std::cout<<"===========Function " <<fnName<<" ======== formal pars " <<yes<<std::endl;


  // Test code : TODO: Remove
  // std::cout<<"Testing code ........."<<std::endl;
  // const Node* suite = TableManager::getInstance().getFunction(fnName);
  // suite->eval();
  // TODO: BE CAREFUL !
  return nullptr;
}

const Literal* FunctionCallNode::eval() const {
  const Node* suite = TableManager::getInstance().getFunction(fnName);
  std::cout<<""<<std::endl;
  std::cout<<"======== Function "<<fnName<<std::endl;
  std::cout<<TableManager::getInstance().checkFormalArgs(fnName)<<std::endl;
  std::cout<<"======== Function "<<fnName<<std::endl;
  std::cout<<""<<std::endl;
  TableManager::getInstance().pushScope();


  // TableManager::getInstance().printScopeStack();
  // suite is a SuiteNode
  try {
    suite->eval(); // either nullptr or literal*
  } catch (...) {
    throw std::string("Error executing function " + fnName);
  }
  // TableManager::getInstance().printScopeStack();
  if (TableManager::getInstance().checkSymbolInCurrentScope("__RETURN__")) {
    const Literal* returnValue = TableManager::getInstance().getSymbol("__RETURN__");
    TableManager::getInstance().popScope();
    return returnValue;
  } else {
    TableManager::getInstance().popScope();
    return nullptr;
  }
  // TableManager::getInstance().printScopeStack();
  // TODO: BE CAREFUL !
}

const Literal* ReturnNode::eval() const {
  // Assuming this is inside a function
  // As soon as we hit return, we save the return val or nullptr inside the currentScope
  // While exec functions, after each eval, check for a __RETURN__ value and
  // exit the func returning that value
  const Literal* res = (retNode == nullptr) ? nullptr : retNode->eval();
  TableManager::getInstance().setSymbol("__RETURN__", res);
  return nullptr;
}

// ============== Classes related to the implementaion of if constructs ============
const Literal* IfNode::eval() const {
  if (!test) {
    throw std::string("Missing condition(s)");
  }
  bool result = static_cast<const FloatLiteral*>(test->eval())->isTrue();
  if (result) {
    try {
      suite->eval();
    } catch (...) {
      throw std::string("Error executing if statements");
    }
  } else {
    if (elseSuite != nullptr) {
      try {
        elseSuite->eval();
      } catch (...) {
        throw std::string("Error executing else statements");
      }
    }
  }
  return nullptr;
}

// Comparison nodes
// Will always return a 1 or a 0 Int Literal
const Literal* EqEqComparisonNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* left_res = left->eval();
  const Literal* right_res = right->eval();
  const Literal* decision = (*left_res) == (*right_res);
  return decision;
}
const Literal* NotEqComparisonNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* left_res = left->eval();
  const Literal* right_res = right->eval();
  const Literal* decision = (*left_res) != (*right_res);
  return decision;
}
const Literal* GreaterComparisonNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* left_res = left->eval();
  const Literal* right_res = right->eval();
  const Literal* decision = (*left_res) > (*right_res);
  return decision;
}
const Literal* GreaterEqComparisonNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* left_res = left->eval();
  const Literal* right_res = right->eval();
  const Literal* decision = (*left_res) >= (*right_res);
  return decision;
}
const Literal* LessComparisonNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* left_res = left->eval();
  const Literal* right_res = right->eval();
  const Literal* decision = (*left_res) < (*right_res);
  return decision;
}
const Literal* LessEqComparisonNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* left_res = left->eval();
  const Literal* right_res = right->eval();
  const Literal* decision = (*left_res) <= (*right_res);
  return decision;
}
// ==================================================================================

const Literal* PrintNode::eval() const {
  if (!nd) {
    throw std::string("Invalid Statement");
  }
  try {
    nd->eval()->print();
  } catch (const std::string msg) {
    std::cout<<"ERROR: "<<msg<<std::endl;
  } catch ( ... ) {
    std::cout<<"ERROR: Uncaught Exception"<<std::endl;
  }
  return nullptr;
}

const Literal* IdentNode::eval() const {
  const Literal* val = TableManager::getInstance().getSymbol(ident);
  return val;
}

const Literal* IndexerNode::eval() const {
  if (!nd) {
    throw std::string("String Required");
  }
  // std::cout<<"$$$$$$$$$$$$$ I see where you are going ...."<<std::endl;
  const Literal* lit = nd->eval();
  return lit->indexOf(start, end, step, hasColon, shouldUseStrLen, isStartIndexEmpty);
}

// AsgBinaryNode::AsgBinaryNode(Node* left, Node* right) :
//   // BinaryNode(left, right) {
//   // const Literal* res = right->eval();
//   // const std::string n = static_cast<IdentNode*>(left)->getIdent();
//   // // std::cout<<"Le Place Herr "<< n <<std::endl;
//   // TableManager::getInstance().setSymbol(n, res);
// }

// PlusAsgBinaryNode::PlusAsgBinaryNode(Node* left, Node* right) :
//   BinaryNode(left, right) {
//   const Literal* right_res = right->eval();
//   const Literal* left_res = left->eval();
//   const Literal* res = (*left_res) + (*right_res);
//   const std::string n = static_cast<IdentNode*>(left)->getIdent();
//   // Updated value
//   TableManager::getInstance().setSymbol(n, res);
// }
// MinusAsgBinaryNode::MinusAsgBinaryNode(Node* left, Node* right) :
//   BinaryNode(left, right) {
//   const Literal* right_res = right->eval();
//   const Literal* left_res = left->eval();
//   const Literal* res = (*left_res) - (*right_res);
//   const std::string n = static_cast<IdentNode*>(left)->getIdent();
//   // Updated value
//   TableManager::getInstance().setSymbol(n, res);
// }
// MulAsgBinaryNode::MulAsgBinaryNode(Node* left, Node* right) :
//   BinaryNode(left, right) {
//   const Literal* right_res = right->eval();
//   const Literal* left_res = left->eval();
//   const Literal* res = (*left_res) * (*right_res);
//   const std::string n = static_cast<IdentNode*>(left)->getIdent();
//   // Updated value
//   TableManager::getInstance().setSymbol(n, res);
// }
// DivideAsgBinaryNode::DivideAsgBinaryNode(Node* left, Node* right) :
//   BinaryNode(left, right) {
//   const Literal* right_res = right->eval();
//   const Literal* left_res = left->eval();
//   const Literal* res = (*left_res) / (*right_res);
//   const std::string n = static_cast<IdentNode*>(left)->getIdent();
//   // Updated value
//   TableManager::getInstance().setSymbol(n, res);
// }
// FloorDivideAsgBinaryNode::FloorDivideAsgBinaryNode(Node* left, Node* right) :
//   BinaryNode(left, right) {
//   const Literal* right_res = right->eval();
//   const Literal* left_res = left->eval();
//   const Literal* res = (*left_res).floorDivide(*right_res);
//   const std::string n = static_cast<IdentNode*>(left)->getIdent();
//   // Updated value
//   TableManager::getInstance().setSymbol(n, res);
// }
// ModAsgBinaryNode::ModAsgBinaryNode(Node* left, Node* right) :
//   BinaryNode(left, right) {
//   const Literal* right_res = right->eval();
//   const Literal* left_res = left->eval();
//   const Literal* res = (*left_res) % (*right_res);
//   const std::string n = static_cast<IdentNode*>(left)->getIdent();
//   // Updated value
//   TableManager::getInstance().setSymbol(n, res);
// }
// PowerAsgBinaryNode::PowerAsgBinaryNode(Node* left, Node* right) :
//   BinaryNode(left, right) {
//   const Literal* right_res = right->eval();
//   const Literal* left_res = left->eval();
//   const Literal* res = (*left_res).raiseTo(*right_res);
//   const std::string n = static_cast<IdentNode*>(left)->getIdent();
//   // Updated value
//   TableManager::getInstance().setSymbol(n, res);
// }


const Literal* AsgBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* res = right->eval();
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  TableManager::getInstance().setSymbol(n, res);
  return res;
}

const Literal* PlusAsgBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* right_res = right->eval();
  const Literal* left_res = left->eval();
  const Literal* res = (*left_res) + (*right_res);
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  // Updated value
  TableManager::getInstance().setSymbol(n, res);
  return res;
}

const Literal* MinusAsgBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* right_res = right->eval();
  const Literal* left_res = left->eval();
  const Literal* res = (*left_res) - (*right_res);
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  // Updated value
  TableManager::getInstance().setSymbol(n, res);
  return res;
}
const Literal* MulAsgBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* right_res = right->eval();
  const Literal* left_res = left->eval();
  const Literal* res = (*left_res) * (*right_res);
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  // Updated value
  TableManager::getInstance().setSymbol(n, res);
  return res;
}
const Literal* DivideAsgBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* right_res = right->eval();
  const Literal* left_res = left->eval();
  const Literal* res = (*left_res) / (*right_res);
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  // Updated value
  TableManager::getInstance().setSymbol(n, res);
  return res;
}
const Literal* FloorDivideAsgBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* right_res = right->eval();
  const Literal* left_res = left->eval();
  const Literal* res = (*left_res).floorDivide(*right_res);
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  // Updated value
  TableManager::getInstance().setSymbol(n, res);
  return res;
}
const Literal* ModAsgBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* right_res = right->eval();
  const Literal* left_res = left->eval();
  const Literal* res = (*left_res) % (*right_res);
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  // Updated value
  TableManager::getInstance().setSymbol(n, res);
  return res;
}
const Literal* PowerAsgBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* right_res = right->eval();
  const Literal* left_res = left->eval();
  const Literal* res = (*left_res).raiseTo(*right_res);
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  // Updated value
  TableManager::getInstance().setSymbol(n, res);
  return res;
}



const Literal* MinusUnaryNode::eval() const {
  if (!nd) {
    throw std::string("Missing operand(s)");
  }
  const IntLiteral minus(-1);
  const Literal* negLit = minus * (*nd->eval());
  return negLit;
}

const Literal* AddBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x+*y);
}

const Literal* SubBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)-(*y));
}

const Literal* MulBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)*(*y));
}

const Literal* DivBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)/(*y));
}

const Literal* FloorDivBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  // Now x and y can be either an int or a float literal
  return (*x).floorDivide(*y);
}

const Literal* ModBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  // Now x and y can be either an int or a float literal
  return ((*x)%(*y));
}

const Literal* PowerBinaryNode::eval() const {
  if (!left || !right) {
    throw std::string("Missing operand(s)");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  // Now x and y can be either an int or a float literal
  return (*x).raiseTo(*y);
}
