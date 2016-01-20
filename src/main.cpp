
#include "info.h"
#include "rex/rex.h"

#include <cxxopts.hpp>

#define ELPP_NO_DEFAULT_LOG_FILE
#define ELPP_THREAD_SAFE
#include <easylogging++.h>
INITIALIZE_EASYLOGGINGPP

#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <memory>
using std::unique_ptr;
using std::make_unique;
#include <algorithm>


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    //
    // Setup command line argument parsing
    //
    cxxopts::Options options(argv[0], " - need to change this.");
    options.add_options()
        // Custom CL agruments
        ("help",                "Display this help message.")
        ("version",             "Print the program version.")
        ("version-triplet",     "Print the undecorated program version.")
        ("appid",               "Print the unique application identifier.");
    options.add_options("Logging")
        // CL arguments for EasyLogging++
        ("log-info",            "Toggle \"INFO\" messages (defaults to off).")
        ("log-warning",         "Toggle \"WARNING\" messages (defaults to on).")
        ("log-error",           "Toggle \"ERROR\" messages (defaults to on).")
        ("log-fatal",           "Toggle \"FATAL\" messages (defaults to on).")
        ("log-debug",           "Toggle \"DEBUG\" messages (defaults to off).")
        ("log-trace",           "Toggle \"TRACE\" messages (defaults to off).")
        ("log-all",             "Turn all messages on.")
        ("log-off",             "Turn all messages off.")
        ("log-file",            "Set the log filename.", cxxopts::value<string>(), "FILE");

    //
    // Parse command line arguments
    //
    try {
        options.parse(argc, argv);
    } catch (const cxxopts::OptionException& e) {
        std::cout << "Error parsing options: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    //
    // Print the help message
    // - no other arguments will be checked and the program will terminate
    //
    if (options.count("help")) {
        std::cout << options.help({"", "Logging"}) << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    //
    // Print the version message
    // - no other arguments will be checked and the program will terminate
    //
    else if (options.count("version")) {
        std::cout << VERSION_MESSAGE << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    //
    // Print the version-triplet message
    // - no other arguments will be checked and the program will terminate
    //
    else if (options.count("version-triplet")) {
        std::cout << VERSION_TRIPLET_MESSAGE << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    //
    // Print the application identifier message
    // - no other arguments will be checked and the program will terminate
    //
    else if (options.count("appid"))
    {
        std::cout << APPLICATION_IDENTIFIER << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    //
    // The remaining options to not terminate the program
    //
    else {

        //
        // Set the EasyLogging++ CL agruments
        //
        auto argcELPP = 1;
        vector<string> argvELPP_strs = {argv[0]};

        if (options.count("log-file")) {
            ++argcELPP;
            argvELPP_strs.push_back("--default-log-file=" + options["log-file"].as<string>());
        }

        // Convert vector of strings into appropriate format
        // - vec<str> -> vec<uptr<ch[]>> -> vec<ch*> (data)
        vector<unique_ptr<char[]>> argvELPP_chrs;
        vector<char*> argvELPP;
        for (const auto& argStr : argvELPP_strs) {
            argvELPP_chrs.push_back(make_unique<char[]>(argStr.length()+1));
            std::copy(argStr.begin(), argStr.end(), argvELPP_chrs.back().get());
            argvELPP_chrs.back().get()[argStr.length()] = '\0';
            argvELPP.push_back(argvELPP_chrs.back().get());
        }
        START_EASYLOGGINGPP(argcELPP, argvELPP.data());

        //
        // Configure the logger
        //
        using CT = el::ConfigurationType;
        using LVL = el::Level;
        el::Configurations logConfig;
        logConfig.setToDefault();
        string T = "true", F = "false";

        // Set the "global" logger parameters
        logConfig.setGlobally(CT::ToFile, options.count("log-file") ? T : F);
        logConfig.setGlobally(CT::ToStandardOutput, T);
        logConfig.setGlobally(CT::MillisecondsWidth, string("3"));
        logConfig.setGlobally(CT::PerformanceTracking, T);
        logConfig.setGlobally(CT::MaxLogFileSize, string("0"));
        logConfig.setGlobally(CT::LogFlushThreshold, string("0"));

        // Adjust the logging format
        const string dtFormat = "%datetime{%H:%m:%s}";
        const string logFormat = dtFormat + string(" %level : [%func] [%fbase:%line] %msg");
        logConfig.setGlobally(CT::Format, dtFormat + string(" %level : %msg"));
        logConfig.set(LVL::Debug, CT::Format, logFormat);
        logConfig.set(LVL::Trace, CT::Format, logFormat);

        // Enable requested log events
        if (options.count("log-all")) {
            logConfig.setGlobally(CT::Enabled, string("true"));
        } else if (options.count("log-off")) {
            logConfig.setGlobally(CT::Enabled, string("false"));
        } else {
            logConfig.set(LVL::Info, CT::Enabled, options.count("log-info") ? T : F);
            logConfig.set(LVL::Warning, CT::Enabled, options.count("log-warning") ? F : T);
            logConfig.set(LVL::Error, CT::Enabled, options.count("log-error") ? F : T);
            logConfig.set(LVL::Fatal, CT::Enabled, options.count("log-fatal") ? F : T);
            logConfig.set(LVL::Debug, CT::Enabled, options.count("log-debug") ? T : F);
            logConfig.set(LVL::Trace, CT::Enabled, options.count("log-trace") ? T : F);
        }

        // Set logger flags
        el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
        el::Loggers::reconfigureLogger("default", logConfig);
    }

    // Message about leftover arguments
    if (argc > 1) {
        LOG(WARNING) << "Some command line arguments were ignored:";
        for (auto i = 1u; static_cast<int>(i) < argc; ++i) {
            LOG(WARNING) << "  \"" << argv[i] << "\"";
        }
    }


    return EXIT_SUCCESS;
}





