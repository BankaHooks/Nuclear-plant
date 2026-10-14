#ifndef RODS_CONTROL_H
#define RODS_CONTROL_H

void rods_render(double rod_position);
int rods_choose(void);
int restart_choosen_rods(int choosen_rods[3][2]);
int rods_control();

extern double rods_data[5][4];


#endif
