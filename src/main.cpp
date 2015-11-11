
#include <iostream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <memory>
using std::unique_ptr;
using std::make_unique;
#include <algorithm>

#include "info.h"

#include <cxxopts.hpp>

#define _ELPP_THREAD_SAFE
#include <easylogging++.h>
INITIALIZE_EASYLOGGINGPP


// ------------------------------------------------------------------------
// Perform a case insensitive comparison between two strings
// ------------------------------------------------------------------------
bool caseInsensitiveCompare_pred(unsigned char a, unsigned char b) {
    return std::tolower(a) == std::tolower(b);
}

bool caseInsensitiveCompare(std::string const& a, std::string const& b) {
    if (a.length() == b.length()) {
        return std::equal(b.begin(), b.end(), a.begin(), caseInsensitiveCompare_pred);
    }
    else {
        return false;
    }
}

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
        ("v,verbose",           "Set verbosity level [0..9].", cxxopts::value<string>())
        ("vmodule",             "Set verbosity of a glob.", cxxopts::value<vector<string>>())
        ("logging-flags",       "Set logging flags (bitmask).", cxxopts::value<string>());

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
        // raptorlang -v 0 --vmodule main --vmodule test=3 --vmodule "test3*=8"
        // bin/raptorlang --logging-flags 3 Sets logging flag. In example i.e, 3, it sets logging flag to NewLineForContainer and AllowVerboseIfModuleNotSpecified. See logging flags section above for further details and values. See macros section to disable this function.
        std::cout << options.help({"", "Logging"}) << std::endl;

            // "  (    1) NewLineForContainer\n"
            // "  (    2) AllowVerboseIfModuleNotSpecified\n"
            // "  (    4) LogDetailedCrashReason\n"
            // "  (    8) DisableApplicationAbortOnFatalLog\n"
            // "  (   16) ImmediateFlush\n"
            // "  (   32) StrictLogFileSizeCheck\n"
            // "  (   64) ColoredTerminalOutput\n"
            // "  (  128) MultiLoggerSupport\n"
            // "  (  256) DisablePerformanceTrackingCheckpointComparison\n"
            // "  (  512) DisableVModules\n"
            // "  ( 1024) DisableVModulesExtensions\n"
            // "  ( 2048) HierarchicalLogging\n"
            // "  ( 4096) CreateLoggerAutomatically\n"
            // "  ( 8192) AutoSpacing\n"
            // "  (16384) FixedTimeFormat\n"
            //
            // information about verbosity level

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
        auto ELPP_argc = 1;
        vector<string> ELPP_argv_strings = {argv[0]};

        if (options.count("verbose")) {
            ++ELPP_argc;
            ELPP_argv_strings.push_back("--v=" + options["verbose"].as<string>());
        }

        if (options.count("vmodule"))
        {
            ++ELPP_argc;
            string smodules = "-vmodule=";
            auto& modules = options["vmodule"].as<vector<string>>();
            string sep = "";
            for (const auto& m : modules) {
                smodules += sep + m;
                sep = ",";
            }
            ELPP_argv_strings.push_back(smodules);
        }

        if (options.count("logging-flags")) {
            ++ELPP_argc;
            ELPP_argv_strings.push_back("--logging-flags=" + options["logging-flags"].as<string>());
        }

        // Convert vector of strings into appropriate format
        // - vec<str> -> vec<uptr<ch[]>> -> vec<ch*>
        vector<unique_ptr<char[]>> ELPP_argv_managed;
        vector<char*> ELPP_argv;
        for (const auto& arg_string : ELPP_argv_strings) {
            ELPP_argv_managed.push_back(make_unique<char[]>(arg_string.length()+1));
            std::copy(arg_string.begin(), arg_string.end(), ELPP_argv_managed.back().get());
            ELPP_argv_managed.back().get()[arg_string.length()] = '\0';
            ELPP_argv.push_back(ELPP_argv_managed.back().get());
        }

        START_EASYLOGGINGPP(ELPP_argc, ELPP_argv.data());

        el::Configurations logConfig;
        logConfig.setToDefault();

        logConfig.setGlobally(el::ConfigurationType::Enabled, string("true"));
        logConfig.setGlobally(el::ConfigurationType::ToFile, string("false"));
        logConfig.setGlobally(el::ConfigurationType::ToStandardOutput, string("true"));
        logConfig.setGlobally(el::ConfigurationType::MillisecondsWidth, string("3"));
        logConfig.setGlobally(el::ConfigurationType::PerformanceTracking, string("true"));
        logConfig.setGlobally(el::ConfigurationType::MaxLogFileSize, string("0"));
        logConfig.setGlobally(el::ConfigurationType::LogFlushThreshold, string("0"));
        logConfig.setGlobally(el::ConfigurationType::Format, string("%datetime %level : %msg"));

        // INFO, WARNING, ERROR, and FATAL are set to default by Level::Global
        logConfig.set(el::Level::Debug, el::ConfigurationType::Format, std::string("%datetime %level : [%func] [%loc] %msg"));
        logConfig.set(el::Level::Verbose, el::ConfigurationType::Format, std::string("%datetime %level-%vlevel : %msg"));
        logConfig.set(el::Level::Trace, el::ConfigurationType::Format, std::string("%datetime %level : [%func] [%loc] %msg"));

        el::Loggers::addFlag(LoggingFlag::ColoredTerminalOutput);

        el::Loggers::reconfigureLogger("default", logConfig);

        VLOG(0) << "Level : " << 0;
        VLOG(1) << "Level : " << 1;
        VLOG(2) << "Level : " << 2;
        VLOG(3) << "Level : " << 3;
        VLOG(4) << "Level : " << 4;
        VLOG(5) << "Level : " << 5;
        VLOG(6) << "Level : " << 6;
        VLOG(7) << "Level : " << 7;
        VLOG(8) << "Level : " << 8;
        VLOG(9) << "Level : " << 9;

        LOG(INFO) << "INFO";
        LOG(WARNING) << "WARNING";
        LOG(ERROR) << "ERROR";
        // LOG(FATAL) << "FATAL";
        LOG(DEBUG) << "DEBUG";
        LOG(TRACE) << "TRACE";

        VLOG(0) << "Logging parameters:";
        for (const auto& arg : ELPP_argv)
            VLOG(0) << "\t" << arg;
    }

    // message about leftover arguments

    return 0;
}





