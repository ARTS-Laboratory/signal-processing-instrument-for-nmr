#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dtypes.h"

int line_count(const char *fname)
{
    FILE *fp = fopen(fname, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", fname);
        return -1;
    }

    int lines = 0;
    char ch;
    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch == '\n')
        {
            lines++;
        }
    }

    fclose(fp);
    return lines;
}

DataPoint *read_data(const char *fname, int *num_data_points, DataPoint *data)
{
    FILE *fp;
    char line[100];
    *num_data_points = line_count(fname);
    if (*num_data_points <= 0)
    {
        fprintf(stderr, "No data points found or error reading file.\n");
        return NULL;
    }

    fp = fopen(fname, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", fname);
        free(data);
        return NULL;
    }

    int count = 0;
    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "%lf\t%lf", &data[count].time, &data[count].volt) == 2)
        {
            count++;
        } else {
            fprintf(stderr, "Invalid line format: %s", line);
        }
    }

    printf("Read %d data points.\n", count);

    fclose(fp);
    if (count != *num_data_points)
    {
        fprintf(stderr, "Number of data points read does not match expected count.\n");
        free(data);
        return NULL;
    }
    return data;
}

