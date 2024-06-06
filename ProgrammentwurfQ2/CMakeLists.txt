# CMakeList.txt: CMake-Projekt für "ProgrammentwurfQ2". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (ProgrammentwurfQ2 "ProgrammentwurfQ2.cpp" "ProgrammentwurfQ2.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ProgrammentwurfQ2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
