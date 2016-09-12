#include "renderer.h"

namespace hsm{
namespace montage{
namespace video{

renderer::renderer(size_t fps, stream *source){
    _fps = fps;
    _src = source;
}

}
}
}
