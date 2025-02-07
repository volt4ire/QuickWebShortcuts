# QuickWebShortcuts

This plugin allows you to use search engines inside Krunner. But instead of specifying the search
engine every time can set one you want to use. Additionally it provides search suggestions and direct 
links. These can be configured in the config dialog, by default they are disabled.

The default search engine is Google. If you type ":example query" it will open your 
browser with the google search results for "example query". The default options are Bing, DuckDuckGo,
Github, Google, Stackoverflow and Youtube and you can add custom ones.

Additionally you can use this plugin to open search results in private/incognito mode. 
This feature gets activated by typing "::example query".
It has been tested with Firefox, Chromium, Google Chrome and Epiphany.
But you have to manually select one of these as your default browser, otherwise Firefox is used as default.

This project also has a minimal branch, which is smaller and more efficient but it has no config dialog.
Because of that the settings have to be configured in the src/Config.h file. After changing the settings you have to recompile the project.   
The master branch (default) is recommended for most users.

### Build Instructions

Required Dependencies on Debian/Ubuntu:  
`sudo apt install cmake extra-cmake-modules build-essential libkf5runner-dev libkf5textwidgets-dev qtdeclarative5-dev gettext libnotify-bin`

openSUSE  
`sudo zypper install cmake extra-cmake-modules libQt5Widgets5 libQt5Core5 libqt5-qtlocation-devel ki18n-devel ktextwidgets-devel
 kservice-devel krunner-devel gettext-tools libnotify-tools`  

Fedora  
`sudo dnf install cmake extra-cmake-modules kf5-ki18n-devel kf5-kservice-devel kf5-krunner-devel kf5-ktextwidgets-devel gettext libnotify`  


The easiest way to install is:  
`curl https://raw.githubusercontent.com/alex1701c/QuickWebShortcuts/master/install.sh | bash`

Or you can do it manually:

```
git clone https://github.com/alex1701c/QuickWebShortcuts.git  
cd QuickWebShortcuts/
mkdir build
cd build
cmake -DQT_PLUGIN_INSTALL_DIR=`kf5-config --qt-plugins` ..
make
sudo make install
kquitapp5 krunner 2> /dev/null; kstart5 --windowclass krunner krunner > /dev/null 2>&1 &
```

## Screenshots

#### Simple search  
![Simple search](https://raw.githubusercontent.com/alex1701c/Screenshots/master/QuickWebShortcuts/simple_search.png)

#### Search in private window  
![Search in private window](https://raw.githubusercontent.com/alex1701c/Screenshots/master/QuickWebShortcuts/private_window_search.png)

#### Search suggestions  
![Search suggestions](https://raw.githubusercontent.com/alex1701c/Screenshots/master/QuickWebShortcuts/search_suggestions_demo.png)

#### Direct links
![Direct links demo](https://raw.githubusercontent.com/alex1701c/Screenshots/master/QuickWebShortcuts/direct_links_demo.png)

## Configuration

#### Configure search engines
In this section of the config dialog you can configure the search engines.  
You can add a custom search engine or you can customize the existing ones. For instance you can change the
icon by clicking on the button with the current icon.  
With the "Defaults" button of the config dialog (not in image) the changes to the original search engines can be undone.  
With the next three checkboxes the text in the Krunner matches is configured:  
The first option adds the name of the search engine to the match text, for instance "Search Google for test".  
The second appends " in private window" / " in incognito window", for instance "::test" would show up as "Search for test in private window"
(if Firefox is your default browser).  
The last one prepends "Search for" to the text. If you just want the query and optionally the private/incognito
mode note to be shown this option can be unchecked.  
![Configure search engines](https://raw.githubusercontent.com/alex1701c/Screenshots/master/QuickWebShortcuts/config_dialog_search_engines_section.png)

#### Configure suggestions
In this section you can configure the suggestions. By default these are turned of.
Both the Google and Bing suggestions provide search suggestions by using an API.  
The DuckDuckGo option provides direct links to the websites. These links are crawled from the lite edition of the 
DuckDuckGo website, because of that this option is not as fast as the others. Unfortunately there is no API from DuckDuckGo available.  
Additionally you can enable suggestions for private/incognito searches.  
To protect your privacy you can configure a proxy. This configuration can be tested by clicking the "Test Proxy Configuration"
button. For this the plugin is sending a request to https://ifconfig.me/ip.  
Note: If your internet connection is very slow and you have search suggestions configured 
the plugin shows sometimes no matches, in this case yu can just add
a space to the query so that the match method is called again.  
![Configure search suggestions](https://raw.githubusercontent.com/alex1701c/Screenshots/master/QuickWebShortcuts/config_dialog_search_suggestions_section.png)

#### Configure history clearing  
This plugin can remove entries form the Krunner history. If the "Clear only Quick Web Shortcuts" option is used, entries that
start with ":" will be removed. Entries for the normal web shortcuts (for example "dd:test") will additionally be removed with the first option.  
![Configure history clearing](https://raw.githubusercontent.com/alex1701c/Screenshots/master/QuickWebShortcuts/config_dialog_clear_history_section.png)
