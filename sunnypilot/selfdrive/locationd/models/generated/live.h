#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_6843814025197600946);
void live_err_fun(double *nom_x, double *delta_x, double *out_2212505165025274649);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_4593866643528134565);
void live_H_mod_fun(double *state, double *out_3141958089349474723);
void live_f_fun(double *state, double dt, double *out_3360342858490261249);
void live_F_fun(double *state, double dt, double *out_51468558315833747);
void live_h_4(double *state, double *unused, double *out_1614851666566202590);
void live_H_4(double *state, double *unused, double *out_7227656648870618848);
void live_h_9(double *state, double *unused, double *out_1283684166394172111);
void live_H_9(double *state, double *unused, double *out_3931868489574485298);
void live_h_10(double *state, double *unused, double *out_8907464111937739962);
void live_H_10(double *state, double *unused, double *out_4795856902048004594);
void live_h_12(double *state, double *unused, double *out_8878290931895780829);
void live_H_12(double *state, double *unused, double *out_6199631016806970973);
void live_h_35(double *state, double *unused, double *out_3598710993023961770);
void live_H_35(double *state, double *unused, double *out_7852425367466325392);
void live_h_32(double *state, double *unused, double *out_2212266580640060517);
void live_H_32(double *state, double *unused, double *out_2051120995258712834);
void live_h_13(double *state, double *unused, double *out_7402999134992983558);
void live_H_13(double *state, double *unused, double *out_7391940872840257484);
void live_h_14(double *state, double *unused, double *out_1283684166394172111);
void live_H_14(double *state, double *unused, double *out_3931868489574485298);
void live_h_33(double *state, double *unused, double *out_8089606173863187959);
void live_H_33(double *state, double *unused, double *out_4701868362827467788);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}