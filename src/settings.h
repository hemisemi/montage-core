#include <map>
#include <hsm/variant.h>

namespace hsm{
namespace montage{

class settings{
public:
    settings();

    const hsm::variant & get(const std::string & key, const hsm::variant & default_value = hsm::variant()) const;
    const hsm::variant & get(const std::string & key, const hsm::variant & default_value = hsm::variant());

    const hsm::variant & set(const std::string & key, const hsm::variant & val, bool override = true);

private:
    std::map<std::string, hsm::variant> _map;
};

}
}
