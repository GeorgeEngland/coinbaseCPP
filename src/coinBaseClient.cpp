#include "coinBaseClient.h"
#include <cpprest/ws_client.h>
#include <string>
#include <iostream>
#include <json/json.h>
#include <mutex>
coinBaseClient::coinBaseClient(std::string wsAddr,Json::Value message)
:_wsAddress(wsAddr){
}
void coinBaseClient::connect2(Json::Value message){
    
    connect(_wsAddress).then([message,this](){
        _oBook = new orderBook();
        onOpen(message);
        
    }).wait();

    set_message_handler([this](web::websockets::client::websocket_incoming_message msg){
        msg.extract_string().then([&](std::string body) {
            onReceive(body);
        }).wait();
    });

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
        const std::lock_guard<std::mutex> lock(mu);
        Json::Value out = _parseBody(body);
        if(out != Json::ValueType::nullValue){
            std::string type = out["type"].asString();
            _oBook->handleMessage(out["type"].asString(),out);
        }

        _oBook->displayBook(10);
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
