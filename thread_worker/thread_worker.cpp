
#include "thread_worker.h"


void ThreadWorker::run(){
   logMessage("thread start");
   
   while( !quitFlag_ ){
       std::shared_ptr<IWorkerTask> task = nullptr;
       
       {
           std::unique_lock<std::mutex> lck( mutex_ );
           condition_.wait( lck, [&]{ return !taskQueue_.empty() || quitFlag_.load(); } );
           
           if ( quitFlag_ ){
               break;
           }
           
           task = taskQueue_.front();
           taskQueue_.pop();
       }
       
       
       switch ( task->exec() ){
           case WorkerTaskResult::failed:
           {
               logMessage("task failed");
           }
               break;
           case WorkerTaskResult::success:
           {
               logMessage("task success");
           }
               break;
       }
   }
   
   logMessage("thread has finished");
}


void ThreadWorker::setLogger(std::function<void(const std::string&)> loger){
   loger_ = loger;
}

void ThreadWorker::logMessage(const std::string& message){
   if (!loger_)
       return;
   
   try{
       loger_(workerName_ + ": " + message);
   }
   catch(const std::exception& er){
       std::cerr << "[ERROR] " << er.what() << "\n";
   }
}



ThreadWorker::ThreadWorker( const std::string& workerName ):
quitFlag_( false ),
workerName_(workerName){}


ThreadWorker::~ThreadWorker(){
   if (!quitFlag_)
       stop();
   
   logMessage("stop");
}


void ThreadWorker::start(){
   thread_ = std::thread( &ThreadWorker::run, this );
}

void ThreadWorker::setTask( std::shared_ptr<IWorkerTask> task ){
   {
       std::unique_lock<std::mutex> lck( mutex_ );
       taskQueue_.push( task );
   }
   condition_.notify_one();
   logMessage("set new task");
}

void ThreadWorker::stop(){
   quitFlag_ = true;
   condition_.notify_one();
   
   if ( thread_.joinable() ){
       thread_.join();
   }
}

void ThreadWorker::clearTasks(){
   while( !taskQueue_.empty() ){
       auto task = taskQueue_.front();
       taskQueue_.pop();
   }
}

