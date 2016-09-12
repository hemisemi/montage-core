#include "montage.h"
#include <iostream>

#include "io/ffmpeg/ffmpeg.h"
#include "settings.h"

namespace hsm{
namespace montage{

bool init(){
    return io::ffmpeg_init();
}

void init_settings(settings & s){
    io::ffmpeg_init_settings(s);
}

}
}
