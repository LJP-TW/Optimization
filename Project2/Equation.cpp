#include <vector>
#include <stack>
#include <sstream>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Equation.h"

// #define IS_INIT !termF
#define IS_INIT true

#define isNum(x) ('0' <= x && x <= '9')
#define isAlphabet(x) ('A' <= x && x <= 'Z' || 'a' <= x && x <= 'z')

#define MAX_OP_LENGTH 3
#define isSign(x) (x == "+" || x == "-")
#define isTF(x) (x == "sin" || x == "cos" || x == "tan" || x == "cot" || x == "sec" || x == "csc")
#define isExp(x) (x == "^")
#define isMul(x) (x == "*")
#define isDiv(x) (x == "/")
#define isAdd(x) (x == "@")
#define isSub(x) (x == "#")
#define isPar(x) (x == "(" || x == ")")
#define is1OP(x) (isSign(x) || isExp(x) || isMul(x) || \
                isDiv(x) || isAdd(x) || isSub(x) || isPar(x))
#define is3OP(x) (isTF(x))
#define isOP(x) (is1OP(x[0]) || is3OP(x[2]))
#define isUnaryOP(x) (isSign(x[0]) || isTF(x[2]))

// Theoretically, h is infinitesimal
// According to IEEE-754, the machine code of smallest number of double is 0x0010000000000001
// unsigned long long int _DIFF_H_BIT_CODE = 0x0018000000000000;
// #define DIFF_H *(double*)&_DIFF_H_BIT_CODE;
constexpr double DIFF_H = 1e-3;
constexpr double DIFF_H_I = 1e3;

// Golden Section Search, 2-(1+sqrt(5))/2
constexpr double GSS_W = 0.38196601125;
constexpr double THRESHOLD = 1E-12;


enum
{
    PARENTHESES_TOP,
    PARENTHESES_NEW_RIGHT,
    ADDSUB,
    MULDIV,
    EXP,
    TF,
    SIGN,
    PARENTHESES_NEW_LEFT,
};

using namespace std;

Equation::Equation() : strF(""), postfixF(""), varTab(map<char, int>())
{
}

Equation::Equation(string f) : varTab(map<char, int>())
{
    try
    {
        this->setString(f);
    }
    catch (...)
    {
        throw;
    }
}

void Equation::setString(string equation)
{
    try
    {
        this->strF = equation;
        this->formatedF = this->formattingString();
        this->postfixF = this->infixToPostfix();
    }
    catch (...)
    {
        throw;
    }
}

double Equation::evalue(Vector x)
{
    if (!IS_INIT)
    {
        return 0.0;
    }

    stack<double> num;
    stringstream ss(this->postfixF);
    string temp;

    try
    {
        while (ss >> temp)
        {
            if (is1OP(temp))
            {
                double t = num.top();
                num.pop();

                if (temp == "-")
                {
                    t = -t;
                }
                else if (temp == "^")
                {
                    double t2 = num.top();
                    num.pop();

                    t = pow(t2, t);
                }
                else if (temp == "*")
                {
                    double t2 = num.top();
                    num.pop();

                    t = t2 * t;
                }
                else if (temp == "/")
                {
                    double t2 = num.top();
                    num.pop();

                    t = t2 / t;
                }
                else if (temp == "@")
                {
                    double t2 = num.top();
                    num.pop();

                    t = t2 + t;
                }
                else if (temp == "#")
                {
                    double t2 = num.top();
                    num.pop();

                    t = t2 - t;
                }

                num.push(t);
            }
            else if (is3OP(temp))
            {
                // isTF
                double t = num.top();
                num.pop();

                if (temp == "sin")
                    t = sin(t);
                else if (temp == "cos")
                    t = cos(t);
                else if (temp == "tan")
                    t = tan(t);
                else if (temp == "cot")
                    t = 1 / tan(t);
                else if (temp == "sec")
                    t = 1 / cos(t);
                else if (temp == "csc")
                    t = 1 / sin(t);

                num.push(t);
            }
            else if (isNum(temp[0]))
            {
                // string to double
                stringstream tss(temp);
                double td;

                tss >> td;

                num.push(td);
            }
            else if (isAlphabet(temp[0]))
            {
                // Find the corresponding vector index
                // The corresponding vector index is search->second
                auto search = this->varTab.find(temp[0]);

                if (search == this->varTab.end() || x.Data.size() <= search->second)
                    throw EQUATION_ERROR::FORMAT_ERROR;

                num.push(x.Data[search->second]);
            }
            else
            {
                throw EQUATION_ERROR::FORMAT_ERROR;
            }
        }

        if (num.size() != 1)
        {
            throw EQUATION_ERROR::FORMAT_ERROR;
        }

        return num.top();
    }
    catch (...)
    {
        throw;
    }
}

double Equation::getMinima(Vector init, Vector rangeLeft, Vector rangeRight, Vector direction)
{
    if (!IS_INIT)
    {
        return 0.0;
    }
    
    Vector leftV, rightV, innerV_l, innerV_r, tempV;
    double leftD, rightD, innerD_l, innerD_r, tempD;

    // Infinity
    tempD = -1E128;

    // Initial left point
    tempV = rangeLeft - init;
    for (int i = 0; i < tempV.Data.size(); ++i)
    {
        // if (direction.Data[i] != 0 && tempV.Data[i] / direction.Data[i] < tempD)
        //     tempD = tempV.Data[i] / direction.Data[i];

        if (direction.Data[i] != 0)
        {
            if ((tempD == -1E128)
                || (direction.Data[i] > 0 && tempV.Data[i] / direction.Data[i] > tempD)
                || (direction.Data[i] < 0 && tempV.Data[i] / direction.Data[i] < tempD))
                tempD = tempV.Data[i] / direction.Data[i];
        }
    }

    leftV = init + Vector(tempD) * direction;
    leftD = this->evalue(leftV);

    // Infinity
    tempD = 1E128;

    // Initial right point
    tempV = rangeRight - init;
    for (int i = 0; i < tempV.Data.size(); ++i)
    {
        // if (direction.Data[i] != 0 && tempV.Data[i] / direction.Data[i] < tempD)
        //    tempD = tempV.Data[i] / direction.Data[i];

        if (direction.Data[i] != 0)
        {
            if ((tempD == 1E128)
                || (direction.Data[i] > 0 && tempV.Data[i] / direction.Data[i] < tempD)
                || (direction.Data[i] < 0 && tempV.Data[i] / direction.Data[i] > tempD))
                tempD = tempV.Data[i] / direction.Data[i];
        }
    }

    rightV = init + Vector(tempD) * direction;
    rightD = this->evalue(rightV);

    tempD = this->evalue(init);

    if (tempD > rightD || tempD > leftD)
    {
        // throw EQUATION_ERROR::FORMAT_ERROR;
#ifdef _DEBUG
        cout << "以下區間非單峰!" << endl;
        cout << "left range  : " << rangeLeft.output() << endl;
        cout << "right range : " << rangeRight.output() << endl;
#endif
    }

    // Inital Inner
    if ((rightV - init).norm() > (init - leftV).norm())
    {
        innerV_l = init;
        innerV_r = innerV_l + Vector(GSS_W) * (rightV - init);

        innerD_l = this->evalue(innerV_l);
        innerD_r = this->evalue(innerV_r);
    }
    else
    {
        innerV_r = init;
        innerV_l = innerV_r - Vector(GSS_W) * (init - leftV);

        innerD_l = this->evalue(innerV_l);
        innerD_r = this->evalue(innerV_r);
    }
    
    while (abs(innerD_l - innerD_r) > THRESHOLD)
    {
        if (innerD_l < innerD_r)
        {
            rightV = innerV_r;
            rightD = innerD_r;

            innerV_r = innerV_l;
            innerD_r = innerD_l;

            innerV_l = innerV_r - Vector(GSS_W) * (innerV_r - leftV);
            innerD_l = this->evalue(innerV_l);
        }
        else
        {
            leftV = innerV_l;
            leftD = innerD_l;

            innerV_l = innerV_r;
            innerD_l = innerD_r;

            innerV_r = innerV_l + Vector(GSS_W) * (rightV - innerV_l);
            innerD_r = this->evalue(innerV_r);
        }
    }

    tempV = innerV_l - init;

    // Infinity
    tempD = 1E128;

    for (int i = 0; i < tempV.Data.size(); ++i)
    {
        if (direction.Data[i] != 0)
        {
            tempD = tempV.Data[i] / direction.Data[i];
            break;
        }
    }

    return tempD;
}

double Equation::diff(Vector x, Vector order)
{
    if (!IS_INIT)
    {
        return 0.0;
    }
    
    int nowOrder;

    for (nowOrder = order.Data.size() - 1; nowOrder >= 0 && order.Data[nowOrder] <= 0; --nowOrder) {}

    if (nowOrder >= 0)
    {
        Vector y = x;
        Vector nextOrder = order;

        x.Data[nowOrder] += DIFF_H;
        y.Data[nowOrder] -= DIFF_H;
        --nextOrder.Data[nowOrder];

#ifdef _DEBUG
        double debug = (this->diff(x, nextOrder) - this->diff(y, nextOrder)) * 0.5 * DIFF_H_I;
        return debug;
#endif

        return (this->diff(x, nextOrder) - this->diff(y, nextOrder)) * 0.5 * DIFF_H_I;
    }
    else 
    {
#ifdef _DEBUG
        double debug = this->evalue(x);
        return debug;
#endif
        return this->evalue(x);
    }
}

Vector Equation::getGradient(Vector x)
{
    Vector result;
    vector<Vector> firstOrders;

    // Initial firstOrders
    for (int i = 0; i < x.size(); ++i)
    {
        firstOrders.push_back(Vector());
    }

    for (int i = 0; i < firstOrders.size(); ++i)
    {
        for (int j = 0; j < firstOrders.size(); ++j)
        {
            if (i == j)
                firstOrders[i].push_back(1);
            else
                firstOrders[i].push_back(0);
        }
    }

    // Compute first order at x with respect to every variable
    for (int i = 0; i < firstOrders.size(); ++i)
    {
#ifdef _DEBUG
        double debug = diff(x, firstOrders[i]);
        result.push_back(debug);
#else
        result.push_back(diff(x, firstOrders[i]));
#endif
    }

    return result;
}

Matrix Equation::getHessian(Vector x)
{
    Matrix result;
    vector<vector<Vector>> secondOrders;

    // Initial result
    for (int i = 0; i < x.size(); ++i)
    {
        result.Data.push_back(vector<double>(x.size(), 0));
    }

    // Initial secondOrders
    for (int i = 0; i < x.size(); ++i)
    {
        vector<Vector> temp;

        for (int j = 0; j <= i; ++j)
        {
            Vector v;
            v.Data = vector<double>(x.size(), 0);

            for (int k = 0; k < v.size(); ++k)
            {
                if (k == i)
                    ++v[k];
                if (k == j)
                    ++v[k];
            }

            temp.push_back(v);
        }

        secondOrders.push_back(temp);
    }

    // Compute second order at x with respect to every variable
    for (int i = 0; i < x.size(); ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            result.Data[i][j] = this->diff(x, secondOrders[i][j]);

            if (i != j)
            {
                result.Data[j][i] = result.Data[i][j];
            }
        }
    }

    return result;
}

/*
 * Phase 1
 * Do formatting for multiplication between Number and Variable
 * Replacing + / -(addition / substration) by @/# to make difference between positive / nagetive and addition / substration
 *  2xy => 2*x*y
 *  -x+y => -x@y
 *  3 2 + 4 => 32+4
 *  sin(2x)*cos(3x) => sin(2*x)*cos(3*x)
 *  *2 => Error
 */
static inline string _formattingString(string target)
{
    string result = std::string();
    // Working on i-th char of this->strF
    unsigned int i = 0;
    // Parenthese Pair Count
    int pc = 0;
    // Some flag that judge here i-th char of this->strF need to add a multiplication sign
    bool isNum = false;
    bool isAlphabet = false;
    bool isPoint = false;
    // is Right Parentheses
    bool isRP = false;

    for (; i < target.size(); ++i)
    {
        if (target[i] == ' ')
            continue;

        string substr[MAX_OP_LENGTH];
        substr[0] = target[i];
        for (int j = 1; j < MAX_OP_LENGTH && i + j < target.size(); ++j)
        {
            substr[j] = substr[j - 1] + target[i + j];
        }

        if (isPoint)
        {
            isPoint = false;
            if (!isNum(target[i]))
            {
                throw EQUATION_ERROR::FORMAT_ERROR;
            }
        }
        else if (isNum)
        {
            if (is1OP(substr[0]))
            {
                isNum = false;
                if (target[i] == '+' || target[i] == '-')
                {
                    result += (target[i] == '+' ? '@' : '#');
                    continue;
                }
                else if (target[i] == '@' || target[i] == '#')
                {
                    throw EQUATION_ERROR::FORMAT_ERROR;
                }
                else if (target[i] == '(')
                {
                    pc += 1;
                    result += '*';
                }
                else if (target[i] == ')')
                {
                    if (--pc < 0)
                    {
                        throw EQUATION_ERROR::FORMAT_ERROR;
                    }
                    isRP = true;
                }
            }
            else if (is3OP(substr[2]))
            {
                // isTF
                isNum = false;
                result += '*';
                result += substr[2];
                i += 2;
                continue;
            }
            else if (isAlphabet(target[i]))
            {
                isNum = false;

                result += '*';

                isAlphabet = true;
            }
            else if (target[i] == '.')
            {
                isPoint = true;
            }
            else if (isNum(target[i]))
            {
                // Do nothing
            }
            else
            {
                throw EQUATION_ERROR::FORMAT_ERROR;
            }
        }
        else if (isAlphabet)
        {
            if (is1OP(substr[0]))
            {
                isAlphabet = false;
                if (target[i] == '+' || target[i] == '-')
                {
                    result += (target[i] == '+' ? '@' : '#');
                    continue;
                }
                else if (target[i] == '@' || target[i] == '#')
                {
                    throw EQUATION_ERROR::FORMAT_ERROR;
                }
                else if (target[i] == '(')
                {
                    pc += 1;
                    result += '*';
                }
                else if (target[i] == ')')
                {
                    if (--pc < 0)
                    {
                        throw EQUATION_ERROR::FORMAT_ERROR;
                    }
                    isRP = true;
                }
            }
            else if (is3OP(substr[2]))
            {
                // isTF
                isAlphabet = false;
                result += '*';
                result += substr[2];
                i += 2;
                continue;
            }
            else if (isNum(target[i]))
            {
                isAlphabet = false;

                result += '*';

                isNum = true;
            }
            else if (isAlphabet(target[i]))
            {
                result += '*';
            }
            else
            {
                throw EQUATION_ERROR::FORMAT_ERROR;
            }
        }
        else if (isRP)
        {
            if (is1OP(substr[0]))
            {
                isRP = false;
                if (target[i] == '+' || target[i] == '-')
                {
                    result += (target[i] == '+' ? '@' : '#');
                    continue;
                }
                else if (target[i] == '@' || target[i] == '#')
                {
                    throw EQUATION_ERROR::FORMAT_ERROR;
                }
                else if (target[i] == '(')
                {
                    pc += 1;
                    result += '*';
                }
                else if (target[i] == ')')
                {
                    if (--pc < 0)
                    {
                        throw EQUATION_ERROR::FORMAT_ERROR;
                    }
                    isRP = true;
                }
            }
            else if (is3OP(substr[2]))
            {
                // isTF
                isRP = false;
                result += '*';
                result += substr[2];
                i += 2;
                continue;
            }
            else if (isNum(target[i]))
            {
                isRP = false;

                result += '*';

                isNum = true;
            }
            else if (isAlphabet(target[i]))
            {
                isRP = false;

                result += '*';

                isAlphabet = true;
            }
            else
            {
                throw EQUATION_ERROR::FORMAT_ERROR;
            }
        }
        else
        {
            if (isUnaryOP(substr))
            {
                if (is1OP(substr[0]))
                {
                    if (target[i] == '@' || target[i] == '#')
                    {
                        throw EQUATION_ERROR::FORMAT_ERROR;
                    }
                }
                else if (is3OP(substr[2]))
                {
                    // isTF
                    result += substr[2];
                    i += 2;
                    continue;
                }
            }
            else if (isNum(target[i]))
            {
                isNum = true;
            }
            else if (isAlphabet(target[i]))
            {
                isAlphabet = true;
            }
            else if (target[i] == '(')
            {
                pc += 1;
            }
            else
            {
                throw EQUATION_ERROR::FORMAT_ERROR;
            }
        }

        result += target[i];
    }

    if (pc != 0)
        throw EQUATION_ERROR::FORMAT_ERROR;

    return result;
}

// Build varTab
static inline void __formattingString(string target, map<char, int>& varTab)
{
    // Working on i-th char of this->strF
    unsigned int i = 0;
    // The vector index that var name is mapped to
    int vi = 0;

    for (; i < target.size(); ++i)
    {
        if (target[i] == ' ')
            continue;

        string substr[MAX_OP_LENGTH];
        substr[0] = target[i];
        for (int j = 1; j < MAX_OP_LENGTH && i + j < target.size(); ++j)
        {
            substr[j] = substr[j - 1] + target[i + j];
        }

        if (is3OP(substr[2]))
        {
            // isTF
            i += 2;
            continue;
        }
        else if (isAlphabet(target[i]))
        {
            auto search = varTab.find(target[i]);
            if (search == varTab.end())
            {
                varTab[target[i]] = vi;
                ++vi;
            }
        }
    }
}

string Equation::formattingString()
{
    try 
    {
        string result = _formattingString(this->strF);

        if (this->varTab.size() == 0)
        {
            __formattingString(this->strF, this->varTab);
        }

        return result;
    }
    catch (...)
    {
        throw;
    }
}

// Helper function for Equation::infixToPostfix()
static inline int getPriority(string topS)
{
    /* Operator Priority:
     * +,-  : positive/negative sign
     * sin  : trigonometric function(cos, tan, ..., arcsin, arccos, ...)
     * ^    : exponential
     * *,/  : multiplication/division
     * +,-  : addition/substration
     * Special Case:
     * (,)  : parentheses
     */

    int topP;

    if (isSign(topS))
    {
        topP = SIGN;
    }
    else if (isTF(topS))
    {
        topP = TF;
    }
    else if (isExp(topS))
    {
        topP = EXP;
    }
    else if (isMul(topS) || isDiv(topS))
    {
        topP = MULDIV;
    }
    else if (isAdd(topS) || isSub(topS))
    {
        topP = ADDSUB;
    }
    else if (isPar(topS))
    {
        topP = PARENTHESES_TOP;
    }
    else
    {
        throw EQUATION_ERROR::FORMAT_ERROR;
    }

    return topP;
}

string Equation::infixToPostfix()
{    
    stack<string> op;
    string result;
    // Working on i-th char of this->formatedF
    unsigned int i = 0;
    bool isNum = true;
    
    try
    {
        for (; i < this->formatedF.size(); ++i)
        {
            string substr[MAX_OP_LENGTH];
            substr[0] = formatedF[i];
            for (int j = 1; j < MAX_OP_LENGTH && i + j < formatedF.size(); ++j)
            {
                substr[j] = substr[j - 1] + formatedF[i + j];
            }

            if (isOP(substr))
            {
                int newP;
                
                isNum = false;

                if (isSign(substr[0]))
                {
                    newP = SIGN;
                }
                else if (isTF(substr[2]))
                {
                    newP = TF;
                    i += 2;
                }
                else if (isExp(substr[0]))
                {
                    newP = EXP;
                }
                else if (isMul(substr[0]) || isDiv(substr[0]))
                {
                    newP = MULDIV;
                }
                else if (isAdd(substr[0]) || isSub(substr[0]))
                {
                    newP = ADDSUB;
                }
                else if (substr[0] == "(")
                {
                    newP = PARENTHESES_NEW_LEFT;
                }
                else if (substr[0] == ")")
                {
                    newP = PARENTHESES_NEW_RIGHT;
                }

                while (op.size() != 0 && newP <= getPriority(op.top()))
                {
                    result += ' ';
                    result += op.top();
                    op.pop();
                }

                // Match parentheses
                if (newP == PARENTHESES_NEW_RIGHT && op.size() != 0 && getPriority(op.top()) == PARENTHESES_TOP)
                {
                    op.pop();
                }
                else 
                {
                    if (is3OP(substr[2]))
                    {
                        op.push(substr[2]);
                    }
                    else if (is1OP(substr[0]))
                    {
                        op.push(substr[0]);
                    }
                }
            }
            else if (isNum(formatedF[i]))
            {
                if (isNum == false)
                    result += ' ';
                isNum = true;             
                result += formatedF[i];
            }
            else if (isNum && formatedF[i] == '.')
            {
                result += formatedF[i];
            }
            else if (isAlphabet(formatedF[i]))
            {
                isNum = false;
                result += ' ';
                result += formatedF[i];
            }
            else
            {
                throw EQUATION_ERROR::FORMAT_ERROR;
            }
        }
        while (op.size() != 0)
        {
            result += ' ';
            result += op.top();
            op.pop();
        }
    }
    catch (...)
    {
        throw;
    }

    if (result[0] == ' ')
        result.erase(result.begin());

    return result;
}