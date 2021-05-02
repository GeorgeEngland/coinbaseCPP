
#include <iostream>
#include <cpprest/ws_client.h>

#include <json/json.h>
#include "src/coinBaseClient.h"
#include <thread>
#include "src/parser.h"
#include "src/database.h"
#include <memory>
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
/*
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  char *sql;

  
  rc = sqlite3_open("./db/testDB.db", &db);

if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   sql = "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }

   sqlite3_close(db);

*/


  Parser p;
  if(p.parseInput(argc,argv)==1)return -1;
   //database::Database* db = database::Database(p.getDatabasePath());
   auto dataBPtr = std::make_shared<database::Database>( database::Database(p.getDatabasePath()) );

  Json::Value root;
  Json::Value infoRoot;
  std::string address= "wss://ws-feed.pro.coinbase.com";

  infoRoot["name"]="ticker";
  auto instruments = p.getInstruments();
  for(int i = 0; i< instruments.size();i++ ){
     infoRoot["product_ids"][i] = instruments.at(i);
     root["product_ids"][i] = instruments.at(i);
  }

  root["type"]="subscribe";
 /* root["product_ids"][1]="BTC-USD";
  root["product_ids"][1]="BTC-GBP";
  root["product_ids"][1]="ETH-GBP";
   infoRoot["product_ids"][1]="BTC-USD";
  infoRoot["product_ids"][1]="BTC-GBP";
  infoRoot["product_ids"][1]="ETH-GBP";*/
  root["channels"][0]="level2";
  root["channels"][1]="heartbeat";
  root["channels"][2]=infoRoot;

  coinBaseClient c(address,root,dataBPtr);
  c.connect2(root);
  std::this_thread::sleep_for(30s);
  std::cout<<"Shutting Down AT End Of Thread Length"<<std::endl;

  return 0;
}