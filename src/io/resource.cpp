#include "resource.h"
#include "../source.h"
#include "ffmpeg/ffmpeg.h"
#include "protocol.h"

#include <iostream>

namespace hsm{
namespace montage{
namespace io{

resource::resource(){
	//
}

resource::instance::~instance(){
    //
}

const std::vector<source *> & resource::sources() const{
	return _sources;
}

const hsm::uri & resource::uri() const{
    return _uri;
}

resource::instance *resource::new_instance() const{
    return _protocol->open();
}

void resource::close(){
    for(source *src : _sources){
        delete src;
    }
    _sources.clear();
    _uri.clear();
}

bool resource::load(const hsm::uri & uri){
    close();
    _uri = uri;
    _protocol = io::protocol::find_protocol(_uri);

    if(_protocol == nullptr){
         std::cerr << "unknown protocol `" << _uri.sheme() << "' for resource `" << uri << "'" << std::endl;
        return false;
    }

    if(ffmpeg_load_resource(*this, _sources))
        return true;

    std::cerr << "cannot open resource `" << uri << "'" << std::endl;
	return false;
}

}
}
}
