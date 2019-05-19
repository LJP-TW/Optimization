#include <sstream>
#include <iomanip>
#include "MyForm.h"
//constexpr double THRESHOLD = 1E-6;


using namespace Project2;
using namespace std;
constexpr double THRESHOLD = 0.0000001;

stringstream oss2;

System::Void MyForm::Newton(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight)
{
	Matrix original (initial);
	Vector x = initial;
	Vector next_x;
	int N = initial.Data.size();
	Matrix gradient(equation.getGradient(initial));
	Matrix hessian=equation.getHessian(initial);
	Matrix inverse=hessian.inverse();
	Matrix next = original - (inverse*gradient);
	for (unsigned int y = 0;y < next.Data.size();++y)
	{
		for (unsigned int x=0;x < next.Data[y].size();++x)
		{
			next_x.push_back(next.Data[y][x]);
		}
	}
		//output hessian
		oss2 <<"Hessian"<<"\n"<< "[" << endl;

		for (unsigned int y = 0;y < hessian.Data.size();y++)
		{
			for (unsigned int x = 0;x < hessian.Data[y].size();x++)
			{
				oss2 << hessian.Data[y][x]<<" ";
			}
			oss2 << endl;
		}
		oss2 << "]" <<"\n"<< endl;
		//output hessian inverse
		oss2 << "Hessian inverse"<<"\n"<<"[" << endl;
		for (unsigned int y = 0;y <inverse.Data.size();y++)
		{
			for (unsigned int x = 0;x < inverse.Data[y].size();x++)
			{
				oss2 << inverse.Data[y][x]<<" ";
			}
			oss2 << endl;
		}
		oss2 <<"]" << "\n" << endl;
		//variable
		oss2 << "x" << "\n" << "["<<endl;
		for (unsigned int i = 0;i < next_x.size();i++)
		{
			oss2 << next_x[i]<<endl;
		}
		oss2 <<"]" << endl;
		
		if (abs(equation.evalue(x)-equation.evalue(next_x))>THRESHOLD)
		{
			oss2 << "=============================================" << endl;
			Newton(equation, next_x, rangeLeft, rangeRight);
		}
		else
		{ 
			double test = equation.evalue(next_x);//
			if (test)
			{
				oss2 << "\n"<<"[x]= [ ";
				for (unsigned int i = 0;i < next_x.size();i++)
				{
					oss2 << next_x[i];
					if (i != next_x.size() - 1) oss2 << " ";
				}
				oss2 << "]" << endl;
				oss2 << "min=[" << equation.evalue(next_x) << "]" << endl;
				oss2 << "=============================================" << endl;
			}
			else
			{
				oss2 << "[x]=非數值" << endl;
				oss2 << "[min]=非數值" << endl;
			}
		}
		printToOutputTextBox(oss2);
		oss2.clear();
}

System::Void MyForm::ConjugateGradient(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight)
{
	Vector var = initial;//x
	Vector var_next;
	Vector S_old;
	Vector S;
	Vector beta;
	beta.push_back(0);
	Vector alpha;
	int count = 0;
	while (1)
	{
		count++;
		if (count == 1)
		{
			S = -equation.getGradient(initial);		//𝑆_𝑖=−𝛻𝑓(𝑋_𝑖 )
		}
		else
		{
			S_old = S;
			S = -equation.getGradient(var);
			beta[0]=(S*S)[0] / (S_old*S_old)[0]; // β=(𝛻𝑓(𝑋_𝑖 )^𝑇 𝛻𝑓(𝑋_𝑖 )) / (𝛻𝑓(𝑋_(𝑖−1) )^𝑇 𝛻𝑓(𝑋_(𝑖−1) ) )
			S = S + beta * S_old;
		}
		alpha = equation.getMinima(var, rangeLeft, rangeRight, S);
		var_next = var + alpha * S;
		for (unsigned int i = 0;i < var.size();++i)
		{
			if (var_next[i] < rangeLeft[i]) var_next[i] = rangeLeft[i];
			if (var_next[i] > rangeRight[i]) var_next[i] = rangeRight[i];
		}

		oss2 << "i=" << count - 1 << endl;
		if (count != 1)
		{
			oss2 << "beta=" << beta[0] << endl;
		}
		oss2 << "Si=" << "\n" << "[" << endl;
		for (unsigned int i = 0;i < S.size();i++)
		{
			oss2 << S[i] << endl;
		}
		oss2 << "]" << endl;
		oss2 << "alpha=" << alpha[0] << endl;
		oss2 << "Xi=" << "\n" << "[" << endl;
		for (unsigned int i = 0;i < S.size();i++)
		{
			oss2 << var_next[i] << endl;
		}
		oss2 << "]" << endl;
		cout << "THRESHOLD= " << THRESHOLD << endl;
		oss2 << "=============================================" << endl;
		if (abs(equation.evalue(var_next) - equation.evalue(var)) < THRESHOLD)
		{
			oss2 << "[x]=[";
			for (unsigned int i = 0;i < var_next.size();i++)
			{
				oss2 << var_next[i];
				if (i != var_next.size() - 1) oss2 << " ";
			}
			oss2 << "]" << endl;
			oss2 << "min=" << equation.evalue(var_next) << endl;
			break;
		}
		else
		{
			var = var_next;
		}
	}
	printToOutputTextBox(oss2);
	oss2.clear();
}
	

