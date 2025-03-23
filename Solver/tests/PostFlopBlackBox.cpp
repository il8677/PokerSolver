#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "PostFlop.hpp"

void HandleHeroNode(HeroNode& node, const History& history) { HandlePlayerNode(node, history); }
void HandleVillianNode(VillianNode& node, const History& history) { HandlePlayerNode(node, history); }

SCENARIO("Empty histories") {
    GIVEN("A player node") {
        HeroNode node { ACTION_COUNT };
        WHEN("HandleHeroNode() is called") {
            HandleHeroNode(node, History{});
            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<VillianNode>(CHECK_FOLD));
                REQUIRE(node.getChild<InvalidNode> (CALL));
                REQUIRE(node.getChild<VillianNode>(RAISE_HALF));
                REQUIRE(node.getChild<VillianNode>(RAISE_1));
                REQUIRE(node.getChild<VillianNode>(RAISE_15));
            }
        }
    }

    GIVEN("An opponent node") {
        VillianNode node{};
        WHEN("HandleVillianNode() is called") {
            HandleVillianNode(node, History{});
            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<HeroNode>(CHECK_FOLD));
                REQUIRE(node.getChild<InvalidNode>(CALL));
                REQUIRE(node.getChild<HeroNode>(RAISE_HALF));
                REQUIRE(node.getChild<HeroNode>(RAISE_1));
                REQUIRE(node.getChild<HeroNode>(RAISE_15));
            }
        }
    }
}

SCENARIO("One action histories") {
    GIVEN("A check action") {
        const History history{ CHECK_FOLD };
        WHEN("HandleHeroNode() is called") {
            HeroNode node{ static_cast<size_t>(Action::ACTION_COUNT) };
            HandleHeroNode(node, history);
            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<CardNode>(CHECK_FOLD));
                REQUIRE(node.getChild<InvalidNode>(CALL));
                REQUIRE(node.getChild<VillianNode>(RAISE_HALF));
                REQUIRE(node.getChild<VillianNode>(RAISE_1));
                REQUIRE(node.getChild<VillianNode>(RAISE_15));
            }
        }

        WHEN("HandleVillianNode() is called") {
            VillianNode node;
            HandleVillianNode(node, history);
            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<CardNode>(CHECK_FOLD));
                REQUIRE(node.getChild<InvalidNode>(CALL));
                REQUIRE(node.getChild<HeroNode>(RAISE_HALF));
                REQUIRE(node.getChild<HeroNode>(RAISE_1));
                REQUIRE(node.getChild<HeroNode>(RAISE_15));
            }
        }
    }

    GIVEN("A raise action") {
        const History history{ RAISE_HALF };
        WHEN("HandleHeroNode() is called"){
            HeroNode node{ ACTION_COUNT };
            HandleHeroNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<VillianNode>(RAISE_HALF));
                REQUIRE(node.getChild<VillianNode>(RAISE_1));
                REQUIRE(node.getChild<VillianNode>(RAISE_15));
            }
        }

        WHEN("HandleVillianNode() is called") {
            VillianNode node;
            HandleVillianNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<HeroNode>(RAISE_HALF));
                REQUIRE(node.getChild<HeroNode>(RAISE_1));
                REQUIRE(node.getChild<HeroNode>(RAISE_15));
            }
        }
    }
}

SCENARIO("Raising") {
    GIVEN("OP open IP continue") {
        History history{RAISE_1, RAISE_1};
        WHEN("HandleHeroNode is called") {
            HeroNode node{ ACTION_COUNT };
            HandleHeroNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<VillianNode>(RAISE_HALF));
                REQUIRE(node.getChild<VillianNode>(RAISE_1));
                REQUIRE(node.getChild<VillianNode>(RAISE_15));
            }
        }

        WHEN("HandleVillianNode is called") {
            VillianNode node;
            HandleVillianNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<HeroNode>(RAISE_HALF));
                REQUIRE(node.getChild<HeroNode>(RAISE_1));
                REQUIRE(node.getChild<HeroNode>(RAISE_15));
            }
        }
    }

    GIVEN("OP open OP continue") {
        History history{RAISE_1, RAISE_1, RAISE_1};
        WHEN("HandleHeroNode is called") {
            HeroNode node{ ACTION_COUNT };
            HandleHeroNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<VillianNode>(RAISE_HALF));
                REQUIRE(node.getChild<VillianNode>(RAISE_1));
                REQUIRE(node.getChild<VillianNode>(RAISE_15));
            }
        }

        WHEN("HandleVillianNode is called") {
            VillianNode node;
            HandleVillianNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<CardNode>(CALL));
                REQUIRE(node.getChild<HeroNode>(RAISE_HALF));
                REQUIRE(node.getChild<HeroNode>(RAISE_1));
                REQUIRE(node.getChild<HeroNode>(RAISE_15));
            }
        }
    }
}

SCENARIO("End of game") {
    GIVEN("An end game history") {
        History history{ CHECK_FOLD, RAISE_1, CALL, CHECK_FOLD };
        WHEN("When HandleHeroNode is called") {
            HeroNode node{ ACTION_COUNT };
            HandleHeroNode(node, history);

            THEN("A node is added for each action") {
                REQUIRE(node.getChildCount() == ACTION_COUNT);
            }

            THEN("The child types are correct") {
                REQUIRE(node.getChild<TerminalNode>(CHECK_FOLD));
                REQUIRE(node.getChild<InvalidNode>(CALL));
                REQUIRE(node.getChild<VillianNode>(RAISE_HALF));
                REQUIRE(node.getChild<VillianNode>(RAISE_1));
                REQUIRE(node.getChild<VillianNode>(RAISE_15));
            }
        }
    }
}

SCENARIO("BuildGameTree tests") {
    WHEN("BuildGameTree is called") {
        //auto tree = BuildGameTree(false);
        THEN("The game tree is correct") {

        }
    }
}

