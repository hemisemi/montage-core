#pragma once

#include <stddef.h>

namespace hsm{
namespace montage{
namespace video{

class frame;

class frame_buffer{
public:
    frame_buffer(size_t capacity);
    ~frame_buffer();

    frame *peek() const;
    frame *consume();

    bool empty() const;

    void clear();

    bool push_back(frame *);

private:
    size_t _capacity;
    size_t _len;
    frame **_data;

    size_t _pos;
};

}
}
}
