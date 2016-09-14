#include "project.h"

namespace hsm{
namespace montage{

project::project(){
    _video_stream = nullptr;
}

video::stream *project::video_stream() const{
    return _video_stream;
}

}
}
