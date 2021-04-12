#include <cpprest/ws_client.h>
#include <json/json.h>
#include "orderBook.h"
#include <mutex>
class coinBaseClient{
    std::string _wsAddress;
    web::websockets::client::websocket_callback_client _wsClient;
    orderBook *_oBook;
    std::mutex _mx;
    public:
    coinBaseClient(std::string wsAddr, web::websockets::client::websocket_callback_client client,Json::Value message );
    coinBaseClient()=delete;
    void onOpen(Json::Value message);
    void onReceive(web::websockets::client::websocket_incoming_message msg);
    void onClose(web::websockets::client::websocket_close_status close_status, const utility::string_t &reason, const std::error_code &error);
};
