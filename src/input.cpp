#include "input.h"

namespace hsm{
namespace montage{

input::input(montage::source::data_type type, const hsm::ref<montage::source> & src){
	_type = type;
	_source = src;
}

source::data_type input::type() const{
	return _type;
}

hsm::ref<source> input::source() const{
	return _source;
}

bool input::set_source(const hsm::ref<montage::source> & src){
	if(src != _source && (src == nullptr || src->type() == _type)){
		_source = src;
		return true;
	}

	return false;
}

}
}
