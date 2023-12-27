/*
		Programmer: Cole Clark
		Date: 1-24-2021

			Description: Solution for PA1

*/

#include "fitbit.h"

int main(void)
{
	FILE* infile = fopen("FitbitData.csv", "r");
	FILE* outfile = fopen("Results.csv", "w");

	if (infile != NULL)
	{
		printf("File opened successfully!\n\n");

		FitbitData record[1440];
		FitbitData totals;
		int averageHeartRate = 0;
		int maxSteps = 0;
		char start[9] = { '\0' };
		char end[9] = { '\0' };

		int count = readLine(infile, &record);

		calculateTotals(record, &totals, count);
		averageHeartRate = calculateAverageHeartRate(record, count);
		maxSteps = findMaxSteps(record, count);
		worstSleep(record, count, &start, &end);


		printf("Total Calories: %lf\n", totals.calories);
		printf("Total Distance: %lf\n", totals.distance);
		printf("Total Floors: %d\n", totals.floors);
		printf("Total Steps: %d\n", totals.steps);
		printf("Average Heart Rate: %d\n",averageHeartRate);
		printf("Max Steps: %d\n", maxSteps);
		printf("Worst Sleep: %s ; %s\n\n", start, end);

		printValues(outfile, record, &totals, averageHeartRate, maxSteps, start, end, count);

		//for (int i = 0; i < 1440; ++i)
		//{

		//	//printf("Patient: %s\n", record[i].patient);
		//	printf("Minute: %s\n", record[i].minute);
		//	/*printf("Calories: %lf\n", record[i].calories);
		//	printf("Distance: %lf\n", record[i].distance);
		//	printf("Floors: %d\n", record[i].floors);
		//	printf("Heart Rate: %d\n", record[i].heartRate);
		//	printf("Steps: %d\n", record[i].steps);*/
		//	printf("Sleep Level: %d\n", record[i].sleepLevel);
		//	printf("\n");
		//}
		//printf("\ncount: %d\n\n", count);
	}
	else
	{
		printf("An error has occured with opening the file\n\n");
	}

	fclose(infile);
	fclose(outfile);

	return 0;
}