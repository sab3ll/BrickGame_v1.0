#include "sandbox.h"

int main(void) {
  initOverlay();
  gameLoop();
  terminateOverlay();
  return 0;
}

void gameLoop() {
  srand(time(NULL));
  GameParams_t params;
  GameInfo_t info;
  Figure_t figure;
  params.info = &info;
  params.figure = &figure;
  bool break_flag = TRUE;
  double counter = 0.0;

  initParams(&params);
  updateParams(&params);
  while (break_flag) {
    if (counter >= 1.50 - params.info->speed * SPEED_RATE &&
        params.state == Game_proceeding) {
      updateCurrentState();
      counter = 0.0;
    }
    counter += TICK * 1E-3;
    int signal = GET_USER_INPUT;
    if (signal != -1)
      sigact(getSignal(signal), &params);
    else
      sigact(Up, &params);
    printOverlay(&params);
    if (params.state == Exit_state) break_flag = FALSE;
  }
  freeMemory(&params);
}
