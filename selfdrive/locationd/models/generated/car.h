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
void car_err_fun(double *nom_x, double *delta_x, double *out_3990337682930970705);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8419919608354584943);
void car_H_mod_fun(double *state, double *out_2419989426863145812);
void car_f_fun(double *state, double dt, double *out_8386161078390113048);
void car_F_fun(double *state, double dt, double *out_3717913866807838179);
void car_h_25(double *state, double *unused, double *out_1684039001660190569);
void car_H_25(double *state, double *unused, double *out_2483702398321519028);
void car_h_24(double *state, double *unused, double *out_609872506711191044);
void car_H_24(double *state, double *unused, double *out_2087057093967659533);
void car_h_30(double *state, double *unused, double *out_8271866928136485732);
void car_H_30(double *state, double *unused, double *out_5002035356828767655);
void car_h_26(double *state, double *unused, double *out_3649680898680377418);
void car_H_26(double *state, double *unused, double *out_1257800920552537196);
void car_h_27(double *state, double *unused, double *out_6685712269321036214);
void car_H_27(double *state, double *unused, double *out_7225629428012710872);
void car_h_29(double *state, double *unused, double *out_5173203877912220239);
void car_H_29(double *state, double *unused, double *out_5512266701143159839);
void car_h_28(double *state, double *unused, double *out_1343845033435005651);
void car_H_28(double *state, double *unused, double *out_429867684073629265);
void car_h_31(double *state, double *unused, double *out_1953410526593831781);
void car_H_31(double *state, double *unused, double *out_1884009022785888672);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}