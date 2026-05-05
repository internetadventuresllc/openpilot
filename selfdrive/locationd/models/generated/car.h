#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_938834332157931826);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8544464575860631527);
void car_H_mod_fun(double *state, double *out_1480121198143705304);
void car_f_fun(double *state, double dt, double *out_7898233353593675752);
void car_F_fun(double *state, double dt, double *out_3958551827706560982);
void car_h_25(double *state, double *unused, double *out_6602979619609835016);
void car_H_25(double *state, double *unused, double *out_5003101848133196981);
void car_h_24(double *state, double *unused, double *out_4795734073702553051);
void car_H_24(double *state, double *unused, double *out_7228809632112065543);
void car_h_30(double *state, double *unused, double *out_7982080977671214948);
void car_H_30(double *state, double *unused, double *out_6526951884084737880);
void car_h_26(double *state, double *unused, double *out_5859252412299898954);
void car_H_26(double *state, double *unused, double *out_1261598529259140757);
void car_h_27(double *state, double *unused, double *out_5659469766708172581);
void car_H_27(double *state, double *unused, double *out_2698999589189532000);
void car_h_29(double *state, double *unused, double *out_2980407710010369303);
void car_H_29(double *state, double *unused, double *out_5383994245304349095);
void car_h_28(double *state, double *unused, double *out_2622683715263839896);
void car_H_28(double *state, double *unused, double *out_7347624516869675346);
void car_h_31(double *state, double *unused, double *out_1054059082969734867);
void car_H_31(double *state, double *unused, double *out_5033747810010157409);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}