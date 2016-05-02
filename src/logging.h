
#ifndef _LOGGING_HEADER_
#define _LOGGING_HEADER_


#ifdef TESTING

    #ifdef DEBUGGING

        #include <iostream>
        #define LOG_INFO(MSG)    std::cout << "INFO    : " << MSG << std::endl;
        #define LOG_WARNING(MSG) std::cout << "WARNING : " << MSG << std::endl;
        #define LOG_ERROR(MSG)   std::cout << "ERROR   : " << MSG << std::endl;
        #define LOG_FATAL(MSG)   std::cout << "FATAL   : " << MSG << std::endl;
        #define LOG_DEBUG(MSG)   std::cout << "DEBUG   : " << MSG << std::endl;
        #define LOG_TRACE(MSG)   std::cout << "TRACE   : " << MSG << std::endl;

    #else

        #define LOG_INFO(MSG)
        #define LOG_WARNING(MSG)
        #define LOG_ERROR(MSG)
        #define LOG_FATAL(MSG)
        #define LOG_DEBUG(MSG)
        #define LOG_TRACE(MSG)

    #endif

#else

    #include <easylogging++.h>
    #define LOG_INFO(MSG)    LOG(INFO)    << MSG;
    #define LOG_WARNING(MSG) LOG(WARNING) << MSG;
    #define LOG_ERROR(MSG)   LOG(ERROR)   << MSG;
    #define LOG_FATAL(MSG)   LOG(FATAL)   << MSG;
    #define LOG_DEBUG(MSG)   LOG(DEBUG)   << MSG;
    #define LOG_TRACE(MSG)   LOG(TRACE)   << MSG;

#endif



#endif
