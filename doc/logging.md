
## Logging Rules

https://wiki.opendaylight.org/view/BestPractices/Logging_Best_Practices
https://jessehu.wordpress.com/2009/11/17/log4j-levels-all-trace-debug-info-warn-error-fatal-off/

- ERROR : error events that might still allow the application to continue running
    + might attempt recovery
    + might forcefully terminate
    + uncorrectable (or correctable) internal state inconsistency, or request-level error
    + primarily for system operators
- WARNING : potentially harmful situations
    + clearly-defined recovery strategy
    + primarily for operators and administrators
- INFO : informational messages that highlight the progress of the application at coarse-grained level
    + API-like contract (info and higher)
    + major state changes within software (init, operating, shutdown, shutdown, termination)
- DEBUG : fine-grained informational events that are most useful to debug an application
    + coarse diagnostic
    + interface contract with support entities
    + general programming concepts
    + indicate internal state transitions
- TRACE : finer-grained informational events than the DEBUG
    + internal state transitions in full detail
- FATAL : very severe error events that will presumably lead the application to abort