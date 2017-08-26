
#ifndef PROGRAM_OPTIONS_H_
#define PROGRAM_OPTIONS_H_

#include <map>
#include <string>
#include <iostream>

#include <boost/lexical_cast.hpp>

namespace r0 {

class program_options {
public:
    program_options();
    program_options(const std::string& filename);

    void load_file(const std::string& filename);

    template<class T>
    T get(const std::string& key, const T& default_val = T()) const;
private:
    std::map<std::string, std::string> options;
};

template<class T>
T program_options::get(const std::string& key, const T& default_val) const {
    auto it = options.find(key);
    if ( it == options.end() ) {
        std::cout << "Program option \"" << key << "\" is not found : default value " << default_val << " is used" << std::endl;
        return default_val;
    } 
    try { 
        return boost::lexical_cast<T>(it->second);
    } catch (const boost::bad_lexical_cast&) {
        std::cout << "Program option \"" << key << "\" can't be converted : default value " << default_val << " is used" << std::endl;
        return default_val;
    }

}

} //namespace r0

#endif //PROGRAM_OPTIONS_H_