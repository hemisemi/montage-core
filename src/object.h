#pragma once

#include <hsm/ref.h>
#include <list>

namespace hsm{
namespace montage{

class object{
public:
	object(object *parent);
    virtual ~object() = 0;

	object *parent() const;
	const std::list<object *> & children() const;

	void set_parent(object *parent);
	void add_child(object *o);
	void remove_child(object *o);

private:
	object *_parent;
	std::list<object *> _children;
};

template<typename t>
using ref = hsm::ref<t, object>;

}
}
