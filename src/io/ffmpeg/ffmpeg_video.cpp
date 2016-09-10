#include "ffmpeg_video.h"
#include "../resource.h"

extern "C"{
#define __STDC_CONSTANT_MACROS // for UINT64_C
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

namespace hsm{
namespace montage{
namespace io{

ffmpeg_video::ffmpeg_video(io::resource *r, size_t stream_index){
	_resource = r;
	_index = stream_index;
}

static int io_read_packet(void *opaque, uint8_t *buf, int buf_size){
	resource::handle *h = (ffmpeg_video*)opaque;
	return h->read(buf, size);
}

static int io_write_packet(void *opaque, uint8_t *buf, int buf_size){
	return -1;
}

static int64_t io_seek(void *opaque, int64_t offset, int whence){
	resource::handle *h = (ffmpeg_video*)opaque;
	return h->seek(offset, whence);
}

static int io_open(struct AVFormatContext *ctx, AVIOContext **pb, const char *url, int flags, AVDictionary **options){
	ffmpeg_video *self = (ffmpeg_video*)ctx->opaque;
	resource::handle *h = self->resource()->new_handle();

	*pb = avio_alloc_context(buffer, buffer_size, 0, (void*)reader, &io_read_packet, &io_write_packet, &io_seek);

	if(*pb == nullptr){
		return AVERROR(ENOMEM);
	}

	return 0;
}

static void io_close(struct AVFormatContext *, AVIOContext *pb){
	resource::handle *h = (resource::handle*)pb->opaque;
	delete h;
}

video::parser *ffmpeg_video::new_parser() const{
	AVFormatContext *ctx = avformat_alloc_context();
	ctx->opaque = (void*)this;
	ctx->io_open = &io_open;
	ctx->io_close = &io_close;

	avformat_open_input(ctx, url, nullptr, nullptr);

	return nullptr;
}

ffmpeg_video::parser::parser(AVFormatContext *ctx, AVStream *stream, AVCodec *codec){
	//
}

}
}
}
