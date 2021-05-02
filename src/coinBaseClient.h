#include <cpprest/ws_client.h>
#include <json/json.h>
#include "orderBook.h"
#include <mutex>
#include <atomic>
#include <unordered_map>
class coinBaseClient : web::web_sockets::client::websocket_callback_client{
    std::string _wsAddress;
    Json::Value _parseBody(const std::string &body);
    std::mutex mu;
    std::atomic<int> _ordersProcessed{0};
    std::chrono::high_resolution_clock::time_point _tStart;
    public:
    std::shared_ptr<database::Database> _dataBPtr;
    std::unordered_map<std::string,orderBook*> _books;
    orderBook *_oBook;
    coinBaseClient(std::string wsAddr,Json::Value message,std::shared_ptr<database::Database> dataBPtr );
    coinBaseClient()=delete;
    void onOpen(Json::Value message);
    void connect2(Json::Value message);
    void test(std::string s){return;}
    void onReceive(std::string body);
    void onClose(web::websockets::client::websocket_close_status close_status, const utility::string_t &reason, const std::error_code &error);
};
