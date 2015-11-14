//
//  Disposable.h
//  qaib
//
//  Created by Kirill Vilkov on 14.11.15.
//
//

#pragma once

#include <vector>

namespace qaib {
    
    class Disposable;
    
    class DisposableBag {
    private:
        std::vector<Disposable*> disposableList;
    public:
        inline void addDisposable(Disposable* disposable) {
            disposableList.push_back(disposable);
        }
        
        ~DisposableBag();
    };
    
    class Disposable {
    public:
        virtual void dispose() = 0;
        virtual ~Disposable();
    };
    

}