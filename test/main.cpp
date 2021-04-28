#include <benchmark/benchmark.h>
#include <fstream>
#include <json/json.h>
#include <iostream>
#include "../src/orderBook.h"
#include <thread>
    
static void BM_HANDLE_SNAP(benchmark::State& state) {
  // Perform setup here
    std::ifstream f("./test/SNAPSHOT.json");
    Json::Value snap;
    f >> snap;
    orderBook oBook;
  for (auto _ : state) {
    // This code gets timed
    for(int i=0;i<state.range(0);i++)
    oBook.handleMessage("snapshot",snap);

  }
}
// Register the function as a benchmark
BENCHMARK(BM_HANDLE_SNAP)->RangeMultiplier(2)->Range(1<<0,1<<4)->Unit(benchmark::TimeUnit::kMillisecond);

static void BM_HANDLE_L2(benchmark::State& state) {
  // Perform setup here
    std::ifstream f("./test/SNAPSHOT.json");
    Json::Value snap;
    f >> snap;

    std::ifstream f2("./test/L2.json");
    Json::Value snap2;
    f2 >> snap2;

    orderBook oBook;
    oBook.handleMessage("snapshot",snap);

  for (auto _ : state) {
    // This code gets timed
    oBook.handleMessage("l2update",snap2);
  }
}
// Register the function as a benchmark
BENCHMARK(BM_HANDLE_L2)->Unit(benchmark::TimeUnit::kMicrosecond);

static void BM_HANDLE_X_L2THREADS(benchmark::State& state) {
  // Perform setup here
    std::ifstream f("./test/SNAPSHOT.json");
    Json::Value snap;
    f >> snap;

    std::ifstream f2("./test/L2.json");
    Json::Value snap2;
    f2 >> snap2;

    orderBook* oBook = new orderBook();
    oBook->handleMessage("snapshot",snap);
    
    oBook->testVal = snap2;
    std::vector<std::thread> t;

  for (auto _ : state) {
    std::string type = "l2update";
    for(int i = 0; i<state.range(0);i++){
      oBook->handleMessageTest(type);
      //t.push_back(std::thread(&orderBook::handleMessageTest, oBook,type));
      t.push_back(std::thread([](){return 0;}) );
    }
    
    // This code gets timed
    //oBook.handleMessage("l2update",snap2);
  }
  for(auto &th : t){
      th.join();
    }
  delete(oBook);

}
// Register the function as a benchmark
BENCHMARK(BM_HANDLE_X_L2THREADS)->RangeMultiplier(2)->Range(1<<0,1<<8)->Unit(benchmark::TimeUnit::kMicrosecond);


// Run the benchmark
BENCHMARK_MAIN();