#include <PostFlop.hpp>

void HandlePlayerNode(PlayerNode* node) {
    for (size_t i = 0; i < Action::ACTION_COUNT; i++) {
        node->emplaceChild<OpponentNode>();
    }
}
