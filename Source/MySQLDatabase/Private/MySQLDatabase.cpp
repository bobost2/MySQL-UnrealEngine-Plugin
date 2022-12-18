// Copyright Epic Games, Inc. All Rights Reserved.

#include "MySQLDatabase.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
//#include <MySQLDatabaseConnectorLibrary/MariaDB Connector C 64-bit/include/mysql.h>
//#include <windows.h>

#define LOCTEXT_NAMESPACE "FMySQLDatabaseModule"

void FMySQLDatabaseModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FString BaseDir = IPluginManager::Get().FindPlugin("MySQLDatabase")->GetBaseDir();

	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/MySQLDatabaseConnectorLibrary/Win64/libmariadb.dll"));


	ExampleLibraryHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;
	/*
	if (ExampleLibraryHandle)
	{
		// Call the test function in the third party library that opens a message box
		MYSQL* conn;
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "***REMOVED***", "dbcon", "***REMOVED***", "***REMOVED***", 3306, NULL, 0);
		if (conn)
		{
			MessageBox(
				NULL,
				(LPCWSTR)L"Connected to the database.",
				(LPCWSTR)L"Database works!",
				MB_OK
			);
			mysql_close(conn);
		}
		else
		{
			const char* error = mysql_error(conn);
			MessageBox(
				NULL,
				(LPCWSTR)error,
				(LPCWSTR)L"Error: ",
				MB_OK
			);
		}

	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Database Plugin", "Failed to load MySQL database plugin!"));
	}*/
}

void FMySQLDatabaseModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FPlatformProcess::FreeDllHandle(ExampleLibraryHandle);
	ExampleLibraryHandle = nullptr;	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMySQLDatabaseModule, MySQLDatabase)