#pragma once

#include <functional>
#include <list>
#include <algorithm>

#include <qaib/util/Disposable.h>

namespace qaib {
        
    template<typename ... Args> class Event {
    private:
        
        struct Callback {
            std::function<void(Args...)> fn;
            void* handler;
        };
        
        std::list<Callback> callbacks;
        
        DisposableBag disposableBag;
    public:
        
        inline void subscribe(void* handler, std::function<void(Args...)> fn) {
            Event::Callback callback;
            callback.fn = fn;
            callback.handler = handler;
            
            callbacks.push_back(callback);
        }
        
        inline void unsubscribe(void* handler) {
            for (auto it = callbacks.begin(); it != callbacks.end(); ++it) {
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
        
        
        
        class DisposableSubscribtion : public Disposable {
            struct DisposableSubscribtionToken {
                bool disposed;
                Event<Args...>* event;
                void* handler;
                
                ~DisposableSubscribtionToken() {
                    delete (char*)handler;
                }
            };
            std::shared_ptr<DisposableSubscribtionToken> token;
        public:
            DisposableSubscribtion(Event<Args...>* event, void* handler) {
                token = std::make_shared<DisposableSubscribtionToken>();
                token->event = event;
                token->handler = handler;
                token->disposed = false;
            }
            
            DisposableSubscribtion(const DisposableSubscribtion& other) {
                token = other.token;
            }
            
            virtual void dispose() override {
                if (!token->disposed) {
                    token->disposed = true;
                    token->event->unsubscribe(token->handler);
                }
            }
            virtual ~DisposableSubscribtion() {}
        };
        
        inline void subscribe(DisposableBag& disposableBag, std::function<void(Args...)> fn) {
            char* handler = new char[1];
            subscribe(handler, fn);
            auto disposable = new DisposableSubscribtion(this, handler);
            this->disposableBag.addDisposable(disposable);
            auto userDisposable = new DisposableSubscribtion(*disposable);
            disposableBag.addDisposable(userDisposable);
        }
    };
    
}