#include <scene/framegraph/shading/ShaderParameter.hpp>
#include <algorithm>

using namespace Hope ;

void ShaderParameter::merge(
    std::set<std::shared_ptr<Hope::ShaderParameter>>& first,
    const std::set<std::shared_ptr<Hope::ShaderParameter>>& second
) {
    for (auto originalParam = first.begin() ; originalParam != first.end() ; ++originalParam) {
        auto it = std::find_if(
            second.begin(),
            second.end(),
            [originalParam]
            (const std::shared_ptr<Hope::ShaderParameter>& param) -> bool {
                return (*originalParam) -> identical(param) ;
            }
        ) ;

        if (it != second.end()) {
            first.erase(originalParam) ;
            first.insert(*it) ;
        }
    }
}

bool ShaderParameter::identical(const std::shared_ptr<Hope::ShaderParameter>& other) {
    return (name() == (other -> name())) &&
            (type() == (other -> type())) ;
}
