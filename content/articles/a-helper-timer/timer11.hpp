#include <chrono>

namespace runtime {
namespace ms {

template < typename Func, typename... Arg >
long long count( Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    func( args... );
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::milliseconds > (std::chrono::steady_clock::now() - start).count();
}

template < typename Func, typename... Arg >
long long countNtimes( auto times, Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    for ( auto i{0}; i<times; ++i ) {
        func(args...);
    }
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::milliseconds > (std::chrono::steady_clock::now() - start).count();
}

}

namespace ns {
    
template < typename Func, typename... Arg >
long long count( Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    func( args... );
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::nanoseconds > (std::chrono::steady_clock::now() - start).count();
}

template < typename Func, typename... Arg >
long long countNtimes( auto times, Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    for ( auto i{0}; i<times; ++i ) {
        func(args...);
    }
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::nanoseconds > (std::chrono::steady_clock::now() - start).count();
}

}

namespace s {

template < typename Func, typename... Arg >
long long count( Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    func( args... );
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::seconds > (std::chrono::steady_clock::now() - start).count();
}

template < typename Func, typename... Arg >
long long countNtimes( auto times, Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    for ( auto i{0}; i<times; ++i ) {
        func(args...);
    }
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::seconds > (std::chrono::steady_clock::now() - start).count();
}
}

}