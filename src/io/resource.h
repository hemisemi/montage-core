#pragma once

#include <vector>
#include <string>
#include <hsm/uri.h>
#include <ios>
#include "../object.h"

namespace hsm{
namespace montage{

class source;
class settings;

namespace io{

class protocol;

class resource : public object{
public:
	resource(object *parent);
	~resource();

    class instance{
    public:
        virtual ~instance() = 0;

        virtual bool is_valid() const = 0;

        virtual int64_t position() const = 0;

        virtual int64_t length() const = 0;

        virtual int64_t read(uint8_t *dst, size_t len) = 0;

        /**
         * @brief seek
         * @param offset
         * @param whence
         * @return On succes the new position of the stream, in bytes. -1 is returned on error.
         */
        virtual int64_t seek(int64_t offset, std::ios_base::seekdir whence) = 0;
	};

    bool is_null() const;

    const hsm::uri & uri() const;

    io::protocol *protocol() const;

    bool load(const hsm::uri & uri);
    bool load(io::protocol & p);

    void close();

    instance *new_instance() const;

	const std::vector<source *> & sources() const;

private:
    hsm::uri _uri;
    io::protocol *_protocol;

    std::vector<source*> _sources;
};

}
}
}
