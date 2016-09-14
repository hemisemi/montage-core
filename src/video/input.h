#pragma once

#include "../input.h"

namespace hsm{
namespace montage{
namespace video{

class source;

class input : public montage::input{
public:
    input(const ref<video::source> & src = ref<video::source>());

    ref<video::source> source() const;
};

}
}
}
