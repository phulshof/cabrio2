//
// Main configuration class (singleton).
//
#ifndef CABRIO_CONFIG_HPP_
#define CABRIO_CONFIG_HPP_

class Config {
  public:
    static Config& get_instance() {
      static Config instance;
      return instance;
    }
  private:
    Config() {};
    Config(Config const&);
    void operator=(Config const&);
};

#endif
