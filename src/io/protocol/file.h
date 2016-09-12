#pragma once

#include <string>
#include <fstream>

#include "../protocol.h"

namespace hsm{
namespace montage{
namespace io{

class file : public protocol{
public:
    file(const std::string & filename);

    class instance : public resource::instance{
    public:
        instance(const file & f);

        bool is_valid() const;

        int64_t position() const;
        int64_t length() const;

        int64_t read(uint8_t *dst, size_t len);
        int64_t seek(int64_t offset, std::ios_base::seekdir whence);

    private:
        std::ifstream _file;
        size_t _size;
        size_t _pos;
    };

    std::string filename() const;

    std::string protocol_name() const;

    resource::instance *open() const;

private:
    std::string _filename;
};

}
}
}
