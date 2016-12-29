/*
 * This is data structures
 * from the json object implemented
 * in C
 */

#ifndef JSON_DATA_H
#define JSON_DATA_H

#include <stdint.h>

// Change as needed
const size_t MAX_DATA_SENT = 1000;

// Structure for storing CSV data
struct p_data {
	char *city;
	char *pro;
	size_t time;
	float x;
	float y;
	float z_score;
};

#endif
