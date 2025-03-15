#include "PostFlop.hpp"

void HandlePlayerNode(PlayerNode* node, History history) {
    for (size_t i = 0; i < Action::ACTION_COUNT; i++) {
        node->emplaceChild<OpponentNode>();
    }
}

void HandleOpponentNode(OpponentNode* node, History history) {

}