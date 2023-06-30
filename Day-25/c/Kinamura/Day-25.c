#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int getNumberDigits(int number) {
    int digits = 1;
    while(number > 9) {
        number /= 10;
        digits++;
    }
    return digits;
}

int getExponent(int number) {
    int digits = 2 * getNumberDigits(number);
    for(int i = digits; i >= 0; i++) {
        if( (2 * pow(5,digits) + 2 * pow(5,digits-1)) >= number &&
        (2 * pow(5,digits-1) + 2 * pow(5,digits-2)) <= number) {
            return i;
        }
    }
    return 0;
}

// check the fuckery
// wtf am I doing here
char getDigit(int number) {
    int exponent = getExponent(number);
    if( 2 * pow(5,exponent) >= number) {
        return '2';
    }
    if( pow(5,exponent) >= number) {
        return '1';
    }
    if( 2 * pow(5,exponent-1) + 2 * pow(5,exponent-2) >= number) {
        return '0';
    }
    if( 2 * pow(5,exponent-1) + 2 * pow(5,exponent-2) >= number - pow(5,exponent)) {
        return '-';
    }
    if( 2 * pow(5,exponent-1) + 2 * pow(5,exponent-2) >= number - 2 * pow(5,exponent)) {
        return '=';
    }
    fprintf(stdout,"passt so nicht\n");
    return -1;
}

char * convertToSNAFU(int number) {
    char *convertedNumber = malloc(128);
    while( number > 0 ) {
        getDigit(number);
    }
    return convertedNumber;
}

int getDigitValue(int power, char digit) {
    int digitValue;
    switch(digit) {
        case '2': digitValue = 2; break;
        case '1': digitValue = 1; break;
        case '0': digitValue = 0; break;
        case '-': digitValue = -1; break;
        case '=': digitValue = -2; break;
    }
    return digitValue * pow(5,power);
}

int addFuelLine(int digits, char number[digits]) {
    int numberValue = 0;
    for (int i = 0; i < digits; i++) {
        numberValue += getDigitValue(digits - i - 1, number[i]);
    }
    return numberValue;
}

int main() {
    FILE *input = fopen("testinput.txt","r");
    int sumFuel = 0;

    if(input != NULL) {
        char line[64];
        while(fgets(line, sizeof(line), input) != NULL) {
            sumFuel += addFuelLine( strlen(line) - 1, line);
        }
    }
    fprintf(stdout, "Fuel Values summed up: %d\n", sumFuel);
    char convertedSum[128];
    strcpy(convertedSum, convertToSNAFU(sumFuel));

    return 0;
}