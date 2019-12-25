#pragma once

namespace Audio {

enum class Clip {
  STARTUP,
  BEGIN_SCAN,
  TARGET_ACQUIRED,
  CONTACT_LOST,
  CONTACT_RESTORED,
  TARGET_LOST,
  PICKED_UP,
};

void init();
void play(Clip);
void tick();

}  // namespace Audio
