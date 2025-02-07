#include <QMap>

#ifndef QUICKWEBSHORTCUTS_SEARCHENGINES_H
#define QUICKWEBSHORTCUTS_SEARCHENGINES_H


#include <QtCore/QString>
#include <QMap>
#include <KSharedConfig>
#include <QtWidgets/QComboBox>
#include "SearchEngine.h"

class SearchEngines {

public:
    static QMap<QString, QString> getDefaultSearchEngines() {
        QMap<QString, QString> engines;
        engines.insert("Google", "https://www.google.com/search?q=");
        engines.insert("DuckDuckGo", "https://duckduckgo.com/?q=");
        engines.insert("Stackoverflow", "https://stackoverflow.com/search?q=");
        engines.insert("Bing", "https://www.bing.com/search?q=");
        engines.insert("Github", "https://github.com/search?q=");
        engines.insert("Youtube", "https://www.youtube.com/results?search_query=");
        return engines;
    }
    static QList<QString> getDefaultSearchEngineNames() {
        return {"Google", "DuckDuckGo", "Stackoverflow", "Bing", "Github", "Youtube"};
    }

    static QMap<QString, QString> getIconNames() {
        return {
                {"Bing",          "/usr/share/icons/bing.svg"},
                {"Google",        "/usr/share/icons/google.svg"},
                {"DuckDuckGo",    "/usr/share/icons/duckduckgo.svg"},
                {"Stackoverflow", "/usr/share/icons/stackoverflow.svg"},
                {"Github",        "/usr/share/icons/github.svg"},
                {"Youtube",       "/usr/share/icons/youtube.svg"},
        };
    }

    static QList<SearchEngine> getAllSearchEngines() {
        QList<SearchEngine> searchEngines;
        auto rootConfig = KSharedConfig::openConfig("krunnerrc")->group("Runners").group("QuickWebShortcuts");
        auto defaultEngines = getDefaultSearchEngines();
        auto iconNames = getIconNames();
        for (const auto &groupName:rootConfig.groupList().filter(QRegExp("^SearchEngine-"))) {
            auto config = rootConfig.group(groupName);
            SearchEngine engine;
            engine.name = config.readEntry("name");
            engine.url = config.readEntry("url");
            engine.icon = config.readEntry("icon");
            if (engine.icon.isEmpty()) engine.icon = config.readEntry("original_icon");
            if (engine.icon.isEmpty()) engine.icon = "globe";
            engine.qIcon = engine.icon.startsWith("/") ? QIcon(engine.icon) : QIcon::fromTheme(engine.icon);
            if (!config.readEntry("original_name").isEmpty()) {
                engine.originalName = config.readEntry("original_name");
                engine.originalURL = defaultEngines.value(engine.originalName);
                engine.originalIcon = iconNames.value(engine.originalName);
                engine.isDefaultBased = true;
                defaultEngines.remove(engine.originalName);
            }
            searchEngines.append(engine);
        }
        for (const auto &item : defaultEngines.toStdMap()) {
            SearchEngine engine;
            engine.name = item.first;
            engine.url = item.second;
            engine.icon = iconNames.value(item.first);
            engine.qIcon = engine.icon.startsWith("/") ? QIcon(engine.icon) : QIcon::fromTheme(engine.icon);
            engine.isDefault = true;
            engine.isDefaultBased = true;
            searchEngines.append(engine);
        }
        return searchEngines;
    }


};

#endif //QUICKWEBSHORTCUTS_SEARCHENGINES_H
