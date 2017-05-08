#ifndef DATABASE
#define DATABASE

#include <mysql/mysql.h>

struct database {
    MYSQL     *con;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *db_name;
    
};


int database_init(struct database *db, char *server, char *user, char *password, char *datab);
int database_close(struct database *db);

int database_generate(struct database *db);
int database_clean(struct database *db);


#endif
