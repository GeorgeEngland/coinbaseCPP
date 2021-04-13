#include <iostream>
#include "parser.h"

void Parser::usage(const char *argv[]){
    std::cerr << std::endl << std::endl;
    std::cerr << "USAGE:" << std::endl;
    std::cerr << argv[0] << " --instrument INSTRUMENT" << std::endl;
    std::cerr << std::endl;
    std::cerr << "--instrument INSTRUMENT  instrument abbreviation, e.g. \"ETH-USD\"" << std::endl;
    std::cerr << std::endl;
}

int Parser::parseInput(int argc,char const* argv[]){
     if (argc <= 2) {
        std::cerr << "Not enough arguments, usage:";
        usage(argv);
        return 1;
    }
    for (int i = 1; i <= argc - 2; i += 2) {
        const std::string opt(argv[i]);
        if (opt == "--instrument") {
            m_instrument = argv[i + 1];
        } 

        else {
            std::cerr << "Unknown option " << opt << ", usage:"; usage(argv); exit(1);
        }
    }
    std::clog<<"Instument: '"<< m_instrument<<"'"<<std::endl;   

}
std::string Parser::getInstrument(){
    return m_instrument;
}
