#include <string>

class Parser{
    std::string m_instrument;
    public:
        int parseInput(int argc,char const* argv[]);

        void usage(const char *argv[]);
        
        std::string getInstrument();
};