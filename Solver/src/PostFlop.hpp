#pragma once
#include "TreeNode.hpp"

#include <memory>
#include <array>

enum class Actions {
	CHECK_FOLD,
	CALL,
	RAISE_HALF,
	RAISE_1,
	ACTION_COUNT
};

enum class Suit {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES,
	SUIT_COUNT
};

enum class Rank {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE, RANK_COUNT
};

struct PokerCard {
    Rank rank;
    Suit suit;
};

const int BET_LIMIT = 3;
const std::array<double, 3> POT_MULTIPLIERS{ 0.5, 1, 1.5 };
const size_t ACTIONS_PER_HAND = POT_MULTIPLIERS.size() + 2;

void HandlePlayerNode(PlayerNode* node);