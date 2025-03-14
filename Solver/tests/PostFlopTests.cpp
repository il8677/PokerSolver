#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <PostFlop.hpp>

SCENARIO("Player Node") {
    GIVEN("A Player Node") {
        PlayerNode node(static_cast<size_t>(Action::ACTION_COUNT));
        WHEN("When HandlePlayerNode() is called") {
            THEN("Opponent nodes are added for each action") {
                HandlePlayerNode(&node);
                REQUIRE(node.getChildCount() == ACTION_COUNT);
                for (auto& child : node) 
                    REQUIRE(dynamic_cast<OpponentNode*>(child.get()));
            }
        }
    }
}