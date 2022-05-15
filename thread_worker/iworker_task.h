
#ifndef iworker_task_h
#define iworker_task_h

enum class WorkerTaskResult
{
 success,
 failed
};


class IWorkerTask
{
public:
   virtual WorkerTaskResult exec() = 0;
   virtual ~IWorkerTask() = default;
};

#endif /* iworker_task_h */
