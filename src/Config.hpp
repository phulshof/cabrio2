//
// Main configuration class (singleton).
//
class Config {
    public:
        static Config& getInstance() {
            static Config instance;
            return instance;
        }
    private:
        Config() {};
        Config(Config const&);
        void operator=(Config const&);
};

