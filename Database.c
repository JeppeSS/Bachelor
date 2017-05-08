#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "Database.h"


int database_init(struct database *db, char *server, char *user, char *password, char *datab){
    
    db->con = mysql_init(NULL);

    if(!db->con){
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }

    if (!mysql_real_connect(db->con, server,
         user, password, datab, 0, NULL, 0)) {
        
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }

    db->db_name = datab;

    fprintf(stdout, "[OK] Database initialized\n");
    
    return EXIT_SUCCESS;
}


int database_addTestData(struct database *db){
    
    if(mysql_select_db(db->con, db->db_name)){

        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;

}


int database_generate(struct database *db){

    char *almanac = "CREATE DATABASE Almanac";

    if(mysql_query(db->con, almanac)){
        
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }


    fprintf(stdout, "[OK] Build Database: Almanac\n");
    
    if(mysql_select_db(db->con, db->db_name)){

        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }


    char *log_create = "CREATE TABLE log (timestamp DATETIME, identity LONGTEXT, service LONGTEXT, action VARCHAR(200))";


    if(mysql_query(db->con, log_create)){
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }


    fprintf(stdout, "[OK] Created Table log\n");
    
    char *identity_reg_create = "CREATE TABLE identity_reg (fullname VARCHAR(200), organixation VARCHAR(200), role VARCHAR(200), id LONGTEXT)";

    if(mysql_query(db->con, identity_reg_create)){
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }
    
    fprintf(stdout, "[OK] Created Table identity_reg\n");

    char *service_reg_create = "CREATE TABLE service_reg (name VARCHAR(200), description VARCHAR(200), permission VARCHAR(200), id LONGTEXT)";

    if(mysql_query(db->con, service_reg_create)){
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }
    
    fprintf(stdout, "[OK] Created Table service_reg\n");


    return EXIT_SUCCESS;
}

int database_clean(struct database *db){
    
    char *dropTables = "DROP TABLE IF EXISTS log, identity_reg, service_reg";
   

    if(mysql_query(db->con, dropTables)){
        
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }

    char *dropAll = "DROP DATABASE IF EXISTS Almanac";
    
    if(mysql_query(db->con, dropAll)){
        
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }



    fprintf(stdout, "[OK] Cleaned Database\n");

    return EXIT_SUCCESS;

}


int database_close(struct database *db){
    
    /* Close connection */
    mysql_close(db->con);

    fprintf(stdout, "[OK] Database connection closed\n");

    return EXIT_SUCCESS;
}
