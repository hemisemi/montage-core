#pragma once

#include "source.h"
#include <hsm/ref.h>

namespace hsm{
namespace montage{

class input{
public:
	montage::source::data_type type() const;

	hsm::ref<montage::source> source() const;
	bool set_source(const hsm::ref<montage::source> & src);

protected:
	input(montage::source::data_type type, const hsm::ref<montage::source> & src);

private:
	montage::source::data_type _type;
	hsm::ref<montage::source> _source;
};

}
}
