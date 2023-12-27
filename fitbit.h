/*
		Programmer: Cole Clark
		Date: 1-24-2021

			Description: Solution for PA1 

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FAKE 555

#ifndef FITBIT_H
#define FITBIT_H

typedef enum sleep
{

    NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3

} Sleep;

typedef struct fitbit
{

    char patient[10];

    char minute[9];

    double calories;

    double distance;

    unsigned int floors;

    unsigned int heartRate;

    unsigned int steps;

    Sleep sleepLevel;

} FitbitData;


//reads the file and puts the values in an array of the FitbitData struct also checks for missing information and puts in non valid information for those spots
int readLine(FILE* infile, FitbitData *record);

//checks the string before strtok for two commas in a row. If there are two commas in a row it puts a * between them
void checkLine(char string[70]);


//gets the values from a string, puts them in a temporary FitbitData and puts in invalid values where there was no data before
void getValues(char* record, FitbitData *temp);


//takes values from a temporary FitbitData and moves them to the record
void inputValues(FitbitData* record, FitbitData* temp, int count);


//finds the total calories, distance, floors and steps
void calculateTotals(FitbitData* record, FitbitData* totals, const int size);


//calculates the average heartrate and rounds to the nearest whole number
int calculateAverageHeartRate(FitbitData* record, int size);


//finds the max steps in a minute for the day
int findMaxSteps(FitbitData* record, int size);


//finds the worst sleep range (Start time and end time)
void worstSleep(FitbitData* record, int size, char* start, char* end);


//prints a header line, the summary and the cleaned records
void printValues(FILE* outfile, FitbitData* record, FitbitData* totals, int averageHeartRate, int maxSteps, char start[], char end[], int count);

#endif