#include "frame_buffer.h"

namespace hsm{
namespace montage{
namespace video{

frame_buffer::frame_buffer(size_t len){
    _len = len;
    _data = new frame*[len];
}

frame_buffer::~frame_buffer(){
    // TODO delete frames
    delete[] _data;
}

void frame_buffer::clear(){
    // TODO
}

void frame_buffer::push_back(const frame *){
    // TODO
}

}
}
}
