#ifndef QUESTION_H
#define QUESTION_H
#include <iostream>
#include <vector>

// Class that represents questions - their content, a good and bad answer
class Question
{
    private:

        std::string content;
        std::string good_answer;
        std::string wrong_answer;
        int id;

    public:

        Question(std::string, std::string, std::string, int);

        std::string get_content() const;
        std::string get_good_answer() const;
        std::string get_wrong_answer() const;
        int get_id() const;

        void set_content(std::string new_content);
        void set_good_answer(std::string new_good_answer);
        void set_wrong_answer(std::string new_wrong_answer);
        void set_id(int new_id);

        friend std::ostream& operator<<(std::ostream& stream, const Question& question);
        bool operator==(const Question& question) const;
        bool operator!=(const Question& question) const;

        void save_to_file(Question& question, std::string path);
        std::vector<Question> read_from_file(std::string path);
};

std::ostream& operator<<(std::ostream& stream, const Question& question);
#endif