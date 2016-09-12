#include "basic_node.h"

namespace hsm{
namespace montage{
namespace node{

basic_node::~basic_node(){
    //
}

const std::vector<input *> & basic_node::inputs() const{
    return _inputs;
}

const std::vector<source *> & basic_node::outputs() const{
    return _outputs;
}

std::vector<input *> & basic_node::inputs(){
    return _inputs;
}

std::vector<source *> & basic_node::outputs(){
    return _outputs;
}

}
}
}
