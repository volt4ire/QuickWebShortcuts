add_definitions(-DTRANSLATION_DOMAIN=\"plasma_runner_org.kde.quickwebshortcuts\")

set(quickwebshortcuts_SRCS quick_web_shortcuts.h quick_web_shortcuts.cpp Config.h)

add_library(krunner_quickwebshortcuts MODULE ${quickwebshortcuts_SRCS})
target_link_libraries(krunner_quickwebshortcuts KF5::Runner)

#The icons have not been modified, sources:
#https://www.iconfinder.com/icons/1220346/overflow_stachoverflow_stack_stackoverflow_icon
#https://www.iconfinder.com/icons/317714/video_youtube_icon
#https://www.iconfinder.com/icons/1217121/bing_icon
#https://www.iconfinder.com/icons/298822/github_mark_icon
#https://www.iconfinder.com/icons/1313555/business_duckduckgo_engine_internet_optimization_search_web_icon
#https://www.iconfinder.com/icons/1298745/google_icon

install(TARGETS krunner_quickwebshortcuts DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-runner-quickwebshortcuts.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
install(FILES icons/bing.svg icons/duckduckgo.svg icons/github.svg icons/google.svg icons/stackoverflow.svg icons/youtube.svg DESTINATION /usr/share/icons/)
