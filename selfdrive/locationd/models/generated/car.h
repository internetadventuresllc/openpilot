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
void car_err_fun(double *nom_x, double *delta_x, double *out_5490557007678757153);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8915261011539861709);
void car_H_mod_fun(double *state, double *out_1909303659468267564);
void car_f_fun(double *state, double dt, double *out_5619520264811798499);
void car_F_fun(double *state, double dt, double *out_4962809153804984575);
void car_h_25(double *state, double *unused, double *out_1588189202735586313);
void car_H_25(double *state, double *unused, double *out_5432284309457759241);
void car_h_24(double *state, double *unused, double *out_5086606811221189508);
void car_H_24(double *state, double *unused, double *out_7657992093436627803);
void car_h_30(double *state, double *unused, double *out_5182646023614764623);
void car_H_30(double *state, double *unused, double *out_6097769422760175620);
void car_h_26(double *state, double *unused, double *out_4467788585828789853);
void car_H_26(double *state, double *unused, double *out_6089138373568071145);
void car_h_27(double *state, double *unused, double *out_7503819956469448649);
void car_H_27(double *state, double *unused, double *out_8272532734560600531);
void car_h_29(double *state, double *unused, double *out_6865056532680937847);
void car_H_29(double *state, double *unused, double *out_5587538078445783436);
void car_h_28(double *state, double *unused, double *out_5064638629681387879);
void car_H_28(double *state, double *unused, double *out_7776806978194237606);
void car_h_31(double *state, double *unused, double *out_1359536787619898648);
void car_H_31(double *state, double *unused, double *out_5462930271334719669);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}