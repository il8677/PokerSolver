#include "PostFlop.hpp"

bool IsEndOfBetting(const History& history) {
    return history.size() % 2 == 0;
}

void HandlePlayerNode(PlayerNode& node, const History& history) {
    History newHistory = { history };
    newHistory.emplace_back();
    for (size_t i = 0; i < Action::ACTION_COUNT; i++) {
        newHistory.back() = static_cast<Action>(i);
        if (IsEndOfBetting(newHistory)) {
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
        if(IsEndOfBetting(newHistory)) {
            node.emplaceChild<CardNode>();
        } else {
            node.emplaceChild<PlayerNode>(Action::ACTION_COUNT);
        }
    }
}