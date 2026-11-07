// Copyright 2026 patsys
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef VIA_ENABLE
#include "raw_hid.h"
#include "via.h"

/* Upstream buffer commands document a28-byte maximum but trust the packet's
 * size byte. Reject oversized requests before the actual VIA handler sees them.
 */
bool via_command_kb(uint8_t *data, uint8_t length) {
  if (length != 32)
    return true;
  switch (data[0]) {
  case id_dynamic_keymap_macro_get_buffer:
  case id_dynamic_keymap_macro_set_buffer:
  case id_dynamic_keymap_get_buffer:
  case id_dynamic_keymap_set_buffer:
    if (data[3] > 28) {
      data[0] = id_unhandled;
      raw_hid_send(data, length);
      return true;
    }
    break;
  }
  return false;
}
#endif
