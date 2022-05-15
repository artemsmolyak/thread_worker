
#include <iostream>

#include "iworker_task.h"

class LoggerTask: public IWorkerTask {
private:
    std::string message_;
    
public:
    LoggerTask(const std::string& message):message_(message){}
    
    WorkerTaskResult exec(){
        std::cout <<"logger: " << message_ << "\n";
        return WorkerTaskResult::success;
    }
    
    ~LoggerTask() = default;
};
