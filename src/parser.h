#include <string>
#include <vector>
class Parser{
    std::vector<std::string> m_instrument;
    public:
        int parseInput(int argc,char const* argv[]);

        void usage(const char *argv[]);
        
        std::vector<std::string> getInstruments();
};