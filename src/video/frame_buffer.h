#pragma once

#include <stddef.h>

namespace hsm{
namespace montage{
namespace video{

class frame;

class frame_buffer{
public:
    frame_buffer(size_t length);
    ~frame_buffer();

    void clear();

    void push_back(const frame *);

private:
    size_t _len;
    frame **_data;
};

}
}
}
