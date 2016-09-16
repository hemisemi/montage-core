#include "project.h"

namespace hsm{
namespace montage{

project::project(){
    _video_stream = nullptr;
	_root = new root_object;
}

project::~project(){
	delete _root;
}

project::root_object::root_object() : object(nullptr){
	//
}

project::root_object::~root_object(){
	//
}

video::stream *project::video_stream() const{
    return _video_stream;
}

object *project::root() const{
	return _root;
}

const hsm::library<object *> project::library() const{
	return _library;
}

hsm::library<object *> project::library(){
	return _library;
}

}
}
