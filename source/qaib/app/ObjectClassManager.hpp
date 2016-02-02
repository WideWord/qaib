#include <qaib/util/Exception.hpp>
#include <qaib/game/StaticObject.hpp>

#include <yaml-cpp/yaml.h>
#include <vector>

namespace qaib {

    class ObjectClassManager {
    private:
        static ObjectClassManager* instance;
        std::vector<std::shared_ptr<StaticObjectClass>> staticObjectClasses;

    public:
        static ObjectClassManager& getInstance();

        void findClasses();
        void loadClass(std::string configPath);
        void loadClass(const YAML::Node& def);

        std::shared_ptr<StaticObjectClass> getRandomStaticObjectClass();
    };

    qaibExceptionDecl(ObjectClassLoadingFailed, "Object class loading failed: ", Exception);


}