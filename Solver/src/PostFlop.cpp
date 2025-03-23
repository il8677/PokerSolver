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

    std::unique_ptr<TreeNode> buildGameTree() {
        auto root = std::make_unique<CardNode>();
        auto& firstPlayer = root->template emplaceChild<OutPositionNode>(ACTION_COUNT);
        HandlePlayerNode<>(firstPlayer, History{});

        using VisitableNode = 
            std::variant<CardNode*, VillianNode*, HeroNode*>;

        std::deque<TreeNode*> thisLayer{ &firstPlayer };
        while(thisLayer.size()) {
            std::deque<TreeNode*> nextLayer;
            while (thisLayer.size()) {
                auto* next = thisLayer.front();
                if(dynamic_cast<VillianNode*>(next) 
                || dynamic_cast<HeroNode*>(next)) 
                    nextLayer.push_back(next);

                thisLayer.pop_front();
            }
            if (nextLayer.size() == 0) break;

            for (TreeNode* n : nextLayer) {
                buildNode(*n);
            }

            
            thisLayer = std::move(nextLayer);
        }

        return root;
    }

};

std::unique_ptr<TreeNode> BuildGameTree(bool heroInPosition) {
    if (heroInPosition) return TreeBuilder<HeroNode>{}();
    return TreeBuilder<VillianNode>{}();
}
