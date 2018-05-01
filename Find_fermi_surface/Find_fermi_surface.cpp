#include "stdafx.h"
using namespace std;

int func(Ipp64f * argkz, Ipp64f * argCos, Ipp64f * argSin, Ipp64f *r, int length, Ipp64f *temp1, Ipp64f *temp2, Ipp64f *temp3, Ipp64f *out);
//int dfunc(Ipp64f * argkz, Ipp64f * argCos, Ipp64f * argSin, Ipp64f *r, int length, Ipp64f *temp1, Ipp64f *temp2, Ipp64f *out);

int _tmain(int argc, _TCHAR* argv[])
{

	DataExtractor extractor("start0.dat");

	Ipp64f * starts = extractor.getDataArray();
	int nPoints = floor((extractor.getNumberOfLines()) / 2);
	
	Ipp64f *temp1 = new Ipp64f[nPoints];
	Ipp64f *temp2 = new Ipp64f[nPoints];
	Ipp64f *temp3 = new Ipp64f[nPoints];
	Ipp64f *argCos = new Ipp64f[nPoints];
	Ipp64f *argSin = new Ipp64f[nPoints];
	Ipp64f *argkz = new Ipp64f[nPoints];
	Ipp64f *theta = new Ipp64f[nPoints];
	Ipp64f *kz = new Ipp64f[nPoints];
	Ipp64f *funcval = new Ipp64f[nPoints];
	Ipp64f *dfunc1 = new Ipp64f[nPoints];
	Ipp64f *dfunc2 = new Ipp64f[nPoints];
	Ipp64f *dfunc = new Ipp64f[nPoints];
	Ipp64f *r = new Ipp64f[nPoints];
	Ipp64f *rtemp = new Ipp64f[nPoints];

		for (int i = 0; i < nPoints; i++) 
		{
		/*cout << starts[2 * i] << " " << starts[2 * i + 1] << endl;*/
			theta[i] = starts[2 * i];
			kz[i] = starts[2 * i + 1];
			r[i] = 0.3;
		}

		for (int i = 0; i < 30; i++) 
		{
			vdSin(nPoints, theta, argSin);
			vdCos(nPoints, theta, argCos);
			ippsMulC_64f_I(3.74767, argSin, nPoints);
			ippsMulC_64f_I(3.74767, argCos, nPoints);
			ippsMulC_64f(kz, 3.3, argkz, nPoints);
			func(argkz, argCos, argSin, r, nPoints, temp1, temp2, temp3, funcval);

			ippsAddC_64f(r, 1E-5, rtemp, nPoints);
			func(argkz, argCos, argSin, rtemp, nPoints, temp1, temp2, temp3, dfunc1);
			ippsAddC_64f(r, -1E-5, rtemp, nPoints);
			func(argkz, argCos, argSin, rtemp, nPoints, temp1, temp2, temp3, dfunc2);
			ippsMulC_64f_I(-1, dfunc2, nPoints);
			ippsAdd_64f(dfunc1, dfunc2, dfunc, nPoints);
			ippsDivC_64f_I(2E-5, dfunc, nPoints);

			ippsDiv_64f_I(dfunc, funcval, nPoints);
			ippsSub_64f_I(funcval, r, nPoints);

		}

	for (int i = 0; i < nPoints; i++)
	{
		cout << r[i] << endl;
	}
	
	while(true);
    return 0;
}

int func(Ipp64f * argkz, Ipp64f * argCos, Ipp64f * argSin, Ipp64f *r, int length, Ipp64f *temp1, Ipp64f *temp2, Ipp64f *temp3, Ipp64f *out){
	ippsMul_64f(r, argCos, temp2, length);	
	vdCos(length, temp2, temp1);

	ippsMul_64f(r, argSin, temp3, length);
	vdCos(length, temp3, temp2);

	ippsAdd_64f_I(temp2, temp1, length);
	ippsMulC_64f_I(-1.75824E7, temp1, length);

	vdCos(length, argkz, temp2);
	ippsMulC_64f_I(-351.648, temp2, length);

	ippsAdd_64f(temp1, temp2, out, length);
	ippsAddC_64f_I(8.79121E6, out, length);
	ippsSqr_64f_I(out, length);

	return 0;
}

//int dfunc(Ipp64f * argkz, Ipp64f * argCos, Ipp64f * argSin, Ipp64f *r, int length, Ipp64f *temp1, Ipp64f *temp2, Ipp64f *out){
//
//	return 0;
//}