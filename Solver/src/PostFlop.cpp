#include <PostFlop.hpp>

void HandlePlayerNode(PlayerNode* node) {
    for (size_t i = 0; i < ACTIONS_PER_HAND; i++) {
        node->emplaceChild<OpponentNode>();
    }
}
