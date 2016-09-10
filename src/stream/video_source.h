#pragma once

#include "source.h"

namespace hsm{
namespace montage{

class video_source : public source{
public:
	virtual data_type type() const;
};

}
}
