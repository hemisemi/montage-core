#pragma once

#include "../stream/video_source.h"
#include <string>

namespace hsm{
namespace montage{
namespace io{

class video : public source{
public:
	class parser{
		//
	};

	virtual parser *new_parser() const = 0;

	/*static video *open(const std::string & filename, AVFormatContext *format, AVStream *stream);

	double duration() const;
	void seek(double time);*/

private:
	video(AVFormatContext *format, AVStream *stream, AVCodec *codec);

	AVFormatContext *_format;
	AVStream *_stream;
	AVCodec *_codec;
	size_t _pos;

	double _duration;
};

}
}
}
