#include "video.h"

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

#include <iostream>

namespace hsm{
namespace montage{
namespace io{

video::video(AVFormatContext *format, AVStream *stream, AVCodec *codec){
	_format = format;
	_stream = stream;
	_codec = codec;
	_duration = _format->duration / 1000000.0;
	_pos = 0;
}

video *video::open(const std::string &filename, AVFormatContext *format, AVStream *stream){
	if(stream->codecpar->codec_type != AVMEDIA_TYPE_VIDEO)
		return nullptr;

	// Get a pointer to the codec context for the video stream
	AVCodecParameters *codec_params = stream->codecpar;
	AVCodec *codec = avcodec_find_decoder(codec_params->codec_id);

	AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
	avcodec_parameters_to_context(codec_ctx, codec_params);

	if(codec == nullptr || (avcodec_open2(codec_ctx, codec, nullptr) < 0)){
		std::cerr << "unsupported codec `" << avcodec_get_name(codec_ctx->codec_id) << "'" << std::endl;
		return nullptr;
	}

	AVPacket *pkt;
	av_read_frame(format, pkt);

	return new video(format, stream, codec);
}

double video::duration() const{
	return _duration;
}

void video::seek(double time){
	//
}

}
}
}
