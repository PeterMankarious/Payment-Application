#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include "card.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



EN_cardError_t getCardHolderNames(ST_cardData_t* cardData)
{
	EN_cardError_t error = OK_Card;
	//Name should be between 20 and 24 characters (+ Null character)
	uint8_t name[26]; //24 + 1 for null character + 1 to detect oversize.
	//scanf("%25s", name);
	printf("Please enter the cardholder's name.\n");
	fgets(name, 26, stdin); 

	if (name[strlen(name) - 1] == '\n')
	{
		name[strlen(name) - 1] = '\0'; //remove newline character
	}
	
	int name_len = strlen(name);
	//puts(name); //testing
	//printf("name length : % d\n", name_len); //testing

	if (name == NULL || name_len < 20 || name_len == 25)
	{
		error = WRONG_NAME;
		return error;
	}

	int i;
	for (i = 0; i < name_len; i++)
	{
		if (!isalpha(name[i]) && !(name[i] == ' '))
		{
			error = WRONG_NAME;
			return error;
		}
	}


	strcpy(cardData -> cardHolderName,name);
	return error;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	EN_cardError_t error = OK_Card;
	//Date should be 5 characters (+ Null character) in the format MM/YY
	uint8_t date[8];
	printf("Please enter the card expiry date. MM/YY\n");
	fgets(date, 8, stdin); //5 + 1 for null character + 1 for \n + 1 to detect oversize.
	if (date[strlen(date) - 1] == '\n')
	{
		date[strlen(date) - 1] = '\0'; //remove newline character
	}

	int date_len = strlen(date);

	//puts(date); //testing
	//printf("date length : % d\n", date_len); //testing

	if (date == NULL || date_len != 5)
	{
		error = WRONG_EXP_DATE;
		return error;
	}

	if (!isdigit(date[0]) || !isdigit(date[1]) || date[2] != '/' || !isdigit(date[3]) || !isdigit(date[4]))
	{
		error = WRONG_EXP_DATE;
		return error;
	}

	uint8_t months[3];
	months[0] = date[0]; months[1] = date[1]; months[2] = '\0';
	int months_i = atoi(months);

	//puts(months); //testing
	//printf("months: %d %d\n", months_i,(months_i <= 0 || months_i > 12)); //testing

	if ( months_i <= 0 || months_i > 12 )
	{
		error = WRONG_EXP_DATE;
		return error;
	}

	strcpy(cardData->cardExpirationDate, date);
	return error;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	EN_cardError_t error = OK_Card;
	//Name should be between 16 and 19 characters (+ Null character)
	uint8_t PAN[21]; //19 + 1 for null character + 1 to detect oversize.
	printf("Please enter the Primary Account Number (PAN).\n");
	fgets(PAN, 21, stdin);
	if (PAN[strlen(PAN) - 1] == '\n')
	{
		PAN[strlen(PAN) - 1] = '\0'; //remove newline character
	}
	if (strcmp(PAN, "luhn") == 0)
	{
		printf("Please enter the PAN and the last digit will be automatically generated.\n");
		fgets(PAN, 21, stdin);
		if (PAN[strlen(PAN) - 1] == '\n')
		{
			PAN[strlen(PAN) - 1] = '\0'; //remove newline character
		}
		if (strlen(PAN) >= 19)
		{
			return WRONG_PAN;
		}
		int PAN_length = strlen(PAN);
		int total = 0;
		int i = 0;
		for (i = PAN_length - 1; i >= 0; i--)
		{
			uint8_t digit = PAN[i] - '0';
			if ((PAN_length - 1 - i) % 2 == 0)
			{
				digit = digit * 2;
				if (digit >= 10)
				{
					digit = digit % 10 + digit / 10;
				}
			}
			total = total + digit;
		}
		uint8_t extraDigit = (10 - total % 10) % 10;
		
		PAN[PAN_length] = '0' + extraDigit; PAN[PAN_length + 1] = '\0';
		printf("The added digit is %d and the final PAN is %s.\n", extraDigit, PAN);
	}


	int PAN_len = strlen(PAN);
	

	if (PAN == NULL || PAN_len < 16 || PAN_len == 20)
	{
		error = WRONG_PAN;
		return error;
	}
	int i;
	for (i = 0; i < PAN_len; i++)
	{
		if (!isdigit(PAN[i]))
		{
			error = WRONG_PAN;
			return error;
		}
	}
	strcpy(cardData->primaryAccountNumber, PAN);
	return error;
}

