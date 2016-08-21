#include <utils/Logger.h>

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <ctime>

Logger* Logger::s_instance = nullptr;
std::string Logger::s_filename = "";

Logger* Logger::instance()
{
  if(s_instance == nullptr)
  {
    s_instance = new Logger;
    std::time_t result = std::time(nullptr);
    std::string timestamp = std::asctime(std::localtime(&result));
    Logger::s_filename = "debug_log/log_" + timestamp + ".txt";
  }
  return s_instance;
}

void Logger::log(const std::string &_logMessage)
{
  QString outputFilename = QString::fromUtf8(Logger::s_filename.c_str());
  QFile outputFile(outputFilename);
  outputFile.open(QIODevice::Append);
  if(outputFile.isOpen())
  {
    QTextStream outStream(&outputFile);
    outStream << QString::fromStdString(_logMessage);
  }
  outputFile.close();
}
