#ifndef LOGGER_H
#define LOGGER_H

#include <string>

//----------------------------------------------------------------------------------------------------------------------
/// @file Logger.h
/// @brief Base Class for Logging
/// @author Erika Camilleri
/// @version 1.0
/// ----------------------------------------------------------------------------------------------------------------------
class Logger
{
  public:
    static void log(const std::string &_logMessage);
    static Logger* instance();
    static Logger* s_instance;
    static std::string s_filename;
  protected:
    Logger() {}
};

#endif
