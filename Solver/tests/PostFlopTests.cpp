#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "PostFlop.hpp"

SCENARIO("Player Node") {
    WHEN("When HandlePlayerNode() is called") {
        GIVEN("A Player Node and an empty history") {
        PlayerNode node(static_cast<size_t>(Action::ACTION_COUNT));
            THEN("Opponent nodes are added for each action") {
                HandlePlayerNode(&node, History{});
                REQUIRE(node.getChildCount() == ACTION_COUNT);
                for (auto& child : node) 
                    REQUIRE(dynamic_cast<OpponentNode*>(child.get()));
            }
        }
    }
}