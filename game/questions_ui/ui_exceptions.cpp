#include "ui_exceptions.h"

LoadError::LoadError():
    std::invalid_argument("Data load error"){}

WrongIndex::WrongIndex(int index):
    std::invalid_argument("This index is out of range: " + std::to_string(index)){}