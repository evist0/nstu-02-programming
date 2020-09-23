#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <lab1/atm.hpp>

TEST_CASE("ATM works correctly") {
    SECTION("Constructor") {
        SECTION("Default") {
            lab1::ATM test_1 = lab1::ATM();

            REQUIRE(strcmp(test_1.id(), "not_provided") == 0);
            REQUIRE(test_1.balance() == 0.f);
            REQUIRE(test_1.maxWithdraw() == 0.f);
        }

        SECTION("Copy") {
            lab1::ATM test_1 = lab1::ATM();
            lab1::ATM test_2 = lab1::ATM(test_1);

            REQUIRE(strcmp(test_1.id(), test_2.id()) == 0);
            REQUIRE(test_1.balance() == test_2.balance());
            REQUIRE(test_1.maxWithdraw() == test_2.balance());
        }

        SECTION("Only id") {
            lab1::ATM test_1 = lab1::ATM("i2zs45");

            REQUIRE(strcmp(test_1.id(), "i2zs45") == 0);
            REQUIRE(test_1.balance() == 0);
            REQUIRE(test_1.maxWithdraw() == 0);
        }

        SECTION("Id, max withdraw") {
            lab1::ATM test_2 = lab1::ATM("pozs3x", 20.0f);

            REQUIRE(strcmp(test_2.id(), "pozs3x") == 0);
            REQUIRE(test_2.maxWithdraw() == 20.0f);
            REQUIRE(test_2.balance() == 0);
        }

        SECTION("Id, max withdraw, balance") {
            lab1::ATM test_3 = lab1::ATM("kslz24", 20.0f, 50.0f);

            REQUIRE(strcmp(test_3.id(), "kslz24") == 0);
            REQUIRE(test_3.maxWithdraw() == 20.0f);
            REQUIRE(test_3.balance() == 50.0f);
        }
    }

    SECTION("Withdraw operation") {
        SECTION("Withdraw default") {
            lab1::ATM atm = lab1::ATM("i2zs45", 20.0f, 15.0f);
            atm.withdraw(15.0f);
            REQUIRE(atm.balance() == 0.0f);
        }

        SECTION("Withdraw < 0 should throw exception") {
            lab1::ATM atm = lab1::ATM("i2zs45", 20.0f, 15.0f);
            REQUIRE_THROWS(atm.withdraw(-20.0f));
        }

        SECTION("Withdraw > balance should throw exception") {
            lab1::ATM atm = lab1::ATM("i2zs45", 20.0f, 15.0f);
            REQUIRE_THROWS(atm.withdraw(16.0f));
        }

        SECTION("Withdraw > maxWithdraw should throw exception") {
            lab1::ATM atm = lab1::ATM("i2zs45", 20.0f, 150.0f);
            REQUIRE_THROWS(atm.withdraw(120));
        }
    }

    SECTION("Deposit operation") {
        SECTION("Deposit default") {
            lab1::ATM atm = lab1::ATM("i2zs45", 20.0f, 15.0f);
            atm.deposit(15.0f);
            REQUIRE(atm.balance() == 30.0f);
        }

        SECTION("Deposit < 0 should throw exception") {
            lab1::ATM atm = lab1::ATM("i2zs45", 20.0f, 15.0f);
            REQUIRE_THROWS(atm.deposit(-20.0f));
        }
    }
}