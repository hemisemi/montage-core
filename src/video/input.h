#pragma once

#include "../input.h"

namespace hsm{
namespace montage{
namespace video{

class source;

class input : public montage::input{
public:
	input(const hsm::ref<video::source> & src = hsm::ref<video::source>());

	hsm::ref<video::source> source() const;
};

}
}
}
