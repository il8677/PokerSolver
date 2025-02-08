#include <vector>
#include <memory>

class TreeNode {
public:
	TreeNode()=default;

	TreeNode(const TreeNode&)=delete;
	TreeNode& operator=(const TreeNode&)=delete;

	size_t getChildCount() const { return children_.size(); }

	template <typename T, typename... Args>
	void emplaceChild(Args&&... args) {
		children_.emplace_back(std::make_unique<T>(args...));
	}

private:
	std::vector<std::unique_ptr<TreeNode>> children_;
};

class CardNode : public TreeNode {

};

class OpponentNode : public TreeNode {

};

class TerminalNode : public TreeNode {

};