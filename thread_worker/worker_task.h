
#ifndef Task_hpp
#define Task_hpp

#include "iworker_task.h" 

class WorkerTask : public IWorkerTask {
private:
    std::function<bool()> task_;
public:
    
    WorkerTask(std::function<bool()> task): task_(task){}
    
    WorkerTaskResult exec(){
        if ( task_() )
            return WorkerTaskResult::success;
        else
            return WorkerTaskResult::failed;
    }
    
    ~WorkerTask() = default;
};

#endif /* Task_hpp */

