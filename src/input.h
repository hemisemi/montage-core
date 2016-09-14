#pragma once

#include "source.h"
#include "object.h"

namespace hsm{
namespace montage{

class input{
public:
	montage::source::data_type type() const;

    const ref<montage::source> & source() const;
    bool set_source(const ref<montage::source> & src);

protected:
    input(montage::source::data_type type, const ref<montage::source> & src);

private:
	montage::source::data_type _type;
    ref<montage::source> _source;
};

}
}
