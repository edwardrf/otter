#ifndef OTTER_BGC_
#define OTTER_BGC_

void bgc_setup(int pin);

void bgc_horizontal_freeze();
void bgc_vertical_freeze();
void bgc_right();
void bgc_left();
void bgc_down();
void bgc_up();
void bgc_mode_follow();
void bgc_mode_no_follow();


#endif // OTTER_BGC_
