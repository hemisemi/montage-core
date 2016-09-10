#pragma once

#include <vector>
#include <string>

struct AVFormatContext;

namespace hsm{
namespace montage{
namespace io{

class source;

class resource{
public:
	resource();

	class handle{
		//
	};

	bool load(const std::string & filename);
	bool load(const std::string & filename, AVFormatContext *format);

	virtual handle *new_handle() const = 0;

	const std::vector<source *> & sources() const;

private:
	std::vector<source*> _sources;
};

}
}
}
