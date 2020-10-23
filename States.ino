void set_state(State newState) {
  state = newState;
  
  switch (newState) {
    case INITIALIZATION:
      set_LED(   0,  0,  0); break; //OFF
    case CLIMBING:
      set_LED(  0, 255,  0); break; //GREEN
    case FREEFALL:
      set_LED(255,  0, 255); break; //PURPLE
    case CHUTEFALL:
      // deploy landing grear here
      set_LED(0,  255, 255); break; //BLUEGREEN
    case LANDED:
      set_LED(  0,  0, 255); break; //BLUE
    case FAIL:
      while (1) {
        set_LED(255, 0, 0); delay(100); //RED
        set_LED(  0, 0, 0); delay(100);
      }
  }
}
