#include "database.h"
#include <string>

void database::Database::_errorCheck(int ErrCode){
    fprintf(stderr, "SQLITE ERROR: %s\n", sqlite3_errmsg(_db));
}
void database::Database::errorCheck(databaseErrorMsg ErrMessage){
    fprintf(stderr, "SQLITE ERROR: %s\n", ErrMessage);
}


int database::Database::callBack(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void database::Database::createTable(std::string name){
    std::cout<<"CREATING TABLE: "<<name<<std::endl;
    std::string comm = 
      "CREATE TABLE "+name+"("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "Quant           FLOAT    NOT NULL," \
      "Price            INT     NOT NULL );";
      database::sqlCommand command = comm.c_str();
      int res = runSQLCommand(command);
      if(res ==SQLITE_OK )std::cout<<"TABLE CREATED SUCCESFULLY"<<std::endl;
      return;
      
}

int database::Database::runSQLCommand(const sqlCommand command){
    char *zErrMsg = 0;
    int rc;

   /* Execute SQL statement */
    rc = sqlite3_exec(_db, command, callBack,0, &zErrMsg);
   
    if( rc != SQLITE_OK ) errorCheck(zErrMsg);
    return rc;

}