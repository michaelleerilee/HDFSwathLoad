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
	string swath1_key = "MODIS SWATH TYPE L2";

	// char filename1[128] = "/home/mrilee/data/TestData/AMSR_E_L2A_BrightnessTemperatures_V09_200206190029_D.hdf";
	// string swath1_key = "Low_Res_Swath";

	/* Open using swath API */


	cout << "Opening swathfile " << filename1 << endl;
	int32 swathfile1;
	if ((swathfile1 = SWopen(filename1, DFACC_RDONLY)) == -1) {
		fprintf(stderr, "error: cannot open swath '%s'\n",filename1);
		return -1;
	}

	/* Open a swath */
	int32 swath1;
	cout << "Attaching to " << swath1_key.c_str();
	if ((swath1 = SWattach(swathfile1, swath1_key.c_str())) == -1) {
		fprintf(stderr, "error: cannot attach to '%s'\n",swath1_key.c_str());
		return -1;
	} else {
		cout << " - ATTACHED" << endl << flush;
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
