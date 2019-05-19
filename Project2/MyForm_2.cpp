#include <sstream>
#include <iomanip>
#include "MyForm.h"

constexpr double THRESHOLD = 1E-3;

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
    double a;
    Vector x = initial, tempX;
    Vector h = equation.getGradient(initial);

    while (abs(h.norm()) > THRESHOLD)
    {
        // Step 1. if f'(x[i]) = 0 stop else compute search direction h[i] = -f'(x[i])
        h = -h;

        // Step 2. compute the step-size a
        a = (h * h)[0] / (Matrix(h).trans() * equation.getHessian(x) * Matrix(h)).Data[0][0];
        
        tempX = x + Vector(a) * h;
        while (equation.evalue(tempX) != equation.evalue(tempX))
        {
            a *= 0.95;
            tempX = x + Vector(a) * h;
        }

        // Step 3. set x[i + 1] = x[i] + a * h[i], go to step 1.
        x = tempX;

        h = equation.getGradient(x);

        ++i;

        oss << "i = " << i - 1 << endl;
        oss << "h = " << h.output(6) << endl;
        oss << "lambda = " << fixed << setprecision(6) << a << endl;
        oss << "X = " << x.output(6) << endl;
        printToOutputTextBox(oss);
        oss.clear();
    }

    oss << "Vector x = " << x.output(8) << endl;
    oss << "min = " << fixed << setprecision(11) << equation.evalue(x) << endl;
    printToOutputTextBox(oss);
    oss.clear();
}

/*
System::Void MyForm::QuasiNewton(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight)
{
    // Set k = 0, x[0] = initial, F[0] = I
    int k = 0;
    Vector x = initial, g = equation.getGradient(initial), temp;
    Matrix H = equation.getHessian(initial);
    Matrix IH = H.inverse();
    double a;

    oss << "Initial Hessian : " << H.output(6) << endl;
    oss << "Initial Hessian Inverse : " << IH.output(6) << endl;
    printToOutputTextBox(oss);
    oss.clear();

    while (abs(g.norm()) > THRESHOLD)
    {
        // Step 1. Determine if method has converged using convergence criteria (gradient) 

        // Step 2. 
        // Calculate change in x
        // x[k + 1] = x[k] - IH[k] * g[k]
        temp.Data = (IH * g).trans().Data[0];
        x = x - temp;

        g = equation.getGradient(x);
        H = equation.getHessian(x);
        IH = H.inverse();

        oss << "x: " << x.output(6) << endl;
        oss << "Hessian : " << H.output(6) << endl;
        printToOutputTextBox(oss);
        oss.clear();
    }

    oss << "Vector x = " << x.output(8) << endl;
    oss << "min = " << fixed << setprecision(11) << equation.evalue(x) << endl;
    printToOutputTextBox(oss);
    oss.clear();
}
*/

// DFP
System::Void MyForm::QuasiNewton(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight)
{
    // Set k = 0, x[0] = initial, F[0] = I
    int k = 0;
    Vector x = initial, g = equation.getGradient(initial), d, dx, dg, temp;
    Matrix F, dx_r, dx_c, dg_r, dg_c;
    double a;

    // F(x) and F(x - 1)
    double e_now = equation.evalue(x);
    double e_pre = e_now - 1;

    for (int i = 0; i < initial.size(); ++i)
    {
        F.Data.push_back(vector<double>(initial.size(), 0));
        F.Data[i][i] = 1;
    }


    while (abs(e_now - e_pre) > THRESHOLD)
    {
        double tempD, step;

        e_pre = e_now;

        // Step 1. if g[k] = 0 stop, else d[k] = -F[k]g[k]
        d.Data = ((-F) * g).trans().Data[0];

        // Step 2. 
        // Find the value of a that minimizes f(x[k] + a[k] * d[k])
        // Set delta_x[k] = a[k] * d[k]
        // Set x[k + 1] = x[k] + a[k] * d[k]
        // Set delta_g[k] = g[k + 1] - g[k]
        step = a = 1;
        while ((tempD = equation.evalue(x + Vector(a) * d)) < e_now)
        {
            e_now = tempD;
            a += step;
        }
        while ((tempD = equation.evalue(x + Vector(a) * d)) - e_now > THRESHOLD || tempD != tempD)
        {
            a -= step;
            step *= 0.1;
            a += step;
            while ((tempD = equation.evalue(x + Vector(a) * d)) < e_now)
            {
                e_now = tempD;
                a += step;
            }
        }
        a -= step;

        dx = Vector(a) * d;
        x = x + dx;
        temp = g;
        g = equation.getGradient(x);
        dg = g - temp;

        // Step 3.
        // Set F[k + 1]
        dx_c = Matrix(dx);
        dx_r = dx_c.trans();
        dg_c = Matrix(dg);
        dg_r = dg_c.trans();
        F = F + (dx_c * dx_r) * (1 / (dx * dg)[0]) - (F * dg_c)*(F * dg_c).trans()*(1 / (dg_r * F * dg_c).Data[0][0]);

        // Step 4.
        // Set k = k + 1
        ++k;

        oss << "x: " << x.output(6) << endl;
        oss << "Inversed Hessian : " << endl << F.output(6) << endl;
        printToOutputTextBox(oss);
        oss.clear();
    }

    oss << "Vector x = " << x.output(8) << endl;
    oss << "min = " << fixed << setprecision(11) << equation.evalue(x) << endl;
    printToOutputTextBox(oss);
    oss.clear();
}
