#include "PostFlop.hpp"

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

void HandlePlayerNode(HeroNode& node, const History& history) {
    History newHistory = { history };
    newHistory.emplace_back();
    for (size_t i = 0; i < Action::ACTION_COUNT; i++) {
        newHistory.back() = static_cast<Action>(i);

        const bool lastActionIsRaise = history.size() && IsRaise(history.back());
        
        if (lastActionIsRaise && newHistory.back() == CHECK_FOLD) {
            node.emplaceChild<TerminalNode>();
        } else if (!lastActionIsRaise && newHistory.back() == CALL) {
            node.emplaceChild<InvalidNode>();
        } else if (IsEndOfBetting(newHistory)) {
            node.emplaceChild<CardNode>();
        } else {
            node.emplaceChild<VillianNode>();
        }
    }
}

void HandleOpponentNode(VillianNode& node, const History& history) {
    History newHistory = { history };
    newHistory.emplace_back();
    for (size_t i = 0; i < Action::ACTION_COUNT; i++) {
        newHistory.back() = static_cast<Action>(i);

        const bool lastActionIsRaise = history.size() && IsRaise(history.back());
        
        if (lastActionIsRaise && newHistory.back() == CHECK_FOLD) {
            node.emplaceChild<TerminalNode>();
        } else if (!lastActionIsRaise && newHistory.back() == CALL) {
            node.emplaceChild<InvalidNode>();
        } else if (IsEndOfBetting(newHistory)) {
            node.emplaceChild<CardNode>();
        } else {
            node.emplaceChild<HeroNode>(ACTION_COUNT);
        }
    }
}