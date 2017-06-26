# WCRT-Hard-real-time-tasks
A algorithm of calculating the worst-case response time of a task in hard real-time system


#introduction#
As the real-time computing industry moves away from static cyclic executive-based scheduling towards 
more flexible process-based scheduling, so it is important for current scheduling analysis techniques 
to advance and to address more realistic application areas.

One commonly proposed way of constructing a hard real-time system is to build the system from a number 
of sporadic and periodic tasks, each assigned static priorities, and dispatched at run-time according 
to the static priority pre-emptive scheduling algorithm.

The priority pre-emptive dispatching algorithm has been analysed by Joseph and Pandya to find the
worst-case response time of a given task. Analysis is derived that finds the worst-case time between a 
task being released (i.e. placed in a notional priority-ordered run-queue) and the task completing the 
execution of a worst-case required computation time. This permits task deadlines to be less than task 
periods: the worst-case response time can be compared to a static deadline.

Lehoczky describes qualitative analysis which can determine the worst-case response time of a given task 
with such arbitrary deadlines. Lehoczky points out that neither the rate monotonic nor deadline monotonic 
priority ordering policies are optimal for tasks with arbitrary deadlines. We will reproduce here an 
algorithm which finds the optimal priority ordering for any task set.

And I will realize the algorithm which Lehoczky has described.
