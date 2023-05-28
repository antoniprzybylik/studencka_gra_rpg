#include "class_exceptions.h"

NegativeArgument::NegativeArgument(int value):
    std::invalid_argument("Negative value: " + std::to_string(value)){}

WrongPath::WrongPath(std::string path):
    std::invalid_argument("This path does not exist: " + path){}

AlreadyDead::AlreadyDead(int health):
    std::invalid_argument("Player already has negative health: " + std::to_string(health)){}

WrongId::WrongId(int id):
    std::invalid_argument("No question with this id: " + std::to_string(id)){}

OutOfRange::OutOfRange(int index):
    std::invalid_argument("Index out of range: " + std::to_string(index)){}

AlreadyExists::AlreadyExists(int id):
    std::invalid_argument("Question with this index already exists: " + std::to_string(id)){}

DoNotExist::DoNotExist(int id):
    std::invalid_argument("Question with this index do not exist: " + std::to_string(id)){}