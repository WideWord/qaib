#pragma once

#include <functional>
#include <list>
#include <algorithm>
#include <memory>

namespace qaib {
    
    class EventHandler {
        
    };
    
    
    template<typename ... Args> class Event {
    private:
        
        struct Callback {
            std::function<void(Args...)> fn;
            std::weak_ptr<EventHandler> handler;
        };
        
        std::list<Callback> callbacks;
    public:
        
        inline void subscribe(std::weak_ptr<EventHandler> handler, std::function<void(Args...)> fn) {
            Event::Callback callback;
            callback.fn = fn;
            callback.handler = handler;
            
            callbacks.push_back(callback);
        }
        
        inline void unsubscribe(std::weak_ptr<EventHandler> handler) {
            for (auto it = callbacks.begin(); it != callbacks.end; ++it) {
                if (it->handler == handler) {
                    callbacks.erase(it);
                    return;
                }
            }
        }
        
        inline void fire(Args ... args) {
            for (auto& cb : callbacks) {
                if (!cb.handler.expired()) {
                    cb.fn(args...);
                }
            }
        }
    };
    
}