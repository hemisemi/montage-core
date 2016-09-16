#pragma once

#include "resource.h"

#include <hsm/uri.h>

namespace hsm{
namespace montage{
namespace io{

class protocol{
public:
	virtual ~protocol() = 0;

    virtual std::string protocol_name() const = 0;
    virtual resource::instance *open() const = 0;

    static protocol *find_protocol(const hsm::uri & uri);
};

}
}
}
