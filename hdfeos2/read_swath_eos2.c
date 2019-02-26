/*
 * read_swath_eos2.c
 *
 *  Created on: Feb 26, 2019
 *      Author: mrilee
 *
 *  Copyright (C) 2019 Rilee Systems Technologies LLC
 */


/*
 *
 *

https://hdfeos.org/examples/c_swath.php

HDF4_DIR=<hdf4_path>
HDFEOS2_DIR=<hdfeos2_path>

CC=$(HDF4_DIR)/bin/h4cc

CFLAGS=-I$(HDFEOS2_DIR)/include
LDFLAGS=-L$(HDFEOS2_DIR)/lib
LIBS=-lhdfeos -lGctp

read_swath: read_swath.c
$(CC) $(CFLAGS) $(LDFLAGS) $< $(LIBS) -o $@

 */

/* This example shows how to read a data field and two geo-location fields in HDF-EOS2 swath data. */

#include <mfhdf.h>
#include <hdf.h>
#include <HdfEosDef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int32 swathfile1;
	int32 swath1;
	int32 datafield1rank;
	int32 datafield1dimsize[32];
	int32 datafield1type;
	char datafield1dimname[512];
	int16 *datafield1data;
	int32 geofield1rank;
	int32 geofield1dimsize[32];
	int32 geofield1type;
	char geofield1dimname[512];
	float32 *geofield1data;
	int32 geofield2rank;
	int32 geofield2dimsize[32];
	int32 geofield2type;
	char geofield2dimname[512];
	float32 *geofield2data;
	int32 i, j;

	/* Open 'AMSR_E_L2A_BrightnessTemperatures_V09_200206190029_D.hdf' using swath API */
	if ((swathfile1 = SWopen("AMSR_E_L2A_BrightnessTemperatures_V09_200206190029_D.hdf", DFACC_RDONLY)) == -1) {
		fprintf(stderr, "error: cannot open swath 'AMSR_E_L2A_BrightnessTemperatures_V09_200206190029_D.hdf'\n");
		return -1;
	}

	/* Open a swath named 'Low_Res_Swath' */
	if ((swath1 = SWattach(swathfile1, "Low_Res_Swath")) == -1) {
		fprintf(stderr, "error: cannot attach to 'Low_Res_Swath'\n");
		return -1;
	}

	/* Retrieve information about '23.8H_Approx._Res.3_TB_(not-resampled)' datafield */
	if ((SWfieldinfo(swath1, "23.8H_Approx._Res.3_TB_(not-resampled)", &datafield1rank, datafield1dimsize, &datafield1type, datafield1dimname)) == -1) {
		fprintf(stderr, "error: cannot get the field info for '23.8H_Approx._Res.3_TB_(not-resampled)'\n");
		return -1;
	}
	/* Allocate buffer for '23.8H_Approx._Res.3_TB_(not-resampled)' */
	if ((datafield1data = malloc(sizeof(int16) * 1997 * 243)) == NULL) {
		fprintf(stderr, "error: cannot allocate memory for '23.8H_Approx._Res.3_TB_(not-resampled)'\n");
		return -1;
	}
	/* Read data from '23.8H_Approx._Res.3_TB_(not-resampled)' */
	if ((SWreadfield(swath1, "23.8H_Approx._Res.3_TB_(not-resampled)", NULL, NULL, NULL, datafield1data)) == -1) {
		fprintf(stderr, "error: cannot read field '23.8H_Approx._Res.3_TB_(not-resampled)'\n");
		return -1;
	}
	/* Dump data from '23.8H_Approx._Res.3_TB_(not-resampled)' */
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 2; ++j) {
			printf("%d ", datafield1data[j + 243 * i]);
		}
		printf("\n");
	}
	/* Release the buffer for '23.8H_Approx._Res.3_TB_(not-resampled)' */
	free(datafield1data);

	/* Retrieve information about 'Longitude' geolocation field */
	if ((SWfieldinfo(swath1, "Longitude", &geofield1rank, geofield1dimsize, &geofield1type, geofield1dimname)) == -1) {
		fprintf(stderr, "error: cannot get the field info for 'Longitude'\n");
		return -1;
	}
	/* Allocate buffer for 'Longitude' */
	if ((geofield1data = malloc(sizeof(float32) * 1997 * 243)) == NULL) {
		fprintf(stderr, "error: cannot allocate memory for 'Longitude'\n");
		return -1;
	}
	/* Read data from 'Longitude' */
	if ((SWreadfield(swath1, "Longitude", NULL, NULL, NULL, geofield1data)) == -1) {
		fprintf(stderr, "error: cannot read field 'Longitude'\n");
		return -1;
	}
	/* Dump data from 'Longitude' */
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 2; ++j) {
			printf("%f ", geofield1data[j + 243 * i]);
		}
		printf("\n");
	}
	/* Release the buffer for 'Longitude' */
	free(geofield1data);

	/* Retrieve information about 'Latitude' geolocation field */
	if ((SWfieldinfo(swath1, "Latitude", &geofield2rank, geofield2dimsize, &geofield2type, geofield2dimname)) == -1) {
		fprintf(stderr, "error: cannot get the field info for 'Latitude'\n");
		return -1;
	}
	/* Allocate buffer for 'Latitude' */
	if ((geofield2data = malloc(sizeof(float32) * 1997 * 243)) == NULL) {
		fprintf(stderr, "error: cannot allocate memory for 'Latitude'\n");
		return -1;
	}
	/* Read data from 'Latitude' */
	if ((SWreadfield(swath1, "Latitude", NULL, NULL, NULL, geofield2data)) == -1) {
		fprintf(stderr, "error: cannot read field 'Latitude'\n");
		return -1;
	}
	/* Dump data from 'Latitude' */
	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 2; ++j) {
			printf("%f ", geofield2data[j + 243 * i]);
		}
		printf("\n");
	}
	/* Release the buffer for 'Latitude' */
	free(geofield2data);

	/* Close the swath named 'Low_Res_Swath' */
	if ((SWdetach(swath1)) == -1) {
		fprintf(stderr, "error: cannot detach from 'Low_Res_Swath'\n");
		return -1;
	}

	/* Close 'AMSR_E_L2A_BrightnessTemperatures_V09_200206190029_D.hdf' */
	if ((SWclose(swathfile1)) == -1) {
		fprintf(stderr, "error: cannot close swath 'AMSR_E_L2A_BrightnessTemperatures_V09_200206190029_D.hdf'\n");
		return -1;
	}

	return 0;
}
