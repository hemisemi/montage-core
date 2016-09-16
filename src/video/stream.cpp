#include "stream.h"

namespace hsm{
namespace montage{
namespace video{

stream::stream(object *parent) : montage::source(parent){
	//
}

source::data_type stream::type() const{
    return source::video_stream;
}

}
}
}
