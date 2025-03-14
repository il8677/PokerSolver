#pragma once 

#include <vector>
#include <memory>



class TreeNode {
protected:
	TreeNode()=default;

	TreeNode(const TreeNode&)=delete;
	TreeNode& operator=(const TreeNode&)=delete;

public:
	size_t getChildCount() const { return children_.size(); }

	template <typename T, typename... Args>
	void emplaceChild(Args&&... args) 
		requires(std::is_base_of_v<TreeNode, T>) {

		std::unique_ptr<TreeNode>& newChild = children_.emplace_back(std::make_unique<T>(args...));
		newChild->parent_ = this;
	}

	TreeNode* getChild(size_t i) { return children_[i].get(); }

private:
	TreeNode* parent_ = nullptr;
	std::vector<std::unique_ptr<TreeNode>> children_;
};

class CardNode : public TreeNode {
public:
	CardNode() {

	}
};

class OpponentNode : public TreeNode {
public:

};

class PlayerNode : public TreeNode {
	struct CalcData{
		float reachProbability;
		float totalRegret;
	};
public:
	PlayerNode(size_t actionCount) : data_(actionCount) {

	}

private:
	std::vector<CalcData> data_;
};

class TerminalNode : public TreeNode {
public:
	TerminalNode() {

	}
private:
};