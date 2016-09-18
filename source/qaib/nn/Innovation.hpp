#pragma once

namespace qaib {

    using Innovation = int;

    class InnovationGenerator {
    private:
        Innovation nextInnovation = 0;
    public:
        inline Innovation generate() {
            return nextInnovation++;
        }
    };

}