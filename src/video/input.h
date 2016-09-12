#pragma once

#include "../input.h"

namespace hsm{
namespace montage{
namespace video{

class source;

class input : public montage::input{
public:
    input(video::source *src = nullptr);

    video::source *source() const;
};

}
}
}
