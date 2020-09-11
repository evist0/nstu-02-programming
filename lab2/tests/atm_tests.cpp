#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <lab2/atm.hpp>

TEST_CASE("ATM works correctly") {
    SECTION("== operator") {
        SECTION("Balance equals number") {
            lab2::ATM atm = lab2::ATM("i2zs45", 20.0f, 15.0f);

            REQUIRE( (atm == 15.0f) == true);
        }

        SECTION("Balance doesn't equal number") {
            lab2::ATM atm = lab2::ATM("i2zs45", 20.0f, 15.0f);

            REQUIRE( (atm == 16.0f) == false);
        }
    }

    SECTION("!= operator") {
        SECTION("Balance equals number") {
            lab2::ATM atm = lab2::ATM("i2zs45", 20.0f, 15.0f);

            REQUIRE( (atm != 16.0f) == true);
        }

        SECTION("Balance doesn't equal number") {
            lab2::ATM atm = lab2::ATM("i2zs45", 20.0f, 15.0f);

            REQUIRE( (atm != 15.0f) == false);
        }
    }

    SECTION("+ operator") {
        SECTION("Deposit default") {
            lab2::ATM atm = lab2::ATM("i2zs45", 20.0f, 15.0f);
            atm + 15.0f;
            CHECK( (atm == 30.0f) == true);
        }

        SECTION("Deposit < 0 should throw exception") {
            lab2::ATM atm = lab2::ATM("i2zs45", 20.0f, 15.0f);

            CHECK_THROWS(atm + -20.0f);
        }
    }

    SECTION("- operator") {
        SECTION("Withdraw default") {
            lab2::ATM atm = lab2::ATM("i2zs45", 20.0f, 15.0f);
            atm - 15.0f;
            CHECK( (atm == 0.0f) == true);
        }

        SECTION("Withdraw < 0 should throw exception") {
            lab2::ATM atm = lab2::ATM("i2zs45", 20.0f, 15.0f);
            CHECK_THROWS(atm - -20.0f);
        }

        SECTION("Withdraw > balance should throw exception") {
            lab2::ATM atm = lab2::ATM("i2zs45", 20.0f, 15.0f);
            CHECK_THROWS(atm - 16.0f);
        }

        SECTION("Withdraw > maxWithdraw should throw exception") {
            lab2::ATM atm = lab2::ATM("i2zs45", 20.0f, 150.0f);
            CHECK_THROWS(atm - 120);
        }
    }
}