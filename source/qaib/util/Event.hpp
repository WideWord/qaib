#pragma once

#include <functional>
#include <list>
#include <algorithm>

namespace qaib {
        
    template<typename ... Args> class Event {
    private:
        
        struct Callback {
            std::function<void(Args...)> fn;
            void* handler;
        };
        
        std::list<Callback> callbacks;
    public:
        
        inline void subscribe(void* handler, std::function<void(Args...)> fn) {
            Event::Callback callback;
            callback.fn = fn;
            callback.handler = handler;
            
            callbacks.push_back(callback);
        }
        
        inline void unsubscribe(void* handler) {
            for (auto it = callbacks.begin(); it != callbacks.end; ++it) {
                if (it->handler == handler) {
                    callbacks.erase(it);
                    return;
                }
            }
        }
        
        inline void fire(Args ... args) {
            for (auto& cb : callbacks) {
                cb.fn(args...);
            }
        }
    };
    
}