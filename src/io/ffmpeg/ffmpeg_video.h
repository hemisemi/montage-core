#include "../video.h"

struct AVFormatContext;
struct AVStream;
struct AVCodec;

namespace hsm{
namespace montage{
namespace io{

class resource;

class ffmpeg_video : public video{
public:
	ffmpeg_video(io::resource *r, size_t stream_index);

	class parser : public video::parser{
	public:
		parser(AVFormatContext *ctx, AVStream *stream, AVCodec *codec);

	private:
		AVFormatContext *_ctx;
		AVStream *_stream;
		AVCodec *_codec;
	};

	io::resource *resource() const;

	video::parser *new_parser() const;

private:
	io::resource *_resource;
	size_t _index;
};

}
}
}
