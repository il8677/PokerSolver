#include "PostFlop.hpp"

bool IsRaise(Action action) {
    switch (action) {
    case RAISE_HALF:
    case RAISE_1:
    case RAISE_15:
        return true;
    default:
        return false;
    }
}

bool IsEndOfBetting(const History& history) {
    if (IsRaise(history.back()))
        return false;
    if (history.back() == CALL)
        return true;

    return history.size() == 2;
}
