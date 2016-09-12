#include "frame.h"

namespace hsm{
namespace montage{
namespace video{

frame::frame(size_t id, double time, const std::vector<hsm::bitmap *> & planes) : _id(id), _time(time), _planes(planes){
    //
}

frame::~frame(){
    for(bitmap *plane : _planes)
        delete plane;
}

size_t frame::id() const{
    return _id;
}

double frame::time() const{
    return _time;
}

const std::vector<hsm::bitmap *> & frame::planes() const{
    return _planes;
}

}
}
}
