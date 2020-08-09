#include "TreeNode.h"

TreeNode::TreeNode()
	:condition(nullptr), action(nullptr), isRoot(false), isLeaf(false), leftChild(nullptr), rightChild(nullptr)
{
}

TreeNode::~TreeNode()
= default;
