#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "PostFlop.hpp"

SCENARIO("Empty histories") {
    GIVEN("A player node") {
        PlayerNode node { static_cast<size_t>(Action::ACTION_COUNT) };
        WHEN("HandlePlayerNode() is called") {
            HandlePlayerNode(node, History{});
            THEN("Opponent nodes are added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
                for (auto& child : node) 
                    REQUIRE(dynamic_cast<OpponentNode*>(child.get()));
            }
        }
    }

    GIVEN("An opponent node") {
        OpponentNode node{};
        WHEN("HandleOpponentNode() is called") {
            HandleOpponentNode(node, History{});
            THEN("Player nodes are added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
                for (auto& child : node) 
                    REQUIRE(dynamic_cast<PlayerNode*>(child.get()));
            }
        }
    }
}

SCENARIO("One action histories") {
    GIVEN("A check action") {
        const History history{CHECK_FOLD};
        WHEN("HandlePlayerNode() is called") {
            PlayerNode node{ static_cast<size_t>(Action::ACTION_COUNT) };
            HandlePlayerNode(node, history);
            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The check action is a card node") {
                REQUIRE(dynamic_cast<CardNode*>(node.getChild(CHECK_FOLD)));
            }
        }

        WHEN("HandleOpponentNode() is called") {
            OpponentNode node{ static_cast<size_t>(Action::ACTION_COUNT) };
            HandleOpponentNode(node, history);
            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The check action is a card node") {
                REQUIRE(dynamic_cast<CardNode*>(node.getChild(CHECK_FOLD)));
            }
        }
    }
}
