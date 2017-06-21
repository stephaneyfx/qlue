add_library(qlue
    app.cpp
    app.h
    config.h
    qlue.h
    helpers/string.hpp
)
recmkConfigureTarget(qlue)
target_link_libraries(qlue PUBLIC clue::clue
    PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick Qt5::QuickControls2
)
recmkInstallTarget(qlue)
install(DIRECTORY . DESTINATION include/${PROJECT_NAME} FILES_MATCHING
    PATTERN *.h PATTERN *.hpp)
