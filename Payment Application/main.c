#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
//#include "card.h"
//#include "terminal.h"
//#include <stdio.h>
//#include <string.h>
//#include "server.h"
//#include <stdlib.h>
#include "Application/app.h"

ST_accountsDB_t accounts[255];
ST_transaction_t transactions[255];

//int main()
//{
//	appStart();
//}
	//ST_cardData_t card;


	//testing getCardHolderNames
	/*EN_cardError_t error = getCardHolderNames(&card);
	if (error == WRONG_NAME)
	{
		printf("Wrong Name Error: Name needs to be between 20 and 24 characters. \n");
	}
	else
	{
		puts(card.cardHolderName);
		printf("%d\n", strlen(card.cardHolderName));
	}*/

	//testing getCardExpiryDate
	/*EN_cardError_t error = getCardExpiryDate(&card);
	if (error == WRONG_EXP_DATE)
	{
		printf("Wrong Expiration Date Error: Date should be in the format MM/YY.\n");
	}
	else
	{
		puts(card.cardExpirationDate);
	}*/

	//testing getCardPAN
	/*EN_cardError_t error = getCardPAN(&card);
	if (error == WRONG_PAN)
	{
		printf("Wrong PAN Error: PAN should be alphanumeric and between 16 and 19 characters.\n");
	}
	else
	{
		puts(card.primaryAccountNumber);
		printf("%d\n", strlen(card.primaryAccountNumber));
	}*/

	//ST_terminalData_t terminal;

	//testing getTransactionDate
	//EN_terminalError_t error = getTransactionDate(&terminal);
	//if (error == WRONG_DATE)
	//{
	//	printf("Wrong Transaction Date Error: date should be in the format DD/MM/YYYY.\n");
	//}
	//else
	//{
	//	puts(terminal.transactionDate);
	//}

	//testing isCardExpired
	//EN_cardError_t error_card=getCardExpiryDate(&card);
	//if (error_card == WRONG_EXP_DATE)
	//{
	//	return 0;
	//}

	//EN_terminalError_t error_terminal=getTransactionDate(&terminal);
	//if (error_terminal == WRONG_DATE)
	//{
	//	return 0;
	//}
	//EN_terminalError_t error = isCardExpired(card,terminal);
	////printf("error numbers: %d %d", error, EXPIRED_CARD);
	//if (error == EXPIRED_CARD)
	//{
	//	printf("Card expired before transaction.");
	//}
	//else
	//{
	//	printf("Valid card");
	//}

	//testing getTransactionAmount
	/*EN_terminalError_t error = getTransactionAmount(&terminal);
	if (error == INVALID_AMOUNT)
	{
		printf("Invalid Amount Error: amount should be larger than 0.");
	}
	else
	{
		printf("%f",terminal.transAmount);
	}*/

	//testing setMaxAmount
	/*EN_terminalError_t error = setMaxAmount(&terminal);
	if (error == INVALID_MAX_AMOUNT)
	{
		printf("Invalid Max Amount Error: amount should be larger than 0.");
	}
	else
	{
		printf("%f", terminal.maxTransAmount);
	}*/

	//testing isBelowMaxAmount
	//setMaxAmount(&terminal);
	//getTransactionAmount(&terminal);
	//EN_terminalError_t error = isBelowMaxAmount(&terminal);
	//if (error == EXCEED_MAX_AMOUNT)
	//{
	//	printf("Transaction exceeds the maximum amount!");
	//}
	//else
	//{
	//	printf("Transaction is below the maximum amount.");
	//}

	//testing isValidCardPAN
	/*strcpy(card.primaryAccountNumber, "1111111111111117");
	EN_terminalError_t valid_error = isValidCardPAN(&card);
	if (valid_error == OK_t)
	{
		printf("PAN is a luhn number.\n");
	}
	else
	{
		printf("PAN is not a luhn number.\n");
	}*/



	//uint8_t i_accounts;
	//uint8_t PAN[20];
	//uint8_t temp[16] = "123456789123456";
	//for (i_accounts = 0; i_accounts < 255; i_accounts++)
	//{
	//	if (i_accounts < 10)
	//	{
	//		PAN[0] = 48 + i_accounts % 10; PAN[1] = '\0';
	//	}
	//	else if (i_accounts < 100)
	//	{
	//		PAN[1] = 48 + i_accounts % 10; PAN[0] = 48 + (i_accounts/10) % 10; PAN[2] = '\0';
	//	}
	//	else
	//	{
	//		PAN[2] = 48 + i_accounts % 10; PAN[1] = 48 + (i_accounts / 10) % 10; PAN[0] = 48 + (i_accounts / 100) % 10; PAN[3] = '\0';
	//	}
	//	strcat(PAN, temp);
	//	accounts[i_accounts].balance = i_accounts*100.0;
	//	strcpy(accounts[i_accounts].primaryAccountNumber, PAN);
	//}
	//FILE* dbptr;

	//dbptr = fopen("Accounts DB.txt","w");
	//for (i_accounts = 0; i_accounts < 255; i_accounts++)
	//{
	//	fprintf(dbptr, "%f %s\n", accounts[i_accounts].balance , accounts[i_accounts].primaryAccountNumber);
	//}
	//fclose(dbptr);
	//printf("done\n");
	//

	////testing isValidAccount
	//ST_cardData_t cardData = {"Peter Magdy Zaky Abdels","1123456789123456","05/24"};
	//EN_serverError_t server_error = isValidAccount(&cardData);
	//if (server_error == OK_s)
	//{
	//	printf("Account is valid.\n");
	//}
	//else
	//{
	//	printf("Account is not in the database.\n");
	//}

	////testing isAmountAvailable
	//ST_terminalData_t termData = { 125.0,10000,"20/02/2022" };
	//EN_serverError_t server_error2 = isAmountAvailable(&termData,&cardData);
	//if (server_error2 == OK_s)
	//{
	//	printf("The amount is available.\n");
	//}
	//else
	//{
	//	printf("Balance is too low.\n");
	//}

	////testing saveTransaction
	//ST_transaction_t transaction = { cardData, termData,OK_s,0};
	////transactions[0].transactionSequenceNumber = 12;
	//EN_serverError_t server_error3 = saveTransaction(&transaction);
	//if (server_error3 == OK_s)
	//{
	//	printf("Transaction was saved.\n");
	//}
	//else
	//{
	//	printf("Transaction could not be saved.\n");
	//}

	////testing recieveTransactionData
	//printf("-------------------------\n");
	//EN_transState_t state = recieveTransactionData(&transaction);
	//if (state == APPROVED)
	//{
	//	uint8_t PAN[20];
	//	strcpy(PAN, cardData.primaryAccountNumber);
	//	int i;
	//	float balance = 0;
	//	for (i = 0; i < 255; i++)
	//	{
	//		if (strcmp(PAN, accounts[i].primaryAccountNumber) == 0)
	//		{
	//			balance = accounts[i].balance;
	//		}
	//	}
	//	printf("Updated balance: %f\n", balance);
	//}
	//else if (state == DECLINED_STOLEN_CARD)
	//{
	//	printf("Card data not found in the database.\n");
	//}
	//else if (state == DECLINED_INSUFFECIENT_FUND)
	//{
	//	printf("Balance does not cover the transaction amount.\n");
	//}
	//else
	//{
	//	printf("Internal server error, contact an administrator.");
	//}

	////testing getTransaction
	//ST_transaction_t* transData = malloc(sizeof(ST_transaction_t));
	//EN_serverError_t find_trans_error = getTransaction(5, transData);

	//if (find_trans_error == OK_s)
	//{
	//	printf("Transaction amount: %f\n", transData->terminalData.transAmount);
	//}
	//else
	//{
	//	printf("Transaction not found.\n");
	//}
	//printf("\n");
	//return 0;
