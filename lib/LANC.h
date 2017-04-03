#ifndef BMPCC_RC_LANC
#define BMPCC_RC_LANC

void lanc_setup(int output_pin, int input_pin);


void lanc_rec();

void lanc_focus_auto();
void lanc_focus_far();
void lanc_focus_near();

void lanc_iris_inc();
void lanc_iris_dec();
void lanc_iris_auto();

#endif
