# Profiling

## Description
Profiling is a powerful tool for developers who want to assess the performances of an application. It is useful when performance issues are encountered as well. It is even more useful if the profiling tool can manage different parts of an application at the same time in a very convenient way.

However, performances can themselves be lowered by the profiling tool. It is so mandatory to disable the profiler in the released versions of an application.

## Terminology
| Word           | Definition                                                                          |
|----------------|-------------------------------------------------------------------------------------|
| Debug mode     | Compilation configuration decreasing performances and adding infos for developers   |
| Developer      | User of the profiling tool to create new applications                               |
| Main loop      | Repetition of the code that makes an application be running until it is closed      |
| Profiler       | Tool to measure the time a task (part of) takes to be executed                      |
| Profiled task  | Task (part of) for which the execution time is measured                             |
| Release mode   | Compilation configuration in which the execution time is minimized by the compiler  |

## Objectives
The profiler can manage several profiled tasks. Each task is identified by a name.

A task may be split in different subparts, so the profiler must be able to aggregate all the execution times of these subparts and merge them as a single time:
* The profiler is first initialized before the main loop of the application.
* The developer registers the different profiled tasks by giving their name. The developer can then surround the profiled part of code with a function to start the profiling of the task, another one to stop the profiling.
* At the end of the main loop, the profiler is flushed.
* From this moment, the execution time of each profiled tasks can be grabbed from the profiler, until the next end of the main loop.
* When the application is closing, the profiler is closed too.

When the application is compiled using a release configuration, the profiler is not effective. There is no CPU overhead because of calling the profiler functions.

## Limitations
The profiler is only available for the debug configuration.

The execution time is measured in milliseconds.
