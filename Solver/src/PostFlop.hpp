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

void HandlePlayerNode(PlayerNode* node, const History&);
void HandleOpponentNode(OpponentNode* node, const History&);