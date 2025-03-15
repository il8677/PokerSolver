#include "PostFlop.hpp"

void HandlePlayerNode(PlayerNode& node, const History& history) {
    for (size_t i = 0; i < Action::ACTION_COUNT; i++) {
        node.emplaceChild<OpponentNode>();
    }
}

void HandleOpponentNode(OpponentNode& node, const History& history) {
    for (size_t i = 0; i < Action::ACTION_COUNT; i++) {
        node.emplaceChild<PlayerNode>(Action::ACTION_COUNT);
    }
}