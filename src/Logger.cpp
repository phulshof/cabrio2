//
// Logging class (singleton).
//
#include "Logger.hpp"

#include <iostream>
using namespace std;

log_level_t Logger::level() {
  return _level;
}

void Logger::level(log_level_t l) {
  if (l >= LOG_ERROR && l <= LOG_DEBUG) {
    _level = l;
  }
}

void Logger::log(log_level_t l, std::string message) {
  if ( l <= _level ) {
    cout << level_str(l) << ": " << message << endl;
  }
}

std::string Logger::level_str(log_level_t l) {
  switch (l) {
    case LOG_ERROR:
      return "ERROR";;
    case LOG_WARNING:
      return "WARNING";;
    case LOG_INFO:
      return "INFO";;
    case LOG_DEBUG:
      return "DEBUG";;
    default:
      return "Unknown";;
  }
}
