#include <sqlite3.h>
#include <string>
#include <iostream>
#ifndef DATABASE_H
#define DATABASE_H
namespace database{
    typedef char* databaseErrorMsg;
    typedef const char* sqlCommand;

    class Database {
        sqlite3 *_db;
        std::string _dbAddress;
        void onClose(){sqlite3_close(_db);};
        void _errorCheck(int res);
        void errorCheck(databaseErrorMsg ErrorMessage);
        static int callBack(void *NotUsed, int argc, char **argv, char **azColName);
        int runSQLCommand(const sqlCommand);

        public:
        void createTable(std::string);
        Database(std::string dbAddress):_dbAddress(dbAddress){
            int res = sqlite3_open(_dbAddress.c_str(),&_db);
           if(res != SQLITE_OK) fprintf(stderr, "SQLITE ERROR: %s\n", sqlite3_errmsg(_db));
           else std::cout<<"DATABASE at: "<<_dbAddress<< " was opened succesfully"<<std::endl;

        }
        /*Database(const Database &d1){
            _db = d1._db;

        }*/

        
       // ~Database(){onClose();}

    };
   
    
    
}

#endif
