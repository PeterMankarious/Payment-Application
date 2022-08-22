#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include "app.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

ST_accountsDB_t accounts[255];
ST_transaction_t transactions[255];

void appStart(void)
{
	ST_cardData_t card;
	EN_cardError_t card_error;
	while (1)
	{
		card_error = getCardHolderNames(&card);
		if (card_error == WRONG_NAME)
		{
			printf("Wrong Name Error: Name needs to be between 20 and 24 alphabetic characters. \n\n");
		}
		else
		{
			printf("Card holder is %s.\n\n", card.cardHolderName);
			break;
		}
	}
	while (1)
	{
		card_error = getCardExpiryDate(&card);
		if (card_error == WRONG_EXP_DATE)
		{
			printf("Wrong Expiration Date Error: Date should be in the format MM/YY.\n\n");
		}
		else
		{
			printf("Expiration date is: %s.\n\n",card.cardExpirationDate);
			break;
		}
	}

	while (1)
	{
		card_error = getCardPAN(&card);
		if (card_error == WRONG_PAN)
		{
			printf("Wrong PAN Error: PAN should be alphanumeric and between 16 and 19 numeric digits.\n\n");
		}
		else
		{
			printf("The entered PAN is: %s.\n\n", card.primaryAccountNumber);
			break;
		}
	}

	ST_terminalData_t terminal;
	terminal.maxTransAmount = 10000;

	EN_terminalError_t terminal_error;
	while (1)
	{
		terminal_error = getTransactionDate(&terminal);
		if (terminal_error == WRONG_DATE)
		{
			printf("Wrong Transaction Date Error: date should be in the format DD/MM/YYYY.\n\n");
		}
		else
		{
			printf("The entered transaction date is %s.\n\n", terminal.transactionDate);
			break;
		}
	}

	terminal_error = isCardExpired(card,terminal);
	if (terminal_error == EXPIRED_CARD)
	{
		printf("The card is expired. Transaction declined.\n\n");
		return;
	}
	else
	{
		printf("Card validated.\n\n");
	}

	terminal_error = isValidCardPAN(&card);
	if (terminal_error == OK_Terminal)
	{
		printf("Card authenticated.\n\n");
	}
	else
	{
		printf("Fraud card detected. Transaction declined.\n\n");
		return;
	}
	
	while(1)
	{
		terminal_error = getTransactionAmount(&terminal);
		if (terminal_error == INVALID_AMOUNT)
		{
			printf("Invalid Amount Error: amount should be larger than 0.\n\n");
		}
		else
		{
			printf("The transfer amount is: %f.\n\n", terminal.transAmount);
			break;
		}
	}

	terminal_error = isBelowMaxAmount(&terminal);
	if (terminal_error == EXCEED_MAX_AMOUNT)
	{
		printf("Transaction can not exceed %f. Transaction declined.\n\n",terminal.maxTransAmount);
		return;
	}
	else
	{
		printf("Transaction is below the maximum allowable amount.\n\n");
	}


	uint8_t i_accounts;
	uint8_t PAN[20];
	uint8_t temp[16] = "123456789123456";
	for (i_accounts = 0; i_accounts < 255; i_accounts++)
	{
		if (i_accounts < 10)
		{
			PAN[0] = 48 + i_accounts % 10; PAN[1] = '\0';
		}
		else if (i_accounts < 100)
		{
			PAN[1] = 48 + i_accounts % 10; PAN[0] = 48 + (i_accounts/10) % 10; PAN[2] = '\0';
		}
		else
		{
			PAN[2] = 48 + i_accounts % 10; PAN[1] = 48 + (i_accounts / 10) % 10; PAN[0] = 48 + (i_accounts / 100) % 10; PAN[3] = '\0';
		}
		strcat(PAN, temp);
		accounts[i_accounts].balance = i_accounts*100.0;
		strcpy(accounts[i_accounts].primaryAccountNumber, PAN);
	}

	strcpy(accounts[25].primaryAccountNumber, "1111111111111117");
	accounts[25].balance = 50000;

	FILE* dbptr;

	dbptr = fopen("Accounts DB.txt","w");
	for (i_accounts = 0; i_accounts < 255; i_accounts++)
	{
		fprintf(dbptr, "%f %s\n", accounts[i_accounts].balance , accounts[i_accounts].primaryAccountNumber);
	}
	fclose(dbptr);


	ST_transaction_t transaction = {card,terminal,OK_Server,0};
	EN_transState_t state = recieveTransactionData(&transaction);
	if (state == APPROVED)
	{
		uint8_t PAN[20];
		strcpy(PAN, card.primaryAccountNumber);
		int i;
		float balance = 0;
		for (i = 0; i < 255; i++)
		{
			if (strcmp(PAN, accounts[i].primaryAccountNumber) == 0)
			{
				balance = accounts[i].balance;
			}
		}
		printf("Transaction saved and approved. Updated balance: %f\n\n", balance);
	}
	else if (state == DECLINED_STOLEN_CARD)
	{
		printf("Account is invalid. Transaction declined. \n\n");
		return;
	}
	else if (state == DECLINED_INSUFFECIENT_FUND)
	{
		printf("Insufficient Funds: Balance does not cover the transaction amount. Transaction declined.\n\n");
		return;
	}
	else
	{
		printf("Internal server error, contact an administrator. \n\n");
		return;
	}
}

int main()
{
	appStart();
}