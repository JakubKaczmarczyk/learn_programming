#include "tasks.h"

const Task* choose_more_important_task(const Task* t1, const Task* t2) {
    if (t1->priority > t2->priority) {
        return t1;
    }
    return t2;
}

const char* priority_as_str(Priority p) {
    switch (p) {
        case LOW:
            return "LOW";
            break;
        case MEDIUM:
            return "MEDIUM";
            break;
        case HIGH:
            return "HIGH";
            break;
        default:
            break;

    }
    return "";
}

void increase_priority(Priority* p) {
    ++(*p);
    if (*p > HIGH) {
        *p = HIGH;
    }
}

void transform_task(Task* t, void(* f)(Priority* p)) {
    f(&t->priority);
    f(&t->priority);
}
