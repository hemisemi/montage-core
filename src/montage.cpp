#include "montage.h"

extern "C"{
#define __STDC_CONSTANT_MACROS // for UINT64_C
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

namespace hsm{
namespace montage{

bool init(){
	avcodec_register_all();
	av_register_all();

	return true;
}

}
}
