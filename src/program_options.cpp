
#include "program_options.h"

#include <fstream>

namespace r0 {

program_options::program_options() {}

program_options::program_options(const std::string& filename) {
    load_file(filename);
}

void program_options::load_file(const std::string& filename) {
    std::ifstream in(filename.c_str());
    
    std::string line;
    while(getline(in, line)) {
        unsigned eqs = line.find('=');
        if ( eqs != std::string::npos ) {
            const std::string key = line.substr(0, eqs);
            const std::string val = line.substr(eqs+1, std::string::npos);
            options[key] = val;
        }
    }
}

} //namespace r0