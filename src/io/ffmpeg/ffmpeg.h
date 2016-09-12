#pragma once

#include "../resource.h"

struct AVFormatContext;
struct AVInputFormat;
struct AVDictionary;

namespace hsm{
namespace montage{

class settings;

namespace io{

bool ffmpeg_init();

void ffmpeg_init_settings(settings & s);

AVDictionary *ffmpeg_alloc_dictionary(const settings & s);

int ffmpeg_open_input(AVFormatContext **ctx, const resource & r, AVInputFormat *, AVDictionary **);

bool ffmpeg_load_resource(resource & r, std::vector<source *> & sources, const settings & s);

}
}
}
