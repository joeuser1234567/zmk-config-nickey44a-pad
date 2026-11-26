#include <zephyr/devicetree.h>
#include <zephyr/settings/settings.h>

#include <zmk/ble.h>
#include <zmk/event_manager.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/keymap.h>

#define WINDOWS_LAYER DT_NODELABEL(windows_default)

#if DT_NODE_EXISTS(WINDOWS_LAYER)
static int sync_profile_layer(void) {
    if (zmk_ble_active_profile_index() == 1) {
        return zmk_keymap_layer_activate(DT_NODE_CHILD_IDX(WINDOWS_LAYER));
    }

    return zmk_keymap_layer_deactivate(DT_NODE_CHILD_IDX(WINDOWS_LAYER));
}

static int profile_layer_listener(const zmk_event_t *event) {
    ARG_UNUSED(event);
    sync_profile_layer();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(profile_layer, profile_layer_listener);
ZMK_SUBSCRIPTION(profile_layer, zmk_ble_active_profile_changed);

#if IS_ENABLED(CONFIG_SETTINGS)
/* The saved Bluetooth profile is available after the settings load. */
SETTINGS_STATIC_HANDLER_DEFINE(profile_layer, "nickey44a/profile_layer", NULL, NULL,
                               sync_profile_layer, NULL);
#endif
#endif
