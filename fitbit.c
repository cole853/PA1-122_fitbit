/*
		Programmer: Cole Clark
		Date: 1-24-2021

			Description: Solution for PA1

*/

#include "fitbit.h"


//reads the file and puts the values in an array of the FitbitData struct also checks for missing information and puts in non valid information for those spots
int readLine(FILE* infile, FitbitData* output)
{
	char rec[70] = { '\0' };
	const char delim[2] = ",";
	static int gCount = 0;
	static int tCount = 0;
	static char* target = NULL;
	FitbitData temp;

	int c = fgets(rec, 70, infile); // get a record

	if (c == NULL) // if the string is null end recursion and return the amount of usable records
	{
		return gCount;
	}
	else
	{
		if (tCount == 0) // get target patient ID
		{
			char* dummy = strtok(rec, delim);
			target = strtok(NULL, delim);

		}
		else if (tCount >= 2)
		{

			checkLine(rec); // fill missing data with *
			getValues(rec, &temp); // put record into FitbitData temp

			int patComp = strcmp(target, temp.patient); //check to see if this is the target patient

			if (patComp == 0)
			{
				int timeComp = strcmp(output[gCount - 1].minute, temp.minute); // check to see if the minute is a duplicate

				if (timeComp != 0)
				{

					inputValues(output, &temp, gCount);

					++gCount;
				}

			}
		}
		++tCount;
		readLine(infile, output);

	}
}


//takes values from a temporary FitbitData and moves them to the record
void inputValues(FitbitData* record, FitbitData* temp, int count)
{
	strcpy(record[count].patient, temp->patient);
	strcpy(record[count].minute, temp->minute);

	record[count].calories = temp->calories;
	record[count].distance = temp->distance;
	record[count].floors = temp->floors;
	record[count].heartRate = temp->heartRate;
	record[count].steps = temp->steps;
	record[count].sleepLevel = temp->sleepLevel;

}


//checks the string before strtok for two commas in a row. If there are two commas in a row it puts a * between them
void checkLine(char string[70])
{
	int i = 0;
	/*int l = strlen(string);
	l += 5;
	int o = l;*/
	int o = strlen(string);
	int g = o;

	if (string[0] == ',') // if the first character is a comma this moves all the characters in the array back by 1 and sets string[0] equal to '*'
	{
		while (g > 0)
		{
			string[g] = string[g - 1];
			--g;
		}

		string[0] = '*';
		++o;
	}

	do // moves characters back and puts * between two commas
	{
		int l = strlen(string);

		if (string[i] == ',' && string[i + 1] == ',')
		{
			
			while (i != l)
			{
				string[l] = string[l - 1];

				--l;
			}

			string[i + 1] = '*';
			++o;

		}

		++i;

	} while (i != o);

	if (string[o - 1] == ',') // puts a * on the end of the string if the last character is a comma
	{
		string[o] = '*';
	}
}


//gets the values from a string, puts them in a temporary FitbitData and puts in invalid values where there was no data before
void getValues(char* record, FitbitData *temp)
{
	char line[10][20] = { '\0' };
	const char delim[2] = ",";
	int i = 0;
	char* patient = NULL;
	char* minute = NULL;
	char* calories = NULL;
	char* distance = NULL;
	char* floors = NULL;
	char* heartRate = NULL;
	char* steps = NULL;
	char* sleepLevel = NULL;

	patient = strtok(record, delim);
	minute = strtok(NULL, delim);
	calories = strtok(NULL, delim);
	distance = strtok(NULL, delim);
	floors = strtok(NULL, delim);
	heartRate = strtok(NULL, delim);
	steps = strtok(NULL, delim);
	sleepLevel = strtok(NULL, delim);

	/*printf("Patient: %s\n", patient);
	printf("Minute: %s\n", minute);
	printf("Calories: %s\n", calories);
	printf("Distance: %s\n", distance);
	printf("Floors: %s\n", floors);
	printf("Heart Rate: %s\n", heartRate);
	printf("Steps: %s\n", steps);
	printf("Sleep Level: %s\n", sleepLevel);
	printf("\n\n");*/

	strcpy(temp->patient, patient);
	strcpy(temp->minute, minute);


	if (calories[0] == '*')
	{
		temp->calories = FAKE;
	}
	else
	{
		temp->calories = strtod(calories, NULL);
	}


	
	if (distance[0] == '*')
	{
		temp->distance = FAKE;
	}
	else
	{
		temp->distance = strtod(distance, NULL);
	}



	if (floors[0] == '*')
	{
		temp->floors = FAKE;
	}
	else
	{
		temp->floors = atoi(floors);
	}



	if (heartRate[0] == '*')
	{
		temp->heartRate = FAKE;
	}
	else
	{
		temp->heartRate = atoi(heartRate);
	}



	if (steps[0] == '*')
	{
		temp->steps = FAKE;
	}
	else
	{
		temp->steps = atoi(steps);
	}



		temp->sleepLevel = atoi(sleepLevel);
	
}


//finds the total calories, distance, floors and steps
void calculateTotals(FitbitData *record, FitbitData *totals, const int size)
{
	double tCals = 0;
	double tDist = 0;
	int tFloors = 0;
	int tSteps = 0;
	int tHeart = 0;

	for (int i = 0; i != size; ++i)
	{
		if (record[i].calories != FAKE)
		{
			tCals += record[i].calories;
		}
		if (record[i].distance != FAKE)
		{
			tDist += record[i].distance;
		}
		if (record[i].floors != FAKE)
		{
			tFloors += record[i].floors;
		}
		if (record[i].steps != FAKE)
		{
			tSteps += record[i].steps;
		}
		if (record[i].heartRate != FAKE)
		{
			tHeart += record[i].heartRate;
		}
	}

	totals->calories = tCals;
	totals->distance = tDist;
	totals->floors = tFloors;
	totals->steps = tSteps;
	totals->heartRate = tHeart;
}


//calculates the average heartrate and rounds to the nearest whole number
int calculateAverageHeartRate(FitbitData* record, int size)
{
	int count = 0;
	int total = 0;

	for (int i = 0; i != size; ++i)
	{
		if (record[i].heartRate != FAKE)
		{
			total += record[i].heartRate;
			++count;
		}
	}

	double averageD = (double) total / (double) count;

	int averageI = averageD;

	averageD - averageI;

	if (averageD >= 0.5)
	{
		++averageI;
	}
	return averageI;
}


//finds the max steps in a minute for the day
int findMaxSteps(FitbitData* record, int size)
{
	int currentMax = 0;

	for (int i = 0; i != size; ++i)
	{
		if (record[i].steps >= currentMax)
		{
			currentMax = record[i].steps;
		}
	}
	return currentMax;
}


//finds the worst sleep range (Start time and end time)
void worstSleep(FitbitData* record, int size, char *start, char *end)
{
	int sleepScore = 0;
	int currentWorst = 0;
	int foundEnd = 0;
	char tempS[9] = { '\0' };
	char tempE[9] = { '\0' };

	for (int i = 0; i != size; ++i)
	{
		if (record[i].sleepLevel > 1 && record[i - 1].sleepLevel <= 1)
		{
			sleepScore = record[i].sleepLevel;
			strcpy(tempS, record[i].minute);
		}
		else if (record[i].sleepLevel > 1)
		{
			sleepScore += record[i].sleepLevel;
		}

		if (record[i].sleepLevel > 1 && record[i + 1].sleepLevel <= 1)
		{
			strcpy(tempE, record[i].minute);
			foundEnd = 1;
		}

		if (foundEnd == 1 && sleepScore > currentWorst)
		{
			currentWorst = sleepScore;
			strcpy(start, tempS);
			strcpy(end, tempE);
			foundEnd = 0;
		}
	}
}


//prints a header line, the summary and the cleaned records
void printValues(FILE* outfile, FitbitData* record, FitbitData* totals, int averageHeartRate, int maxSteps, char start[], char end[], int count)
{
	fprintf(outfile, "Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
	fprintf(outfile, "%lf,%lf,%d,%d,%d,%d,%s,%s\n\n", totals->calories, totals->distance, totals->floors, totals->steps, averageHeartRate, maxSteps, start, end);

	for (int i = 0; i < count; ++i)
	{
		fprintf(outfile, "%s,%s,%lf,%lf,%d,%d,%d,%d\n", record[i].patient, record[i].minute, record[i].calories, record[i].distance, record[i].floors, record[i].heartRate, record[i].steps, record[i].sleepLevel);
		//Patient, minute, calories, distance, floors, heart, steps, sleep_level
	}
	printf("Results have been printed to Results.csv!\n");
}