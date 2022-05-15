
#ifndef Task_hpp
#define Task_hpp

#include "iworker_task.h"
 
#include <unistd.h> // sleep

class WorkerTask : public IWorkerTask {
    
public:
    WorkerTaskResult exec(){
        sleep(1);
        return WorkerTaskResult::success;
    }
    
    ~WorkerTask() = default;
};

#endif /* Task_hpp */

