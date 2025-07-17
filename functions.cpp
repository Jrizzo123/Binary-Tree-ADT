#include "functions.h"

int random_range(int min, int max) {
    return (std::rand() % (max - min + 1)) +min;
}
