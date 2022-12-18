# About this plugin
Simple plugin that allows the developers to use MySQL with the Unreal Engine blueprint language.

It was created originally for a school project back in early 2021.

Updated to work with UE 5.1

# Is it secure?
Please do not use this plugin in production. Your database password could be exposed if someone tries to reverse engineer your code. Instead, use API's to access a remote database. [VaRest](https://www.unrealengine.com/marketplace/en-US/product/varest-plugin) is a plugin that allows you to communicate with these API's.

# Installation
- Create a `Plugins` folder in your project directory if it doesn't exist.
- Inside that `Plugins` folder, extract the [repo](https://github.com/bobost2/MySQL-UnrealEngine-Plugin/archive/refs/heads/main.zip)
- If done correctly, you should have in the `Plugins` folder another folder, named `MySQL-UnrealEngine-Plugin-main`. You can rename it whatever you like, but it's recommended to not touch the files inside that folder.

# Node documentation
## Connect to database
Used to make connection between the database and the client.

![ConnectToDB image](https://user-images.githubusercontent.com/24987944/208312854-5622a7cd-d5a7-4119-8b40-aa9bc2f7a76e.jpg)

Inputs:
- `Server` - The IP address of the database server
- `User` - The username of the user that has access to the database
- `Password` - The password of the user that has access to the database
- `Database` - The name of the database the user is trying to access
- `Port` - The port of the database server (Usually is 3306)

Outputs:
- `Connection ID` - Store it in a variable, so you can access the DB later
- `Connection Status` - Returns true if connection is successful
- `Connection Error` - Returns an error message if the connection failed

### Example
![Example image #1](https://user-images.githubusercontent.com/24987944/208313300-8d80e262-db24-4ccd-8fda-dc939e76a040.jpg)

### ⚠️ Warning
The database user has to identify with `mysql_native_password`, otherwise it will throw an error that a plugin for caching a sha2 password is missing and will refuse to connect. To fix the issue, create new user or alter existing one. Here's how:
```SQL
# Create user
CREATE USER 'userDB'@'%' IDENTIFIED WITH mysql_native_password BY 'SecurePassword';

# Alter user
ALTER USER 'userDB'@'%' IDENTIFIED WITH mysql_native_password BY 'SecurePassword';
```

## Send query
Send query to the database. Useful for creating entries or any other task that doesn't return rows.

![SendQuery node image](https://user-images.githubusercontent.com/24987944/208314567-ff438d91-e32a-4352-92f2-9bb784d6592a.jpg)

Inputs:
- `Command` - The query to execute
- `Connection ID` - The ID that the `Connect to database` node returns

Outputs:
- `Is Successful` - Returns true if there are no issues with the query

### Example
![Example image #2](https://user-images.githubusercontent.com/24987944/208314782-fa388b0d-d1ce-4d85-beed-ae143170da14.jpg)

## Recieve data (Query)
Send query to the database that returns unformatted data.

![Recieve data node image](https://user-images.githubusercontent.com/24987944/208315166-b909db3d-9956-4904-945f-dd741d1d8ea3.jpg)

Inputs:
- `Command` - The query to execute
- `Connection ID` - The ID that the `Connect to database` node returns

Outputs:
- `Result` - Unformatted response from the query
- `Rows` - The amount of rows the query returned
- `Fields` - The amount of fields the query returned
- `Is Successful` - Returns true if there are no issues with the query

## Format data
After receiving data from the `Recive data (Query)` node, it returns an array of string that represent the fields in a specific row.
Returns only one entry.

![Format data node image](https://user-images.githubusercontent.com/24987944/208315344-1968a844-05d6-4679-a389-398e05f4d153.jpg)

Inputs:
- `Data` - The result from the `Recive data (Query)` node
- `Amount Of Fields` - Amount of fields returned from the `Recive data (Query)` node
- `Current Row` - Current row index 

Outputs:
- `Result` - Array of strings that represent the fields in a specific row
- `Is Out Of Range` - If the `Current Row` index is out of range

### Example
![Example image #3](https://user-images.githubusercontent.com/24987944/208315791-cfd57543-f052-43f1-8bee-653562e36f43.jpg)

## Close connection
If we no longer need to interact with the database, we close the connection to save resources.

![Close connection node image](https://user-images.githubusercontent.com/24987944/208315944-0eb0d1fc-a0aa-4c02-99ed-1ea6c4b0cf80.jpg)

Inputs:
- `Connection ID` - The ID that the `Connect to database` node returns

Outputs:
- `Is Successful` - Returns true if the database connection is successfully closed

## Close all connections
Similar to the `Close connection` node, but instead of one, it closes all connections.

![Close all connections node image](https://user-images.githubusercontent.com/24987944/208316032-41280895-7ded-4c22-9f2e-c514721d9562.jpg)

Outputs:
- `Is Successful` - Returns true if the database connections are successfully closed
