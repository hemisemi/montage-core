#include "frame.h"

namespace hsm{
namespace montage{
namespace video{

frame::frame(double time, size_t width, size_t height, size_t plane_count) : _time(time){
    for(size_t i = 0; i < plane_count; ++i)
        _planes.push_back(new image(width, height, bitmap::pixel_format::rgb, 0));
}

frame::frame(double time, const std::vector<hsm::image *> & planes) : _time(time), _planes(planes){
    //
}

frame::~frame(){
    for(image *plane : _planes)
        delete plane;
}

double frame::time() const{
    return _time;
}

const std::vector<hsm::image *> & frame::planes() const{
    return _planes;
}

}
}
}
