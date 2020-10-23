void apply_filter() {
  if (first_reading_height) {
    reading_height_filtered = reading_height;
    first_reading_height = false;
  } else {
    reading_height_filtered = (FILTER_HEIGHT)*(reading_height_filtered) + (1 - FILTER_HEIGHT)*reading_height;
  }

  if (first_reading_acc) {
    reading_acc_filtered = reading_acc;
    first_reading_acc = false;
  } else {
    reading_acc_filtered = (FILTER_ACC)*(reading_acc_filtered) + (1 - FILTER_ACC)*(reading_acc);
  }
}
