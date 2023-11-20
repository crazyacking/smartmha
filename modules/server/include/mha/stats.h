#include <chrono>
#include <cstdint>

namespace model {
struct ServerStats {
    uint64_t Uptimes;
};
} // namespace model

class Server {
  public:
    model::ServerStats getStats() const {
        auto now  = std::chrono::steady_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - begin);
        return {static_cast<uint64_t>(diff.count())};
    }

  private:
    std::chrono::time_point<std::chrono::steady_clock> begin = std::chrono::steady_clock::now();
};