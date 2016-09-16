#include "source.h"

#include <iostream>

namespace hsm{
namespace montage{
namespace video{

source::source(object *parent) : montage::source(parent){
	//
}

source::parser::~parser(){
    //
}

montage::source::data_type source::type() const{
    return montage::source::video;
}

}
}
}
