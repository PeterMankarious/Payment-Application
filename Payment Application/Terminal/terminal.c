#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include "terminal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	EN_terminalError_t error = OK_Terminal;
	//Date should be 10 characters (+ Null character) in the format DD/MM/YYYY
	uint8_t date[13];
	printf("Please enter transaction date DD/MM/YYYY. If you want to use today's date type 'today'.\n");
	fgets(date, 13, stdin); //10 + 1 for null character + 1 for \n + 1 to detect oversize.

	if (date[strlen(date) - 1] == '\n')
	{
		date[strlen(date) - 1] = '\0'; //remove newline character
	}

	if (!strcmp(date, "today"))
	{
		time_t seconds = time(NULL);
		struct tm current_date = *localtime(&seconds);
		int current_year = current_date.tm_year + 1900;
		int current_month = current_date.tm_mon + 1;
		int current_day = current_date.tm_mday;
		uint8_t current_date_string[11];
		sprintf(&current_date_string,"%02d/%02d/%d", current_day, current_month, current_year);
		strcpy(termData->transactionDate, current_date_string);
		return error;
	}
	int date_len = strlen(date);

	//puts(date); //testing
	//printf("date length : % d\n", date_len); //testing

	if (date == NULL || date_len != 10)
	{
		error = WRONG_DATE;
		return error;
	}
	if (!isdigit(date[0]) || !isdigit(date[1]) || date[2] != '/' 
		|| !isdigit(date[3]) || !isdigit(date[4]) || date[5] != '/'
		|| !isdigit(date[6])|| !isdigit(date[7]) || !isdigit(date[8]) || !isdigit(date[9]))
	{
		error = WRONG_DATE;
		return error;
	}

	uint8_t days[3];
	days[0] = date[0]; days[1] = date[1]; days[2] = '\0';
	int days_i = atoi(days);

	//puts(days); //testing
	//printf("days: %d %d\n", days_i,(days_i <= 0 || days_i > 31)); //testing

	if (days_i <= 0 || days_i > 31)
	{
		//printf("error in day"); // testing
		error = WRONG_DATE;
		return error;
	}

	uint8_t months[3];
	months[0] = date[3]; months[1] = date[4]; months[2] = '\0';
	int months_i = atoi(months);

	//puts(months); //testing
	//printf("months: %d %d\n", months_i,(months_i <= 0 || months_i > 12)); //testing

	if (months_i <= 0 || months_i > 12)
	{
		error = WRONG_DATE;
		return error;
	}

	strcpy(termData->transactionDate, date);
	return error;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	EN_terminalError_t error = OK_Terminal;

	uint8_t expDate[6]; strcpy(expDate, cardData.cardExpirationDate);
	uint8_t tranDate[11]; strcpy(tranDate, termData.transactionDate);

	uint8_t expYears[5];
	expYears[0] = '2'; expYears[1] = '0'; expYears[2] = expDate[3]; expYears[3] = expDate[4]; expYears[4] = '\0';
	int expYears_i = atoi(expYears);
	//printf("Expiration Year: %d\n", expYears_i); //testing


	uint8_t tranYears[5];
	tranYears[0] = tranDate[6]; tranYears[1] = tranDate[7]; tranYears[2] = tranDate[8];
	tranYears[3] = tranDate[9];  tranYears[4] = '\0';
	int tranYears_i = atoi(tranYears);
	//printf("Transaction Year: %d\n", tranYears_i); //testing
	if (expYears_i < tranYears_i)
	{
		//printf("expired (years)\n"); //testing
		error = EXPIRED_CARD;
		return error;
	}
	else if (expYears_i > tranYears_i)
	{
		return error;
	}
	
	uint8_t expMonths[3];
	expMonths[0] = expDate[0]; expMonths[1] = expDate[1]; expMonths[2] = '\0';
	int expMonths_i = atoi(expMonths);
	//printf("Expiration Month: %d\n", expMonths_i); //testing

	uint8_t tranMonths[3];
	tranMonths[0] = tranDate[3]; tranMonths[1] = tranDate[4]; tranMonths[2] = '\0';
	int tranMonths_i = atoi(tranMonths);
	//printf("Transaction Month: %d\n", tranMonths_i); //testing

	if (expMonths_i < tranMonths_i)
	{
		//printf("expired (months)\n");//testing
		error = EXPIRED_CARD;
	}
	//testing
	/*if (error == EXPIRED_CARD)
	{
		printf("output error is expired card\n");
	}
	if (error == OK_t)
	{
		printf("output is OK\n");
	}*/
	return error;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	int total = 0;
	uint8_t PAN[20];
	strcpy(PAN, cardData->primaryAccountNumber);
	int i = 0;
	for (i = strlen(PAN) - 1; i >= 0; i--)
	{
		uint8_t digit = PAN[i] - '0';
		if ((strlen(PAN) - 1 - i) % 2 == 1)
		{
			digit = digit * 2;
			if (digit >= 10)
			{
				digit = digit % 10 + digit / 10;
			}
		}
		total = total + digit;
	}
	printf("Total is %d\n", total);
	if (total % 10 == 0)
	{
		return OK_Terminal;
	}
	else
	{
		return INVALID_CARD;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t error = OK_Terminal;
	
	printf("Enter transaction amount.\n");
	float amount;
	scanf("%f", &amount);
	if (amount <= 0)
	{
		error = INVALID_AMOUNT;
		return error;
	}
	termData->transAmount = amount;
	return error;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t error = OK_Terminal;
	float maxAmount = termData->maxTransAmount;
	float transAmount = termData->transAmount;
	
	if (transAmount > maxAmount)
	{
		error = EXCEED_MAX_AMOUNT;
	}
	return error;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t error = OK_Terminal;

	printf("Enter max transaction amount.\n");
	float amount;
	scanf("%f", &amount);
	if (amount <= 0)
	{
		error = INVALID_MAX_AMOUNT;
		return error;
	}
	termData->maxTransAmount = amount;
	return error;
}