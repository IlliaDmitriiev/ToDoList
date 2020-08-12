
#include "api/TaskService.h"
#include "api/Creator.h"

int main() {
    TaskService ts = Creator::createService();
    return 0;
}
