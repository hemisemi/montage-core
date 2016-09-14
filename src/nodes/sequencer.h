#pragma once

#include "basic_node.h"
#include "../video/stream.h"
#include "../video/source.h"
#include "../video/frame_buffer.h"

#include <hsm/paint/painter.h>

namespace hsm{
namespace montage{

namespace video{

class input;

}

namespace node{

class sequencer : public basic_node{
public:
    sequencer();
    ~sequencer();

    video::input *input() const;
    video::stream *output() const;

private:
    class output_stream : public video::stream{
    public:
        output_stream(video::input *input);
        ~output_stream();

        void draw(video::frame *);

        void refresh();

    private:
        video::input *_input;
        video::source *_source;
        video::source::parser *_parser;

        video::frame *_frame;
        video::frame_buffer _buffer;
        hsm::painter _painter;

        double _time;
    };

    video::input *_input;
    output_stream *_output;
};

}
}
}
