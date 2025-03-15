#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "PostFlop.hpp"

SCENARIO("Player Node Generation") {
    WHEN("HandlePlayerNode() is called") {
        GIVEN("A Player Node and an empty history") {
            PlayerNode node { static_cast<size_t>(Action::ACTION_COUNT) };
            HandlePlayerNode(&node, History{});
            THEN("Opponent nodes are added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
                for (auto& child : node) 
                    REQUIRE(dynamic_cast<OpponentNode*>(child.get()));
            }
        }
    }
}

SCENARIO("Opponent Node Generation") {
    WHEN("HandleOpponentNode() is called") {
        GIVEN("An Opponent Node and an empty history") {
            OpponentNode node{};
            HandleOpponentNode(&node, History{});
            THEN("") {

            }
        }
    }
}