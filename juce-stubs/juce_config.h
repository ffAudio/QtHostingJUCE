
#pragma once

#define JUCE_CUSTOM_VST3_SDK   0
#define JUCE_PLUGINHOST_VST    0
#define JUCE_PLUGINHOST_VST3   1
#define JUCE_PLUGINHOST_AU     1
#define JUCE_PLUGINHOST_LADSPA 0

#define JUCE_WEB_BROWSER 0

#define JUCE_MODULE_AVAILABLE_juce_audio_basics     1
#define JUCE_MODULE_AVAILABLE_juce_audio_devices    1
#define JUCE_MODULE_AVAILABLE_juce_audio_formats    1
#define JUCE_MODULE_AVAILABLE_juce_audio_processors 1
#define JUCE_MODULE_AVAILABLE_juce_core             1
#define JUCE_MODULE_AVAILABLE_juce_data_structures  1
#define JUCE_MODULE_AVAILABLE_juce_dsp              1
#define JUCE_MODULE_AVAILABLE_juce_events           1
#define JUCE_MODULE_AVAILABLE_juce_graphics         1
#define JUCE_MODULE_AVAILABLE_juce_gui_basics       1
#define JUCE_MODULE_AVAILABLE_juce_gui_extras       1

// these silences some warnings in juce when not using their toolchain
#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED 1
#define JUCE_STANDALONE_APPLICATION          0

#define JUCE_DISPLAY_SPLASH_SCREEN           0
