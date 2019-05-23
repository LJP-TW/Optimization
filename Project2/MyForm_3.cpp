#include <sstream>
#include <iomanip>
#include "MyForm.h"
constexpr double THRESHOLD = 1E-3;


using namespace Project2;
using namespace std;
//constexpr double THRESHOLD = 0.0000001;

stringstream oss2;

System::Void MyForm::Newton(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight)
{
	Matrix original(initial);
	Vector x = initial;
	Vector next_x;
	int N = initial.Data.size();
	Matrix gradient(equation.getGradient(initial));
	Matrix hessian = equation.getHessian(initial);
	Matrix inverse = hessian.inverse();
	Matrix next = original - (inverse*gradient);
	for (int y = 0;y < next.Data.size();y++)
	{
		for (unsigned int x = 0;x < next.Data[y].size();++x)
		{

			next_x.push_back(next.Data[y][x]);
		}
	}
		//output hessian
		oss2 << "Hessian" << hessian.output(6)<< endl;
		//output hessian inverse
		oss2<< "Hessian inverse" <<inverse.output(6)<< endl;
		//variable
		oss2 << "x" << next_x.output(6)<<endl;
		while (equation.evalue(next_x) != equation.evalue(next_x))
		{
			inverse = inverse * 0.9;
			next = original - (inverse*gradient);
			int i = 0;
			for (int y = 0;y < next.Data.size();y++)
			{
				for (unsigned int x = 0;x < next.Data[y].size();++x)
				{

					next_x[i]=next.Data[y][x];
					i++;
				}
			}
		}
		if (abs(equation.evalue(x)- equation.evalue(next_x))>THRESHOLD)
		{
			Newton(equation, next_x, rangeLeft, rangeRight);
		}
		else
		{ 
			double test = equation.evalue(next_x);//
			oss2 << "Vector X "<<next_x.output(6) << endl;
			oss2 << "min=[" << equation.evalue(next_x) << "]" << endl;
		}
		printToOutputTextBox(oss2);
		oss2.clear();
}

System::Void MyForm::ConjugateGradient(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight)
{
	Vector var = initial;//x
	
	Vector fix;
	fix.push_back(0.9);
	//beta.push_back(0);
	int count = 0;
	while (1)
	{
		Vector var_next;
		Vector S_old;
		Vector S;
		Vector beta;
		Matrix hessian;
		Vector alpha;
		count++;
		S_old = -equation.getGradient(var);
		hessian = equation.getHessian(var);
		Matrix d;
		Matrix d_temp;
		Vector d_ans;
		d.Data.push_back(S_old);
		d_temp = d*hessian;
		Vector temp;
		for (unsigned int i = 0;i < d_temp.Data[0].size();i++)
		{
			temp.push_back(d_temp.Data[0][i]);
		}
		d_ans = temp * S_old;
		Vector alphaUp = equation.getGradient(var)*S_old;
		Vector alphaDown;
		alphaDown.push_back(d_ans.Data[0]);
		alpha.push_back(-1 * (alphaUp[0] / alphaDown[0]));
		var_next = var + alpha * S_old;
		Vector check = equation.getGradient(var_next);
		bool flag = true;
		for (unsigned int i = 0;i < check.size();i++)
		{
			if (check[i] != check[i]) flag = false;
		}
		while (!flag)
		{
			alpha= alpha * fix;
			var_next = var + alpha * S_old;
			check = equation.getGradient(var_next);
			flag = true;
			for (unsigned int i = 0;i < check.size();i++)
			{
				if (check[i] != check[i]) flag = false;
			}
			//int i = 0;
			/*for (int y = 0;y < next.Data.size();y++)
			{
				for (unsigned int x = 0;x < next.Data[y].size();++x)
				{

					next_x[i] = next.Data[y][x];
					i++;
				}
			}*/
		}
		
		
		S = -equation.getGradient(var_next);//next
		/*Matrix b;
		Matrix b_temp;
		Matrix b_ans;
		b.Data.push_back(S_old);
		b = b * hessian;
		b = b * S_old;*/
		Vector betaUp = equation.getGradient(var_next)*S_old;
		Vector betaDown=alphaDown;
		//betaDown.push_back(b.Data[0][0]);
		beta.push_back(-1 * (betaUp[0] / betaDown[0]));
		/*if (count == 1)
		{
			S = -equation.getGradient(initial);		//𝑆_𝑖=−𝛻𝑓(𝑋_𝑖 )
		}
		else
		{
			S_old = S;
			S = -equation.getGradient(var);
			hessian = equation.getHessian(initial);
			beta[0]=(S*S)[0] / (S_old*S_old)[0]; // β=(𝛻𝑓(𝑋_𝑖 )^𝑇 𝛻𝑓(𝑋_𝑖 )) / (𝛻𝑓(𝑋_(𝑖−1) )^𝑇 𝛻𝑓(𝑋_(𝑖−1) ) )
			S = S + beta * S_old;
		}
		
		
		//alpha = equation.getMinima(var, rangeLeft, rangeRight, S);
		
		*/
		for (unsigned int i = 0;i < var.size();++i)
		{
			if (var_next[i] < rangeLeft[i]) var_next[i] = rangeLeft[i];
			if (var_next[i] > rangeRight[i]) var_next[i] = rangeRight[i];
		}

		oss2 << "i=" << count - 1 << endl;
		if (count != 1)
		{
			oss2 << "beta=" << beta.output(6) << endl;
		}
		oss2 << "Si=" << S.output(6)<< endl;
		oss2 << "alpha=" << alpha.output(6) << endl;
		oss2 << "Xi=" << var_next.output(6)<< endl;
		cout << "THRESHOLD= " << THRESHOLD << endl;
		if (abs(equation.evalue(var_next) - equation.evalue(var)) < THRESHOLD)
		{
			oss2 << "Vector X " << var_next.output(6) << endl;
			/*oss2 << "[x]=[";
			for (unsigned int i = 0;i < var_next.size();i++)
			{
				oss2 << var_next[i];
				if (i != var_next.size() - 1) oss2 << " ";
			}
			oss2 << "]" << endl;*/
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
	

