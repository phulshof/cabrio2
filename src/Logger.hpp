//
// Logging class (singleton).
//
#ifndef CABRIO_LOGGER_HPP_
#define CABRIO_LOGGER_HPP_

#include <string>

typedef enum {
  LOG_ERROR,
  LOG_WARNING,
  LOG_INFO,
  LOG_DEBUG
} log_level_t;

class Logger {
  public:
    static Logger& get_instance() {
      static Logger instance;
      return instance;
    }

    log_level_t level();
    void level(log_level_t l);
    void log(log_level_t l, std::string message);
    std::string level_str(log_level_t l);

  private:
    Logger() { _level = LOG_ERROR; };
    Logger(Logger const&);
    void operator=(Logger const&);

    log_level_t _level;
};

#endif
