#include <cpprest/ws_client.h>
#include <json/json.h>
#include "orderBook.h"
#include <mutex>
class coinBaseClient{
    std::string _wsAddress;
    web::websockets::client::websocket_callback_client _wsClient;
    Json::Value parseBody(const std::string &body);
    std::mutex mu;

    public:
    orderBook *_oBook;
    coinBaseClient(std::string wsAddr, web::websockets::client::websocket_callback_client client,Json::Value message );
    coinBaseClient()=delete;
    void onOpen(Json::Value message);
    void connect(Json::Value message);
    void test(std::string s){return;}
    void onReceive(std::string body);
    void onClose(web::websockets::client::websocket_close_status close_status, const utility::string_t &reason, const std::error_code &error);
};
