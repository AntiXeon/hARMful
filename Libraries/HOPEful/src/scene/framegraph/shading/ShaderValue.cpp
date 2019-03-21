#include <scene/framegraph/shading/ShaderValue.hpp>
#include <algorithm>

using namespace Hope ;

void ShaderValue::merge(
    std::set<std::shared_ptr<Hope::ShaderValue>>& first,
    const std::set<std::shared_ptr<Hope::ShaderValue>>& second
) {
    for (auto originalParam = first.begin() ; originalParam != first.end() ; ++originalParam) {
        auto it = std::find_if(
            second.begin(),
            second.end(),
            [originalParam]
            (const std::shared_ptr<Hope::ShaderValue>& param) -> bool {
                return (*originalParam) -> identical(param) ;
            }
        ) ;

        if (it != second.end()) {
            first.erase(originalParam) ;
            first.insert(*it) ;
        }
    }
}

bool ShaderValue::identical(const std::shared_ptr<Hope::ShaderValue>& other) {
    return (name() == (other -> name())) &&
            (type() == (other -> type())) ;
}
