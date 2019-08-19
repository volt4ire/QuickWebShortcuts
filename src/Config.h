#ifndef QUICKWEBSHORTCUTS_CONFIG_H
#define QUICKWEBSHORTCUTS_CONFIG_H

#include <QtCore/QString>

class Config {
public:
    /**
    Bing=https://www.bing.com/search?q=
    DuckDuckGo=https://duckduckgo.com/?q=
    Github=https://github.com/search?q=
    Google=https://www.google.com/search?q=
    Stackoverflow=https://stackoverflow.com/search?q=
    Youtube=https://www.youtube.com/results?search_query=
     */
    const QString searchEngine = "Google";
    const QString searchEngineURL = "https://www.google.com/search?q=";
    const QString icon = "/usr/share/icons/google.svg";
    const QString browser = "firefox";
    const QString privateBrowser = "firefox --private-window";

// All = 2, Only from this plugin = 1, Do not clear = 1 or undefined
#define clear_history 2
#define open_urls
#undef show_search_engine_name
};


#endif //QUICKWEBSHORTCUTS_CONFIG_H
