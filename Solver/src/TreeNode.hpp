#pragma once 

#include <vector>
#include <memory>

class TreeNode {
protected:
	TreeNode() = default;

	TreeNode(const TreeNode&) = delete;
	TreeNode& operator=(const TreeNode&) = delete;

public:
	virtual ~TreeNode() = default;

	size_t getChildCount() const { return children_.size(); }

	template <typename T, typename... Args>
	void emplaceChild(Args&&... args) 
		requires(std::is_base_of_v<TreeNode, T>) {

		std::unique_ptr<TreeNode>& newChild = children_.emplace_back(std::make_unique<T>(args...));
		newChild->parent_ = this;
	}

	TreeNode* getChild(size_t i) { return children_[i].get(); }
	
	template <typename T>
	T* getChild(size_t i) { return dynamic_cast<T*>(children_[i].get()); }

	auto begin() { return children_.begin(); }
	auto end()   { return children_.end(); }

private:
	TreeNode* parent_ = nullptr;
	std::vector<std::unique_ptr<TreeNode>> children_;
};

class CardNode : public TreeNode {
public:
	CardNode() = default;
	~CardNode() = default;
};

class OpponentNode : public TreeNode {
public:
	OpponentNode() = default;
	~OpponentNode() = default;
};

class PlayerNode : public TreeNode {
	struct CalcData{
		float reachProbability;
		float totalRegret;
	};
public:
	PlayerNode(size_t actionCount) : data_(actionCount) {}
	~PlayerNode() = default;

private:
	std::vector<CalcData> data_;
};

class TerminalNode : public TreeNode {
public:
	TerminalNode() = default;
	~TerminalNode() = default;
private:
};