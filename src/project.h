#pragma once

#include <vector>
#include <map>
#include <hsm/uri.h>
#include <hsm/library.h>
#include "object.h"

namespace hsm{
namespace montage{

class resource;

namespace video{

class stream;

}

class project{
public:
    project();
	~project();

	class root_object : public object{
	public:
		root_object();
		~root_object();
	};

    video::stream *video_stream() const;

	object *root() const;

	const hsm::library<object *> library() const;
	hsm::library<object *> library();

private:
    video::stream *_video_stream;

    std::map<hsm::uri, resource *> _resources;

	hsm::library<object *> _library;

	object *_root;
};

}
}
