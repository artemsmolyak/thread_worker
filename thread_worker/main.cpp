  
#include <iostream>
#include <string>

#include "thread_worker.h"
#include "worker_task.h"
#include "logger_task.h"

int main(int argc, const char * argv[]) {
    
    ThreadWorker loggerThread("loger");
    loggerThread.start();
    
    
    ThreadWorker thread1("thread1");
    thread1.setLogger([&loggerThread](const std::string& message){
        auto loggerTask = std::make_shared<LoggerTask>(message);
        loggerThread.setTask(loggerTask);
    });
    thread1.start();
    
    
    ThreadWorker thread2("thread2");
    thread2.setLogger([](const std::string& message){
        std::cout << "console: " << message << "\n";
    });
    thread2.start();
    
    
    
    ThreadWorker thread3("thread3");
    thread3.setLogger([](const std::string& message){
        std::cout << "console: " << message << "\n";
    });
    thread3.start();
    
    
    
    while(true){
        auto task1 = std::make_shared<WorkerTask>([](){
            sleep(1);
            return true;
        });
        
        thread1.setTask(task1);
        
        auto task2 = std::make_shared<WorkerTask>([](){
            sleep(2);
            return false;
        });
        
        thread2.setTask(task2);
        thread3.setTask(task2);
        
        sleep(1);
    }
   
    return 0;
}
