#include "sequencer.h"
#include "../video/input.h"
#include "../video/stream.h"

#define FRAME_BUFFER_SIZE 1024

namespace hsm{
namespace montage{
namespace node{

sequencer::sequencer(){
    _input = new video::input;
    _output = new output_stream(_input);

    inputs().push_back(_input);
    outputs().push_back(_output);
}

sequencer::~sequencer(){
    //
}

video::input *sequencer::input() const{
    return _input;
}

video::stream *sequencer::output() const{
    return _output;
}

sequencer::output_stream::output_stream(video::input *input) : _buffer(FRAME_BUFFER_SIZE){
    _input = input;
    _source = nullptr;
    _parser = nullptr;
}

void sequencer::output_stream::refresh(){
    if(_input->source() != _source){
        _buffer.clear();

        if(_parser)
            delete _parser;
        _parser = nullptr;
        _source = _input->source();

        if(_source != nullptr){
            _parser = _source->new_parser();
        }
    }
}

void sequencer::output_stream::draw(video::frame *, size_t pos, size_t fps){
    refresh();

    if(_parser != nullptr){
        //video::frame *f = _parser->read_frame();
    }
}

}
}
}
