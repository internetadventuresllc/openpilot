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
void car_err_fun(double *nom_x, double *delta_x, double *out_5180017016346976199);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8487031610083345537);
void car_H_mod_fun(double *state, double *out_5706437107101781759);
void car_f_fun(double *state, double dt, double *out_1153822413136816832);
void car_F_fun(double *state, double dt, double *out_8315107788488877245);
void car_h_25(double *state, double *unused, double *out_6700023275112118041);
void car_H_25(double *state, double *unused, double *out_3547118740695532620);
void car_h_24(double *state, double *unused, double *out_3324231918695756867);
void car_H_24(double *state, double *unused, double *out_5772826524674401182);
void car_h_30(double *state, double *unused, double *out_5158892872121138412);
void car_H_30(double *state, double *unused, double *out_7982934991522402241);
void car_h_26(double *state, double *unused, double *out_1843869831671927367);
void car_H_26(double *state, double *unused, double *out_194384578178523604);
void car_h_27(double *state, double *unused, double *out_6520813582762108628);
void car_H_27(double *state, double *unused, double *out_8289045770386724464);
void car_h_29(double *state, double *unused, double *out_2883364054508086278);
void car_H_29(double *state, double *unused, double *out_7472703647208010057);
void car_h_28(double *state, double *unused, double *out_1678630012218245207);
void car_H_28(double *state, double *unused, double *out_5891641409432010985);
void car_h_31(double *state, double *unused, double *out_3062573746858095691);
void car_H_31(double *state, double *unused, double *out_3577764702572493048);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}