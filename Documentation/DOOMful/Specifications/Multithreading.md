# Multithreading

## Description
Nowadays, computers have multicore CPUs that can efficiently run several tasks at the same time. It is then more and more interesting to use their power to create quicker applications. In some other cases, different tasks may have to be run at the same time to perform operations as playing sounds and rendering a CGI scene simultaneously.

Thus, adding the support of multithreading to an application is really a useful feature. Most of the programming language provide a way to create threads. Some of them manage these threads in order to easily handle them in some situations.
Yet, C++ does not.

The current feature provides a thread manager. The aim of this manager is to let developers use several threads in their applications with a convenient way to handle them: start, pause, stop, etc.

## Terminology
| Word           | Definition                                                                          |
|----------------|-------------------------------------------------------------------------------------|
| Developer      | User of the **hARMful** API to create new applications                              |
| Join a thread  | Wait until the end of the execution of a thread                                     |
| Loop           | Fixed or indeterminate amount of repetitions of a part of code                      |
| Thread         | Task that can be concurrently executed to another task in the same application      |

## Objectives
The thread manager is based on the threads of the standard library. This will allow an easier port to new operating systems and provide a more robust code.

When the thread manager creates a new thread, it returns the corresponding ID. This ID is then used to access the different features of the thread manager to handle the state of a wanted thread : start, stop, get the status of the thread. The features are explained in the following paragraphs.

The threads will be run, stopped or canceled from the thread manager. The way to stop the thread in a proper manner implies it is aknowledged that it must stop. So, a flag might be used in such situations in order to let the manager end the underlying thread. As all threads do not run a loop of indeterminate length, this flag is not mandatory.

Additionally, the thread manager provides utilities functions to let the developer know the state of the created threads (not started, running, joinable, stopped).

## Limitations
A thread can never end if it uses an infinite loop (`while(true)`, `for(;;)`). The current solution cannot be used to ensure the threads will be able to end in a proper manner. Moreover, asking to the manager to stop a thread can lead to an application freeze. This case is not handled, the developer is responsible for the code.
