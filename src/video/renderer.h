#include <stddef.h>

namespace hsm{
namespace montage{
namespace video{

class stream;
class frame;

class renderer{
public:
    renderer(size_t fps = 25, stream *source = nullptr);

    stream *source() const;
    size_t position() const;
    double time() const;
    video::frame *frame() const;

    void set_source(stream *src);
    void set_position(size_t pos);
    void set_time(double t);

    video::frame *next_frame();

private:
    stream *_src;

    size_t _fps;
    size_t _pos;

    video::frame *_frame;
};

}
}
}
