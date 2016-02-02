#include <qaib/app/ObjectClassManager.hpp>

#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>


namespace qaib {

    ObjectClassManager* ObjectClassManager::instance = nullptr;

    ObjectClassManager& ObjectClassManager::getInstance() {
        if (instance == nullptr) instance = new ObjectClassManager();
        return *instance;
    }

    void ObjectClassManager::findClasses() {
        using namespace boost::filesystem;

        recursive_directory_iterator it(path("data/")), end;

        while (it != end) {

            if (boost::filesystem::is_regular_file(it->path())) {

                auto ext = it->path().extension();

                if (ext.compare(".yaml") == 0) {
                    try {
                        loadClass(it->path().generic_string());
                    } catch (Exception e) {
                        std::cout << e.prettyMessage() << '\n';
                    }
                }
            }

            it++;
        }
    }

    void ObjectClassManager::loadClass(std::string configPath) {
        auto def = YAML::LoadFile(configPath);

        if (def.IsSequence()) {
            for (auto node : def) {
                loadClass(node);
            }
        } else if (def.IsMap()) {
            loadClass(def);
        }

    }

    void ObjectClassManager::loadClass(const YAML::Node& def) {
        auto typeNode = def["type"];

        std::string type = typeNode.as<std::string>("");

        if (type.compare("static") == 0) {
            staticObjectClasses.push_back(std::make_shared<StaticObjectClass>(def));
        }
    }

    std::shared_ptr<StaticObjectClass> ObjectClassManager::getRandomStaticObjectClass() {
        auto classesCount = staticObjectClasses.size();
        if (classesCount == 0) {
            return nullptr;
        } else {
            return staticObjectClasses[rand() % classesCount];
        }
    }
}