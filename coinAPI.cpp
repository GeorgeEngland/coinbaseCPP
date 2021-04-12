
#include <iostream>
#include <cpprest/ws_client.h>
#include <json/json.h>
#include "src/coinBaseClient.h"
#include <thread>
using namespace std;
using namespace web;
using namespace web::websockets::client;

int main() {
  
  websocket_callback_client client;
  Json::Value root;
  Json::Value infoRoot;
  std::string address= "wss://ws-feed.pro.coinbase.com";
  infoRoot["name"]="ticker";
  infoRoot["product_ids"][0]="ETH-USD";

  root["type"]="subscribe";
  root["product_ids"][0]="ETH-USD";
  root["channels"][0]="level2";
  root["channels"][1]="heartbeat";
  root["channels"][2]=infoRoot;

  coinBaseClient(address,client,root);
  std::this_thread::sleep_for(10s);
  std::cout<<"Shutting Down AT End Of Thread Length"<<std::endl;

  return 0;
}