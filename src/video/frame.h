#pragma once

#include <stddef.h>
#include <inttypes.h>
#include <vector>

#include <hsm/paint/image.h>

namespace hsm{
namespace montage{
namespace video{

class frame{
public:
    frame(double time, size_t width, size_t height, size_t plane_count = 1);
    frame(double time, const std::vector<hsm::image *> & planes);
    ~frame();

    double time() const;
    const std::vector<hsm::image *> & planes() const;

private:
    double _time;
    std::vector<hsm::image *> _planes;
};

}
}
}
