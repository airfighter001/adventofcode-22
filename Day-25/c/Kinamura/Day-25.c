#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

char getClosestOption(long number, long *currNumber, int exponent) {
	long diffs[5];
	diffs[0] = 2 * (long)powl(5,exponent);
	diffs[1] = 1 * (long)powl(5,exponent);
	diffs[2] = 0;
	diffs[3] = -1 * (long)powl(5,exponent);
	diffs[4] = -2 * (long)powl(5,exponent);

	long diff = LONG_MAX;
	for(int i = 0; i < 5; i++) {
		if(labs(number - (*currNumber + diffs[i])) < labs(number - (*currNumber + diff))) {
			diff = diffs[i];
		}
	}

	*currNumber += diff;
	if(diff == diffs[0]) {
		return '2';
	}
	if(diff == diffs[1]) {
		return '1';
	}
	if(diff == diffs[2]) {
		return '0';
	}
	if(diff == diffs[3]) {
		return '-';
	}
	if(diff == diffs[4]) {
		return '=';
	}
	return 'f';
}

long maxValueExponent(int exponent) {
	long maxValue = 0;
	for (int i = 0; i <= exponent; i++) {
		maxValue += 2 * (long)powl(5,i);
	}
	return maxValue;
}

char * convertToSNAFU(long number) {
	char * convertedNumber = NULL;
	int digits = 0;
	long currNumber = 0;
	while(maxValueExponent(digits) < number) {
		digits++;
	}
	convertedNumber = malloc(digits * sizeof(char));
	for(int i = digits; i >= 0; i--) {
		char currentSymbol = getClosestOption(number,&currNumber,i);
		convertedNumber[digits - i] = currentSymbol;
	}
	return convertedNumber;
}

long getDigitValue(int power, char digit) {
    long digitValue;
    switch(digit) {
        case '2': return (long)(2 * powl(5,power));
        case '1': return (long)(powl(5,power));
        case '0': return 0;
        case '-': return (long)(-1 * powl(5,power));
        case '=': return (long)(-2 * powl(5,power));
    }
}

long addFuelLine(int digits, char number[digits]) {
    long numberValue = 0;
    for (int i = 0; i < digits; i++) {
        numberValue += getDigitValue(digits - i - 1, number[i]);
    }
    return numberValue;
}

int main() {
    FILE *input = fopen("Input_Day-25.txt","r");
    long sumFuel = 0;

    if(input != NULL) {
        char line[64];
        while(fgets(line, sizeof(line), input) != NULL) {
            sumFuel += addFuelLine( strlen(line) - 1, line);
        }
    }
    fprintf(stdout, "Fuel Values summed up: %ld\n", sumFuel);
    char * convertedSum = convertToSNAFU(sumFuel);
    fprintf(stdout, "Fuel sum in SNAFU: %s\n", convertedSum);

    return 0;
}
