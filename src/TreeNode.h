#pragma once
#ifndef __TREE_NODE__
#define __TREE_NODE__

#include <string>
#include <functional>

class TreeNode
{
public:
	TreeNode();
	~TreeNode();

	typedef std::function<bool()> Condition;
	typedef std::function<void()> Action;

	Condition condition;
	Action action;
	
	bool isRoot;
	bool isLeaf;
	TreeNode* leftChild;
	TreeNode* rightChild;
	std::string Name;
};

#endif /* defined (__TREE_NODE__) */