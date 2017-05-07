/* >>>>DO NOT RUN THIS IF YOU HAVE IMPORTANT DATA IN YOUR DATABASE!!!<<<<
Upon running this file, the previous db will be dropped and a new one created.
This code is largely based on the following site(+ mysql's own doc..):
http://zetcode.com/db/mysqlc/  

Prequsite for executing this:
* installing mysql -> sudo apt-get install libmysqlclient-dev
  -note: when importing this into my code, i had to run it with the following flag: 
  '-I/usr/include/mysql'
* To enable connection to mysql, the code also needs to be run with the flags: 
  '-L/usr/include/mysql -lmysqlclient -lz' (here -L[path] is possibly optional and the path can 
  vary depending on where mysql is located)
* Ensure that mysql server is running on your machine before executing the code:
  - https://coolestguidesontheplanet.com/start-stop-mysql-from-the-command-line-terminal-osx-linux/
* You can now create your database (here in the end i included the compiling command + flags i use:
  'gcc -std=c11 -I/usr/include/mysql -pedantic -W -Wall [file_name].c -o [file_name] -L/usr/include/mysql -lmysqlclient -lz'
*/
typedef unsigned int uint;

#include <stdio.h>
#include <mysql.h>
#include <my_global.h>

int main (void)
{
  MYSQL *con = mysql_init(NULL);

  char pw_root_user[] = "kirk3kLokke_muf%fin";
  char db_name[] = "testDB";
  char log[] = "log";
  char identity_reg[] = "identity_reg";
  char service_reg[] = "service_reg";

  
  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", pw_root_user, 
          NULL, 0, NULL, 0) == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }  

  // This deletes the database (if it exists...) 
  char cleanup_query[] = "DROP DATABASE IF EXISTS ";
  strcat(cleanup_query, db_name);
  if (mysql_query(con, cleanup_query)) 
  {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
  }
  
  // This creates the database 
  char create_query[] = "CREATE DATABASE ";
  strcat(create_query, db_name);
  if (mysql_query(con, create_query)) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

  // Connect to the database "db_name"
  if (mysql_select_db(con, db_name)) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

  // creates the log-table
  char log_create[] = "CREATE TABLE ";
  strcat(log_create, log);
  strcat(log_create,
	 " (timestamp DATETIME, identity LONGTEXT, service LONGTEXT, action VARCHAR(200))");
  if (mysql_query(con, log_create)) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

  // creates the identity-table
  char identity_reg_create[] = "CREATE TABLE ";
  strcat(identity_reg_create, identity_reg);
  strcat(identity_reg_create,
  	 " (fullname VARCHAR(200), organization VARCHAR(200), role VARCHAR(200), id LONGTEXT)");
  if (mysql_query(con, identity_reg_create)) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

  // creates the registry-table
  char service_reg_create[] = "CREATE TABLE ";
  strcat(service_reg_create, service_reg);
  strcat(service_reg_create,
	 " (name VARCHAR(200), description VARCHAR(200), permission VARCHAR(200), id LONGTEXT)");
  if (mysql_query(con, service_reg_create)) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      exit(1);
  }

  // Close connection & exit program - the db and all tables should now be sucessfully created
  mysql_close(con);
  exit(0);
}
