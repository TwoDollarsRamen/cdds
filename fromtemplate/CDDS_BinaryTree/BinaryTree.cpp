/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <numeric>
#include <cstdlib>
using namespace std;


BinaryTree::BinaryTree()
{
    m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
	while (m_pRoot)
	{
		Remove(m_pRoot->m_value);
	}
}

// Return whether the tree is empty
bool BinaryTree::IsEmpty() const 
{ 
	return (m_pRoot == nullptr);
}

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
void BinaryTree::Insert(int a_nValue) /* Literally have no idea what these naming conventions mean. */
{
	if (!m_pRoot) {
		m_pRoot = new TreeNode(a_nValue);
		return;
	}
	
	TreeNode* parent = nullptr;
	for (auto cur = m_pRoot; cur;) {
		parent = cur;

		if (a_nValue < cur->m_value) {
			cur = cur->m_left;
			continue;
		} else if (a_nValue > cur->m_value) {
			cur = cur->m_right;
			continue;
		} else {
			return;
		}
	}

	if (a_nValue < parent->m_value) {
		parent->m_left = new TreeNode(a_nValue);
		return;
	}
	parent->m_right = new TreeNode(a_nValue);
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent: nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	TreeNode* parent = nullptr;
	for (auto cur = m_pRoot; cur;) {
		if (a_nSearchValue == cur->m_value) {
			ppOutNode = cur;
			ppOutParent = parent;
			return true;
		} else {
			parent = cur;
			if (a_nSearchValue < cur->m_value) {
				cur = cur->m_left;
			} else {
				cur = cur->m_right;
			}
		}

	}

	return false;
}

void BinaryTree::Remove(int a_nValue)
{
	TreeNode* parent;
	TreeNode* node;

	FindNode(a_nValue, node, parent);
	
	if (!node) { return; }

	if (node->m_right) {
		int min = std::numeric_limits<int>::max();
		auto n = node->m_right;
		for (; n; n = n->m_left) {
			if (n->m_value < min) { min = n->m_value; }
		}

		auto min_node = Find(min);
		node->m_value = min;

		if (parent) {
			if (a_nValue == parent->m_left->m_value) {
				parent->m_left = min_node->m_right;
			}
			else if (a_nValue == parent->m_right->m_value) {
				parent->m_right = min_node->m_right;
			}
		}
	} else {
		if (parent) {
			if (parent->m_left && a_nValue == parent->m_left->m_value) {
				parent->m_left = node->m_left;
			}
			else if (parent->m_right && a_nValue == parent->m_right->m_value) {
				parent->m_right = node->m_left;
			}
		}

		if (a_nValue == m_pRoot->m_value) {
			m_pRoot = node->m_left;
		}
	}

	if (node == m_pRoot) {
		m_pRoot = nullptr;
	}

	delete node;
}

void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	
	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			
			Draw(pNode->m_left, x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			Draw(pNode->m_right, x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		pNode->Draw(x, y, (selected == pNode));
	}
}