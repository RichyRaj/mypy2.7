#include <cmath>
#include <algorithm>
#include "node.h"
#include "poolOfNodes.h"

class Literal : public Node {
public:
  virtual ~Literal() {}

  virtual const Literal* operator+(const Literal& rhs) const = 0;
  virtual const Literal* opPlus(float) const = 0;
  virtual const Literal* opPlus(int) const = 0;
  virtual const Literal* opPlus(const std::string&) const {
    throw std::string("Operation not supportd on type");
  }


  virtual const Literal* operator*(const Literal& rhs) const = 0;
  virtual const Literal* opMult(float) const = 0;
  virtual const Literal* opMult(int) const = 0;
  virtual const Literal* opMult(const std::string&) const {
    throw std::string("Operation not supportd on type");
  }


  virtual const Literal* operator-(const Literal& rhs) const = 0;
  virtual const Literal* opSubt(float) const = 0;
  virtual const Literal* opSubt(int) const = 0;

  virtual const Literal* operator/(const Literal& rhs) const = 0;
  virtual const Literal* opDiv(float) const = 0;
  virtual const Literal* opDiv(int) const = 0;

  virtual const Literal* floorDivide(const Literal& rhs) const = 0;
  virtual const Literal* opFloorDiv(float) const = 0;
  virtual const Literal* opFloorDiv(int) const = 0;

  virtual const Literal* operator%(const Literal& rhs) const = 0;
  virtual const Literal* opMod(float) const = 0;
  virtual const Literal* opMod(int) const = 0;

  virtual const Literal* raiseTo(const Literal& rhs) const = 0;
  virtual const Literal* opPower(float) const = 0;
  virtual const Literal* opPower(int) const = 0;

  virtual const Literal* indexOf(int start, int end, int step, bool hasColon,
    bool shouldUseStrLen, bool isStartIndexEmpty) const = 0;

  // ============================Comparisons - START ===================================
  virtual const Literal* operator==(const Literal&) const = 0;
  virtual const Literal* compEqEq(int) const = 0;
  virtual const Literal* compEqEq(float) const = 0;
  virtual const Literal* compEqEq(const std::string&) const = 0;


  virtual const Literal* operator!=(const Literal&) const = 0;
  virtual const Literal* compNotEq(int) const = 0;
  virtual const Literal* compNotEq(float) const = 0;
  virtual const Literal* compNotEq(const std::string&) const = 0;

  virtual const Literal* operator>(const Literal&) const = 0;
  virtual const Literal* compGreater(int) const = 0;
  virtual const Literal* compGreater(float) const = 0;
  virtual const Literal* compGreater(const std::string&) const = 0;

  virtual const Literal* operator>=(const Literal&) const = 0;
  virtual const Literal* compGreaterEq(int) const = 0;
  virtual const Literal* compGreaterEq(float) const = 0;
  virtual const Literal* compGreaterEq(const std::string&) const = 0;

  virtual const Literal* operator<(const Literal&) const = 0;
  virtual const Literal* compLess(int) const = 0;
  virtual const Literal* compLess(float) const = 0;
  virtual const Literal* compLess(const std::string&) const = 0;

  virtual const Literal* operator<=(const Literal&) const = 0;
  virtual const Literal* compLessEq(int) const = 0;
  virtual const Literal* compLessEq(float) const = 0;
  virtual const Literal* compLessEq(const std::string&) const = 0;
  // ============================Comparisons - END ===================================

  virtual const Literal* eval() const = 0;
  virtual void print() const {
    std::cout << "No Way" << std::endl;
  }
};

/// ##################### Start of FLOAT literal ############################//
class FloatLiteral: public Literal {
public:
  FloatLiteral(float _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(int lhs) const  {
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<float>(lhs) * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(float lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  // Custom operations - BEGIN
  // Rules for Floor Division
  // Div gives true division for floats and div2 is floor division for floats
  // Eg. >>> 17.0 / 2
  // 8.5
  // >>> 17.0 / 2.0
  // 8.5
  // >>> 17.0 // 2
  // 8.0
  // >>> 17.0 // 2.0
  // 8.0
  virtual const Literal* floorDivide(const Literal& rhs) const {
    return rhs.opFloorDiv(val);
  }
  virtual const Literal* opFloorDiv(int lhs) const {
    // std::cout << "INT BY FLOAT 2" << std::endl;
    if ( val == 0 ) throw std::string("Zero Division Error");
    // Here lhs is a int value
    // val is a float (int / float) = float but with a point 0 (i.e loose precision)
    int result = int(lhs / val);
    const Literal* node = new FloatLiteral(float(result));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opFloorDiv(float lhs) const {
    // std::cout << "FLOAT BY FLOAT" << std::endl;
    if ( val == 0 ) throw std::string("Zero Division Error");
    // Here lhs is a float value
    // val is a float (float // float) = gives a float with .0 precision
    int result = int(lhs / val);
    const Literal* node = new FloatLiteral(float(result));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator%(const Literal& rhs) const {
    return rhs.opMod(val);
  }
  virtual const Literal* opMod(float lhs) const  {
    // Here val is a float
    // lhs is a float
    // Anything mod to float should be a float as well
    if ( val == 0 ) throw std::string("Zero Division Error");
    // std::cout << "Mod float, float" << std::endl;
    float result = float(fmod(lhs, val));
    const Literal* node = new FloatLiteral(result);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMod(int lhs) const  {
    // Here val is a float
    // lhs is an int
    // int mod float should be a float
    if ( val == 0 ) throw std::string("Zero Division Error");
    // std::cout << "Mod int, float" << std::endl;
    float result = float(fmod(lhs, val));
    const Literal* node = new FloatLiteral(result);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* raiseTo(const Literal& rhs) const {
    return rhs.opPower(val);
  }
  virtual const Literal* opPower(float lhs) const {
    // std::cout << "FLOAT TO FLOAT" << std::endl;
    // Here lhs is a float value
    // val is a float (float ^ float) = float
    float result = std::pow(lhs, val);
    const Literal* node = new FloatLiteral(result);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPower(int lhs) const {
    // std::cout << "INT TO FLOAT" << std::endl;
    // Here lhs is a int value
    // val is an float (int ^ float) = float
    float result = std::pow(lhs, val);
    const Literal* node = new FloatLiteral(result);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* indexOf(int, int, int, bool, bool, bool) const {
    throw std::string("Unsupported Type");
  }

  virtual const Literal* operator==(const Literal& rhs) const {
    return rhs.compEqEq(val);
  }
  virtual const Literal* compEqEq(int) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compEqEq(float lhs) const {
    int decision = lhs == val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compEqEq(const std::string&) const {
    throw std::string("Operation not supported");
  }

  virtual const Literal* operator!=(const Literal& rhs) const {
    return rhs.compNotEq(val);
  }
  virtual const Literal* compNotEq(int) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compNotEq(float lhs) const {
    int decision = lhs != val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compNotEq(const std::string&) const {
    throw std::string("Operation not supported");
  }

  virtual const Literal* operator>(const Literal& rhs) const {
    return rhs.compGreater(val);
  }
  virtual const Literal* compGreater(int) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compGreater(float lhs) const {
    int decision = lhs > val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compGreater(const std::string&) const {
    throw std::string("Operation not supported");
  }

  virtual const Literal* operator>=(const Literal& rhs) const {
    return rhs.compGreaterEq(val);
  }
  virtual const Literal* compGreaterEq(int) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compGreaterEq(float lhs) const {
    int decision = lhs >= val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compGreaterEq(const std::string&) const {
    throw std::string("Operation not supported");
  }

  virtual const Literal* operator<(const Literal& rhs) const {
    return rhs.compLess(val);
  }
  virtual const Literal* compLess(int) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compLess(float lhs) const {
    int decision = lhs < val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compLess(const std::string&) const {
    throw std::string("Operation not supported");
  }

  virtual const Literal* operator<=(const Literal& rhs) const {
    return rhs.compLessEq(val);
  }
  virtual const Literal* compLessEq(int) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compLessEq(float lhs) const {
    int decision = lhs <= val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compLessEq(const std::string&) const {
    throw std::string("Operation not supported");
  }

  // exclusive methods
  bool isTrue() const {
    if (val == 0 || val == 0.0) {
      return false;
    }
    return true;
  }
  // Custom operations - END

  virtual const Literal* eval() const { return this; }
  virtual void print() const {
    std::cout << "FLOAT: " << val << std::endl;
  }
private:
  float val;
};
/// ##################### End of FLOAT literal ############################//

// ############### Start of String Literal #############################
class StringLiteral : public Literal {
  public:
    StringLiteral(const std::string _val): val(_val) {}
    // ------------------ Methods for string concat ---------------------
    // ------------- requires lhs and rhs to be string literals ---------
    virtual const Literal* operator+(const Literal& rhs) const {
      return rhs.opPlus(val);
    }
    virtual const Literal* opPlus(float) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opPlus(int) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opPlus(const std::string& lhs) const {
      const Literal* node = new StringLiteral(lhs + val);
      PoolOfNodes::getInstance().add(node);
      return node;
    }

    // For string multiplication, a string and an int are needed
    // Here, we will handle the int * str case
    virtual const Literal* operator*(const Literal& rhs) const {
      return rhs.opMult(val);
    }
    virtual const Literal* opMult(float) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opMult(int times) const {
      std::string result("");
      const std::string multiply(val);
      for (int i = 0; i < times; i++) {
        result = result + multiply;
      }
      const Literal* node = new StringLiteral(result);
      PoolOfNodes::getInstance().add(node);
      return node;
    }

    virtual const Literal* operator-(const Literal&) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opSubt(float) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opSubt(int) const  {
      throw std::string("Operation not supported on types");
    }

    virtual const Literal* operator/(const Literal&) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opDiv(float) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opDiv(int) const {
      throw std::string("Operation not supported on types");
    }

    virtual const Literal* floorDivide(const Literal&) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opFloorDiv(float) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opFloorDiv(int) const {
      throw std::string("Operation not supported on types");
    }

    virtual const Literal* operator%(const Literal&) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opMod(float) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opMod(int) const {
      throw std::string("Operation not supported on types");
    }

    virtual const Literal* raiseTo(const Literal&) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opPower(float) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* opPower(int) const {
      throw std::string("Operation not supported on types");
    }
    virtual const Literal* indexOf(int start, int end, int step, bool hasColon,
    bool shouldUseStrLen, bool isStartIndexEmpty) const {
      const Literal* result;
      bool shouldReverseString = false;
      int len = val.length();

      const Literal* emptyStringLiteral = new StringLiteral("");
      PoolOfNodes::getInstance().add(emptyStringLiteral);

      if (hasColon) {
        // ---------------------------------------------------------------------
        // ++++++++++++++++++++++ COMPLEX INDEXING =+++++++++++++++++++++++++++++
        // ---------------------------------------------------------------------

        // Start and End Bound Check
        // If start > len of string, there should be no errors thrown
        // Result is an empty string
        // if end > len of string, end = len of str
        // That is the exact behaviour of c++'s substr method

        // ===================== Update - Step ===============================
        // Python slice includes a third optional parameter for stepping up characters
        // Note: This has nothing to do with the normal indexing as it would be handled
        // in the else part since hasColon will not be set
        // There can be three cases now :
        // Step can be either : empty (in which case it defaults to 1)
        // positive, negative(in which case both start and end has to be empty)
        // 0 in which case, we should throw an error

        // First case: if step is zero, throw an error
        if (step == 0) {
          throw std::string("slice step cannot be zero");
        }

        if (step < 0) {
          // Second case, use negative indexing only if start and end indices
          // are empty
          if (isStartIndexEmpty && shouldUseStrLen) {
            shouldReverseString = true;
            step = abs(step);
          } else {
            // return empty string
            return emptyStringLiteral;
          }
        }

        if (start > (len - 1)) {
          return emptyStringLiteral;
        }
        // ======== Negative indices handling - START ============
        if (start < 0) {
          // will get the equivalent 0 based index
          start = start + len;
          // If start is still negative, threshold it at 0
          if (start < 0) {
            start = 0;
          }
        }
        if (end < 0) {
          // will get the equivalent 0 based index
          end = end + len;
          // If end is still negative, return empty string
          if (end < 0) {
            return emptyStringLiteral;
          }
        }
        // Override if shouldUseStrLen is set
        if (shouldUseStrLen) {
          end = len;
        }
        // C++ substr behaves differently than that of Python's slice :(
          // subst(start, npos) npos = number of chars to include after start
          // TODO : REVIEW end - start condition
          // npos = end - start
        const int nPos = end - start;

        // Indexing should have start <= end
        if (start > end) {
          return emptyStringLiteral;
        }

        // ======== Negative indices handling - END ============
        std::string indexed(val.substr(start, nPos));
        std::string stepIndexed("");
        // Special case : Reversing
        // if shouldReverseString is set, it means that start and end are not given
        // which is the complete string
        if (shouldReverseString) {
          std::reverse(indexed.begin(), indexed.end());
        }
        // Now Handle the step parameter
        // step = 0 is already handled. So step can now be >= 1
        // if step is 1, the result is same as that of indexed
        // Else, starting from the first character
        if (step > 1) {
          for (unsigned int i = 0; i < indexed.length(); i+=(step) ) {
            stepIndexed += indexed[i];
          }
          result = new StringLiteral(stepIndexed);
        } else {
          result = new StringLiteral(indexed);
        }

      } else {

        // ---------------------------------------------------------------------
        // ++++++++++++++++++++++ SIMPLE INDEXING =+++++++++++++++++++++++++++++
        // ---------------------------------------------------------------------

        // Python supports negative indexing :(. But Why ??
        if (start < 0) {
          // will get the equivalent 0 based index
          start = start + len;
        }
        // if len is the length of the string to be indexed, start can be 0 to len - 1
        if (start < 0 || start > (len - 1)) {
          throw std::string("Index Out Of Range");
        }
        std::string indexed(1, val[start]);
        result = new StringLiteral(indexed);
      }
      PoolOfNodes::getInstance().add(result);
      return result;
    }

    virtual const Literal* operator==(const Literal& rhs) const {
      return rhs.compEqEq(val);
    }
    virtual const Literal* compEqEq(int) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compEqEq(float) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compEqEq(const std::string& lhs) const {
      int decision = lhs == val;
      const Literal* node = new FloatLiteral(decision);
      PoolOfNodes::getInstance().add(node);
      return node;
    }

    virtual const Literal* operator!=(const Literal& rhs) const {
      return rhs.compNotEq(val);
    }
    virtual const Literal* compNotEq(int) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compNotEq(float) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compNotEq(const std::string& lhs) const {
      int decision = lhs != val;
      const Literal* node = new FloatLiteral(decision);
      PoolOfNodes::getInstance().add(node);
      return node;
    }

    virtual const Literal* operator>(const Literal& rhs) const {
      return rhs.compGreater(val);
    }
    virtual const Literal* compGreater(int) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compGreater(float) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compGreater(const std::string& lhs) const {
      int decision = lhs > val;
      const Literal* node = new FloatLiteral(decision);
      PoolOfNodes::getInstance().add(node);
      return node;
    }

    virtual const Literal* operator>=(const Literal& rhs) const {
      return rhs.compGreaterEq(val);
    }
    virtual const Literal* compGreaterEq(int) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compGreaterEq(float) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compGreaterEq(const std::string& lhs) const {
      int decision = lhs >= val;
      const Literal* node = new FloatLiteral(decision);
      PoolOfNodes::getInstance().add(node);
      return node;
    }

    virtual const Literal* operator<(const Literal& rhs) const {
      return rhs.compLess(val);
    }
    virtual const Literal* compLess(int) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compLess(float) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compLess(const std::string& lhs) const {
      int decision = lhs < val;
      const Literal* node = new FloatLiteral(decision);
      PoolOfNodes::getInstance().add(node);
      return node;
    }

    virtual const Literal* operator<=(const Literal& rhs) const {
      return rhs.compLessEq(val);
    }
    virtual const Literal* compLessEq(int) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compLessEq(float) const {
      throw std::string("Operation not supported");
    }
    virtual const Literal* compLessEq(const std::string& lhs) const {
      int decision = lhs <= val;
      const Literal* node = new FloatLiteral(decision);
      PoolOfNodes::getInstance().add(node);
      return node;
    }

    virtual const Literal* eval() const {
      return this;
    }
    virtual void print() const {
      std::cout << "STR: " << val << std::endl;
    }
  private:
    std::string val;
};

// ############### End of String Literal #############################



/// ##################### Start of INT literal ############################//

class IntLiteral: public Literal {
public:
 IntLiteral(int _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(float lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<float>(val) + lhs);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(int lhs) const  {
    const Literal* node = new IntLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new IntLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new IntLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(const std::string& lhs) const  {
    std::string result("");
    const std::string multiply(lhs);
    for (int i = 0; i < val; i++) {
      result = result + multiply;
    }
    const Literal* node = new StringLiteral(result);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(float lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new IntLiteral(int(floor(float(lhs) / val)));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  // Custom operations - BEGIN
  // Rules for Floor Division
  // Div gives true division for floats and div2 is floor division for floats
  // Eg. >>> 17.0 / 2
  // 8.5
  // >>> 17.0 / 2.0
  // 8.5
  // >>> 17.0 // 2
  // 8.0
  // >>> 17.0 // 2.0
  // 8.0
  virtual const Literal* floorDivide(const Literal& rhs) const {
    return rhs.opFloorDiv(val);
  }
  virtual const Literal* opFloorDiv(float lhs) const {
    // std::cout << "FLOAT BY INT" << std::endl;
    if ( val == 0 ) throw std::string("Zero Division Error");
    // Here lhs is a float value
    // val is an integer (float / int) = float but with a point 0 (i.e loose precision)
    int result = int(lhs / val);
    const Literal* node = new FloatLiteral(float(result));
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opFloorDiv(int lhs) const {
    // std::cout << "INT BY INT" << std::endl;
    if ( val == 0 ) throw std::string("Zero Division Error");
    // Here lhs is a int value
    // val is an integer (int / int) = gives an int
    const Literal* node = new IntLiteral(int(floor(float(lhs) / val)));
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator%(const Literal& rhs) const {
    return rhs.opMod(val);
  }
  virtual const Literal* opMod(float lhs) const  {
    // Here val is an int
    // lhs is a float
    // Anything mod to float should be a float as well
    if ( val == 0 ) throw std::string("Zero Division Error");
    // std::cout << "Mod float, int" << std::endl;
    float result = float(fmod(lhs, val));
    // std::cout<<"Your reseult result is " << float(fmod(lhs, val)) << std::endl;
    const Literal* node = new FloatLiteral(result);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMod(int lhs) const  {
    // Here val is an int
    // lhs is an int
    // int mod int should be an int as well
    if ( val == 0 ) throw std::string("Zero Division Error");
    // std::cout << "Mod int, int" << std::endl;
    const Literal* node = new IntLiteral(lhs % val);
    PoolOfNodes::getInstance().add(node);
    if ( val == 0 ) throw std::string("Zero Division Error");
    return node;
  }

  virtual const Literal* raiseTo(const Literal& rhs) const {
    return rhs.opPower(val);
  }
  virtual const Literal* opPower(float lhs) const {
    // std::cout << "FLOAT TO INT" << std::endl;
    // Here lhs is a float value
    // val is an integer (float ^ int) = float
    float result = std::pow(lhs, val);
    const Literal* node = new FloatLiteral(result);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPower(int lhs) const {
    // std::cout << "INT TO INT" << std::endl;
    // Here lhs is a int value
    // val is an integer (int ^ int) = gives an int
    // Edge case: int ^ -int = can give a float
    // Eg. : 2 ** -1 = 0.5
    const Literal* node;
    if (val < 0) {
      float result = std::pow(lhs, val);
      node = new FloatLiteral(result);
    } else {
      int result = std::pow(lhs, val);
      node = new IntLiteral(result);
    }
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* indexOf(int, int, int, bool, bool, bool) const {
    throw std::string("Unsupported Type");
  }
  virtual const Literal* operator== (const Literal& rhs) const {
    return rhs.compEqEq(val);
  }
  virtual const Literal* compEqEq(int lhs) const {
    int decision = lhs == val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compEqEq(float) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compEqEq(const std::string&) const {
    throw std::string("Operation not supported");
  }

  virtual const Literal* operator!=(const Literal& rhs) const {
    return rhs.compNotEq(val);
  }
  virtual const Literal* compNotEq(int lhs) const {
    int decision = lhs != val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compNotEq(float) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compNotEq(const std::string&) const {
    throw std::string("Operation not supported");
  }


  virtual const Literal* operator>(const Literal& rhs) const {
    return rhs.compGreater(val);
  }
  virtual const Literal* compGreater(int lhs) const {
    int decision = lhs > val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compGreater(float) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compGreater(const std::string&) const {
    throw std::string("Operation not supported");
  }

  virtual const Literal* operator>=(const Literal& rhs) const {
    return rhs.compGreaterEq(val);
  }
  virtual const Literal* compGreaterEq(int lhs) const {
    int decision = lhs >= val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compGreaterEq(float) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compGreaterEq(const std::string&) const {
    throw std::string("Operation not supported");
  }

  virtual const Literal* operator<(const Literal& rhs) const {
    return rhs.compLess(val);
  }
  virtual const Literal* compLess(int lhs) const {
    int decision = lhs < val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compLess(float) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compLess(const std::string&) const {
    throw std::string("Operation not supported");
  }

  virtual const Literal* operator<=(const Literal& rhs) const {
    return rhs.compLessEq(val);
  }
  virtual const Literal* compLessEq(int lhs) const {
    int decision = lhs <= val;
    const Literal* node = new FloatLiteral(decision);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* compLessEq(float) const {
    throw std::string("Operation not supported");
  }
  virtual const Literal* compLessEq(const std::string&) const {
    throw std::string("Operation not supported");
  }
  // Custom operations - END

  virtual const Literal* eval() const { return this; }
  virtual void print() const {
    std::cout << "INT: " << val << std::endl;
  }
  // ======================= INT Only Methods ============================
  int getIntValue() const {
    return val;
  }
private:
  int val;
};
/// ##################### End of INT literal ############################//
