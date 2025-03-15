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
    if (IsRaise(history.back())) {
        return false;
    }

    return history.size() % 2 == 0;;
}

void HandlePlayerNode(PlayerNode& node, const History& history) {
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
            node.emplaceChild<OpponentNode>();
        }
    }
}

void HandleOpponentNode(OpponentNode& node, const History& history) {
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
            node.emplaceChild<PlayerNode>(ACTION_COUNT);
        }
    }
}