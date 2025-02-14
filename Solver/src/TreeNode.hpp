#include <vector>
#include <memory>



class TreeNode {
public:
	TreeNode()=default;

	TreeNode(const TreeNode&)=delete;
	TreeNode& operator=(const TreeNode&)=delete;

	size_t getChildCount() const { return children_.size(); }

	template <typename T, typename... Args>
	void emplaceChild(Args&&... args) 
		requires(std::is_base_of_v<TreeNode, T>) {

		children_.emplace_back(std::make_unique<T>(args...));
	}

	TreeNode* getChild(size_t i) { return children_[i].get(); }

private:
	std::vector<std::unique_ptr<TreeNode>> children_;
};

class CardNode : public TreeNode {
public:
	CardNode();
};

class OpponentNode : public TreeNode {

};

class TerminalNode : public TreeNode {

};