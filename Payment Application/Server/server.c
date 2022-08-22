#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include "server.h"
#include <stdio.h>
#include <string.h> 

ST_accountsDB_t accounts[255];
ST_transaction_t transactions[255] = { 0 };


EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_transState_t state = APPROVED;
	transData->transState = state;

	ST_cardData_t cardData = transData->cardHolderData;
	ST_terminalData_t termData = transData->terminalData;
	EN_serverError_t validError = isValidAccount(&cardData);
	if (validError == DECLINED_STOLEN_CARD)
	{
		state = DECLINED_STOLEN_CARD;
		transData->transState = state;
		EN_serverError_t saveError = saveTransaction(transData);
		if (saveError == SAVING_FAILED)
		{
			state = INTERNAL_SERVER_ERROR;
			return state;
		}
	}
	else
	{
		EN_serverError_t amountError = isAmountAvailable(&termData,&cardData);
		if (amountError == LOW_BALANCE)
		{
			state = DECLINED_INSUFFECIENT_FUND;
			transData->transState = state;
			EN_serverError_t saveError = saveTransaction(transData);
			if (saveError == SAVING_FAILED)
			{
				state = INTERNAL_SERVER_ERROR;
				return state;
			}
		}
	}
	if (state == APPROVED)
	{
		transData->transState = state;
		EN_serverError_t saveError = saveTransaction(transData);
		if (saveError == SAVING_FAILED)
		{
			state = INTERNAL_SERVER_ERROR;
			return state;
		}

		uint8_t PAN[20];
		strcpy(PAN, cardData.primaryAccountNumber);
		int i;
		for (i = 0; i < 255; i++)
		{
			if (strcmp(PAN, accounts[i].primaryAccountNumber) == 0)
			{
				accounts[i].balance = accounts[i].balance - transData->terminalData.transAmount;
			}
		}
	}
	return state;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	EN_serverError_t error = OK_Server;
	uint8_t PAN[20];
	strcpy(PAN, cardData -> primaryAccountNumber);
	int i;
	unsigned char found_flag = 0;
	for (i = 0; i < 255; i++)
	{
		if (strcmp(PAN, accounts[i].primaryAccountNumber) == 0)
		{
			found_flag = 1;
		}
	}
	if (!found_flag)
	{
		error = DECLINED_STOLEN_CARD;
	}
	return error;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData,ST_cardData_t* cardData)
{
	EN_serverError_t error = OK_Server;

	uint8_t PAN[20];
	strcpy(PAN, cardData->primaryAccountNumber);
	int i;
	float balance = 0;
	for (i = 0; i < 255; i++)
	{
		if (strcmp(PAN, accounts[i].primaryAccountNumber) == 0)
		{
			balance = accounts[i].balance;
		}
	}
	
	if (termData->transAmount > balance)
	{
		error = LOW_BALANCE;
	}
	return error;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	EN_serverError_t error = OK_Server;
	static uint32_t sequenceNumber = 1;
	static curIndex = 0;
	if (curIndex >= 255)
	{
		error = SAVING_FAILED;
		return error;
	}
	if (transactions[curIndex].transactionSequenceNumber == 0)
	{
		transData->transactionSequenceNumber = sequenceNumber;
		transactions[curIndex] = *transData;
		curIndex++;
		sequenceNumber++;
	}
	else
	{
		error = SAVING_FAILED;
	}
	return error;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	EN_serverError_t error = OK_Server;
	int i = 0;
	uint8_t found_flag = 0;
	for (i = 0; i < 255; i++)
	{
		if (transactionSequenceNumber == transactions[i].transactionSequenceNumber)
		{
			found_flag = 1;
			break;
		}
	}
	if (found_flag)
	{
		*transData = transactions[i];
	}
	else
	{
		error = TRANSACTION_NOT_FOUND;
	}
	return error;
}