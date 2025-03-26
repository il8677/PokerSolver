#include "PostFlop.hpp"

#include <algorithm>
#include <variant>
#include <deque>

bool IsRaise(Action action) {
    switch (action) {
    case RAISE_HALF:
    case RAISE_1:
    case RAISE_15:
        return true;
    default:
        return false;
    }
}

bool IsEndOfBetting(const History& history) {
    if (IsRaise(history.back()))
        return false;
    if (history.back() == CALL)
        return true;

    return history.size() == 2;
}

bool IsEndOfGame(const History& history) {
    if (IsRaise(history.back()))
        return false;
    return history.size() >= 4;
}

size_t ChildIndexOf(TreeNode& parent, TreeNode& child) {
    for (size_t i = 0; i < parent.getChildCount(); i++) {
        if (parent.getChild(i) == &child) return i;
    }
    return -1;
}

History GetHistoryOf(TreeNode& node) {
    if (!node.getParent()) return History{};

    History h = GetHistoryOf(*node.getParent());
    h.push_back(static_cast<Action>(ChildIndexOf(*node.getParent(), node)));

    return h;
}

bool ReachedBetLimit(const History& h) {
    auto searchUntil = std::max<History::size_type>(0, h.size() - BET_LIMIT);
    for (size_t i = h.size() - 1; i >= searchUntil; i--) {
        if (!IsRaise(h[i])) return false;
    }

    return true;
}

// TODO: What a mess
template <PlayerNode InPositionNode>
struct TreeBuilder {
    using OutPositionNode = OpponentOf<InPositionNode>;
public:

    std::unique_ptr<TreeNode> operator()() {
        return buildGameTree();
    }

private:
    void buildNode(TreeNode& node) {
        History h = GetHistoryOf(node);
        if(auto* n = dynamic_cast<VillianNode*>(&node)) {
            HandlePlayerNode(*n, h, false);
        }

        if(auto* n = dynamic_cast<HeroNode*>(&node)) {
            HandlePlayerNode(*n, h, false);
        }

        if(auto* n = dynamic_cast<CardNode*>(&node)) {
            node.template emplaceChild<OutPositionNode>(ACTION_COUNT);
        }
    }

    void processLayer(std::deque<TreeNode*>& layer) {
        std::deque<TreeNode*> nextLayer;

        for (TreeNode* n : layer) {
            buildNode(*n);
            for (size_t i = 0; i < n->getChildCount(); i++) {
                TreeNode* node = n->getChild(i);

                if (dynamic_cast<PlayerNode*>(node) || dynamic_cast<VillianNode*>(node) || dynamic_cast<CardNode*>(node) {
                    nextLayer.push_back(node);
                }
            }
        }
        
        layer = std::move(nextLayer);
    }

    std::unique_ptr<TreeNode> buildGameTree() {
        auto root = std::make_unique<CardNode>();
        auto& firstPlayer = root->template emplaceChild<OutPositionNode>(ACTION_COUNT);
        HandlePlayerNode<>(firstPlayer, History{});

        std::deque<TreeNode*> thisLayer{ &firstPlayer };
        while(thisLayer.size()) {
            processLayer(layer);
        }

        return root;
    }

};

std::unique_ptr<TreeNode> BuildGameTree(bool heroInPosition) {
    if (heroInPosition) return TreeBuilder<HeroNode>{}();
    return TreeBuilder<VillianNode>{}();
}
