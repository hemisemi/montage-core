#pragma once

namespace hsm{
namespace montage{

class source{
public:
	enum data_type{
		numeric,

		audio,
		video,

		audio_stream,
		video_stream
	};

	virtual ~source() = 0;

	virtual data_type type() const = 0;
};

}
}
