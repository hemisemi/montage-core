#include "ffmpeg_video.h"
#include "ffmpeg.h"
#include "../resource.h"

#include <stdio.h>
#include <ios>
#include <iostream>

extern "C"{
#define __STDC_CONSTANT_MACROS // for UINT64_C
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libavutil/pixfmt.h>
#include <libswscale/swscale.h>
}

#define IO_BUFFER_SIZE 32768

namespace hsm{
namespace montage{
namespace io{

ffmpeg_video::ffmpeg_video(const io::resource & r, size_t stream_index, const settings & s) : _resource(r){
	_index = stream_index;
    _dic = ffmpeg_alloc_dictionary(s);
}

ffmpeg_video::~ffmpeg_video(){
    av_dict_free(&_dic);
}

video::source::parser *ffmpeg_video::new_parser(){
    AVFormatContext *ctx = nullptr;

    if(ffmpeg_open_input(&ctx, _resource, nullptr, &_dic) != 0){
        std::cerr << "unable to open ffmpeg_video resource `" << _resource.uri() << "'" << std::endl;
        return nullptr;
    }

    // Retrieve stream information
    if(avformat_find_stream_info(ctx, nullptr) != 0)
        return nullptr;

    // Get the right stream
    if(_index >= ctx->nb_streams || ctx->streams[_index]->codecpar->codec_type != AVMEDIA_TYPE_VIDEO){
        avformat_close_input(&ctx);
        return nullptr;
    }

    AVStream *stream = ctx->streams[_index];

    // Get a pointer to the codec context for the video stream
    AVCodecParameters *codec_params = stream->codecpar;
    AVCodec *codec = avcodec_find_decoder(codec_params->codec_id);

    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codec_ctx, codec_params);

    if(codec == nullptr || (avcodec_open2(codec_ctx, codec, nullptr) < 0)){
        std::cerr << "unsupported codec `" << avcodec_get_name(codec_ctx->codec_id) << "'" << std::endl;
        avcodec_free_context(&codec_ctx);
        avformat_free_context(ctx);
        return nullptr;
    }

    if(codec_ctx->pix_fmt == AV_PIX_FMT_NONE){
        std::cerr << "unknown pixel format" << std::endl;
        avcodec_free_context(&codec_ctx);
        avformat_free_context(ctx);
        return nullptr;
    }

    return new parser(*this, ctx, stream, codec, codec_ctx);
}

size_t ffmpeg_video::stream_index() const{
    return _index;
}

ffmpeg_video::parser::parser(const ffmpeg_video & src, AVFormatContext *ctx, AVStream *stream, AVCodec *codec, AVCodecContext *codec_ctx) : _src(src){
    _ctx = ctx;
    _stream = stream;
    _codec = codec;
    _codec_ctx = codec_ctx;
    _duration = (double)_ctx->duration / 1000000.0;
    _pos = 0;

    _frame = av_frame_alloc();

    for(size_t i = 0; i < 8; ++i)
        _linesize[i] = _codec_ctx->width*4;

    //size_t len = av_image_get_buffer_size(AV_PIX_FMT_ARGB, _codec_ctx->width, _codec_ctx->height, 1);
    //uint8_t *buffer = new uint8_t[len];
    //av_image_fill_arrays(_rgb_frame->data, _rgb_frame->linesize, nullptr, AV_PIX_FMT_ARGB, width, height, 1);

    _sws = sws_getContext(_codec_ctx->width, _codec_ctx->height, _codec_ctx->pix_fmt,
                   _codec_ctx->width, _codec_ctx->height, AV_PIX_FMT_RGBA,
                   SWS_BILINEAR, nullptr, nullptr, nullptr);

    _packet = av_packet_alloc();
}

ffmpeg_video::parser::~parser(){
    av_packet_unref(_packet);
    avcodec_free_context(&_codec_ctx);
    avformat_close_input(&_ctx);
}

video::frame *ffmpeg_video::parser::read_frame(){
    size_t length = 4*_codec_ctx->width*_codec_ctx->height;

    int status = 0;
    while((status = av_read_frame(_ctx, _packet)) >= 0){
        if(_packet->stream_index == (int)_src.stream_index()){
            // decode video frame
            avcodec_send_packet(_codec_ctx, _packet);
            if(avcodec_receive_frame(_codec_ctx, _frame) == 0){
                uint8_t **dst = new uint8_t*[AV_NUM_DATA_POINTERS];

                for(size_t i = 0; i < AV_NUM_DATA_POINTERS; ++i){
                    dst[i] = nullptr;
                    if(_frame->data[i]!= nullptr){
                        dst[i] = new uint8_t[length];
                    }
                }

                sws_scale(_sws, _frame->data, _frame->linesize, 0, _codec_ctx->height, dst, _linesize);

                std::vector<hsm::bitmap *> planes;
                for(size_t i = 0; i < AV_NUM_DATA_POINTERS; ++i){
                    if(dst[i] != nullptr)
                        planes.push_back(new bitmap(dst[i], _codec_ctx->width, _codec_ctx->height, bitmap::pixel_format::rgba, false));
                }

                return new video::frame(_pos, _frame->pts*av_q2d(_codec_ctx->time_base), planes);
            }
        }
    }

    std::cerr << "status: " << status << std::endl;
    return nullptr;
}

}
}
}
