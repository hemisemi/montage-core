#include "file.h"
#include <iostream>

namespace hsm{
namespace montage{
namespace io{

file::file(const std::string & filename) : _filename(filename){
    //
}

std::string file::filename() const{
    return _filename;
}

std::string file::protocol_name() const{
    return "file";
}

resource::instance *file::open() const{
    instance *i = new instance(*this);
    if(!i->is_valid()){
        std::cerr << "unable to open file `" << _filename << "'" << std::endl;
        delete i;
        return nullptr;
    }
    return i;
}

file::instance::instance(const file &f){
    _size = 0;
    _pos = 0;
    _file.open(f.filename(), std::ios_base::binary);

    if(_file.is_open()){
        _file.seekg(0, std::ios_base::end);
        _size = _file.tellg();
        _file.seekg(0, std::ios_base::beg);
    }
}

bool file::instance::is_valid() const{
    return _file.is_open();
}

int64_t file::instance::position() const{
    if(!_file.is_open())
        return -1;

    return _pos;
}

int64_t file::instance::length() const{
    if(!_file.is_open())
        return -1;

    return (int64_t)_size;
}

int64_t file::instance::read(uint8_t *dst, size_t len){
    if(!_file.is_open())
        return -1;
    _file.clear();

    _file.read((char*)dst, len);
    /*if(_file.fail())
        return -1;*/

    return _file.gcount();
}

int64_t file::instance::seek(int64_t offset, std::ios_base::seekdir whence){
    if(!_file.is_open())
        return -1;
    _file.clear();

    _file.seekg(offset, whence);
    _pos = _file.tellg();

    return _pos;
}

}
}
}
