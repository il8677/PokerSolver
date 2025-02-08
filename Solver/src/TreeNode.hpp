#include <vector>
#include <memory>

class TreeNode {
public:
	size_t getChildCount() const { return children_.size(); }
private:
	std::vector<std::unique_ptr<TreeNode>> children_;
};

class CardNode : public TreeNode {

};

class OpponentNode : public TreeNode {

};

class TerminalNode : public TreeNode {

};