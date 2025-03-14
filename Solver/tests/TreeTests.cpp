#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <TreeNode.hpp>
#include <PostFlop.hpp>

class MockNode : public TreeNode{};

SCENARIO("Tree children management") {
	GIVEN("A tree node") {
		MockNode node;
		THEN("It starts with no children") {
			REQUIRE(node.getChildCount() == 0);
		}

		WHEN("A child is added") {
			node.emplaceChild<MockNode>();
			THEN("Child count is incremented") {
				REQUIRE(node.getChildCount() == 1);
			}

			THEN("The children can be retrieved") {
				REQUIRE(node.getChild(0) != nullptr);
			}
		}
	}
}

SCENARIO("Card nodes") {
	GIVEN("A card node") {
		CardNode node;
	}
}

SCENARIO("Opponent nodes") {
}

SCENARIO("Player nodes") {
	GIVEN("A player node with 3 actions") {
		PlayerNode player(3);
	}
}