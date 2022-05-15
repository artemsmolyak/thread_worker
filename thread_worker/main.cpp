  
#include <iostream>
#include <string>

#include "thread_worker.h"
#include "worker_task.h"

int main(int argc, const char * argv[]) {
    
    ThreadWorker thread1("thread1");
    thread1.setLogger([](const std::string& message){
        std::cout << message << "\n";
    });
    thread1.start();
    
    
    ThreadWorker thread2("thread2");
    thread2.setLogger([](const std::string& message){
        std::cout << message << "\n";
    });
    thread2.start();
    
    
    while(true){
        auto task = std::make_shared<WorkerTask>();
        thread1.setTask(task);
        thread2.setTask(task);
        sleep(1);
    }
   
    return 0;
}
