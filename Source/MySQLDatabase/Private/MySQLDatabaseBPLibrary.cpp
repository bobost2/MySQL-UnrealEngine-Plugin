// Copyright Epic Games, Inc. All Rights Reserved.

#include "MySQLDatabaseBPLibrary.h"
#include "MySQLDatabase.h"
#include <MySQLDatabaseConnectorLibrary/MariaDB Connector C 64-bit/include/mysql.h>

UMySQLDatabaseBPLibrary::UMySQLDatabaseBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

TArray <MYSQL*> connections;

void UMySQLDatabaseBPLibrary::ConnectToDatabase(FString server, FString user, FString password, FString database, int port, int& connectionID, bool& connection_Status, FString& connection_Error)
{
	MYSQL* conn = mysql_init(NULL);

	if (mysql_real_connect(conn, TCHAR_TO_ANSI(*server), TCHAR_TO_ANSI(*user), TCHAR_TO_ANSI(*password), TCHAR_TO_ANSI(*database), port, NULL, 0))
	{
		connection_Status = true;
		connections.Add(conn);
		connectionID = connections.Num() - 1;
	}
	else
	{
		connection_Error = mysql_error(conn);
		connection_Status = false;
	}
}

void UMySQLDatabaseBPLibrary::CloseDatabase(int ConnectionID, bool& isSuccessful)
{
	if (connections.Num() != 0 && (ConnectionID + 1) <= connections.Num())
	{
		mysql_close(connections[ConnectionID]);
		connections.RemoveAtSwap(ConnectionID);
		isSuccessful = true;
	}
	else
	{
		isSuccessful = false;
	}
}

void UMySQLDatabaseBPLibrary::CloseAllConnections(bool& isSuccessful)
{
	if (connections.Num() != 0)
	{
		for (int i = 0; i < connections.Num(); i++)
		{
			mysql_close(connections[i]);
		}
		connections.Empty();
		isSuccessful = true;
	}
	else
	{
		isSuccessful = false;
	}
}

void UMySQLDatabaseBPLibrary::SendQuery(FString command, int ConnectionID, bool& isSuccessful)
{	
	if (connections.Num() != 0 && (ConnectionID + 1) <= connections.Num())
	{
		const char* query = TCHAR_TO_ANSI(*command);
		int qstate = mysql_query(connections[ConnectionID], query);
		if (qstate == 0)
		{
			isSuccessful = true;
		}
		else
		{
			isSuccessful = false;
		}
	}
}

void UMySQLDatabaseBPLibrary::ReciveData(FString command, int ConnectionID, TArray<FString>& result, int& rows, int& fields, bool& isSuccessful)
{
	if (connections.Num() != 0 && (ConnectionID + 1) <= connections.Num())
	{
		MYSQL_ROW row;
		MYSQL_RES* res;
		row = NULL;
		if (connections[ConnectionID])
		{
			int query = mysql_query(connections[ConnectionID], TCHAR_TO_ANSI(*command));
			if (!query)
			{
				res = mysql_store_result(connections[ConnectionID]);
				rows = res->row_count;
				fields = res->field_count;
				while ((row = mysql_fetch_row(res)) != 0) {
					for (int i = 0; i < fields; i++)
					{
						result.Add(row[i]);
					}
				}
				isSuccessful = true;
			}
			else
			{
				isSuccessful = false;
			}
		}
		else
		{
			isSuccessful = false;
		}
	}
	else
	{
		isSuccessful = false;
	}
}

void UMySQLDatabaseBPLibrary::FormatData(TArray<FString> data, int amountOfFields, int currentRow, TArray<FString>& result, bool& IsOutOfRange)
{
	if (((currentRow * amountOfFields) + amountOfFields) <= data.Num())
	{
		for (int i = 0; i < amountOfFields; i++)
		{
			result.Add(data[(currentRow * amountOfFields) + i]);
		}
		IsOutOfRange = false;
	}
	else
	{
		IsOutOfRange = true;
	}
}
