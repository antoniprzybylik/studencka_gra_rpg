#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <fstream>

#include "player.h"
#include "question.h"
#include "enemy.h"


TEST_CASE("player tests", "[player]")
{

    Player player("Bob", 10, 1, 1);
    Enemy enemy("ork", 1, 1, 1);

    CHECK(player.get_name() == "Bob");
    CHECK(player.get_hp() == 10);
    CHECK(player.get_pos_x() == 1);
    CHECK(player.get_pos_y() == 1);

    SECTION("modifications of name only")
    {
        player.set_name("John");
        CHECK(player.get_name() == "John");
        CHECK(player.get_hp() == 10);
        CHECK(player.get_pos_x() == 1);
        CHECK(player.get_pos_y() == 1);
    }

    SECTION("modifications of health only")
    {
        player.set_hp(20);
        CHECK(player.get_name() == "Bob");
        CHECK(player.get_hp() == 20);
        CHECK(player.get_pos_x() == 1);
        CHECK(player.get_pos_y() == 1);
    }

    SECTION("modifications of pos_x and pos_y")
    {
        player.set_pos_x(20);
        player.set_pos_y(40);
        CHECK(player.get_name() == "Bob");
        CHECK(player.get_hp() == 10);
        CHECK(player.get_pos_x() == 20);
        CHECK(player.get_pos_y() == 40);
    }

    SECTION("is alive")
    {
        CHECK(player.is_alive() == true);
        player.set_hp(0);
        CHECK(player.is_alive() == false);
    }

    SECTION("checking range")
    {
        CHECK(player.get_range(enemy) == 0);
    }

    SECTION("operator ==")
    {
        Player player1("Bob", 10, 1, 1);
        CHECK(player == player1);
    }

    SECTION("operator !=")
    {
        Player player1("Bobby", 1, 1, 1);
        CHECK(player != player1);
    }

    SECTION("read from file")
    {
        Json::Reader reader;
        Json::Value root;
	std::ifstream ifs;

	ifs.open("output_player.json");
	REQUIRE(reader.parse(ifs, root));

	Player player1(root);
	ifs.close();

        CHECK(player1.get_name() == "Zoja");
        CHECK(player1.get_hp() == 100);
        CHECK(player1.get_pos_x() == 1);
        CHECK(player1.get_pos_y() == 1);
    }
}


TEST_CASE("question tests", "[question]")
{
    Question question1(L"Ile to 2+2?", L"4", L"3", 1);
    Question question2(L"Ile to 2+3?", L"5", L"2", 2);

    CHECK(question1.get_content() == L"Ile to 2+2?");
    CHECK(question1.get_good_answer() == L"4");
    CHECK(question1.get_wrong_answer() == L"3");
    CHECK(question1.get_id() == 1);

    SECTION("modifications")
    {
        question1.set_content(L"Ile to 3+3?");
        question1.set_good_answer(L"6");
        question1.set_wrong_answer(L"2");
        question1.set_id(5);

        CHECK(question1.get_content() == L"Ile to 3+3?");
        CHECK(question1.get_good_answer() == L"6");
        CHECK(question1.get_wrong_answer() == L"2");
        CHECK(question1.get_id() == 5);
    }

    SECTION("modifications")
    {
        question1.set_content(L"Ile to 3+8?");
        question1.set_good_answer(L"11");
        question1.set_wrong_answer(L"3");
        question1.set_id(9);

        CHECK(question1.get_content() == L"Ile to 3+8?");
        CHECK(question1.get_good_answer() == L"11");
        CHECK(question1.get_wrong_answer() == L"3");
        CHECK(question1.get_id() == 9);
    }

    SECTION("operator ==")
    {
        Question question3(L"Ile to 2+2?", L"4", L"3", 1);
        CHECK(question3 == question1);
    }

    SECTION("operator !=")
    {
        Question question4(L"Ile to 2+2?", L"4", L"3", 9);
        CHECK(question1 != question2);
        CHECK(question1 != question4);
        CHECK(question2 != question4);
    }
}


TEST_CASE("enemy tests", "[enemy]")
{
    Player player("Bob", 10, 1, 1);
    Enemy enemy("ork", 1, 1, 1);
    Question question1(L"Ile to 2+2?", L"4", L"3", 1);
    Question question2(L"Ile to 2+3?", L"5", L"2", 2);

    CHECK(enemy.get_name() == "ork");
    CHECK(enemy.get_attack_damage() == 1);
    CHECK(enemy.get_pos_x() == 1);
    CHECK(enemy.get_pos_y() == 1);
    CHECK(enemy.is_done() == false);

    SECTION("modifications")
    {
        enemy.set_name("troll");
        enemy.set_attack_damage(6);
        enemy.set_pos_x(2);
        enemy.set_pos_y(2);
        enemy.set_done(true);
        CHECK(enemy.get_name() == "troll");
        CHECK(enemy.get_attack_damage() == 6);
        CHECK(enemy.get_pos_x() == 2);
        CHECK(enemy.get_pos_y() == 2);
        CHECK(enemy.is_done() == true);
    }

    SECTION("modifications 2")
    {
        enemy.set_name("jozek");
        enemy.set_attack_damage(1);
        enemy.set_pos_x(4);
        enemy.set_pos_y(6);
        enemy.set_done(false);
        CHECK(enemy.get_name() == "jozek");
        CHECK(enemy.get_attack_damage() == 1);
        CHECK(enemy.get_pos_x() == 4);
        CHECK(enemy.get_pos_y() == 6);
        CHECK(enemy.is_done() == false);
    }

    SECTION("modifications 3")
    {
        enemy.set_name("bully");
        enemy.set_attack_damage(5);
        enemy.set_pos_x(2);
        enemy.set_pos_y(1);
        enemy.set_done(true);
        CHECK(enemy.get_name() == "bully");
        CHECK(enemy.get_attack_damage() == 5);
        CHECK(enemy.get_pos_x() == 2);
        CHECK(enemy.get_pos_y() == 1);
        CHECK(enemy.is_done() == true);
    }

    SECTION("attack player")
    {
        CHECK(player.get_hp() == 10);
        enemy.attack(player);
        CHECK(player.get_hp() == 9);
    }

    SECTION("attack player")
    {
        CHECK(player.get_hp() == 10);
        enemy.attack(player);
        enemy.attack(player);
        enemy.attack(player);
        CHECK(player.get_hp() == 7);
    }

    SECTION("operator ==")
    {
        Enemy enemy1("ork", 2, 1, 1);
        CHECK(enemy == enemy1);
    }

    SECTION("operator !=")
    {
        Enemy enemy1("orc", 2, 1, 5);
        CHECK(enemy != enemy1);
    }

    SECTION("load from file")
    {
        Json::Reader reader;
        Json::Value root;
	std::ifstream ifs;

	ifs.open("output_enemy.json");
	REQUIRE(reader.parse(ifs, root));

	Enemy enemy1(root);
	ifs.close();

        CHECK(enemy1.get_name() == "ork");
        CHECK(enemy1.get_attack_damage() == 1);
        CHECK(enemy1.get_pos_x() == 2);
        CHECK(enemy1.get_pos_y() == 3);
        CHECK(enemy1.is_done() == 0);
    }

    SECTION("setting inventory")
    {
        enemy.set_questions(question1);
        CHECK(enemy.is_in_questions(1) == true);
        enemy.set_questions(question2);
        CHECK(enemy.is_in_questions(2) == true);
        CHECK(enemy.is_in_questions(5) == false);
    }

    SECTION("setting inventory")
    {
        enemy.set_questions(question1);
        CHECK(enemy.is_in_questions(2) == false);
    }

    SECTION("get question")
    {
        enemy.set_questions(question1);
        CHECK(enemy.get_question(1) == question1);
    }

    SECTION("get from i")
    {
        enemy.set_questions(question1);
        enemy.set_questions(question2);
        CHECK(enemy.get_content_fromid(0) == L"Ile to 2+2?");
        CHECK(enemy.get_ganswer_fromid(0) == L"4");
        CHECK(enemy.get_wanswer_fromid(0) == L"3");

        CHECK(enemy.get_content_fromid(1) == L"Ile to 2+3?");
        CHECK(enemy.get_ganswer_fromid(1) == L"5");
        CHECK(enemy.get_wanswer_fromid(1) == L"2");
    }


    SECTION("removing from questions, checking size")
    {
        enemy.set_questions(question1);
        enemy.set_questions(question2);
        CHECK(enemy.number_of_elements() == 2);
        enemy.remove_question(question1);
        enemy.remove_question(question2);
        CHECK(enemy.number_of_elements() == 0);
    }
}


TEST_CASE("player class exceptions", "[player]")
{
    Player player("Bob", 60, 1, 1);
    Enemy enemy("ork", 1, 1, 1);

    SECTION("setters exceptions")
    {
        CHECK_THROWS(player.set_pos_x(-2));
        CHECK_THROWS(player.set_pos_y(-7));
        CHECK_THROWS(player.set_pos_x(-10));
        CHECK_THROWS(player.set_pos_y(-5));
    }
}


TEST_CASE("question class exceptions", "[question]")
{
    Question question1(L"Ile to 2+2?", L"4", L"3", 1);

    SECTION("read from not existing file")
    {
        CHECK_THROWS(question1.read_from_file(L"output111.txt"));
    }
}


TEST_CASE("enemy class exceptions", "[enemy]")
{
    Enemy enemy("ork", 1, 1, 1);
    Player player("Bob", 1, 1, 1);
    Question question1(L"Ile to 2+2?", L"4", L"3", 1);
    Question question2(L"Ile to 2+5?", L"7", L"3", 4);

    SECTION("setters exceptions")
    {
        CHECK_THROWS(enemy.set_attack_damage(-5));
        CHECK_THROWS(enemy.set_pos_x(-10));
        CHECK_THROWS(enemy.set_pos_y(-11));
        CHECK_THROWS(enemy.set_attack_damage(-10));
        CHECK_THROWS(enemy.set_pos_x(-1));
        CHECK_THROWS(enemy.set_pos_y(-1));
    }

    SECTION("player not alive")
    {
        enemy.attack(player);
        CHECK_THROWS(enemy.attack(player));
    }

    SECTION("questions errors")
    {
        enemy.set_questions(question1);
        CHECK_THROWS(enemy.get_question(2));
        CHECK_THROWS(enemy.get_content_fromid(-1));
        CHECK_THROWS(enemy.get_content_fromid(2));
        CHECK_THROWS(enemy.get_ganswer_fromid(-1));
        CHECK_THROWS(enemy.get_ganswer_fromid(2));
        CHECK_THROWS(enemy.get_wanswer_fromid(-1));
        CHECK_THROWS(enemy.get_wanswer_fromid(2));
        CHECK_THROWS(enemy.remove_question(question2));
    }
}

