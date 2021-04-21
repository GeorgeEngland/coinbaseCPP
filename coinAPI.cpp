
#include <iostream>
#include <cpprest/ws_client.h>
#include <json/json.h>
#include "src/coinBaseClient.h"
#include <thread>
#include "src/parser.h"
#include <sqlite3.h>
using namespace std;
using namespace web;
using namespace web::websockets::client;
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
int main(int argc, char const *argv[]) {

  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  char *sql;

  /* Open database */
  rc = sqlite3_open("./db/testDB.db", &db);

if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }

/* Create SQL statement */
   sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }



   sqlite3_close(db);



  Parser p;
  if(p.parseInput(argc,argv)==1)return -1;
  
  Json::Value root;
  Json::Value infoRoot;
  std::string address= "wss://ws-feed.pro.coinbase.com";

  infoRoot["name"]="ticker";
  infoRoot["product_ids"][0]=p.getInstrument();

  root["type"]="subscribe";
  root["product_ids"][0]=p.getInstrument();
  root["channels"][0]="level2";
  root["channels"][1]="heartbeat";
  root["channels"][2]=infoRoot;

  coinBaseClient c(address,root);
  c.connect2(root);
  std::this_thread::sleep_for(10s);
  std::cout<<"Shutting Down AT End Of Thread Length"<<std::endl;

  return 0;
}