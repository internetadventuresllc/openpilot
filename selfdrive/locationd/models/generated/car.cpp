#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3990337682930970705) {
   out_3990337682930970705[0] = delta_x[0] + nom_x[0];
   out_3990337682930970705[1] = delta_x[1] + nom_x[1];
   out_3990337682930970705[2] = delta_x[2] + nom_x[2];
   out_3990337682930970705[3] = delta_x[3] + nom_x[3];
   out_3990337682930970705[4] = delta_x[4] + nom_x[4];
   out_3990337682930970705[5] = delta_x[5] + nom_x[5];
   out_3990337682930970705[6] = delta_x[6] + nom_x[6];
   out_3990337682930970705[7] = delta_x[7] + nom_x[7];
   out_3990337682930970705[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8419919608354584943) {
   out_8419919608354584943[0] = -nom_x[0] + true_x[0];
   out_8419919608354584943[1] = -nom_x[1] + true_x[1];
   out_8419919608354584943[2] = -nom_x[2] + true_x[2];
   out_8419919608354584943[3] = -nom_x[3] + true_x[3];
   out_8419919608354584943[4] = -nom_x[4] + true_x[4];
   out_8419919608354584943[5] = -nom_x[5] + true_x[5];
   out_8419919608354584943[6] = -nom_x[6] + true_x[6];
   out_8419919608354584943[7] = -nom_x[7] + true_x[7];
   out_8419919608354584943[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2419989426863145812) {
   out_2419989426863145812[0] = 1.0;
   out_2419989426863145812[1] = 0.0;
   out_2419989426863145812[2] = 0.0;
   out_2419989426863145812[3] = 0.0;
   out_2419989426863145812[4] = 0.0;
   out_2419989426863145812[5] = 0.0;
   out_2419989426863145812[6] = 0.0;
   out_2419989426863145812[7] = 0.0;
   out_2419989426863145812[8] = 0.0;
   out_2419989426863145812[9] = 0.0;
   out_2419989426863145812[10] = 1.0;
   out_2419989426863145812[11] = 0.0;
   out_2419989426863145812[12] = 0.0;
   out_2419989426863145812[13] = 0.0;
   out_2419989426863145812[14] = 0.0;
   out_2419989426863145812[15] = 0.0;
   out_2419989426863145812[16] = 0.0;
   out_2419989426863145812[17] = 0.0;
   out_2419989426863145812[18] = 0.0;
   out_2419989426863145812[19] = 0.0;
   out_2419989426863145812[20] = 1.0;
   out_2419989426863145812[21] = 0.0;
   out_2419989426863145812[22] = 0.0;
   out_2419989426863145812[23] = 0.0;
   out_2419989426863145812[24] = 0.0;
   out_2419989426863145812[25] = 0.0;
   out_2419989426863145812[26] = 0.0;
   out_2419989426863145812[27] = 0.0;
   out_2419989426863145812[28] = 0.0;
   out_2419989426863145812[29] = 0.0;
   out_2419989426863145812[30] = 1.0;
   out_2419989426863145812[31] = 0.0;
   out_2419989426863145812[32] = 0.0;
   out_2419989426863145812[33] = 0.0;
   out_2419989426863145812[34] = 0.0;
   out_2419989426863145812[35] = 0.0;
   out_2419989426863145812[36] = 0.0;
   out_2419989426863145812[37] = 0.0;
   out_2419989426863145812[38] = 0.0;
   out_2419989426863145812[39] = 0.0;
   out_2419989426863145812[40] = 1.0;
   out_2419989426863145812[41] = 0.0;
   out_2419989426863145812[42] = 0.0;
   out_2419989426863145812[43] = 0.0;
   out_2419989426863145812[44] = 0.0;
   out_2419989426863145812[45] = 0.0;
   out_2419989426863145812[46] = 0.0;
   out_2419989426863145812[47] = 0.0;
   out_2419989426863145812[48] = 0.0;
   out_2419989426863145812[49] = 0.0;
   out_2419989426863145812[50] = 1.0;
   out_2419989426863145812[51] = 0.0;
   out_2419989426863145812[52] = 0.0;
   out_2419989426863145812[53] = 0.0;
   out_2419989426863145812[54] = 0.0;
   out_2419989426863145812[55] = 0.0;
   out_2419989426863145812[56] = 0.0;
   out_2419989426863145812[57] = 0.0;
   out_2419989426863145812[58] = 0.0;
   out_2419989426863145812[59] = 0.0;
   out_2419989426863145812[60] = 1.0;
   out_2419989426863145812[61] = 0.0;
   out_2419989426863145812[62] = 0.0;
   out_2419989426863145812[63] = 0.0;
   out_2419989426863145812[64] = 0.0;
   out_2419989426863145812[65] = 0.0;
   out_2419989426863145812[66] = 0.0;
   out_2419989426863145812[67] = 0.0;
   out_2419989426863145812[68] = 0.0;
   out_2419989426863145812[69] = 0.0;
   out_2419989426863145812[70] = 1.0;
   out_2419989426863145812[71] = 0.0;
   out_2419989426863145812[72] = 0.0;
   out_2419989426863145812[73] = 0.0;
   out_2419989426863145812[74] = 0.0;
   out_2419989426863145812[75] = 0.0;
   out_2419989426863145812[76] = 0.0;
   out_2419989426863145812[77] = 0.0;
   out_2419989426863145812[78] = 0.0;
   out_2419989426863145812[79] = 0.0;
   out_2419989426863145812[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8386161078390113048) {
   out_8386161078390113048[0] = state[0];
   out_8386161078390113048[1] = state[1];
   out_8386161078390113048[2] = state[2];
   out_8386161078390113048[3] = state[3];
   out_8386161078390113048[4] = state[4];
   out_8386161078390113048[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8386161078390113048[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8386161078390113048[7] = state[7];
   out_8386161078390113048[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3717913866807838179) {
   out_3717913866807838179[0] = 1;
   out_3717913866807838179[1] = 0;
   out_3717913866807838179[2] = 0;
   out_3717913866807838179[3] = 0;
   out_3717913866807838179[4] = 0;
   out_3717913866807838179[5] = 0;
   out_3717913866807838179[6] = 0;
   out_3717913866807838179[7] = 0;
   out_3717913866807838179[8] = 0;
   out_3717913866807838179[9] = 0;
   out_3717913866807838179[10] = 1;
   out_3717913866807838179[11] = 0;
   out_3717913866807838179[12] = 0;
   out_3717913866807838179[13] = 0;
   out_3717913866807838179[14] = 0;
   out_3717913866807838179[15] = 0;
   out_3717913866807838179[16] = 0;
   out_3717913866807838179[17] = 0;
   out_3717913866807838179[18] = 0;
   out_3717913866807838179[19] = 0;
   out_3717913866807838179[20] = 1;
   out_3717913866807838179[21] = 0;
   out_3717913866807838179[22] = 0;
   out_3717913866807838179[23] = 0;
   out_3717913866807838179[24] = 0;
   out_3717913866807838179[25] = 0;
   out_3717913866807838179[26] = 0;
   out_3717913866807838179[27] = 0;
   out_3717913866807838179[28] = 0;
   out_3717913866807838179[29] = 0;
   out_3717913866807838179[30] = 1;
   out_3717913866807838179[31] = 0;
   out_3717913866807838179[32] = 0;
   out_3717913866807838179[33] = 0;
   out_3717913866807838179[34] = 0;
   out_3717913866807838179[35] = 0;
   out_3717913866807838179[36] = 0;
   out_3717913866807838179[37] = 0;
   out_3717913866807838179[38] = 0;
   out_3717913866807838179[39] = 0;
   out_3717913866807838179[40] = 1;
   out_3717913866807838179[41] = 0;
   out_3717913866807838179[42] = 0;
   out_3717913866807838179[43] = 0;
   out_3717913866807838179[44] = 0;
   out_3717913866807838179[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3717913866807838179[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3717913866807838179[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3717913866807838179[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3717913866807838179[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3717913866807838179[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3717913866807838179[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3717913866807838179[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3717913866807838179[53] = -9.8100000000000005*dt;
   out_3717913866807838179[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3717913866807838179[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3717913866807838179[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3717913866807838179[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3717913866807838179[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3717913866807838179[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3717913866807838179[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3717913866807838179[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3717913866807838179[62] = 0;
   out_3717913866807838179[63] = 0;
   out_3717913866807838179[64] = 0;
   out_3717913866807838179[65] = 0;
   out_3717913866807838179[66] = 0;
   out_3717913866807838179[67] = 0;
   out_3717913866807838179[68] = 0;
   out_3717913866807838179[69] = 0;
   out_3717913866807838179[70] = 1;
   out_3717913866807838179[71] = 0;
   out_3717913866807838179[72] = 0;
   out_3717913866807838179[73] = 0;
   out_3717913866807838179[74] = 0;
   out_3717913866807838179[75] = 0;
   out_3717913866807838179[76] = 0;
   out_3717913866807838179[77] = 0;
   out_3717913866807838179[78] = 0;
   out_3717913866807838179[79] = 0;
   out_3717913866807838179[80] = 1;
}
void h_25(double *state, double *unused, double *out_1684039001660190569) {
   out_1684039001660190569[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2483702398321519028) {
   out_2483702398321519028[0] = 0;
   out_2483702398321519028[1] = 0;
   out_2483702398321519028[2] = 0;
   out_2483702398321519028[3] = 0;
   out_2483702398321519028[4] = 0;
   out_2483702398321519028[5] = 0;
   out_2483702398321519028[6] = 1;
   out_2483702398321519028[7] = 0;
   out_2483702398321519028[8] = 0;
}
void h_24(double *state, double *unused, double *out_609872506711191044) {
   out_609872506711191044[0] = state[4];
   out_609872506711191044[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2087057093967659533) {
   out_2087057093967659533[0] = 0;
   out_2087057093967659533[1] = 0;
   out_2087057093967659533[2] = 0;
   out_2087057093967659533[3] = 0;
   out_2087057093967659533[4] = 1;
   out_2087057093967659533[5] = 0;
   out_2087057093967659533[6] = 0;
   out_2087057093967659533[7] = 0;
   out_2087057093967659533[8] = 0;
   out_2087057093967659533[9] = 0;
   out_2087057093967659533[10] = 0;
   out_2087057093967659533[11] = 0;
   out_2087057093967659533[12] = 0;
   out_2087057093967659533[13] = 0;
   out_2087057093967659533[14] = 1;
   out_2087057093967659533[15] = 0;
   out_2087057093967659533[16] = 0;
   out_2087057093967659533[17] = 0;
}
void h_30(double *state, double *unused, double *out_8271866928136485732) {
   out_8271866928136485732[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5002035356828767655) {
   out_5002035356828767655[0] = 0;
   out_5002035356828767655[1] = 0;
   out_5002035356828767655[2] = 0;
   out_5002035356828767655[3] = 0;
   out_5002035356828767655[4] = 1;
   out_5002035356828767655[5] = 0;
   out_5002035356828767655[6] = 0;
   out_5002035356828767655[7] = 0;
   out_5002035356828767655[8] = 0;
}
void h_26(double *state, double *unused, double *out_3649680898680377418) {
   out_3649680898680377418[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1257800920552537196) {
   out_1257800920552537196[0] = 0;
   out_1257800920552537196[1] = 0;
   out_1257800920552537196[2] = 0;
   out_1257800920552537196[3] = 0;
   out_1257800920552537196[4] = 0;
   out_1257800920552537196[5] = 0;
   out_1257800920552537196[6] = 0;
   out_1257800920552537196[7] = 1;
   out_1257800920552537196[8] = 0;
}
void h_27(double *state, double *unused, double *out_6685712269321036214) {
   out_6685712269321036214[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7225629428012710872) {
   out_7225629428012710872[0] = 0;
   out_7225629428012710872[1] = 0;
   out_7225629428012710872[2] = 0;
   out_7225629428012710872[3] = 1;
   out_7225629428012710872[4] = 0;
   out_7225629428012710872[5] = 0;
   out_7225629428012710872[6] = 0;
   out_7225629428012710872[7] = 0;
   out_7225629428012710872[8] = 0;
}
void h_29(double *state, double *unused, double *out_5173203877912220239) {
   out_5173203877912220239[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5512266701143159839) {
   out_5512266701143159839[0] = 0;
   out_5512266701143159839[1] = 1;
   out_5512266701143159839[2] = 0;
   out_5512266701143159839[3] = 0;
   out_5512266701143159839[4] = 0;
   out_5512266701143159839[5] = 0;
   out_5512266701143159839[6] = 0;
   out_5512266701143159839[7] = 0;
   out_5512266701143159839[8] = 0;
}
void h_28(double *state, double *unused, double *out_1343845033435005651) {
   out_1343845033435005651[0] = state[0];
}
void H_28(double *state, double *unused, double *out_429867684073629265) {
   out_429867684073629265[0] = 1;
   out_429867684073629265[1] = 0;
   out_429867684073629265[2] = 0;
   out_429867684073629265[3] = 0;
   out_429867684073629265[4] = 0;
   out_429867684073629265[5] = 0;
   out_429867684073629265[6] = 0;
   out_429867684073629265[7] = 0;
   out_429867684073629265[8] = 0;
}
void h_31(double *state, double *unused, double *out_1953410526593831781) {
   out_1953410526593831781[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1884009022785888672) {
   out_1884009022785888672[0] = 0;
   out_1884009022785888672[1] = 0;
   out_1884009022785888672[2] = 0;
   out_1884009022785888672[3] = 0;
   out_1884009022785888672[4] = 0;
   out_1884009022785888672[5] = 0;
   out_1884009022785888672[6] = 0;
   out_1884009022785888672[7] = 0;
   out_1884009022785888672[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_3990337682930970705) {
  err_fun(nom_x, delta_x, out_3990337682930970705);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8419919608354584943) {
  inv_err_fun(nom_x, true_x, out_8419919608354584943);
}
void car_H_mod_fun(double *state, double *out_2419989426863145812) {
  H_mod_fun(state, out_2419989426863145812);
}
void car_f_fun(double *state, double dt, double *out_8386161078390113048) {
  f_fun(state,  dt, out_8386161078390113048);
}
void car_F_fun(double *state, double dt, double *out_3717913866807838179) {
  F_fun(state,  dt, out_3717913866807838179);
}
void car_h_25(double *state, double *unused, double *out_1684039001660190569) {
  h_25(state, unused, out_1684039001660190569);
}
void car_H_25(double *state, double *unused, double *out_2483702398321519028) {
  H_25(state, unused, out_2483702398321519028);
}
void car_h_24(double *state, double *unused, double *out_609872506711191044) {
  h_24(state, unused, out_609872506711191044);
}
void car_H_24(double *state, double *unused, double *out_2087057093967659533) {
  H_24(state, unused, out_2087057093967659533);
}
void car_h_30(double *state, double *unused, double *out_8271866928136485732) {
  h_30(state, unused, out_8271866928136485732);
}
void car_H_30(double *state, double *unused, double *out_5002035356828767655) {
  H_30(state, unused, out_5002035356828767655);
}
void car_h_26(double *state, double *unused, double *out_3649680898680377418) {
  h_26(state, unused, out_3649680898680377418);
}
void car_H_26(double *state, double *unused, double *out_1257800920552537196) {
  H_26(state, unused, out_1257800920552537196);
}
void car_h_27(double *state, double *unused, double *out_6685712269321036214) {
  h_27(state, unused, out_6685712269321036214);
}
void car_H_27(double *state, double *unused, double *out_7225629428012710872) {
  H_27(state, unused, out_7225629428012710872);
}
void car_h_29(double *state, double *unused, double *out_5173203877912220239) {
  h_29(state, unused, out_5173203877912220239);
}
void car_H_29(double *state, double *unused, double *out_5512266701143159839) {
  H_29(state, unused, out_5512266701143159839);
}
void car_h_28(double *state, double *unused, double *out_1343845033435005651) {
  h_28(state, unused, out_1343845033435005651);
}
void car_H_28(double *state, double *unused, double *out_429867684073629265) {
  H_28(state, unused, out_429867684073629265);
}
void car_h_31(double *state, double *unused, double *out_1953410526593831781) {
  h_31(state, unused, out_1953410526593831781);
}
void car_H_31(double *state, double *unused, double *out_1884009022785888672) {
  H_31(state, unused, out_1884009022785888672);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
