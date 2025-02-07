#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <Strategy.hpp>

SCENARIO("Strategies can be created") {
	GIVEN("An information set") {
		InfromationPartition set = {"a", "ab", "abc"};
		WHEN("A strategy is created") {
			Strategy<3> strategy(set);
			THEN("The actions are uniformly distributed") {
				for(const auto& is : set) {
					for(size_t i = 0; i < 3; i++) {
						REQUIRE(strategy.getAction(is, i) == Catch::Approx(1.f/3));
					}
				}
			}

		}

	}

}

SCENARIO("Strategies can be updated") {
	GIVEN("A strategy") {
		InfromationPartition set = {"a", "ab", "abc"};
		Strategy<3> strategy(set);
		WHEN("The actions are corrected") {
			strategy.updateAction("a", {0.25, 0.375, 0.375});
			THEN("The same actions are retrieved") {
				REQUIRE(strategy.getAction("a", 0) == Catch::Approx(0.25));
			}

		}

	}
}