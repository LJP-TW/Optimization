#pragma once
#include <map>
#include "Matrix.h"

class Equation
{
public:
    /* Constructors */
    Equation();
    Equation(std::string);

    /* Access functions */
    void setString(std::string equation);    
    const std::string& get_strF() const { return strF; };
    int get_VarNum() const { return varTab.size(); };

    /* Member functions */
    // evalue f(x) using postfixF
    double evalue(Vector x);
    /*  Get the scalar A that f(init + A * direction) will have minima where
     *  init + A * direction between rangeLeft ~ rangeRight
     *  by using golden section search
     */
    double getMinima(Vector init, Vector rangeLeft, Vector rangeRight, Vector direction);
    /*  Partial differentiate this f(x), using numerical differential method
     *  IT IS VERY IMPRECISE AT HIGHER-ORDER DERIVATIVE !!!
     */
    double diff(Vector x, Vector order);
    // Get gradient of this function at x
    Vector getGradient(Vector x);
    // Get Hessian matrix at x
    Matrix getHessian(Vector x);
    
private:
    /* Helper Function */
    /*  Do formatting for multiplication
     *  Replacing +/- (addition/substration) by @/# to make difference between positive/nagetive and addition/substration
     *  2xy => 2*x*y
     *  2sinx => 2*sinx
     *  -x+y => -x@y
     *  3 2 + 4 => 32+4
     */
    std::string formattingString();
    // Original f(x) to postfix f(x)
    std::string infixToPostfix();

    /* Data members */
    // Original f(x)
    std::string strF;
    // Formated f(x)
    std::string formatedF;
    // Postfix f(x)
    std::string postfixF;
    // Variable Table, mapping var name to vector index
    std::map<char, int> varTab;
};

enum class EQUATION_ERROR
{
    FORMAT_ERROR, // The format of thisa equation cannot transfer to Terms
};