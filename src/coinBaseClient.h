#include <cpprest/ws_client.h>
#include <json/json.h>
#include "orderBook.h"
#include <mutex>
class coinBaseClient : web::web_sockets::client::websocket_callback_client{
    std::string _wsAddress;
    
    Json::Value _parseBody(const std::string &body);
    std::mutex mu;

    public:
    orderBook *_oBook;
    coinBaseClient(std::string wsAddr,Json::Value message );
    coinBaseClient()=delete;
    void onOpen(Json::Value message);
    void connect2(Json::Value message);
    void test(std::string s){return;}
    void onReceive(std::string body);
    void onClose(web::websockets::client::websocket_close_status close_status, const utility::string_t &reason, const std::error_code &error);
};
