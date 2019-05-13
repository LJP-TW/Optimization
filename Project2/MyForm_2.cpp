#include <sstream>
#include <iomanip>
#include "MyForm.h"

constexpr double THRESHOLD = 1E-6;

using namespace Project2;
using namespace std;

// Output temp
stringstream oss;

System::Void MyForm::Powell(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight)
{
    int i = 0;
    Vector x = initial;
    int N = initial.Data.size();
    double min_a;

    // P0 ~ Pn
    // U1 ~ Un
    std::vector<Vector> P, U;
    for (int k = 0; k <= N; ++k)
    {
        P.push_back(Vector());
        U.push_back(Vector());
    }

    // Initial U
    for (int k = 1; k <= N; ++k)
    {
        for (int m = 1; m <= N; ++m)
        {
            if (m == k)
                U[k].Data.push_back(1);
            else
                U[k].Data.push_back(0);
        }
    }

    do
    {
        // Step 1.
        // Set P0 = xi
        P[0] = x;

        // Step 2.
        // For k = 1, 2, ..., N
        // Find the value of a that minimizes f(P[k - 1] + a * U[k])
        // Set P[k] = P[k - 1] + a * U[k]

        // Infinity
        min_a = 1E128;
        for (int k = 1; k <= N; ++k)
        {
            double a = equation.getMinima(P[k - 1], rangeLeft, rangeRight, U[k]);
            P[k] = P[k - 1] + Vector(a) * U[k];
            if (a < min_a)
                min_a = a;
        }

        // Step 3.
        // Set i = i + 1
        ++i;

        // Step 4.
        // Set U[k] = U[k + 1] for k = 1, 2, ..., N - 1
        // Set U[N] = P[N] - P[0]
        U[0] = U[N];
        for (int k = 1; k < N; ++k)
        {
            U[k] = U[k + 1];
        }
        U[N] = P[N] - P[0];

        // Step 5.
        // Find the value of a that minimizes f(P[0] + a * U[N])
        // Set xi = P[0] + a * U[N]
        double a = equation.getMinima(P[0], rangeLeft, rangeRight, U[N]);
        x = P[0] + Vector(a) * U[N];

        oss << "j = " << i - 1 << endl;
        oss << "x" << P[0].output(6) << endl;
        oss << "alpha:" << fixed << setprecision(6) << min_a << endl;
        oss << "s" << i << U[0].output(6) << endl;
        oss << "x" << x.output(6) << endl;
        oss << "s" << i + 1 << U[N].output(6) << endl;
        printToOutputTextBox(oss);
        oss.clear();

        // Step 6.
        // Repeat step 1. through 5.
    } while (abs((equation.evalue(x) - equation.evalue(P[0]))) > THRESHOLD || abs((x - P[0]).norm()) > THRESHOLD);
    
    oss << "Vector x = " << x.output(8) << endl;
    oss << "min = " << fixed << setprecision(11) << equation.evalue(x) << endl;
    printToOutputTextBox(oss);
    oss.clear();
}

System::Void MyForm::SteepDescent(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight)
{
    // set i = 0, x[0] = initial
    int i = 0;
    Vector x = initial;
    Vector h = equation.getGradient(initial);

    while (h.norm() > THRESHOLD)
    {
        // Step 1. if f'(x[i]) = 0 stop else compute search direction h[i] = -f'(x[i])
        h = -h;

        // Step 2. compute the step-size a


        // Step 3. set x[i + 1] = x[i] + a * h[i], go to step 1.
    }

    
}

System::Void MyForm::QuasiNewton(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight)
{
}
