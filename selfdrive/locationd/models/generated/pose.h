#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7744429972371327634);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8537065090514966302);
void pose_H_mod_fun(double *state, double *out_3490805559008343978);
void pose_f_fun(double *state, double dt, double *out_904637507366578298);
void pose_F_fun(double *state, double dt, double *out_1053199935176261758);
void pose_h_4(double *state, double *unused, double *out_5407864488122211268);
void pose_H_4(double *state, double *unused, double *out_281001650835563594);
void pose_h_10(double *state, double *unused, double *out_3236269100831306834);
void pose_H_10(double *state, double *unused, double *out_3078753176381222045);
void pose_h_13(double *state, double *unused, double *out_8498957831141607887);
void pose_H_13(double *state, double *unused, double *out_3493275476167896395);
void pose_h_14(double *state, double *unused, double *out_9161980078330107534);
void pose_H_14(double *state, double *unused, double *out_4244242507175048123);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}