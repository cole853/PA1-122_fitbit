# PA1-122_fitbit
A Fitbit data analyzer for CPTS 122 programming assignment 1. Completed on 1/24/2021.

This program reads all records from a FitbitData.csv file and stores them in an array of structs. Then it calculates total calories, total distance, total floors, total steps, average heart rate, max steps, and worst sleep. The results are printed to a Results.csv file.

# Four Files Are Required

fitbit.h: contains declarations for functions defined in fitbit.c and structs.

fitbit.c: contains definitions for functions declared in fitbit.h.

main.c: contains a main function that reads from FitbitData.csv and writes to Results.csv.

FitbitData.csv: contains the data that will be read by the main function.

# Possible Improvements

This program could be modified to find more information from the FitbitData.csv file such as average calories or max distance etc.
