// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class MySQLDatabaseConnectorLibrary : ModuleRules
{
	public MySQLDatabaseConnectorLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Android)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "MariaDB Connector C 64-bit", "lib", "libmariadb.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "MariaDB Connector C 64-bit", "lib", "libmariadbclient.lib"));

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("libmariadb.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/MySQLDatabaseConnectorLibrary/Win64/libmariadb.dll");
        }
		//Support for win32 is dropped in UE5
        /*else if (Target.Platform == UnrealTargetPlatform.Win32)
        {
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "MariaDB Connector C", "lib", "libmariadb.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "MariaDB Connector C", "lib", "libmariadbclient.lib"));

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("libmariadb.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/ThirdParty/MySQLDatabaseConnectorLibrary/Win32/libmariadb.dll");
		}*/
	}
}
