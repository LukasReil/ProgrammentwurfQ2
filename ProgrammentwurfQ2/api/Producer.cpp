#include "Producer.h"

using namespace std;

Producer::Producer(string id)
{
    this->id = id;
}

string Producer::getId()
{
    return id;
}