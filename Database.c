#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


char *readTestData(char *filename){
    
    FILE *fp = fopen(filename, "r");

    char *source;

    if(fp){

        /*Go to the end of the file */
        if(fseek(fp, 0L, SEEK_END) == 0){

            long bufsize = ftell(fp);

            if(bufsize == -1){
                fprintf(stderr, "[ERROR] Could not read file\n");
            }

            /* Allocate our buffer to that size.  */
            source = malloc(sizeof(char) * (bufsize + 1));

            /*  Go back to the start of the file. */
            if(fseek(fp, 0L, SEEK_SET) != 0){
                fprintf(stderr, "[ERROR] Could not read file\n");
            }

            /* Read the entire file into memory. */
            size_t newLen = fread(source, sizeof(char), bufsize, fp);

            if(ferror(fp) != 0){
                fprintf(stderr, "[ERROR] Could not read file\n"); 
            } else {
                /* Just to be sure that the file has an ending. */
                source[newLen++] = '\0';
            }

            fclose(fp);
        }
    } else{
        fprintf(stderr, "[ERROR] Could not read file: %s\n", filename);
    }

    return source;
}



int addService(struct database *db, char* name, char* desc, char* perm, char* id){
    
    if(mysql_select_db(db->con, db->db_name)){

        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }

    char *insert = "INSERT INTO service_reg(name, description, permission, id) VALUES (";
    char *query = malloc(strlen(insert) + strlen(name) + strlen(desc) + strlen(perm) + strlen(id) + 10);

    
    strcpy(query, insert);
    strcat(query, "'");
    strcat(query, name);
    strcat(query, "'");
    strcat(query, ", ");
    strcat(query, "'");
    strcat(query, desc);
    strcat(query, "'");
    strcat(query, ", ");
    strcat(query, "'");
    strcat(query, perm);
    strcat(query, "'");
    strcat(query, ", ");
    strcat(query, "'");
    strcat(query, id);
    strcat(query, "'");
    strcat(query, ")");


    if(mysql_query(db->con, query)){
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

int addIdentity(struct database *db, char* name, char* org, char* role, char* id){
    
    if(mysql_select_db(db->con, db->db_name)){

        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }

    char *insert = "INSERT INTO identity_reg(fullname, organization, role, id) VALUES (";
    char *query = malloc(strlen(insert) + strlen(name) + strlen(org) + strlen(role) + strlen(id) + 10);

    
    strcpy(query, insert);
    strcat(query, "'");
    strcat(query, name);
    strcat(query, "'");
    strcat(query, ", ");
    strcat(query, "'");
    strcat(query, org);
    strcat(query, "'");
    strcat(query, ", ");
    strcat(query, "'");
    strcat(query, role);
    strcat(query, "'");
    strcat(query, ", ");
    strcat(query, "'");
    strcat(query, id);
    strcat(query, "'");
    strcat(query, ")");


    if(mysql_query(db->con, query)){
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

int splitTestData(struct database *db, char* testData, int numData, int iS){
    
    char *name = strtok(testData, ",");
    char *des  = strtok(NULL, ",");
    char *per  = strtok(NULL, ",");
    char *id   = strtok(NULL, "\n");

    if(iS){
        addService(db, name, des, per, id);
    } else {
        addIdentity(db, name, des, per, id);
    }

    for(int i = 0; i < (numData-1); i++){
        name = strtok(NULL, ",");

        if(name == NULL){
            fprintf(stderr, "[Error] Wrong file format\n");
            return EXIT_FAILURE;
        }

        des  = strtok(NULL, ",");
        
        if(des == NULL){
            fprintf(stderr, "[Error] Wrong file format\n");
            return EXIT_FAILURE;
        }

        per  = strtok(NULL, ",");
        
        if(per == NULL){
            fprintf(stderr, "[Error] Wrong file format\n");
            return EXIT_FAILURE;
        }
        
        id  = strtok(NULL, "\n");
        
        if(id == NULL){
            fprintf(stderr, "[Error] Wrong file format\n");
            return EXIT_FAILURE;
        }
        
        if(iS){
            addService(db, name, des, per, id);
        } else {
            addIdentity(db, name, des, per, id);
        }

    }
    
    if(iS){
        fprintf(stdout, "[OK] Added %d data values to service_reg\n", numData);
    } else {
        fprintf(stdout, "[OK] Added %d data values to identity_reg\n", numData);
    }

    
    return EXIT_SUCCESS;


}


int countLines(char *filename){
    
    FILE *fp = fopen(filename, "r");
    
    int count = 0;
    char c;


    if(fp){

        for(c = getc(fp); c != EOF; c = getc(fp)){
            if(c == '\n'){
                count++;
            }
        }

        fclose(fp);

    } else{
        fprintf(stderr, "[ERROR] Could not read file: %s\n", filename);
        return EXIT_FAILURE;
    }



    return count;


}

int database_addTestData(struct database *db){
    
    char *serviceData = readTestData("Data/serviceData.txt");
    char *identityData = readTestData("Data/identityData.txt");

    int serviceLines = countLines("Data/serviceData.txt");
    int identityLines = countLines("Data/identityData.txt");

    int service  = splitTestData(db, serviceData, serviceLines, 1);
    int identity = splitTestData(db, identityData, identityLines, 0);
    

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
    
    char *identity_reg_create = "CREATE TABLE identity_reg (fullname VARCHAR(200), organization VARCHAR(200), role VARCHAR(200), id LONGTEXT)";

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
