/*
 * Header gaurd cause makes it more
 * readable for me at least then
 * pragma once
 */
#ifndef JSON_FUNCTIONS_H
#define JSON_FUNCTIONS_H

// Include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Includes stdint.h
#include "datatypes.h"

/*
 * Simple function to improve readability
 * still hard to read definition on an 80
 * column display
 */
void add_d(struct p_data *ptr, const int size, const uint8_t t, const char* s)
{
	switch (t) {
	case 0:
		ptr->city = (char*) calloc(size, sizeof(char));
		strcpy(ptr->city, s);
		break;
	case 1:
		ptr->pro = (char*) calloc(size, sizeof(char));
		strcpy(ptr->pro, s);
		break;
	case 2:
		ptr->time = atol(s);
		break;
	case 3:
		ptr->x = atof(s);
		break;
	case 4:
		ptr->y = atof(s);
		break;
	}
}

/*
 * This is just the modified
 * javascript second function
 * which uses less long term
 * local storage, as it computes
 * Right values and uses them
 * immediately
 * 
 * Might want to change the computation
 * a bit as a square can technically
 * be "mul %eax,%eax" where mul is the
 * correct multiplication command for
 * float values and eax is the correct
 * register, pow I believe is close
 * to this but it probably stores
 * this in a secondary register
 *
 * This is an iffy inline as multiple
 * uses can make the executable too
 * big and lower the speed of the
 * executing code
 */
static inline float haversineDistance(float x1, float y1, float x2, float y2)
{
	// Code readability variable
	const double R = 6378.137;

	double a = pow(sin((y2 - y1) * M_PI / 360), 2) + cos(y1 * M_PI / 180) *
		cos(y2 * M_PI / 180) * pow(sin((x2 - x1) * M_PI / 360), 2);

	return R * 2 * atan2(sqrt(a), sqrt(1 - a));
}

void calc_zscore(struct p_data *ptr, const size_t size)
{
	/*
	 * Variables for use, yes size_t is
	 * a bit of overkill for this application
	 * but I want to make sure it is
	 * modular and expandable
	 */
	size_t i;
	size_t j;
	size_t average_time = 0;
	double average_time_square = 0;
	double gert_xix = 0;
	double gert_weight = 0;
	double gert_weight_square = 0;
	uint8_t hav;

	// Linear speed up in algo from js code
	for (i = 0; i < size; ++i) {
		average_time += 2015 - ptr[i].time;
		average_time_square += pow((2015 - ptr[i].time), 2);
	}

	average_time /= size;
	average_time_square /= size;

	// Loop for all z scores
	for (i = 0; i < size; ++i) {
		// Calculates the individual z score
		for (j = 0; j < size; ++j) {
			hav = (haversineDistance(ptr[j].x, ptr[j].y, ptr[i].x, ptr[i].y) <= 15) ? 1:0;
			gert_xix += hav * (2015 - ptr[j].time);
			gert_weight += hav;
			gert_weight_square = pow(hav, 2); // Note worthless if 1 or 0, but for code reuseablity
		}

		// Split up for better readability
		ptr[i].z_score = (gert_xix - average_time * gert_weight);
		ptr[i].z_score /= (average_time_square * sqrt(fabs(size * gert_weight_square - pow(gert_weight, 2))) / (size - 1));
		
		// Reset computation variables
		gert_xix = 0;
		gert_weight = 0;
		gert_weight_square = 0;
	}
}

#endif
