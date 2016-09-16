#pragma once

#include <vector>
#include "../object.h"

namespace hsm{
namespace montage{

class input;
class source;

namespace node{

class basic_node : public object{
public:
	basic_node(object *parent);

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
