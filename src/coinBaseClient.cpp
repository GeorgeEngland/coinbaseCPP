#include "coinBaseClient.h"
#include <cpprest/ws_client.h>
#include <string>
#include <iostream>
#include <json/json.h>
#include <mutex>
#include "timer.h"

coinBaseClient::coinBaseClient(std::string wsAddr,Json::Value message)
:_wsAddress(wsAddr){}

void coinBaseClient::connect2(Json::Value message){
    
    connect(_wsAddress).then([message,this](){
        for(auto instrument : message["product_ids"]){
            this->_books[instrument.asString()]=new orderBook();
        }
        _oBook = new orderBook();
        onOpen(message);
        
    }).wait();
    set_message_handler([this](web::websockets::client::websocket_incoming_message msg){
//        Timer* t1 = new Timer("Whole Function");
        _ordersProcessed++;
        msg.extract_string().then([this](std::string body) {
//            Timer* t2 = new Timer("Algo");
            mu.lock();
            
            onReceive(body);
//            delete(t2);
//            delete(t1);
            mu.unlock();

        });
    });
    std::cout<<"Set Message Handler"<<std::endl;


    set_close_handler([this](web::websockets::client::websocket_close_status close_status, const utility::string_t &reason, const std::error_code &error){
        onClose(close_status,reason,error);
    });

}
void coinBaseClient::onOpen(Json::Value message){
 
    std::cout<<"Connection to: "<<_wsAddress<<" was succesful"<<std::endl;
    Json::StreamWriterBuilder builder;
    web::websockets::client::websocket_outgoing_message out_msg;
    std::string s = Json::writeString(builder,message);
    out_msg.set_utf8_message(s);
    send(out_msg);  

}

void coinBaseClient::onReceive(std::string body){
        Json::Value out = _parseBody(body);
        std::chrono::high_resolution_clock::time_point tNow = std::chrono::high_resolution_clock::now();
        if((tNow-_tStart).count()>100000000){
            std::cout<<"\nOrders Processed: "<<_ordersProcessed<<" Type: "<<out["product_id"].asString()<<std::endl;
            std::cout<<"Time Taken: "<<(std::chrono::high_resolution_clock::now()-_tStart).count()/1000000<<" ms"<<std::endl;
            _tStart = std::chrono::high_resolution_clock::now();
            _ordersProcessed=0;

        }
        if(out != Json::ValueType::nullValue && out["product_id"] != Json::ValueType::nullValue){
            std::string type = out["type"].asString();
           // Timer t3("\nHandle Message");
           _books[out["product_id"].asString()]->handleMessage(out["type"].asString(),out);
             std::cout<<"BOOK NAME: "<<out["product_id"].asString()<<std::endl;
             _books[out["product_id"].asString()]->displayBook(10);
        }

        //_oBook->displayBook(10);
}

Json::Value coinBaseClient::_parseBody(const std::string &body){
        Json::CharReaderBuilder builder;
        Json::Value out;
        Json::String errs;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        if (!reader->parse(body.c_str(), body.c_str() +static_cast<int>(body.length()), 
        &out, &errs)) {
            std::cout << "error parsing" << std::endl;
            out = Json::nullValue;
        }
        return out;
}

void coinBaseClient::onClose(web::websockets::client::websocket_close_status close_status, const utility::string_t &reason, const std::error_code &error){
    delete(_oBook);

    std::cout<<"Client closed with error code: "<<error<<std::endl;
    std::cout<<"Reason: "<< reason<<std::endl;
}
