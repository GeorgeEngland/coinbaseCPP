#include "orderBook.h"
#include <iostream>
#include <json/json.h>
#include <vector>
void orderBook::handleMessage(std::string type, Json::Value& msg){
    if(type=="snapshot")handleSnapshot(msg);
    if(type=="l2update")handleL2Update(msg);
    if(type=="ticker")handleTicker(msg);
    return;
}
void orderBook::handleMessageTest(std::string type){
    Json::Value msg = testVal;
    if(type=="snapshot")handleSnapshot(msg);
    if(type=="l2update")handleL2Update(msg);
    if(type=="ticker")handleTicker(msg);
    return;
}

void orderBook::handleTicker(Json::Value &data){
}
void orderBook::handleL2Update(Json::Value &data){

    std::string instruction = data["changes"][0][0].asString();
    int price = std::stof(data["changes"][0][1].asString())*100;
    float quant = std::stof(data["changes"][0][2].asString());

    if(instruction=="sell"){
        handleBuy(price,quant);
    }
    if(instruction=="buy"){

        handleSell(price,quant);

    }


}
void orderBook::handleSnapshot(Json::Value &data){

    Json::Value f = data["asks"];

    int askHeadPrice = std::stof(data["asks"][0][0].asString())*100;
    double askHeadQuant = std::stof(data["asks"][0][1].asString());

    int bidHeadPrice = static_cast<int>(std::stof(data["bids"][0][0].asString())*100);
    double bidHeadQuant = std::stof(data["bids"][0][1].asString());

    _askHead = new orderItem(askHeadPrice,askHeadQuant);
    _bidHead = new orderItem(bidHeadPrice,bidHeadQuant);

    orderItem* currAskItem = _askHead;
    orderItem* currBidItem = _bidHead;

    for(Json::Value::ArrayIndex i = 1;i!= data["asks"].size();i++){

        int askPrice = std::stof(data["asks"][i][0].asString())*100;
        double askQuant = std::stof(data["asks"][i][1].asString());

        orderItem* ask = new orderItem(askPrice,askQuant,currAskItem);
        currAskItem->next = ask;
        currAskItem = ask;
    }

    for(Json::Value::ArrayIndex i = 1;i!= data["bids"].size();i++){
        int bidPrice = std::stof(data["bids"][i][0].asString())*100;
        double bidQuant = std::stof(data["bids"][i][1].asString());

        orderItem* bid = new orderItem(bidPrice,bidQuant,currBidItem);

        currBidItem->next = bid;
        currBidItem = bid;
    }
}


void orderBook::handleBuy(int price, float quant){
    orderItem* toOperateOn = _askHead;
    if(!toOperateOn)return;
    while(toOperateOn!=nullptr && price>toOperateOn->price){
        toOperateOn=toOperateOn->next;
    }
    
    if(toOperateOn==nullptr){
        std::cout<<"Inserting To End"<<std::endl;
        orderItem* insertItem = new orderItem(price,quant);
        toOperateOn->prev->next=insertItem;
        insertItem->prev= toOperateOn->prev;
        return;
    }
    if(toOperateOn->price==price){
        //edit quant
        toOperateOn->quant=quant;
        if(quant==0 && toOperateOn->prev){
            toOperateOn->prev->next=toOperateOn->next;
            toOperateOn->next->prev=toOperateOn->prev;
            delete(toOperateOn);
        }
        else if(quant==0){
            _askHead=toOperateOn->next;
            _askHead->prev=nullptr;
            delete(toOperateOn);
        }
    }
    else{

        //insert into list
        toOperateOn=toOperateOn->prev;

        orderItem* insertItem = new orderItem(price,quant,toOperateOn);
        if(quant!=0){
            if(toOperateOn){
            insertItem->next = toOperateOn ->next;
            toOperateOn->next = insertItem;
            insertItem->next->prev=insertItem;
            }
            else{
                orderItem* tmp = _askHead;
                insertItem->next=tmp;
                tmp->prev = insertItem;
                _askHead = insertItem;
            }
        }
    }
}

void orderBook::handleSell(int price, float quant){
    orderItem* toOperateOn = _bidHead;
    if(!toOperateOn)return;
    while(toOperateOn!=nullptr && price<toOperateOn->price){
        toOperateOn=toOperateOn->next;
    }
    if(!toOperateOn){
        
        orderItem* insertItem = new orderItem(price,quant);
        toOperateOn->prev->next=insertItem;
        insertItem->prev= toOperateOn->prev;
        toOperateOn->next=nullptr;
        return;
    }
    else{
        if(toOperateOn->price==price){
            //edit quant
            toOperateOn->quant=quant;
            if(quant==0 && toOperateOn->prev){
                toOperateOn->prev->next=toOperateOn->next;
                toOperateOn->next->prev=toOperateOn->prev;
                delete(toOperateOn);
            }
            else if(quant==0){
                _bidHead=toOperateOn->next;
                _bidHead->prev=nullptr;
                delete(toOperateOn);
            }
        }
        else{

            //insert into list
            toOperateOn=toOperateOn->prev;

            orderItem* insertItem = new orderItem(price,quant,toOperateOn);
            if(quant!=0){
                if(toOperateOn){
                insertItem->next = toOperateOn ->next;
                toOperateOn->next = insertItem;
                insertItem->next->prev=insertItem;
                }
                else{
                    orderItem* tmp = _bidHead;
                    insertItem->next=tmp;
                    tmp->prev = insertItem;
                    _bidHead = insertItem;
                }
            }
        }
    }

}


void orderBook::displayBook(int depth){
    std::cout<<"\n__________ YOUR BOOK ___________\n\n";
    if(!_askHead || !_bidHead)return;
    orderItem* currAsk = _askHead;
    orderItem* currBid = _bidHead;
    std::cout<<"Ask Prices: ";
    for(int i = 0; i< depth;i++){
        std::cout<<currAsk->price<<"  ";
        currAsk= currAsk->next;
    }
     std::cout<<"\nBid Prices: ";

    for(int i = 0; i< depth;i++){
        std::cout<<currBid->price<<"  ";
        currBid= currBid->next;
    }
    std::cout<<"\nAsk Quants: ";
    for(int i = 0; i< depth;i++){
        std::cout<<currAsk->quant<<"  ";
        currAsk= currAsk->next;
    }
     std::cout<<"\nBid Quants: ";

    for(int i = 0; i< depth;i++){
        std::cout<<currBid->quant<<"  ";
        currBid= currBid->next;
    }
    std::cout<<"\n\n"<<std::endl;

}