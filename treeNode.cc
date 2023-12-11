#include "treeNode.h"
#include <iostream>

TreeNode::TreeNode(std::string cntt): content {cntt } {}

std::string TreeNode::getContent() const {
    // your code starts here
    return this->content;
}

TreeNode *TreeNode::getLeftChild() const {
    // your code starts here
    return this->leftChild;
}
TreeNode *TreeNode::getRightChild() const {
    // your code starts here
    return this->rightChild;
}


void TreeNode::updateLeftChild(TreeNode *lChild) {
    // your code starts here
    this->leftChild = lChild;

}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
    // your code starts here
    this->leftChild=lChild;
    this->rightChild=rChild;
}
OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const {
    // your code starts here 
}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const {
    // your code starts here
  
}


VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}
bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {
    // your code starts here
   
}

TreeNode::~TreeNode() {
    // your code starts here
}
