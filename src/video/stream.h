#pragma once

#include "source.h"

namespace hsm{
namespace montage{
namespace video{

class frame;

class stream : public montage::source{
public:
	virtual data_type type() const;

    virtual void draw(frame *, size_t pos, size_t fps) = 0;

private:
    //
};

}
}
}
