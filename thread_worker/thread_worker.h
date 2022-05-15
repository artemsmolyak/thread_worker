
#ifndef threadWorker_hpp
#define threadWorker_hpp

#include <queue>
#include <thread>
#include <mutex> 

#include <exception>
#include <iostream>

#include "iworker_task.h"

// ThreadWorker performs IWorkerTask
class ThreadWorker
{
private:
  std::function<void(const std::string&)> loger_;
  const std::string workerName_;
  
  std::thread thread_;
  
  void logMessage(const std::string& message);
  
protected:
  std::atomic<bool> quitFlag_;
  std::mutex mutex_;
  std::condition_variable condition_;
  std::queue< std::shared_ptr<IWorkerTask> > taskQueue_;

  virtual void threadWorker();
  
public:
  
  ThreadWorker( const std::string& workerName );
  ~ThreadWorker();
  
  void setLogger(std::function<void(const std::string&)>);
  
  void start();
  void setTask( std::shared_ptr<IWorkerTask> task );
  void stop();
  void clearTasks();
};
#endif /* threadWorker_hpp */
