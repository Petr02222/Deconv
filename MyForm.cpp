#include "MyForm.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "FFF.h"
#include <iostream>
#include <vector>
#include <complex>

using namespace System;
using namespace System::Windows::Forms;


//[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Feinyp::MyForm form;
	Application::Run(% form);
}
int N;
struct cmplx* Signal1 = new struct cmplx[N];
struct cmplx* Signal = new struct cmplx[N];
System::Void Feinyp::MyForm::sgen_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->chart1->Series[0]->Points->Clear();
	this->chart2->Series[0]->Points->Clear();
	this->chart1->Series[1]->Points->Clear();
	this->chart1->Series[2]->Points->Clear();

	double A1 = 0; double A2 = 0; double A3 = 0;
	double E1 = 0; double E2 = 0; double E3 = 0;
	double Si1 = 0; double Si2 = 0; double Si3 = 0;  double Si4 = 0;
	double S1 = 0; double S2 = 0; double S3 = 0; double S = 0;
	


	A1 = System::Convert::ToDouble(a1->Text);
	A2 = System::Convert::ToDouble(a2->Text);
	A3 = System::Convert::ToDouble(a3->Text);

	Si1 = System::Convert::ToDouble(si1->Text);
	Si2 = System::Convert::ToDouble(si2->Text);
	Si3 = System::Convert::ToDouble(si3->Text);


	E1 = System::Convert::ToDouble(e1->Text);
	E2 = System::Convert::ToDouble(e2->Text);
	E3 = System::Convert::ToDouble(e3->Text);

	int N = System::Convert::ToInt32(n->Text);

	double* Spektr = new double[N];
	double* phasa = new double[N];
	for (int i = 0; i < N; i++)
	{


		S1 = A1 * exp(-((i - E1) * (i - E1)) / (2 * (Si1 * Si1)));
		S2 = A2 * exp(-((i - E2) * (i - E2)) / (2 * (Si2 * Si2)));
		S3 = A3 * exp(-((i - E3) * (i - E3)) / (2 * (Si3 * Si3)));




		S = S1 + S2 + S3;
		
		Signal[i].real = S;
		Signal[i].image = 0;

		this->chart1->Series[0]->Points->AddXY(i, S);

	}

	FFFF(Signal, N, 1);
	for (int i = 0; i < N; i++)
	{
		Spektr[i] = sqrt(Signal[i].real * Signal[i].real + Signal[i].image * Signal[i].image);
		this->chart2->Series[0]->Points->AddXY(i, Spektr[i]);
	}
	FFFF(Signal, N, -1);
	for (int i = 0; i < N; i++)
	{
		double fi_0 = 2. * M_PI * rand() / RAND_MAX - 0.5;
		Signal1[i].real = Spektr[i] * cos(fi_0);
		Signal1[i].image = Spektr[i] * sin(fi_0);
	}

	for (int j = 0; j < 10000; j++)
	{

		FFFF(Signal1, N, -1);
		for (int i = 0; i < N; i++)
		{
			if (Signal1[i].real >= 0)
			{
				Signal1[i].real = Signal1[i].real;
			}
			else
			{
				Signal1[i].real = 0;
				//Signal1[i].image = 0;
			}
			Signal1[i].image = 0;
		}
		FFFF(Signal1, N, 1);
		for (int i = 0; i < N; i++)
		{

			phasa[i] = atan2(Signal1[i].image, Signal1[i].real);
			Signal1[i].real = Spektr[i] * cos(phasa[i]);
			Signal1[i].image = Spektr[i] * sin(phasa[i]);
		}

	}

	FFFF(Signal1, N, -1);
	for (int i = 0; i < N; i++)
	{
		this->chart1->Series[1]->Points->AddXY(i, sqrt(Signal1[i].real * Signal1[i].real + Signal1[i].image * Signal1[i].image));
	}
	delete[] Spektr;
	delete[] phasa;
	double errr = otklonenie(Signal, Signal1, N);
	alfa->Text = errr.ToString();
	return System::Void();
}

System::Void Feinyp::MyForm::inv_Click(System::Object^ sender, System::EventArgs^ e)
{
	N = System::Convert::ToInt32(n->Text);
	this->chart1->Series[1]->Points->Clear();
	double temp=0;
	for (int i = 0; i < N; i++)
	{
		
		if (i < N / 2)
		{
			temp = Signal1[i].real;
			Signal1[i].real = Signal1[N - i - 1].real;
			Signal1[N - i - 1].real = temp;

		}

		this->chart1->Series[1]->Points->AddXY(i, Signal1[i].real);

	}
	double errr = otklonenie(Signal, Signal1, N);
	alfa->Text = errr.ToString();
	return System::Void();
}

System::Void Feinyp::MyForm::sdig_Click(System::Object^ sender, System::EventArgs^ e)
{
	N = System::Convert::ToInt32(n->Text);
	this->chart1->Series[1]->Points->Clear();
	//int p = 0;
	while (otklonenie(Signal, Signal1, N) > 6 /* && p<N + N / 2*/)
	{
		//p++;
		otklonenie(Signal, Signal1, N);
		sdvig(Signal1, N);
	}
	for (int k = 0; k < N; k++)
	{
		this->chart1->Series[2]->Points->AddXY(k, Signal[k].real);
	}
	for (int k = 0; k < N; k++)
	{
		this->chart1->Series[1]->Points->AddXY(k, Signal1[k].real);
	}
	double errr = otklonenie(Signal, Signal1, N);
	alfa->Text = errr.ToString();
	return System::Void();
}

System::Void Feinyp::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	N = System::Convert::ToInt32(n->Text);
	this->chart1->Series[1]->Points->Clear();
	if (otklonenie(Signal, Signal1, N) > 0.01)
	{
		otklonenie(Signal, Signal1, N);
		sdvig(Signal1, N);
	}
	for (int k = 0; k < N; k++)
	{

		this->chart1->Series[1]->Points->AddXY(k, Signal1[k].real);

	}
	double errr = otklonenie(Signal, Signal1, N);
	alfa->Text = errr.ToString();
	return System::Void();
}
