#include "stdafx.h"
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{

	DataExtractor extractor("start0.dat");

	Ipp64f * starts = extractor.getDataArray();
	int nPoints = floor((extractor.getNumberOfLines()) / 2);

	for (int i = 0; i < nPoints; i++) {
		cout << starts[2 * i] << " " << starts[2 * i + 1] << endl;
	}







	while(true);
    return 0;
}

