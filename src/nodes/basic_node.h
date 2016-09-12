#pragma once

#include <vector>

namespace hsm{
namespace montage{

class input;
class source;

namespace node{

class basic_node{
public:
    virtual ~basic_node() = 0;

    const std::vector<input *> & inputs() const;
    const std::vector<source *> & outputs() const;

protected:
    std::vector<input *> & inputs();
    std::vector<source *> & outputs();

private:
    std::vector<input *> _inputs;
    std::vector<source *> _outputs;
};

}
}
}
