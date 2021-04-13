#include "coinBaseClient.h"
#include <cpprest/ws_client.h>
#include <string>
#include <iostream>
#include <json/json.h>
#include <mutex>
std::mutex mu;

coinBaseClient::coinBaseClient(std::string wsAddr,
web::websockets::client::websocket_callback_client client,Json::Value message)
:_wsAddress(wsAddr),_wsClient(client){
    _wsClient.connect(wsAddr).then([wsAddr,message,this](){
        _oBook = new orderBook();
        onOpen(message);
    }).wait();

    _wsClient.set_message_handler([this](web::websockets::client::websocket_incoming_message msg){
        const std::lock_guard<std::mutex> lock(mu);
        _oBook->displayBook(10);

        onReceive(msg);
    });
    _wsClient.set_close_handler([this](web::websockets::client::websocket_close_status close_status, const utility::string_t &reason, const std::error_code &error){
        onClose(close_status,reason,error);
    });
     
}

void coinBaseClient::onOpen(Json::Value message){
    std::cout<<"Connection to: "<<_wsAddress<<" was succesful"<<std::endl;
    Json::StreamWriterBuilder builder;
    web::websockets::client::websocket_outgoing_message out_msg;
    std::cout<<"Subscribing to websocket with: "<<Json::writeString(builder,message)<<std::endl;
    out_msg.set_utf8_message(Json::writeString(builder,message));
    _wsClient.send(out_msg);  
}

void coinBaseClient::onReceive(web::websockets::client::websocket_incoming_message msg){
        msg.extract_string().then([&](std::string body) {
        Json::CharReaderBuilder builder;
        Json::Value out;
        Json::String errs;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        if (!reader->parse(body.c_str(), body.c_str() +static_cast<int>(body.length()), 
        &out, &errs)) {
            std::cout << "error parsing" << std::endl;
        }
        return out;
        }).then([this](Json::Value out){
        std::string type = out["type"].asString();
        _oBook->handleMessage(out["type"].asString(),out);
    }).wait();
}

void coinBaseClient::onClose(web::websockets::client::websocket_close_status close_status, const utility::string_t &reason, const std::error_code &error){
    delete(_oBook);
    std::cout<<"Client closed with error code: "<<error<<std::endl;
    std::cout<<"Reason: "<< reason<<std::endl;
}
