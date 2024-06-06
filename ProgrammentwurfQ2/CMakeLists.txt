# CMakeList.txt: CMake-Projekt für "ProgrammentwurfQ2". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (ProgrammentwurfQ2 "ProgrammentwurfQ2.cpp"       "apiWrapper/CustomDispatcher.h" "apiWrapper/CustomDispatcher.cpp" "Sensors/Sensor.h" "Sensors/Sensor.cpp" "Sensors/OutsideTemperatureSensor.h" "Sensors/OutsideTemperatureSensor.cpp" "Sensors/InsideTemperatureSensor.cpp" "Sensors/InsideTemperatureSensor.h" "Sensors/SunIntensitySensor.h" "Sensors/SunIntensitySensor.cpp"   "TemperatureMonitor/TemperatureMonitor.h" "TemperatureMonitor/TemperatureMonitor.cpp" "api/Consumer.cpp" "api/Consumer.h" "api/Dispatcher.cpp" "api/Dispatcher.h" "api/Producer.cpp" "api/Producer.h"  "api/Umwelt.cpp"  "api/Umwelt.h" "Sensors/SensorMeasureThread.cpp" "Sensors/SensorMeasureThread.h" "multithreading/CustomThread.h" "multithreading/CustomThread.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ProgrammentwurfQ2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
