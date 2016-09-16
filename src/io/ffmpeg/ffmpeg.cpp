#include "ffmpeg.h"
#include "ffmpeg_video.h"

#include "../../settings.h"

#include <iostream>
#include <hsm/algorithm.h>

extern "C"{
#define __STDC_CONSTANT_MACROS // for UINT64_C
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#define IO_BUFFER_SIZE 32768
#define PROBESIZE 2147483647

namespace hsm{
namespace montage{
namespace io{

bool ffmpeg_init(){
    std::cerr << "ffmpeg version: " << av_version_info() << std::endl;

    avcodec_register_all();
    av_register_all();

    /*AVCodec *codec = nullptr;
    while((codec = av_codec_next(codec)) != nullptr){
        std::cerr << codec->name << std::endl;
    }*/

    return true;
}

void ffmpeg_init_settings(settings &){
    //s.set("ffmpeg/analyzeduration", (int)PROBESIZE);
    //s.set("ffmpeg/probesize", (int)PROBESIZE);
}

static int io_read_packet(void *opaque, uint8_t *buf, int buf_size){
    resource::instance *h = (resource::instance*)opaque;
    int64_t read = h->read(buf, buf_size);
    //std::cerr << "read " << (void*)buf << " (" << read << ")" << std::endl;

    if(read < 0)
        return AVERROR(errno);

    return read;
}

static int io_write_packet(void *, uint8_t *, int){
    //std::cerr << "write " << (void*)buf << std::endl;
    return -1;
}

static int64_t io_seek(void *opaque, int64_t offset, int whence){
    resource::instance *h = (resource::instance*)opaque;
    //std::cerr << "seek " << offset << std::endl;

    if(whence & AVSEEK_SIZE)
        return h->length();

    //if(whence & AVSEEK_FORCE); force resource to re-open if closed
    whence &= ~AVSEEK_FORCE;

    std::ios_base::seekdir dir;

    switch(whence){
    case SEEK_SET:
        dir = std::ios_base::beg;
        break;
    case SEEK_CUR:
        dir = std::ios_base::cur;
        break;
    case SEEK_END:
        dir = std::ios_base::end;
        break;
    default:
        std::cerr << "hsm::montage::io::ffmpeg_video::io_seek: invalid whence" << std::endl;
        return AVERROR(errno);
    }

    int64_t ret = h->seek(offset, dir);

    if(ret < 0)
        return AVERROR(errno);

    return ret;
}

static int io_open(struct AVFormatContext *ctx, AVIOContext **pb, const char *, int flags, AVDictionary **){
    //std::cerr << "open" << std::endl;
    const resource *r = (const resource*)ctx->opaque;
    resource::instance *h = r->new_instance();
    if(h == nullptr){
        return AVERROR(ENOENT);
    }

    size_t buffer_len = IO_BUFFER_SIZE;
    uint8_t *buffer = new uint8_t[buffer_len];

    *pb = avio_alloc_context(buffer, buffer_len, flags & AVIO_FLAG_WRITE, (void*)h, &io_read_packet, &io_write_packet, &io_seek);

    if(*pb == nullptr){
        return AVERROR(ENOMEM);
    }

    return 0;
}

static void io_close(struct AVFormatContext *, AVIOContext *pb){
    //std::cerr << "close" << std::endl;
    resource::instance *h = (resource::instance*)pb->opaque;
    delete[] pb->buffer;
    delete h;
}

int ffmpeg_open_input(AVFormatContext **ctx, const resource & r, AVInputFormat *ifmt, AVDictionary **dic){
    if(*ctx == nullptr)
        *ctx = avformat_alloc_context();
    (*ctx)->opaque = (void*)&r;
    (*ctx)->io_open = &io_open;
    (*ctx)->io_close = &io_close;
    //(*ctx)->flags |= AVFMT_FLAG_CUSTOM_IO;
    int status = avformat_open_input(ctx, r.uri().to_string().c_str(), ifmt, dic);

    return status;
}

bool ffmpeg_load_resource(resource & r, std::vector<source *> & sources){
    AVInputFormat *input_format = nullptr;
    AVFormatContext *format_ctx = avformat_alloc_context();

    format_ctx->flags |= AVFMT_FLAG_GENPTS;

    // Check out format
    if(ffmpeg_open_input(&format_ctx, r, input_format, nullptr) < 0){
        return false;
    }

    // Retrieve stream information
    if(avformat_find_stream_info(format_ctx, nullptr) < 0){
        return false;
    }

    // Dump information about file onto standard error
    //av_dump_format(format_ctx, 0, r.uri().to_string().c_str(), 0);

    for(size_t i = 0; i < format_ctx->nb_streams; ++i){
        AVCodecParameters *codec_params = format_ctx->streams[i]->codecpar;

        if(codec_params->codec_type == AVMEDIA_TYPE_AUDIO){
            // audio stream
        }

        if(codec_params->codec_type == AVMEDIA_TYPE_VIDEO){
            // video stream
			sources.push_back((source*)new ffmpeg_video(r, i, &r));
        }
    }

    return true;
}

AVDictionary *ffmpeg_alloc_dictionary(const settings &){
    AVDictionary *dic = nullptr;

    /*std::string name("ffmpeg/analyseduration");
    hsm::variant d(PROBESIZE);
    const hsm::variant & v = s.get(name, d);
    const char *str = hsm::to_string(v.value<int>());*/

    //av_dict_set(&dic, "analyzeduration", hsm::to_string(s.get("ffmpeg/analyzeduration", PROBESIZE).value<int>()), 0);
    //av_dict_set(&dic, "probesize", hsm::to_string(s.get("ffmpeg/probesize", PROBESIZE).value<int>()), 0);

    return dic;
}

}
}
}
