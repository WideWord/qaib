//
//  Disposable.cpp
//  qaib
//
//  Created by Kirill Vilkov on 14.11.15.
//
//

#include <qaib/util/Disposable.h>

namespace qaib {
    
    DisposableBag::~DisposableBag() {
        for(auto disposable : disposableList) {
            disposable->dispose();
            delete disposable;
        }
    }
    
    Disposable::~Disposable() {}

    
}