#ifndef QUESTION_H
#define QUESTION_H
#include <iostream>
#include <vector>

// Class that represents questions - their content, a good and bad answer
class Question
{
    private:

        std::wstring content;
        std::wstring good_answer;
        std::wstring wrong_answer;
        int id;

    public:

        Question(std::wstring, std::wstring, std::wstring, int);

        std::wstring get_content() const;
        std::wstring get_good_answer() const;
        std::wstring get_wrong_answer() const;
        int get_id() const;

        void set_content(std::wstring new_content);
        void set_good_answer(std::wstring new_good_answer);
        void set_wrong_answer(std::wstring new_wrong_answer);
        void set_id(int new_id);

        friend std::ostream& operator<<(std::ostream& stream, const Question& question);
        bool operator==(const Question& question) const;
        bool operator!=(const Question& question) const;

        void save_to_file(Question& question, std::wstring path);
        std::vector<Question> read_from_file(std::wstring path);
};

std::ostream& operator<<(std::ostream& stream, const Question& question);
#endif
