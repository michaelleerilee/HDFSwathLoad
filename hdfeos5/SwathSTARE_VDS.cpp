/*
 * SwathSTARE_VDS.cpp
 *
 *  Created on: Jun 27, 2019
 *      Author: mrilee
 *
 *  Copyright (C) 2019 Rilee Systems Technologies LLC
 */

#include "STARE.h"

#include <HE5_HdfEosDef.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include <H5Cpp.h>

using namespace H5;

int main(int argc, char **argv)
{
	STARE index;

	hid_t swathfile1;
	hid_t swath1;
	int datafield1rank;
	hsize_t datafield1dimsize[32];
	hid_t datafield1type;
	char datafield1dimname[512];
	char datafield1maxdimname[512];
	short *datafield1data;
	int geofield1rank;
	hsize_t geofield1dimsize[32];
	hid_t geofield1type;
	char geofield1dimname[512];
	char geofield1maxdimname[512];
	float *geofield1data;
	int geofield2rank;
	hsize_t geofield2dimsize[32];
	hid_t geofield2type;
	char geofield2dimname[512];
	char geofield2maxdimname[512];
	float *geofield2data;
	hsize_t i, j;

	/*
	char filename1[128] = "/home/mrilee/data/OMI/OMI-Aura_L2-OMAERO_2004m1001t0003-o01132_v003-2011m0926t170457.he5";
	char filename1[128] = "/home/mrilee/data/OMI/OMI-Aura_L2-OMAERUV_2004m1001t0003-o01132_v003-2017m0720t173902.he5";
	 */

	char filename1[128] = "/home/mrilee/data/OMI/OMI-Aura_L2-OMAERO_2004m1001t0003-o01132_v003-2011m0926t170457.he5";

	/* Open 'OMI-Aura_L2-OMAERO_2004m1001t0003-o01132_v003.he5' using swath API
	if ((swathfile1 = HE5_SWopen("OMI-Aura_L2-OMAERO_2004m1001t0003-o01132_v003.he5", H5F_ACC_RDONLY)) == -1) {
		fprintf(stderr, "error: cannot open swath 'OMI-Aura_L2-OMAERO_2004m1001t0003-o01132_v003.he5'\n");
		return -1;
	} */
	if ((swathfile1 = HE5_SWopen(filename1, H5F_ACC_RDONLY)) == -1) {
		fprintf(stderr, "error: cannot open swath '%s'\n",filename1);
		return -1;
	}
	printf("100\n");
	/* Open a swath named 'ColumnAmountAerosol' */
	if ((swath1 = HE5_SWattach(swathfile1, "ColumnAmountAerosol")) == -1) {
		fprintf(stderr, "error: cannot attach to 'ColumnAmountAerosol'\n");
		return -1;
	}

	printf("110\n");
	/* Retrieve information about 'AerosolIndexUV' datafield */
	if ((HE5_SWfieldinfo(swath1, "AerosolIndexUV", &datafield1rank, datafield1dimsize, &datafield1type, datafield1dimname, datafield1maxdimname)) == -1) {
		fprintf(stderr, "error: cannot get the field info for 'AerosolIndexUV'\n");
		return -1;
	}

	// HDFEOS/SWATHS/ColumnAmountAerosol/Data_Fields/AerosolIndexUV

	printf("datafield1rank    %d\n",datafield1rank);
	for(int i=0; i < datafield1rank; ++i ) {
		printf("datafield1dimsize %d: %d\n",i,datafield1dimsize[i]);
	}
	printf("datafield1dimname %s\n",datafield1dimname);
	printf("datafield1maxdimname %s\n",datafield1maxdimname);
	printf("120\n");
	/* Allocate buffer for 'AerosolIndexUV' */
	if ((datafield1data = (short int*)malloc(sizeof(short) * 1644 * 60)) == NULL) {
		fprintf(stderr, "error: cannot allocate memory for 'AerosolIndexUV'\n");
		return -1;
	}
	printf("130\n");
	if(1) {
		/* Read data from 'AerosolIndexUV' */
		if ((HE5_SWreadfield(swath1, "AerosolIndexUV", NULL, NULL, NULL, datafield1data)) == -1) {
			fprintf(stderr, "error: cannot read field 'AerosolIndexUV'\n");
			return -1;
		}
		printf("140\n");
		/* Dump data from 'AerosolIndexUV' */
		for (i = 0; i < 16; ++i) {
			for (j = 0; j < 6; ++j) {
				printf("%d ", datafield1data[j + 60 * i]);
			}
			printf("\n");
		}
		printf("150\n");
		//	/* Release the buffer for 'AerosolIndexUV' */
		//	free(datafield1data);
	}

	printf("160\n");
	/* Retrieve information about 'Longitude' geolocation field */
	if ((HE5_SWfieldinfo(swath1, "Longitude", &geofield1rank, geofield1dimsize, &geofield1type, geofield1dimname, geofield1maxdimname)) == -1) {
		fprintf(stderr, "error: cannot get the field info for 'Longitude'\n");
		return -1;
	}
	printf("170\n");
	/* Allocate buffer for 'Longitude' */
	if ((geofield1data = (float*)malloc(sizeof(float) * 1644 * 60)) == NULL) {
		fprintf(stderr, "error: cannot allocate memory for 'Longitude'\n");
		return -1;
	}
	printf("180\n");
	/* Read data from 'Longitude' */
	if ((HE5_SWreadfield(swath1, "Longitude", NULL, NULL, NULL, geofield1data)) == -1) {
		fprintf(stderr, "error: cannot read field 'Longitude'\n");
		return -1;
	}
	printf("190\n");
	/* Dump data from 'Longitude' */
	for (i = 0; i < 16; ++i) {
		for (j = 0; j < 6; ++j) {
			printf("%f ", geofield1data[j + 60 * i]);
		}
		printf("\n");
	}
	printf("200\n");


	printf("210\n");

	/* Retrieve information about 'Latitude' geolocation field */
	if ((HE5_SWfieldinfo(swath1, "Latitude", &geofield2rank, geofield2dimsize, &geofield2type, geofield2dimname, geofield2maxdimname)) == -1) {
		fprintf(stderr, "error: cannot get the field info for 'Latitude'\n");
		return -1;
	}
	printf("220\n");
	/* Allocate buffer for 'Latitude' */
	if ((geofield2data = (float*)malloc(sizeof(float) * 1644 * 60)) == NULL) {
		fprintf(stderr, "error: cannot allocate memory for 'Latitude'\n");
		return -1;
	}
	printf("230\n");
	/* Read data from 'Latitude' */
	if ((HE5_SWreadfield(swath1, "Latitude", NULL, NULL, NULL, geofield2data)) == -1) {
		fprintf(stderr, "error: cannot read field 'Latitude'\n");
		return -1;
	}
	printf("240\n");
	/* Dump data from 'Latitude' */
	for (i = 0; i < 16; ++i) {
		for (j = 0; j < 6; ++j) {
			printf("%f ", geofield2data[j + 60 * i]);
		}
		printf("\n");
	}

	/* Now, work with STARE. */

	int ndata = 16;

	int64_t idx0;

	for(i = 0; i < ndata; ++i) {
		double
		latDegrees = geofield2data[i],
		lonDegrees = geofield1data[i];
		int
		level = 9; // for about 20km
		STARE_ArrayIndexTemporalValue idx =
				index.ValueFromLatLonDegrees(latDegrees, lonDegrees, level);
		if ( i == 0 ) {
			idx0 = idx;
		}
		cout << "idx: "
				<< "0x" << setw(16) << setfill('0') << hex << idx
				<< dec << " " << latDegrees << " , " << lonDegrees
				<< ", diffbit: " << firstBitDifferenceFromLeft(idx0,idx)
				<< endl << flush;
	}

	/* Close the swath named 'ColumnAmountAerosol' */
	if ((HE5_SWdetach(swath1)) == -1) {
		fprintf(stderr, "error: cannot detach from 'ColumnAmountAerosol'\n");
		return -1;
	}

	/* Close 'OMI-Aura_L2-OMAERO_2004m1001t0003-o01132_v003.he5' */
	if ((HE5_SWclose(swathfile1)) == -1) {
		fprintf(stderr, "error: cannot close swath 'OMI-Aura_L2-OMAERO_2004m1001t0003-o01132_v003.he5'\n");
		return -1;
	}

	/* Write files */

	Exception::dontPrint();
	try {

		cout << "h5 output test" << endl << flush;

		int iFile = 0;
		stringstream ss; ss.str("");

		int iData0 = 0;

		int originalArrayIndex[ndata];
		// Hack the following to get started
		for(int i=0; i<ndata; ++i) {
			originalArrayIndex[i] = i+iData0;
		}

		int rank = 1;
		hsize_t dims[rank] = { ndata };
		// hsize_t cdims[rank] = { ndata };

		ss << "testout-" << iFile << ".h5";
		H5std_string fName(ss.str());

		H5File *file = new H5File( fName, H5F_ACC_TRUNC );
		Group  *group = new Group( file->createGroup( "/data" ) );


		cout << "h5 output test 100" << endl << flush;
		DataSpace *source_dataspace = new DataSpace(rank,dims);

		cout << "h5 output test 110" << endl << flush;
		DataSpace *dataspace = new DataSpace(rank,dims);
		DSetCreatPropList ds_creatplist;
		// ds_creatplist.setChunk(2, cdmins);
		// ds_creatplist.setDeflate( 6 );
		cout << "h5 output test 120" << endl << flush;
		DataSet *dataset = new DataSet(
		file->createDataSet(
				"/data/dataset1", PredType::NATIVE_SHORT, *dataspace
				// "/data/dataset1", PredType::NATIVE_DOUBLE, *dataspace
				// "/Data/dataset1", PredType::NATIVE_DOUBLE, *dataspace, ds_creatplist
		));
		cout << "h5 output test 130" << endl << flush;
		// mspace is like?
		// fspace is like dataspace.
		dataset->write( datafield1data, PredType::NATIVE_SHORT, *source_dataspace, *dataspace );
		cout << "h5 output test cleaning up" << endl << flush;
		delete dataset;

		dataset = new DataSet(
				file->createDataSet(
						"/data/latitude", PredType::NATIVE_FLOAT, *dataspace
				));
		dataset->write( geofield2data, PredType::NATIVE_FLOAT, *source_dataspace, *dataspace );
		delete dataset;

		dataset = new DataSet(
				file->createDataSet(
						"/data/longitude", PredType::NATIVE_FLOAT, *dataspace
				));
		dataset->write( geofield1data, PredType::NATIVE_FLOAT, *source_dataspace, *dataspace );
		delete dataset;

		dataset = new DataSet(
				file->createDataSet(
						"/data/originalArrayIndex", PredType::NATIVE_INT, *dataspace
				));
		dataset->write( originalArrayIndex, PredType::NATIVE_INT, *source_dataspace, *dataspace );
		delete dataset;

		delete source_dataspace;
		delete dataspace;
		delete group;
		delete file;

	} catch ( FileIException error ) {
		cout << error.getDetailMsg() << endl << flush;
		error.printError();	return -1;
	} catch ( DataSetIException error ) {
		cout << error.getDetailMsg() << endl << flush;
		error.printError(); return -1;
	} catch ( DataSpaceIException error ) {
		cout << error.getDetailMsg() << endl << flush;
		error.printError(); return -1;
	} catch ( DataTypeIException error ) {
		cout << error.getDetailMsg() << endl << flush;
		error.printError(); return -1;
	}

	cout << "h5 output test done" << endl << flush;

	/* Finalize */

	/* Release the buffer for 'AerosolIndexUV' */
	free(datafield1data);
	/* Release the buffer for 'Longitude' */
	free(geofield1data);
	/* Release the buffer for 'Latitude' */
	free(geofield2data);

	return 0;
}


