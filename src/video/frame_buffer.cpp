#include "frame_buffer.h"
#include "frame.h"

namespace hsm{
namespace montage{
namespace video{

frame_buffer::frame_buffer(size_t capacity){
    _capacity = capacity;
    _len = 0;
    _data = new frame*[_capacity];

    _pos = 0;
}

frame_buffer::~frame_buffer(){
    for(size_t i = 0; i < _len; ++i){
        delete _data[(_pos+i)%_capacity];
    }
    delete[] _data;
}

bool frame_buffer::empty() const{
    return _len == 0;
}

frame *frame_buffer::peek() const{
    if(empty())
        return nullptr;
    return _data[_pos];
}

frame *frame_buffer::consume(){
    if(empty())
        return nullptr;
    frame *f = _data[_pos];
    _pos = (_pos+1)%_capacity;
    --_len;

    return f;
}

void frame_buffer::clear(){
    for(size_t i = 0; i < _len; ++i){
        delete _data[(_pos+i)%_capacity];
    }
    _len = 0;
    _pos = 0;
}

bool frame_buffer::push_back(frame *f){
    if(f != nullptr && _len < _capacity){
        _data[(_pos+_len)%_capacity] = f;
        ++_len;

        return true;
    }

    return false;
}

}
}
}
