
#include "api/TaskService.h"
#include "api/TaskServiceCreator.h"

int main() {
   TaskService ts = todo_list::createService();

   return 0;
}
