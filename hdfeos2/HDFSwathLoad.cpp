#include <mfhdf.h>
#include <hdf.h>
#include <HdfEosDef.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

int main(int argc, char **argv) {
	cout << "Hello world" << endl;

	// char filename1[128] = "/home/mrilee/data/OMI/OMI-Aura_L2-OMAERO_2004m1001t0003-o01132_v003-2011m0926t170457.he5";

	// An hdf4 file...
	char filename1[128] = "/home/mrilee/data/STARE/MYD09.A2019003.2040.006.2019005020913.hdf";
	/* Open using swath API */


	cout << "Opening swathfile " << filename1 << endl;
	int32 swathfile1;
	if ((swathfile1 = SWopen(filename1, DFACC_RDONLY)) == -1) {
		fprintf(stderr, "error: cannot open swath '%s'\n",filename1);
		return -1;
	}

	cout << "Closing swathfile " << filename1 << endl;
	/* Close */
	if ((SWclose(swathfile1)) == -1) {
		fprintf(stderr, "error: cannot close swath\n");
		return -1;
	}

	cout << "Done...";
	return 0;
}
