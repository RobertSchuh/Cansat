bool test_freefall() {
  static bool acc_drop = false;
  static unsigned long acc_drop_timestamp;
  static float acc_drop_height;

  if (!acc_drop && reading_acc_filtered < DROP_CRIT_ACC) {
    acc_drop = true;
    acc_drop_timestamp = millis();
    acc_drop_height = reading_height_filtered;
  }
  
  if (acc_drop && millis() - acc_drop_timestamp > DROP_TEST_DURATION) {
    if (acc_drop_height - reading_height_filtered > DROP_CRIT_HEIGHT) {
      // acc_drop = false; // uncomment to enable more than one drop detection per flight
      return  true;
    } else {
      acc_drop = false;
      return false;
    }
  }
  
  return false;
}

bool test_chutefall() {
  static unsigned long drop_timestamp = millis();

  if (millis() - drop_timestamp > CHUTE_CRIT_TIME || reading_height_filtered < CHUTE_CRIT_HEIGHT) {
    return true;
  }
  
  return false;
}

bool test_landed() {
  static float window_max_height;
  static float window_min_height;
  static int window_count = 0;

  if (window_count == 0) {
    window_max_height = reading_height_filtered;
    window_min_height = reading_height_filtered;
  } else {
    window_max_height = (reading_height_filtered > window_max_height)? reading_height_filtered : window_max_height;
    window_min_height = (reading_height_filtered < window_min_height)? reading_height_filtered : window_min_height;    
  }

  window_count++;

  if (window_count >= LANDED_TEST_WINDOW) {
    window_count = 0;
    return (window_max_height - window_min_height < LANDED_HEIGHT_VARIATION);
  } else {
    return false;
  }
}
