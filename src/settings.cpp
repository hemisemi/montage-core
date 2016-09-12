#include "settings.h"

namespace hsm{
namespace montage{

settings::settings(){
    //
}

const hsm::variant & settings::get(const std::string &key, const variant &default_value) const{
    auto it = _map.find(key);
    if(it == _map.end()){
        return default_value;
    }

    return it->second;
}

const hsm::variant & settings::get(const std::string &key, const variant &default_value){
    auto it = _map.find(key);
    if(it == _map.end()){
        if(!default_value.is_null())
            _map.insert(std::make_pair(key, default_value));
        return default_value;
    }

    return it->second;
}

const hsm::variant & settings::set(const std::string & key, const hsm::variant & val, bool override){
    auto it = _map.find(key);
    if(it != _map.end()){
        if(override)
            it->second = val;
        return it->second;
    }

    _map.insert(std::make_pair(key, val));
    return val;
}

}
}
