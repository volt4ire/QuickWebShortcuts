### QuickWebShortcuts

This branch of the plugin contains a minified version.  
This branch does not have a graphical config dialog and settings have to be changes an the src/Config.h
file, after making changes you have to recompile your project.

By removing unnecessary dependencies and features the file size is significantly smaller
and less code has to be executed.  

# Build Instructions

Required Dependencies on Debian/Ubuntu:  
`sudo apt install cmake extra-cmake-modules build-essential libkf5runner-dev libkf5textwidgets-dev qtdeclarative5-dev gettext`

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
```
Restart krunner to load the runner (in a terminal type: `kquitapp5 krunner;kstart5 krunner` )

This plugin allows you to use search engines inside Krunner. But instead of specifying the search
engine every time can set one you want to use. The default is Google. If you type ":example query" it will open your 
browser with the google search results for "example query". 

Additionally you can use this plugin to open search results in private/incognito mode. 
This feature gets activated by typing "::example query".

## Screenshots

#### Simple search
![Simple search](https://raw.githubusercontent.com/alex1701c/Screenshots/master/QuickWebShortcuts/simple_search.png)

#### Search in private window
![Search in private window](https://raw.githubusercontent.com/alex1701c/Screenshots/master/QuickWebShortcuts/private_window_search.png)

