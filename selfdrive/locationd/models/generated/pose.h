#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6370445090975775647);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1677323290782450214);
void pose_H_mod_fun(double *state, double *out_3468986617292713816);
void pose_f_fun(double *state, double dt, double *out_5742408842642162042);
void pose_F_fun(double *state, double dt, double *out_9145761553590380035);
void pose_h_4(double *state, double *unused, double *out_3188976776469400668);
void pose_H_4(double *state, double *unused, double *out_2271039135409815712);
void pose_h_10(double *state, double *unused, double *out_4978471082043505925);
void pose_H_10(double *state, double *unused, double *out_6025972524295180069);
void pose_h_13(double *state, double *unused, double *out_3010889495309434270);
void pose_H_13(double *state, double *unused, double *out_6104794598712339736);
void pose_h_14(double *state, double *unused, double *out_7339283631215046728);
void pose_H_14(double *state, double *unused, double *out_8694559123019995480);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}