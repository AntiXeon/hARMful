# Logging system specifications

## Description
The logging system is used to inform both developers and final users of possible issues while an application is running.

Logs can be written in two different types of outputs:
- Temporary logs to a console. They will disappear as soon as the application is closed;
- Durable logs in one or several files. They are available until the files are erased.

A logging system provides several informations on the application status. It can write outputs on different levels:
- a debug information (for developers only);
- a general information to follow the sequence of actions that the user has made;
- a warning when an unexpected behavior is detected but not affecting the execution of the application;
- an error if the application is in a bad state and its execution must be deliberately stopped before a fatal error occurs;
- a critical error if an unexpected behavior blocks the application, makes it data being incorrect or leads to a crash.

## Terminology
| Word           | Definition                                                                          |
|----------------|-------------------------------------------------------------------------------------|
| Console        | Combination of a terminal and a shell to input commands and output results or texts |
| Developer      | User of the logging system to create new applications                               |
| File           | Aggregated and persisting data saved on a mass storage as a hard disk drive.        |
| Final user     | User of the application(s) created by the developer                                 |
| Log            | Message about the current status of an application                                  |
| Log level      | Degree of importance of a message                                                   |
| Thread         | Task that can be concurrently executed to another task in the same application      |

## Objectives
The logging system must provide both console and file outputs. The developer can select which output to use: console, file or both.

Moreover, the developer can select the level of the lowest status to output. Lower levels will be ignored without being printed. Console and file outputs have independent levels of outputs so that it is possible to print more logs on console than in files, for example.
The selection of the level is applied at the creation of the logging system and can be changed while the application is running. The logging system can only be initialized once.

No file is created when the logging system is initialized. It is created only if a log is outputted into a file.
The outputs must be thread-safe as they can be used in a multithreaded application.

Each information is written on a new line, with the date and time when it was produced as follows:
`[AAAA-MM-DD hh:mm:ss] Log information details.`

## Limitations
Many log systems output colors in the console messages. This is not a requirement at the moment, all the output message types will be displayed with the default color of the used console.

File logs are not written in color and are only formatted as ASCII files.
