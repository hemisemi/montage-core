#include "input.h"
#include "source.h"

namespace hsm{
namespace montage{
namespace video{

input::input(const ref<video::source> & src) : montage::input(montage::source::video, src){
    //
}

hsm::ref<video::source> input::source() const{
	return (hsm::ref<video::source>)montage::input::source();
}

}
}
}
