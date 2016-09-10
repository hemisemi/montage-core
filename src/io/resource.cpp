#include "resource.h"
#include "ffmpeg/ffmpeg_video.h"

extern "C"{
#define __STDC_CONSTANT_MACROS // for UINT64_C
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include <iostream>

namespace hsm{
namespace montage{
namespace io{

resource::resource(){
	//
}

const std::vector<source *> & resource::sources() const{
	return _sources;
}

bool resource::load(const std::string &filename){
	AVFormatContext *format = nullptr;

	// Check out format
	int status = avformat_open_input(&format, filename.c_str(), nullptr, nullptr);

	if(status == 0){
		if(load(filename, format))
			return true;
	}

	std::cerr << "cannot open resource `" << filename << "'" << std::endl;
	return false;
}

bool resource::load(const std::string &filename, AVFormatContext *format){
	// Retrieve stream information
	if(avformat_find_stream_info(format, nullptr) < 0)
		return false;

	// Dump information about file onto standard error
	av_dump_format(format, 0, filename.c_str(), 0);

	for(size_t i = 0; i < format->nb_streams; ++i){
		AVCodecParameters *codec_params = format->streams[i]->codecpar;

		if(codec_params->codec_type == AVMEDIA_TYPE_AUDIO){
			// audio stream
		}

		if(codec_params->codec_type == AVMEDIA_TYPE_VIDEO){
			// video stream
			//_sources.push_back((source*)video::open(filename, format, format->streams[i]));
			_sources.push_back(new ffmpeg_video());
		}
	}

	return true;
}

}
}
}
