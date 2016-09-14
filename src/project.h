#pragma once

#include <vector>
#include <map>
#include <hsm/uri.h>

namespace hsm{
namespace montage{

class resource;

namespace video{

class stream;

}

class project{
public:
    project();

    video::stream *video_stream() const;

private:
    video::stream *_video_stream;

    std::map<hsm::uri, resource *> _resources;
};

}
}
