// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include <MySQLDatabaseConnectorLibrary/MariaDB Connector C 64-bit/include/mysql.h>
#include "MySQLDatabaseBPLibrary.generated.h"


/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/


UCLASS()
class UMySQLDatabaseBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Connect to database", Keywords = "Database MySQL connect server"), Category = "MySQL Database|Connection")
		static void ConnectToDatabase(FString server, FString user, FString password, FString database, int port, int& connectionID, bool& connection_Status, FString& connection_Error);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Close connection", Keywords = "Database MySQL connect close disconnect server"), Category = "MySQL Database|Connection")
		static void CloseDatabase(int ConnectionID, bool& isSuccessful);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Send query", Keywords = "send database MySQL query data server"), Category = "MySQL Database|Send Data")
		static void SendQuery(FString command, int ConnectionID, bool& isSuccessful);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Close all connections", Keywords = "all everything database MySQL connect close disconnect server"), Category = "MySQL Database|Connection")
		static void CloseAllConnections(bool& isSuccessful);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Recive data (Query)", Keywords = "recive database MySQL query data server"), Category = "MySQL Database|Recive Data")
		static void ReciveData(FString command, int ConnectionID, TArray<FString>& result, int& rows, int& fields, bool& isSuccessful);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Format data", Keywords = "recive format database MySQL query data server"), Category = "MySQL Database|Format Data")
		static void FormatData(TArray<FString> data, int amountOfFields, int currentRow, TArray<FString>& result, bool& IsOutOfRange);
};
