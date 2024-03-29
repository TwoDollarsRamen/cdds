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
	/* The node is inserted at the root if the tree is empty */
	if (!m_pRoot) {
		m_pRoot = new TreeNode(a_nValue);
		return;
	}
	
	/* Traverse down the correct branches of the tree
	 * to find the end; smaller numbers get places
	 * on the left branch, larger values are placed
	 * on the right branch. */
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

	/* Create the branch on the correct parent. */
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
	/* Traverse to find the value. */
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
	TreeNode* parent = nullptr;
	TreeNode* node = nullptr;

	if (!FindNode(a_nValue, node, parent)) {
		return;
	}

	if (node->m_right) {
		/* Find the minimum value on the right branch */
		auto n = node->m_right;
		auto nparent = node;
		for (; n->m_left; nparent = n, n = n->m_left) {
			
		}

		node->m_value = n->m_value;

		/* Fill in any gaps left by the deletion */
		if (n == nparent->m_left) {
			nparent->m_left = n->m_right;
		} else if (n == nparent->m_right) {
			nparent->m_right = n->m_right;
		}

		delete n;
	} else {
		/* Fill in any gaps left by the deletion */
		if (parent) {
			if (node == parent->m_left) {
				parent->m_left = node->m_left;
			} else if (node == parent->m_right) {
				parent->m_right = node->m_left;
			}
		}

		/* If it's the root being deleted,
		 * set a new root. */
		if (node == m_pRoot) {
			m_pRoot = node->m_left;
		}

		delete node;
	}
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
