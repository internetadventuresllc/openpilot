#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_495600354373200881);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1169161554918362952);
void pose_H_mod_fun(double *state, double *out_269990567082015073);
void pose_f_fun(double *state, double dt, double *out_2663299199207308722);
void pose_F_fun(double *state, double dt, double *out_502897361153597694);
void pose_h_4(double *state, double *unused, double *out_1859606723148110361);
void pose_H_4(double *state, double *unused, double *out_8742993852831669419);
void pose_h_10(double *state, double *unused, double *out_8451494295132406513);
void pose_H_10(double *state, double *unused, double *out_7097327689072921534);
void pose_h_13(double *state, double *unused, double *out_8832559562355137152);
void pose_H_13(double *state, double *unused, double *out_6491476395545549396);
void pose_h_14(double *state, double *unused, double *out_2493859926449381385);
void pose_H_14(double *state, double *unused, double *out_5740509364538397668);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}