#include "object.h"

namespace hsm{
namespace montage{

object::~object(){
    //
}

object::object(object *parent){
	_parent = nullptr;
	set_parent(parent);
}

object *object::parent() const{
	return _parent;
}

const std::list<object *> & object::children() const{
	return _children;
}

void object::set_parent(object *parent){
	if(_parent != parent){
		if(_parent != nullptr){
			_parent->_children.remove(this);
		}
		_parent = parent;
		if(_parent != nullptr){
			_parent->_children.push_back(this);
		}
	}
}

void object::add_child(object *o){
	if(o != nullptr)
		o->set_parent(this);
}

void object::remove_child(object *o){
	if(o != nullptr && o->parent() == this)
		o->set_parent(nullptr);
}

}
}
