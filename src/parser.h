#include <string>
#include <vector>
class Parser{
    std::vector<std::string> m_instrument;
    std::string m_databasePath;
    public:
        int parseInput(int argc,char const* argv[]);

        void usage(const char *argv[]);
        std::string getDatabasePath();
        std::vector<std::string> getInstruments();
};