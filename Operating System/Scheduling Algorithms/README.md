# Scheduling Algorithms
* ## First Come First Serve(FCFS)
    * Jobs are executed on first come, first serve basis.
    * Easy to understand and implement.
    * Its implementation is based on FIFO queue.
    * Poor in performance as average wait time is high.

* ## Shortest Job First(SJF)
    * This is a non-preemptive, pre-emptive scheduling algorithm.
    * Best approach to minimize waiting time.

* ## Priority
    * Each process is assigned a priority. Process with highest priority is to be executed first and so on.
    * Processes with same priority are executed on first come first served basis.
    * Priority can be decided based on memory requirements, time requirements or any other resource requirement

* ## Round Robin
    * Round Robin is the preemptive process scheduling algorithm.
    * Each process is provided a fix time to execute, it is called a quantum.
    * Once a process is executed for a given time period, it is preempted and other process executes for a given time period.
    * Context switching is used to save states of preempted processes
