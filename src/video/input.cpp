#include "input.h"
#include "source.h"

namespace hsm{
namespace montage{
namespace video{

input::input(const ref<video::source> & src) : montage::input(montage::source::video, src){
    //
}

ref<video::source> input::source() const{
    return ref<video::source>(montage::input::source());
}

}
}
}
