#pragma once

#include <hsm/ref.h>

namespace hsm{
namespace montage{

class object{
public:
    virtual ~object() = 0;
};

template<typename t>
using ref = hsm::ref<t, object>;

}
}
