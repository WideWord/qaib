#pragma once

namespace qaib {

    class Damagable {
    public:
        virtual void applyDamage(float damage) = 0;
    };

}