#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "Database.h"

int main(int argc, char* argv[]){
    
    struct database db;

    database_init(&db, "localhost", "root", "kirk3kLokke_muf%fin", "Almanac");
    database_clean(&db);
    database_generate(&db);
    database_addTestData(&db);
    getIdentity(&db, "Jens Peter");
    database_close(&db);

    return 0;    
}
