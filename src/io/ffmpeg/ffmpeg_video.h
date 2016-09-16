#include "../../video/source.h"

struct AVFormatContext;
struct AVStream;
struct AVCodec;
struct AVCodecContext;
struct AVDictionary;
struct AVFrame;
struct AVPacket;
struct SwsContext;

namespace hsm{
namespace montage{

class settings;

namespace io{

class resource;

class ffmpeg_video : public video::source{
public:
	ffmpeg_video(const io::resource & r, size_t stream_index, object *parent);
    ~ffmpeg_video();

    class parser : public video::source::parser{
	public:
        parser(const ffmpeg_video & src, AVFormatContext *ctx, AVStream *stream, AVCodec *codec, AVCodecContext *codex_ctx);
        ~parser();

        video::frame *read_frame();

        double time() const;

        double seek(double time);

	private:
        const ffmpeg_video & _src;
		AVFormatContext *_ctx;
		AVStream *_stream;
        size_t _index;
		AVCodec *_codec;
        AVCodecContext *_codec_ctx;
        SwsContext *_sws;

        int _linesize[8];

        double _duration;
        double _time;

        AVFrame *_frame;
        AVPacket *_packet;
	};

	io::resource *resource() const;

    video::source::parser *new_parser();

    size_t stream_index() const;

private:
    const io::resource & _resource;
	size_t _index;

    AVDictionary *_dic;
};

}
}
}
