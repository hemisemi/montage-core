#include "protocol.h"
#include "protocol/file.h"

namespace hsm{
namespace montage{
namespace io{

protocol::~protocol(){
	//
}

protocol *protocol::find_protocol(const uri &uri){
    if(uri.sheme().empty() || uri.sheme() == "file")
        return new io::file(uri.path_string());

    return nullptr;
}

}
}
}
