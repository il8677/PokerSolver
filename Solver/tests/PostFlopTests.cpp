#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "PostFlop.hpp"

SCENARIO("Empty Histories") {
    GIVEN("A Player Node") {
        WHEN("HandlePlayerNode() is called") {
            PlayerNode node { static_cast<size_t>(Action::ACTION_COUNT) };
            HandlePlayerNode(&node, History{});
            THEN("Opponent nodes are added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
                for (auto& child : node) 
                    REQUIRE(dynamic_cast<OpponentNode*>(child.get()));
            }
        }
    }

    GIVEN("An Opponent Node") {
        WHEN("HandleOpponentNode() is called") {
            OpponentNode node{};
            HandleOpponentNode(&node, History{});
            THEN("Player nodes are added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
                for (auto& child : node) 
                    REQUIRE(dynamic_cast<PlayerNode*>(child.get()));
            }
        }
    }
}
