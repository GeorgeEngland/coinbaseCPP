#include <json/json.h>
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <memory>
#include "database.h"
#ifndef ORDERBOOK_H
#define ORDERBOOK_H

class orderItem{
    public:
    orderItem(int pr,float quan, orderItem* pre):
    price(pr),quant(quan),next(nullptr),prev(pre){}
    orderItem(int pr,float quan)
    {
        next=nullptr;
        prev = nullptr;
        price = pr;
        quant = quan;
        }
        int price;
        float quant;
        orderItem* next;
        orderItem* prev;
};

class orderBook{
    orderItem* _bidHead;
    orderItem* _askHead;
    std::string _instrument;
    std::shared_ptr<database::Database> DB;
    void handleL2Update(Json::Value& msg);
    void handleSell(int price, float quant);
    void handleBuy(int price, float quant);
    void handleSnapshot(Json::Value& msg);
    void handleTicker(Json::Value& msg);

    public:
    Json::Value testVal;
    
    void test(std::string msg){return;}
    void displayBook(int depth);
    void handleMessage(std::string type, Json::Value& msg);
    void handleMessageTest(std::string type);
    orderBook(std::string instrument):_bidHead(nullptr),_askHead(nullptr),_instrument(instrument){

    }

};
#endif /* ORDERBOOK_H */
