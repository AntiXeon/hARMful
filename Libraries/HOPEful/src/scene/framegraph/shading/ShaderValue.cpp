#include <scene/framegraph/shading/ShaderValue.hpp>
#include <algorithm>

using namespace Hope ;

void ShaderValue::merge(
    std::map<std::string, std::shared_ptr<Hope::ShaderValue>>& first,
    const std::map<std::string, std::shared_ptr<Hope::ShaderValue>>& second
) {
    for (auto& [name, value] : second) {
        first[name] = value;
    }
}

bool ShaderValue::identical(const std::shared_ptr<Hope::ShaderValue>& other) {
    return (name() == (other -> name())) &&
            (type() == (other -> type())) ;
}
