#include <stddef.h>
#include <inttypes.h>
#include <vector>

#include <hsm/bitmap.h>

namespace hsm{
namespace montage{
namespace video{

class frame{
public:
    frame(size_t id, double time, const std::vector<hsm::bitmap *> & planes);
    ~frame();

    size_t id() const;
    double time() const;
    const std::vector<hsm::bitmap *> & planes() const;

private:
    size_t _id;
    double _time;
    std::vector<hsm::bitmap *> _planes;
};

}
}
}
