
#ifndef _LOGGING_HEADER_
#define _LOGGING_HEADER_


#ifdef TESTING

    #ifdef DEBUGGING

        #include <iostream>
        #define INFO(MSG)    std::cout << "INFO    : " << MSG << std::endl;
        #define WARNING(MSG) std::cout << "WARNING : " << MSG << std::endl;
        #define ERROR(MSG)   std::cout << "ERROR   : " << MSG << std::endl;
        #define FATAL(MSG)   std::cout << "FATAL   : " << MSG << std::endl;
        #define DEBUG(MSG)   std::cout << "DEBUG   : " << MSG << std::endl;
        #define TRACE(MSG)   std::cout << "TRACE   : " << MSG << std::endl;

    #else

        #define INFO(MSG)
        #define WARNING(MSG)
        #define ERROR(MSG)
        #define FATAL(MSG)
        #define DEBUG(MSG)
        #define TRACE(MSG)

    #endif

#else

    #include <easylogging++.h>
    #define INFO(MSG)    LOG(INFO)    << MSG;
    #define WARNING(MSG) LOG(WARNING) << MSG;
    #define ERROR(MSG)   LOG(ERROR)   << MSG;
    #define FATAL(MSG)   LOG(FATAL)   << MSG;
    #define DEBUG(MSG)   LOG(DEBUG)   << MSG;
    #define TRACE(MSG)   LOG(TRACE)   << MSG;

#endif

#endif