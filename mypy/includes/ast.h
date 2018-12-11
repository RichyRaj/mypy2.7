#pragma once

//  Declarations for a calculator that builds an AST
//  and a graphical representation of the AST.
//  by Brian Malloy

#include <iostream>
#include <string>
#include <map>
#include "literal.h"

extern void yyerror(const char*);
extern void yyerror(const char*, const char);



// ============== Classes related to the implementaion of functions ============
class SuiteNode: public Node {
  public:
    SuiteNode(std::vector<Node*>* stmts): Node(), fnStatements(stmts) {
    }
    virtual ~SuiteNode() {
      delete fnStatements;
    }
    const std::vector<Node*>* getSuite() const {
      return fnStatements;
    }
    virtual const Literal* eval() const;
    SuiteNode(const SuiteNode&) = delete;
    SuiteNode& operator=(const SuiteNode&) = delete;
  private:
    std::vector<Node*>* fnStatements;
};

class FunctionNode: public Node {
  public:
    FunctionNode(const std::string name, Node* suite,
      std::vector<Node*>* args): Node(), fnName(name),
      fnStatements(suite),
      formalArgs(args) {}
    virtual ~FunctionNode() {
      // TODO: delete args
    }
    FunctionNode(const FunctionNode&) = delete;
    FunctionNode& operator=(const FunctionNode&) = delete;
    virtual const Literal* eval() const;
  private:
    const std::string fnName;
    Node* fnStatements;
    std::vector<Node*>* formalArgs;
};

class FunctionCallNode: public Node {
  public:
    FunctionCallNode(const std::string name, std::vector<Node*>* args) : fnName(name), actArgs(args) {}
    virtual ~FunctionCallNode() {
      // TODO : Delete args
    }
    virtual const Literal* eval() const;
    FunctionCallNode(const FunctionCallNode&) = delete;
    FunctionCallNode& operator=(const FunctionCallNode&) = delete;
  private:
    const std::string fnName;
    std::vector<Node*>* actArgs;
};

class ReturnNode: public Node {
  public:
    ReturnNode(Node* returnVal): Node(), retNode(returnVal) {}
    virtual ~ReturnNode() {}
    ReturnNode(const ReturnNode&) = delete;
    ReturnNode& operator=(const ReturnNode&) = delete;
    virtual const Literal* eval() const;
  private:
    Node* retNode;
};

// class ActualParametersNode: public Node {
//   public:
//     ActualParametersNode(std::vector<Node*>* args): Node(), actArgs(args) {
//     }
//     virtual ~ActualParametersNode() {
//       // TODO: Delete !
//       // delete fnStatements;
//     }
//     const std::vector<Node*>* getActualArgs() const {
//       return actArgs;
//     }
//     virtual const Literal* eval() const;
//     ActualParametersNode(const ActualParametersNode&) = delete;
//     ActualParametersNode& operator=(const ActualParametersNode&) = delete;
//   private:
//     std::vector<Node*>* actArgs;
// };

// ============== Classes related to the implementaion of if constructs ============
class IfNode: public Node {
  public:
    IfNode(Node* pTest, Node* pSuite, Node* pElse): Node(), test(pTest),
      suite(pSuite), elseSuite(pElse) {}
    virtual ~IfNode() {}
    IfNode(const IfNode&) = delete;
    IfNode& operator=(const IfNode&) = delete;
    virtual const Literal* eval() const;
  private:
    Node* test; // Any comparison node
    Node* suite; // Suite node
    Node* elseSuite; // Suite node for else
};

// Since we should not print at the print statement and instead wait till it
// reaches a higher production, we need something that when eval(), prints out
// the result. So,
class PrintNode: public Node {
  public:
    PrintNode(Node* n) : Node(), nd(n) {}
    virtual ~PrintNode() {}
    PrintNode(const PrintNode&) = delete;
    PrintNode& operator=(const PrintNode&) = delete;
    virtual const Literal* eval() const;
  private:
    Node* nd;
};

class IdentNode : public Node {
public:
  IdentNode(const std::string id) : Node(), ident(id) {
    // std::<<" ...." << id << std::endl;
  }
  virtual ~IdentNode() {}
  const std::string getIdent() const { return ident; }
  virtual const Literal* eval() const;
private:
  std::string ident;
};

class IndexerNode : public Node {
  public:
    // TODO: Probably too many arguments here. Wrap them up in a data structure.
    IndexerNode(Node* n, int _start, int _end, int _step, bool _hasColon,
      bool _shouldUseStrLen, bool _isStartIndexEmpty):
    Node(),
    nd(n), start(_start), end(_end), step(_step), hasColon(_hasColon),
    shouldUseStrLen(_shouldUseStrLen), isStartIndexEmpty(_isStartIndexEmpty) {}
    virtual const Literal* eval() const;
    IndexerNode(const IndexerNode&) = delete;
    IndexerNode& operator=(const IndexerNode&) = delete;
  private:
    Node* nd;
    int start;
    int end;
    int step;
    bool hasColon;
    bool shouldUseStrLen;
    bool isStartIndexEmpty;
};

class UnaryNode : public Node {
  public:
    UnaryNode(Node* n): Node(), nd(n) {}
    virtual const Literal* eval() const = 0;
    Node* getNode()  const { return nd; }
    UnaryNode(const UnaryNode&) = delete;
    UnaryNode& operator=(const UnaryNode&) = delete;
  protected:
    Node *nd;
};

class MinusUnaryNode : public UnaryNode {
  public:
    MinusUnaryNode(Node* nd) : UnaryNode(nd) {};
    virtual const Literal* eval() const;
};

// ==================== Binary Nodes ===========================
class BinaryNode : public Node {
public:
  BinaryNode(Node* l, Node* r) : Node(), left(l), right(r) {}
  virtual const Literal* eval() const = 0;
  Node* getLeft()  const { return left; }
  Node* getRight() const { return right; }
  BinaryNode(const BinaryNode&) = delete;
  BinaryNode& operator=(const BinaryNode&) = delete;
protected:
  Node *left;
  Node *right;
};

// =============================================================================
// classes related to rel ops
// Comparison operations
class EqEqComparisonNode: public BinaryNode {
  public:
    EqEqComparisonNode(Node* left, Node* right): BinaryNode(left, right) {}
    virtual const Literal* eval() const;
};
class NotEqComparisonNode: public BinaryNode {
  public:
    NotEqComparisonNode(Node* left, Node* right): BinaryNode(left, right) {}
    virtual const Literal* eval() const;
};
class GreaterComparisonNode: public BinaryNode {
  public:
    GreaterComparisonNode(Node* left, Node* right): BinaryNode(left, right) {}
    virtual const Literal* eval() const;
};
class GreaterEqComparisonNode: public BinaryNode {
  public:
    GreaterEqComparisonNode(Node* left, Node* right): BinaryNode(left, right) {}
    virtual const Literal* eval() const;
};
class LessComparisonNode: public BinaryNode {
  public:
    LessComparisonNode(Node* left, Node* right): BinaryNode(left, right) {}
    virtual const Literal* eval() const;
};
class LessEqComparisonNode: public BinaryNode {
  public:
    LessEqComparisonNode(Node* left, Node* right): BinaryNode(left, right) {}
    virtual const Literal* eval() const;
};


// =============================================================================

class AsgBinaryNode : public BinaryNode {
public:
  AsgBinaryNode(Node* left, Node* right): BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class PlusAsgBinaryNode : public BinaryNode {
public:
  PlusAsgBinaryNode(Node* left, Node* right): BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class MinusAsgBinaryNode : public BinaryNode {
public:
  MinusAsgBinaryNode(Node* left, Node* right): BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class MulAsgBinaryNode : public BinaryNode {
public:
  MulAsgBinaryNode(Node* left, Node* right): BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class DivideAsgBinaryNode : public BinaryNode {
public:
  DivideAsgBinaryNode(Node* left, Node* right): BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class FloorDivideAsgBinaryNode : public BinaryNode {
public:
  FloorDivideAsgBinaryNode(Node* left, Node* right): BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};
class ModAsgBinaryNode : public BinaryNode {
public:
  ModAsgBinaryNode(Node* left, Node* right): BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};
class PowerAsgBinaryNode : public BinaryNode {
public:
  PowerAsgBinaryNode(Node* left, Node* right): BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};



class AddBinaryNode : public BinaryNode {
public:
  AddBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class SubBinaryNode : public BinaryNode {
public:
  SubBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class MulBinaryNode : public BinaryNode {
public:
  MulBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class DivBinaryNode : public BinaryNode {
public:
  DivBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class FloorDivBinaryNode : public BinaryNode {
public:
  FloorDivBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class ModBinaryNode : public BinaryNode {
public:
  ModBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class PowerBinaryNode : public BinaryNode {
public:
  PowerBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};
