#pragma once

#include <exception>

class UnableToSend : public std::exception
{
};

class UnableToRead : public std::exception
{
};
