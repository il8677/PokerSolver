#pragma once
#include "TreeNode.hpp"

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

void HandlePlayerNode(PlayerNode* node);