
#include <iostream>
#include <cpprest/ws_client.h>
#include <json/json.h>
#include "src/coinBaseClient.h"
#include <thread>
#include "src/parser.h"
using namespace std;
using namespace web;
using namespace web::websockets::client;

int main(int argc, char const *argv[]) {
  Parser p;
  if(p.parseInput(argc,argv)==1)return -1;
  
  websocket_callback_client client;
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

  coinBaseClient c(address,client,root);
  c.connect(root);
  std::this_thread::sleep_for(10s);
  std::cout<<"Shutting Down AT End Of Thread Length"<<std::endl;

  return 0;
}