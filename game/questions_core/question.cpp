#include <iostream>
#include <math.h>
#include "enemy.h"
#include "player.h"
#include "question.h"
#include "class_exceptions.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <locale>
#include <codecvt>

Question::Question(std::wstring new_content, std::wstring new_good_answer, std::wstring new_wrong_answer, int new_id)
{
    set_content(new_content);
    set_good_answer(new_good_answer);
    set_wrong_answer(new_wrong_answer);
    set_id(new_id);
}

std::wstring Question::get_content() const
{
    return content;
}

std::wstring Question::get_good_answer() const
{
    return good_answer;
}

std::wstring Question::get_wrong_answer() const
{
    return wrong_answer;
}

int Question::get_id() const
{
    return id;
}


void Question::set_content(std::wstring new_content)
{
    content = new_content;
}

void Question::set_good_answer(std::wstring new_good_answer)
{
    good_answer = new_good_answer;
}

void Question::set_wrong_answer(std::wstring new_wrong_answer)
{
    wrong_answer = new_wrong_answer;
}

void Question::set_id(int new_id)
{
    id = new_id;
}

std::ostream& operator<<(std::ostream& stream, const Question& question)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    stream << converter.to_bytes(question.get_content())
	   << "? Answear one: " << converter.to_bytes(question.get_good_answer())
	   << ". Answear two: " << converter.to_bytes(question.get_wrong_answer())
	   << std::endl;
    return stream;
}

bool Question::operator==(const Question& question) const
{
    return id == question.id;
}

bool Question::operator!=(const Question& question) const
{
    return !(*this == question);
}

void Question::save_to_file(Question& question, std::wstring path)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wofstream file;

    file.open(converter.to_bytes(path), std::ios::out | std::ios::app);
    if (!file)
    {
        throw WrongPath(path);
    }
    file << question.get_content()
	 << " " << question.get_good_answer()
	 << " " << question.get_wrong_answer()
	 << " " << question.get_id()
	 << std::endl;
    file.close();
}

std::vector<Question> Question::read_from_file(std::wstring path)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wifstream file;

    file.open(converter.to_bytes(path));

    if (!file)
    {
        throw WrongPath(path);
    }
    std::vector<Question> questions;
    Question temp(L" ", L" ", L" ",0);
    while (file>>temp.content>>temp.good_answer>>temp.wrong_answer>>temp.id)
    {
        questions.push_back(temp);
    }
    return questions;
}
