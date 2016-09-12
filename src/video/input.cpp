#include "input.h"
#include "source.h"

namespace hsm{
namespace montage{
namespace video{

input::input(video::source *src) : montage::input(montage::source::video, src){
    //
}

video::source *input::source() const{
    return (video::source*)montage::input::source();
}

}
}
}
