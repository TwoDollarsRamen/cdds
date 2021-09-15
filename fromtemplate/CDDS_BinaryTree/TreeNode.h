#pragma once

class TreeNode
{
public:
	TreeNode(int value);
	~TreeNode();

	bool HasLeft() { return (m_left != nullptr); }
	bool HasRight() { return (m_right != nullptr); }

	void Draw(int x, int y, bool selected=false);

	/* This class originally had getters and setters.
	 * 
	 * I removed them and just made the members public,
	 * getters and setters that only set and return
	 * values are completely useless. */

	int m_value;

	TreeNode* m_left = nullptr;
	TreeNode* m_right = nullptr;
};

