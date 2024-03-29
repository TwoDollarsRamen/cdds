/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

class TreeNode;

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	bool IsEmpty() const;
	void Insert(int a_nValue);
	
	/* Remove a node from the list */
	void Remove(int a_nValue);

	/* Find a node by it's value */
	TreeNode* Find(int a_nValue);

	/* Draw the tree */
	void Draw(TreeNode* selected = nullptr);

private:
	//Find the node with the specified value.
	bool FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent);

	/* Draw a node */
	void Draw(TreeNode*, int x, int y, int horizontalSpacing, TreeNode* selected = nullptr);

	//The root node of the tree
	TreeNode* m_pRoot; /* what is this naming convention? */
};

#endif //_BINARYTREE_H_