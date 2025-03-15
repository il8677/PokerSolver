#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "PostFlop.hpp"

SCENARIO("Empty histories") {
    GIVEN("A player node") {
        PlayerNode node { ACTION_COUNT };
        WHEN("HandlePlayerNode() is called") {
            HandlePlayerNode(node, History{});
            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<OpponentNode>(CHECK_FOLD));
                REQUIRE(node.getChild<InvalidNode> (CALL));
                REQUIRE(node.getChild<OpponentNode>(RAISE_HALF));
                REQUIRE(node.getChild<OpponentNode>(RAISE_1));
                REQUIRE(node.getChild<OpponentNode>(RAISE_15));
            }
        }
    }

    GIVEN("An opponent node") {
        OpponentNode node{};
        WHEN("HandleOpponentNode() is called") {
            HandleOpponentNode(node, History{});
            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<PlayerNode>(CHECK_FOLD));
                REQUIRE(node.getChild<InvalidNode>(CALL));
                REQUIRE(node.getChild<PlayerNode>(RAISE_HALF));
                REQUIRE(node.getChild<PlayerNode>(RAISE_1));
                REQUIRE(node.getChild<PlayerNode>(RAISE_15));
            }
        }
    }
}

SCENARIO("One action histories") {
    GIVEN("A check action") {
        const History history{ CHECK_FOLD };
        WHEN("HandlePlayerNode() is called") {
            PlayerNode node{ static_cast<size_t>(Action::ACTION_COUNT) };
            HandlePlayerNode(node, history);
            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<CardNode>(CHECK_FOLD));
                REQUIRE(node.getChild<InvalidNode>(CALL));
                REQUIRE(node.getChild<OpponentNode>(RAISE_HALF));
                REQUIRE(node.getChild<OpponentNode>(RAISE_1));
                REQUIRE(node.getChild<OpponentNode>(RAISE_15));
            }
        }

        WHEN("HandleOpponentNode() is called") {
            OpponentNode node;
            HandleOpponentNode(node, history);
            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<CardNode>(CHECK_FOLD));
                REQUIRE(node.getChild<InvalidNode>(CALL));
                REQUIRE(node.getChild<PlayerNode>(RAISE_HALF));
                REQUIRE(node.getChild<PlayerNode>(RAISE_1));
                REQUIRE(node.getChild<PlayerNode>(RAISE_15));
            }
        }
    }

    GIVEN("A raise action") {
        const History history{ RAISE_HALF };
        WHEN("HandlePlayerNode() is called"){
            PlayerNode node{ ACTION_COUNT };
            HandlePlayerNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<OpponentNode>(RAISE_HALF));
                REQUIRE(node.getChild<OpponentNode>(RAISE_1));
                REQUIRE(node.getChild<OpponentNode>(RAISE_15));
            }
        }

        WHEN("HandleOpponentNode() is called") {
            OpponentNode node;
            HandleOpponentNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<PlayerNode>(RAISE_HALF));
                REQUIRE(node.getChild<PlayerNode>(RAISE_1));
                REQUIRE(node.getChild<PlayerNode>(RAISE_15));
            }
        }
    }
}

SCENARIO("Raising") {
    GIVEN("OP open IP continue") {
        History history{RAISE_1, RAISE_1};
        WHEN("HandlePlayerNode is called") {
            PlayerNode node{ ACTION_COUNT };
            HandlePlayerNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<OpponentNode>(RAISE_HALF));
                REQUIRE(node.getChild<OpponentNode>(RAISE_1));
                REQUIRE(node.getChild<OpponentNode>(RAISE_15));
            }
        }

        WHEN("HandleOpponentNode is called") {
            OpponentNode node;
            HandleOpponentNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<PlayerNode>(RAISE_HALF));
                REQUIRE(node.getChild<PlayerNode>(RAISE_1));
                REQUIRE(node.getChild<PlayerNode>(RAISE_15));
            }
        }
    }

    GIVEN("OP open OP continue") {
        History history{RAISE_1, RAISE_1, RAISE_1};
        WHEN("HandlePlayerNode is called") {
            PlayerNode node{ ACTION_COUNT };
            HandlePlayerNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<OpponentNode>(RAISE_HALF));
                REQUIRE(node.getChild<OpponentNode>(RAISE_1));
                REQUIRE(node.getChild<OpponentNode>(RAISE_15));
            }
        }

        WHEN("HandleOpponentNode is called") {
            OpponentNode node;
            HandleOpponentNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<PlayerNode>(RAISE_HALF));
                REQUIRE(node.getChild<PlayerNode>(RAISE_1));
                REQUIRE(node.getChild<PlayerNode>(RAISE_15));
            }
        }
    }
}
