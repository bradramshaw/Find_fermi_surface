#include "stdafx.h"
using namespace std;

int func(Ipp64f *params, Ipp64f * argkz, Ipp64f * argCos, Ipp64f * argSin, Ipp64f *r, int length, Ipp64f *temp, Ipp64f *out);
//int dfunc(Ipp64f * argkz, Ipp64f * argCos, Ipp64f * argSin, Ipp64f *r, int length, Ipp64f *temp1, Ipp64f *temp2, Ipp64f *out);

int _tmain(int argc, _TCHAR* argv[])
{

	DataExtractor extractor("start0.dat");
	Ipp64f params[9] = { .5, 475, 525, -60, 16, 9, .5, 1, 8 };

	Ipp64f * starts = extractor.getDataArray();
	int nPoints = floor((extractor.getNumberOfLines()) / 2);
	
	Ipp64f *temp = new Ipp64f[20*nPoints];
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
			/*vdSin(nPoints, theta, argSin);
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
			ippsSub_64f_I(funcval, r, nPoints);*/

			vdSin(nPoints, theta, argSin);
			vdCos(nPoints, theta, argCos);
			ippsMulC_64f(kz, 3.3, argkz, nPoints);
			func(params, argkz, argCos, argSin, r, nPoints, temp, funcval);
			
			cout << funcval[0] << endl;

			ippsAddC_64f(r, 1E-6, rtemp, nPoints);
			func(params, argkz, argCos, argSin, rtemp, nPoints, temp, dfunc1);
			ippsAddC_64f(r, -1E-6, rtemp, nPoints);
			func(params, argkz, argCos, argSin, rtemp, nPoints, temp, dfunc2);
			ippsMulC_64f_I(-1, dfunc2, nPoints);
			ippsAdd_64f(dfunc1, dfunc2, dfunc, nPoints);
			ippsDivC_64f_I(2E-6, dfunc, nPoints);		

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

int func(Ipp64f *params, Ipp64f * argkz, Ipp64f * argCos, Ipp64f * argSin, Ipp64f *r, int length, Ipp64f *temp, Ipp64f *out){
	
	ippsMulC_64f(argCos, 3.747665940, temp, length);
	ippsMul_64f_I(r, temp, length);
	vdCos(length, temp, &temp[1 * length]); // cos cos
	ippsMulC_64f(argSin, 3.747665940, temp, length);
	ippsMul_64f_I(r, temp, length);
	vdCos(length, temp, &temp[2 * length]); // cos sin
	ippsMulC_64f(argCos, 3.747665940 /2, temp, length);
	ippsMul_64f_I(r, temp, length);
	vdCos(length, temp, &temp[3 * length]); // cos cos/2
	ippsMulC_64f(argSin, 3.747665940 / 2, temp, length);
	ippsMul_64f_I(r, temp, length);
	vdCos(length, temp, &temp[4 * length]); // cos sin/2
	ippsMulC_64f(argCos, 3.747665940 *2 , temp, length);
	ippsMul_64f_I(r, temp, length);
	vdCos(length, temp, &temp[5 * length]); // cos 2 cos
	ippsMulC_64f(argSin, 3.747665940 * 2, temp, length);
	ippsMul_64f_I(r, temp, length);
	vdCos(length, temp, &temp[6 * length]); // cos 2 sin
	vdCos(length, argkz, &temp[7 * length]); // cos kz/2

	ippsAdd_64f(&temp[5 * length], &temp[6 * length], temp, length);// param 5
	ippsMulC_64f(temp, -35164.83516*params[5 - 1], out, length);

	ippsMul_64f(&temp[1 * length], &temp[2 * length], temp, length);// param 4
	ippsMulC_64f_I(-35164.83516 *2*params[4 - 1], temp, length);
	ippsAdd_64f_I(temp, out, length);

	ippsAdd_64f(&temp[1 * length], &temp[2 * length], temp, length);// param 3
	ippsMulC_64f_I(-35164.83516 * params[3 - 1], temp, length);
	ippsAdd_64f_I(temp, out, length);
	ippsAddC_64f_I(35164.83516 / 2 * params[2 - 1], out, length);// param 2
	ippsSub_64f(&temp[2 * length] , &temp[1 * length], temp, length);// param 6
	ippsSqr_64f_I(temp, length); //square
	ippsMul_64f_I(&temp[3 * length], temp, length); // mult by cos cos/2
	ippsMul_64f_I(&temp[4 * length], temp, length); // mult by cos sin/2
	ippsMul_64f_I(&temp[7 * length], temp, length); // mult by cos  kz/2
	ippsMulC_64f_I(-35164.83516 * params[6 - 1], temp, length);
	ippsAdd_64f_I(temp, out, length);

	return 0;
}

//int func(Ipp64f * argkz, Ipp64f * argCos, Ipp64f * argSin, Ipp64f *r, int length, Ipp64f *temp1, Ipp64f *temp2, Ipp64f *temp3, Ipp64f *out) {
//	ippsMul_64f(r, argCos, temp2, length);
//	vdCos(length, temp2, temp1);
//
//	ippsMul_64f(r, argSin, temp3, length);
//	vdCos(length, temp3, temp2);
//
//	ippsAdd_64f_I(temp2, temp1, length);
//	ippsMulC_64f_I(-1.75824E7, temp1, length);
//
//	vdCos(length, argkz, temp2);
//	ippsMulC_64f_I(-351.648, temp2, length);
//
//	ippsAdd_64f(temp1, temp2, out, length);
//	ippsAddC_64f_I(8.79121E6, out, length);
//	ippsSqr_64f_I(out, length);
//
//	return 0;
//}

//int dfunc(Ipp64f * argkz, Ipp64f * argCos, Ipp64f * argSin, Ipp64f *r, int length, Ipp64f *temp1, Ipp64f *temp2, Ipp64f *out){
//
//	return 0;
//}