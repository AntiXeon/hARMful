#include <modules/scene/UTNode.hpp>
#include <scene/Node.hpp>

#include <iostream>

namespace UTHope {
    void UTNode::runTests() {
        basicRelationship() ;
        changeParent() ;
    }

    void UTNode::basicRelationship() {
        Hope::Node* root = new Hope::Node() ;
        Hope::Node* firstChildRoot = new Hope::Node(root) ;
        Hope::Node* secondChildRoot = new Hope::Node(root) ;

        check(root == firstChildRoot -> parent()) ;
        check(root == secondChildRoot -> parent()) ;

        const std::vector<Hope::Node*> rootChildren = root -> children() ;
        check(rootChildren.size() == 2) ;
        check(rootChildren[0] == firstChildRoot) ;
        check(rootChildren[1] == secondChildRoot) ;

        delete root ;
    }

    void UTNode::changeParent() {
        /*
         Tree structure at creation:
         + root
            + A
                + A1 --> attached to A-3 later
                + A2 --> attached to B-1 later
                + A3
            + B
                + B1 --> attached to A-1 later
                + B2 --> attached to root later

        Tree structure at end:
        + root
           + A
               + A3
                    + A1
                        + B1
                            + A2
           + B
           + B2
         */

        Hope::Node* root = new Hope::Node() ;
        Hope::Node* rootAChild = new Hope::Node(root) ;
        Hope::Node* rootA1Child = new Hope::Node(rootAChild) ;
        Hope::Node* rootA2Child = new Hope::Node(rootAChild) ;
        Hope::Node* rootA3Child = new Hope::Node(rootAChild) ;
        Hope::Node* rootBChild = new Hope::Node(root) ;
        Hope::Node* rootB1Child = new Hope::Node(rootBChild) ;
        Hope::Node* rootB2Child = new Hope::Node(rootBChild) ;

        check(root == rootAChild -> parent()) ;
        check(rootAChild == rootA1Child -> parent()) ;
        check(rootAChild == rootA2Child -> parent()) ;
        check(rootAChild == rootA3Child -> parent()) ;
        check(root == rootBChild -> parent()) ;
        check(rootBChild == rootB1Child -> parent()) ;
        check(rootBChild == rootB2Child -> parent()) ;

        rootA1Child -> setParent(rootA3Child) ;
        rootA2Child -> setParent(rootB1Child) ;
        rootB1Child -> setParent(rootA1Child) ;
        rootB2Child -> setParent(root) ;

        check(root == rootAChild -> parent()) ;
        check(rootA3Child == rootA1Child -> parent()) ;
        check(rootB1Child == rootA2Child -> parent()) ;
        check(rootAChild == rootA3Child -> parent()) ;
        check(root == rootBChild -> parent()) ;
        check(rootA1Child == rootB1Child -> parent()) ;
        check(root == rootB2Child -> parent()) ;

        check(root -> children().size() == 3) ;

        delete root ;
    }
}
