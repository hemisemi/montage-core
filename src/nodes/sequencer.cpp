#include "sequencer.h"
#include "../video/input.h"
#include "../video/stream.h"

#include <iostream>
#include <hsm/paint/painter.h>

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
    _frame = nullptr;

    _time = 0.0;
}

sequencer::output_stream::~output_stream(){
    if(_frame != nullptr)
        delete _frame;
}

void sequencer::output_stream::refresh(){
    if(_input->source() != _source){
        _buffer.clear();
        if(_frame != nullptr)
            delete _frame;
        _frame = nullptr;
        if(_parser != nullptr)
            delete _parser;
        _parser = nullptr;
        _source = _input->source();

        if(_source != nullptr){
            _parser = _source->new_parser();
        }
    }
}

void sequencer::output_stream::draw(video::frame *dst){
    refresh();

    if(_parser != nullptr){
        if(dst->time() < _time){
            std::cerr << "backward reading" << std::endl;
        }else{
            if(_buffer.empty())
                _buffer.push_back(_parser->read_frame());
            video::frame *next_frame = _buffer.peek();

            while(next_frame != nullptr && next_frame->time() <= dst->time()){
                if(_frame != nullptr)
                    delete _frame;
                _frame = _buffer.consume();

                if(_buffer.empty())
                    _buffer.push_back(_parser->read_frame());
                next_frame = _buffer.peek();
            }
        }
    }

    if(_frame != nullptr && dst != nullptr && !dst->planes().empty() && !_frame->planes().empty()){
        _time = _frame->time();

        _painter.begin(dst->planes().front());

        _painter.draw_bitmap(0, 0, *_frame->planes().front());

        _painter.end();
    }
}

}
}
}
