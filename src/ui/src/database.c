// C++ program for connecting to database (and error handling)
#include<stdio.h>
#include<SQLAPI.h>

int main(int argc, char* argv[])
{
	// create connection object to connect to database
	SAConnection con;
	try
	{
		// connect to database
		// in this example, it is Oracle,
		// but can also be Sybase, Informix, DB2
		// SQLServer, InterBase, SQLBase and ODBC
		con.Connect ("test", // database name
					"tester", // user name
					"tester", // password
					SA_Oracle_Client); //Oracle Client
		printf("We are connected!\n");

		// Disconnect is optional
		// autodisconnect will occur in destructor if needed
		con.Disconnect();
		printf("We are disconnected!\n");
	}

	catch(SAException &amp; x)
	{
		// SAConnection::Rollback()
		// can also throw an exception
		// (if a network error for example),
		// we will be ready
		try
		{
			// on error rollback changes
			con.Rollback ();
		}
		catch(SAException &amp;)
		{
		}
		// print error message
		printf("%s\n", (const char*)x.ErrText());
	}
	return 0;
}
