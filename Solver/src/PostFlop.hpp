#pragma once
#include "TreeNode.hpp"
#include "Poker.hpp"
#include "InformationSet.hpp"

#include <memory>
#include <array>

enum Action : size_t {
	CHECK_FOLD,
	CALL,
	RAISE_HALF,
	RAISE_1,
    RAISE_15,
	ACTION_COUNT
};

using History = std::vector<Action>;

struct PokerCard {
    Rank rank;
    Suit suit;
};

const int BET_LIMIT = 3;

bool IsRaise(Action action);
bool IsEndOfBetting(const History& history);

template<PlayerNode HandledType, TreeNodeType BettingEndType = CardNode>
void HandlePlayerNode(HandledType& node, const History& history) {
    using NextPlayerType = OpponentOf<HandledType>;

    History newHistory = { history };
    newHistory.emplace_back();
    for (size_t i = 0; i < Action::ACTION_COUNT; i++) {
        newHistory.back() = static_cast<Action>(i);

        const bool lastActionIsRaise = history.size() && IsRaise(history.back());
        
        if (lastActionIsRaise && newHistory.back() == CHECK_FOLD) {
            node.template emplaceChild<TerminalNode>();
        } 
        else if (!lastActionIsRaise && newHistory.back() == CALL) {
            node.template emplaceChild<InvalidNode>();
        } else if (IsEndOfBetting(newHistory)) {
            node.template emplaceChild<BettingEndType>();
        } else {
            node.template emplaceChild<NextPlayerType>(ACTION_COUNT);
        }
    }
}

