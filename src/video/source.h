#pragma once

#include "../source.h"
#include "frame.h"
#include <string>

namespace hsm{
namespace montage{
namespace video{

class source : public montage::source{
public:
    class parser{
    public:
        virtual ~parser() = 0;

        virtual frame *read_frame() = 0;
    };

    data_type type() const;

    virtual parser *new_parser() = 0;
};

}
}
}
