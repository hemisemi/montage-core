#pragma once

#include "source.h"

namespace hsm{
namespace montage{

class input{
public:
	montage::source::data_type type() const;

	montage::source *source() const;
	bool set_source(montage::source *src);

protected:
	input(montage::source::data_type type, montage::source *src = nullptr);

private:
	montage::source::data_type _type;
	montage::source *_source;
};

}
}
