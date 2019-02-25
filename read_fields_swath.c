/*
 * example.c
 *
 *  Created on: Feb 25, 2019
 *      Author: mrilee
 *
 *  Copyright (C) 2019 Rilee Systems Technologies LLC
 */


/* This example shows how to read a data field and two geo-location fields in HDF-EOS5 swath data. */

#include <HE5_HdfEosDef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
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
	if ((datafield1data = malloc(sizeof(short) * 1644 * 60)) == NULL) {
		fprintf(stderr, "error: cannot allocate memory for 'AerosolIndexUV'\n");
		return -1;
	}
	printf("130\n");
	if(true) {
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
	/* Release the buffer for 'AerosolIndexUV' */
	free(datafield1data);
	}

	printf("160\n");
	/* Retrieve information about 'Longitude' geolocation field */
	if ((HE5_SWfieldinfo(swath1, "Longitude", &geofield1rank, geofield1dimsize, &geofield1type, geofield1dimname, geofield1maxdimname)) == -1) {
		fprintf(stderr, "error: cannot get the field info for 'Longitude'\n");
		return -1;
	}
	printf("170\n");
	/* Allocate buffer for 'Longitude' */
	if ((geofield1data = malloc(sizeof(float) * 1644 * 60)) == NULL) {
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
	/* Release the buffer for 'Longitude' */
	free(geofield1data);

	printf("210\n");

	/* Retrieve information about 'Latitude' geolocation field */
	if ((HE5_SWfieldinfo(swath1, "Latitude", &geofield2rank, geofield2dimsize, &geofield2type, geofield2dimname, geofield2maxdimname)) == -1) {
		fprintf(stderr, "error: cannot get the field info for 'Latitude'\n");
		return -1;
	}
	printf("220\n");
	/* Allocate buffer for 'Latitude' */
	if ((geofield2data = malloc(sizeof(float) * 1644 * 60)) == NULL) {
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
	/* Release the buffer for 'Latitude' */
	free(geofield2data);

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

	return 0;
}
