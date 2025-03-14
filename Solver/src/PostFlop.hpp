#pragma once
#include "TreeNode.hpp"

#include <queue>
#include <memory>

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

const int betLimit = 3;

void HandlePlayerNode(PlayerNode* node);