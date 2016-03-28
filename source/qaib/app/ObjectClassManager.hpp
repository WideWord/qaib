#include <qaib/util/Exception.hpp>
#include <qaib/game/StaticObject.hpp>

#include <yaml-cpp/yaml.h>
#include <vector>

namespace qaib {

    class ObjectClassManager {
    private:
        std::vector<StaticObjectClass> staticObjectClasses;

    public:
        void findClasses();
        void loadClass(std::string configPath);
        void loadClass(const YAML::Node& def);

        StaticObjectClass* getRandomStaticObjectClass();
        StaticObjectClass* getStaticObjectClassWithName(std::string name);
    };

    qaibExceptionDecl(ObjectClassLoadingFailed, "Object class loading failed: ", Exception);


}