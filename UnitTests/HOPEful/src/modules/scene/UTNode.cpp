#include <modules/scene/UTNode.hpp>
#include <scene/Node.hpp>

namespace UTHope {
    void UTNode::runTests() {
        relationship() ;
    }

    void UTNode::relationship() {
        Hope::Node root ;
        Hope::Node firstChildRoot(&root) ;
        Hope::Node secondChildRoot(&root) ;

        check(&root == firstChildRoot.parent()) ;
        check(&root == secondChildRoot.parent()) ;
    }
}
