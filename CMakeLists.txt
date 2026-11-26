# Bundled until the standalone touch-inertia module is published and SHA-pinned.
add_subdirectory(modules/zmk-input-processor-touch-inertia)
add_subdirectory(modules/zmk-input-processor-touch-swipe)

if(CONFIG_SHIELD_NICKEY44A_R AND CONFIG_ZMK_BLE)
  target_sources(app PRIVATE src/bt_profile_layers.c)
endif()
