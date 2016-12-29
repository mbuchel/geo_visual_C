// For cleaner looking code
#include "functions.h"

/*
 * Read/write file for easier
 * javascript code which has to
 * be written, eventually will
 * be changed to a multithread
 * object
 */
int main(int argc, char** argv)
{
	const char csv_delimiter[2] = {
		(char) 0x0D, (char) 0x0A
	};

	FILE *file;

	char x;
	char buffer[100];
	
	uint8_t type = 0;
	
	int i = 0;

	size_t data_num = 0;

	struct p_data data[MAX_DATA_SENT];

	if (argc < 3) {
		i = 1;
		goto exit;
	}

	file = fopen(argv[1],"r");

	/*
	 * Note: I know that goto is not
	 * used in high level langauges
	 * however I have been getting more
	 * into the habit of using it for
	 * both my compiler and OS projects
	 * as it is SLIGHTLY better practice
	 * for low level langauges to use
	 * gotos for your return statements
	 * as now you only have return in
	 * one area of your function as opposed
	 * to multiple which would be done
	 * by most compilers anyways
	 */
	if (file == NULL) {
		printf("\nerror opening file\n");
		i = 1;
		goto exit;
	}

	do {
		x = fgetc(file);

		// Skips the spaces, tabs and line feeds
		if(x == ' ' || x == '\t' || x == 0x0A)
			continue;

		// If it is a delimiter then put \0 instead else character
		if (x != ',' && x != EOF && x != '\n' && x != 0x0D)
			buffer[i] = x;
		else
			buffer[i] = '\0';

		// Checks what type of data it is
		if (type == 5) {
			type = 0;
			++data_num;
		}

		// Checks that the buffer is not full
		if (buffer[i++] == '\0') {
			add_d(&data[data_num], i, type++, buffer);
			i = 0;
		}
	} while (x != EOF);

	fclose(file);

	// Calcs zscore of the data and appends
	calc_zscore(data, data_num);

	file = fopen(argv[2], "w");

	if (file == NULL) {
		printf("\nerror opening second file\n");
		i = 1;
		goto exit;
	}

	for (i = 0; i < data_num; ++i) {
		// Almost forgot to export as .csv file format
		fprintf(file, "%s,%s,%ld,%f,%f,%f%s", data[i].city, data[i].pro, data[i].time,
			data[i].x, data[i].y, data[i].z_score, (strcmp(argv[2] + strlen(argv[2]) - 4, ".csv") == 0) ? csv_delimiter:"\n");
	}

	fclose(file);
	
	i = 0;

exit:
	return i;
}
