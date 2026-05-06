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
void err_fun(double *nom_x, double *delta_x, double *out_5490557007678757153) {
   out_5490557007678757153[0] = delta_x[0] + nom_x[0];
   out_5490557007678757153[1] = delta_x[1] + nom_x[1];
   out_5490557007678757153[2] = delta_x[2] + nom_x[2];
   out_5490557007678757153[3] = delta_x[3] + nom_x[3];
   out_5490557007678757153[4] = delta_x[4] + nom_x[4];
   out_5490557007678757153[5] = delta_x[5] + nom_x[5];
   out_5490557007678757153[6] = delta_x[6] + nom_x[6];
   out_5490557007678757153[7] = delta_x[7] + nom_x[7];
   out_5490557007678757153[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8915261011539861709) {
   out_8915261011539861709[0] = -nom_x[0] + true_x[0];
   out_8915261011539861709[1] = -nom_x[1] + true_x[1];
   out_8915261011539861709[2] = -nom_x[2] + true_x[2];
   out_8915261011539861709[3] = -nom_x[3] + true_x[3];
   out_8915261011539861709[4] = -nom_x[4] + true_x[4];
   out_8915261011539861709[5] = -nom_x[5] + true_x[5];
   out_8915261011539861709[6] = -nom_x[6] + true_x[6];
   out_8915261011539861709[7] = -nom_x[7] + true_x[7];
   out_8915261011539861709[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1909303659468267564) {
   out_1909303659468267564[0] = 1.0;
   out_1909303659468267564[1] = 0.0;
   out_1909303659468267564[2] = 0.0;
   out_1909303659468267564[3] = 0.0;
   out_1909303659468267564[4] = 0.0;
   out_1909303659468267564[5] = 0.0;
   out_1909303659468267564[6] = 0.0;
   out_1909303659468267564[7] = 0.0;
   out_1909303659468267564[8] = 0.0;
   out_1909303659468267564[9] = 0.0;
   out_1909303659468267564[10] = 1.0;
   out_1909303659468267564[11] = 0.0;
   out_1909303659468267564[12] = 0.0;
   out_1909303659468267564[13] = 0.0;
   out_1909303659468267564[14] = 0.0;
   out_1909303659468267564[15] = 0.0;
   out_1909303659468267564[16] = 0.0;
   out_1909303659468267564[17] = 0.0;
   out_1909303659468267564[18] = 0.0;
   out_1909303659468267564[19] = 0.0;
   out_1909303659468267564[20] = 1.0;
   out_1909303659468267564[21] = 0.0;
   out_1909303659468267564[22] = 0.0;
   out_1909303659468267564[23] = 0.0;
   out_1909303659468267564[24] = 0.0;
   out_1909303659468267564[25] = 0.0;
   out_1909303659468267564[26] = 0.0;
   out_1909303659468267564[27] = 0.0;
   out_1909303659468267564[28] = 0.0;
   out_1909303659468267564[29] = 0.0;
   out_1909303659468267564[30] = 1.0;
   out_1909303659468267564[31] = 0.0;
   out_1909303659468267564[32] = 0.0;
   out_1909303659468267564[33] = 0.0;
   out_1909303659468267564[34] = 0.0;
   out_1909303659468267564[35] = 0.0;
   out_1909303659468267564[36] = 0.0;
   out_1909303659468267564[37] = 0.0;
   out_1909303659468267564[38] = 0.0;
   out_1909303659468267564[39] = 0.0;
   out_1909303659468267564[40] = 1.0;
   out_1909303659468267564[41] = 0.0;
   out_1909303659468267564[42] = 0.0;
   out_1909303659468267564[43] = 0.0;
   out_1909303659468267564[44] = 0.0;
   out_1909303659468267564[45] = 0.0;
   out_1909303659468267564[46] = 0.0;
   out_1909303659468267564[47] = 0.0;
   out_1909303659468267564[48] = 0.0;
   out_1909303659468267564[49] = 0.0;
   out_1909303659468267564[50] = 1.0;
   out_1909303659468267564[51] = 0.0;
   out_1909303659468267564[52] = 0.0;
   out_1909303659468267564[53] = 0.0;
   out_1909303659468267564[54] = 0.0;
   out_1909303659468267564[55] = 0.0;
   out_1909303659468267564[56] = 0.0;
   out_1909303659468267564[57] = 0.0;
   out_1909303659468267564[58] = 0.0;
   out_1909303659468267564[59] = 0.0;
   out_1909303659468267564[60] = 1.0;
   out_1909303659468267564[61] = 0.0;
   out_1909303659468267564[62] = 0.0;
   out_1909303659468267564[63] = 0.0;
   out_1909303659468267564[64] = 0.0;
   out_1909303659468267564[65] = 0.0;
   out_1909303659468267564[66] = 0.0;
   out_1909303659468267564[67] = 0.0;
   out_1909303659468267564[68] = 0.0;
   out_1909303659468267564[69] = 0.0;
   out_1909303659468267564[70] = 1.0;
   out_1909303659468267564[71] = 0.0;
   out_1909303659468267564[72] = 0.0;
   out_1909303659468267564[73] = 0.0;
   out_1909303659468267564[74] = 0.0;
   out_1909303659468267564[75] = 0.0;
   out_1909303659468267564[76] = 0.0;
   out_1909303659468267564[77] = 0.0;
   out_1909303659468267564[78] = 0.0;
   out_1909303659468267564[79] = 0.0;
   out_1909303659468267564[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5619520264811798499) {
   out_5619520264811798499[0] = state[0];
   out_5619520264811798499[1] = state[1];
   out_5619520264811798499[2] = state[2];
   out_5619520264811798499[3] = state[3];
   out_5619520264811798499[4] = state[4];
   out_5619520264811798499[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5619520264811798499[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5619520264811798499[7] = state[7];
   out_5619520264811798499[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4962809153804984575) {
   out_4962809153804984575[0] = 1;
   out_4962809153804984575[1] = 0;
   out_4962809153804984575[2] = 0;
   out_4962809153804984575[3] = 0;
   out_4962809153804984575[4] = 0;
   out_4962809153804984575[5] = 0;
   out_4962809153804984575[6] = 0;
   out_4962809153804984575[7] = 0;
   out_4962809153804984575[8] = 0;
   out_4962809153804984575[9] = 0;
   out_4962809153804984575[10] = 1;
   out_4962809153804984575[11] = 0;
   out_4962809153804984575[12] = 0;
   out_4962809153804984575[13] = 0;
   out_4962809153804984575[14] = 0;
   out_4962809153804984575[15] = 0;
   out_4962809153804984575[16] = 0;
   out_4962809153804984575[17] = 0;
   out_4962809153804984575[18] = 0;
   out_4962809153804984575[19] = 0;
   out_4962809153804984575[20] = 1;
   out_4962809153804984575[21] = 0;
   out_4962809153804984575[22] = 0;
   out_4962809153804984575[23] = 0;
   out_4962809153804984575[24] = 0;
   out_4962809153804984575[25] = 0;
   out_4962809153804984575[26] = 0;
   out_4962809153804984575[27] = 0;
   out_4962809153804984575[28] = 0;
   out_4962809153804984575[29] = 0;
   out_4962809153804984575[30] = 1;
   out_4962809153804984575[31] = 0;
   out_4962809153804984575[32] = 0;
   out_4962809153804984575[33] = 0;
   out_4962809153804984575[34] = 0;
   out_4962809153804984575[35] = 0;
   out_4962809153804984575[36] = 0;
   out_4962809153804984575[37] = 0;
   out_4962809153804984575[38] = 0;
   out_4962809153804984575[39] = 0;
   out_4962809153804984575[40] = 1;
   out_4962809153804984575[41] = 0;
   out_4962809153804984575[42] = 0;
   out_4962809153804984575[43] = 0;
   out_4962809153804984575[44] = 0;
   out_4962809153804984575[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4962809153804984575[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4962809153804984575[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4962809153804984575[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4962809153804984575[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4962809153804984575[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4962809153804984575[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4962809153804984575[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4962809153804984575[53] = -9.8100000000000005*dt;
   out_4962809153804984575[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4962809153804984575[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4962809153804984575[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4962809153804984575[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4962809153804984575[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4962809153804984575[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4962809153804984575[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4962809153804984575[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4962809153804984575[62] = 0;
   out_4962809153804984575[63] = 0;
   out_4962809153804984575[64] = 0;
   out_4962809153804984575[65] = 0;
   out_4962809153804984575[66] = 0;
   out_4962809153804984575[67] = 0;
   out_4962809153804984575[68] = 0;
   out_4962809153804984575[69] = 0;
   out_4962809153804984575[70] = 1;
   out_4962809153804984575[71] = 0;
   out_4962809153804984575[72] = 0;
   out_4962809153804984575[73] = 0;
   out_4962809153804984575[74] = 0;
   out_4962809153804984575[75] = 0;
   out_4962809153804984575[76] = 0;
   out_4962809153804984575[77] = 0;
   out_4962809153804984575[78] = 0;
   out_4962809153804984575[79] = 0;
   out_4962809153804984575[80] = 1;
}
void h_25(double *state, double *unused, double *out_1588189202735586313) {
   out_1588189202735586313[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5432284309457759241) {
   out_5432284309457759241[0] = 0;
   out_5432284309457759241[1] = 0;
   out_5432284309457759241[2] = 0;
   out_5432284309457759241[3] = 0;
   out_5432284309457759241[4] = 0;
   out_5432284309457759241[5] = 0;
   out_5432284309457759241[6] = 1;
   out_5432284309457759241[7] = 0;
   out_5432284309457759241[8] = 0;
}
void h_24(double *state, double *unused, double *out_5086606811221189508) {
   out_5086606811221189508[0] = state[4];
   out_5086606811221189508[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7657992093436627803) {
   out_7657992093436627803[0] = 0;
   out_7657992093436627803[1] = 0;
   out_7657992093436627803[2] = 0;
   out_7657992093436627803[3] = 0;
   out_7657992093436627803[4] = 1;
   out_7657992093436627803[5] = 0;
   out_7657992093436627803[6] = 0;
   out_7657992093436627803[7] = 0;
   out_7657992093436627803[8] = 0;
   out_7657992093436627803[9] = 0;
   out_7657992093436627803[10] = 0;
   out_7657992093436627803[11] = 0;
   out_7657992093436627803[12] = 0;
   out_7657992093436627803[13] = 0;
   out_7657992093436627803[14] = 1;
   out_7657992093436627803[15] = 0;
   out_7657992093436627803[16] = 0;
   out_7657992093436627803[17] = 0;
}
void h_30(double *state, double *unused, double *out_5182646023614764623) {
   out_5182646023614764623[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6097769422760175620) {
   out_6097769422760175620[0] = 0;
   out_6097769422760175620[1] = 0;
   out_6097769422760175620[2] = 0;
   out_6097769422760175620[3] = 0;
   out_6097769422760175620[4] = 1;
   out_6097769422760175620[5] = 0;
   out_6097769422760175620[6] = 0;
   out_6097769422760175620[7] = 0;
   out_6097769422760175620[8] = 0;
}
void h_26(double *state, double *unused, double *out_4467788585828789853) {
   out_4467788585828789853[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6089138373568071145) {
   out_6089138373568071145[0] = 0;
   out_6089138373568071145[1] = 0;
   out_6089138373568071145[2] = 0;
   out_6089138373568071145[3] = 0;
   out_6089138373568071145[4] = 0;
   out_6089138373568071145[5] = 0;
   out_6089138373568071145[6] = 0;
   out_6089138373568071145[7] = 1;
   out_6089138373568071145[8] = 0;
}
void h_27(double *state, double *unused, double *out_7503819956469448649) {
   out_7503819956469448649[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8272532734560600531) {
   out_8272532734560600531[0] = 0;
   out_8272532734560600531[1] = 0;
   out_8272532734560600531[2] = 0;
   out_8272532734560600531[3] = 1;
   out_8272532734560600531[4] = 0;
   out_8272532734560600531[5] = 0;
   out_8272532734560600531[6] = 0;
   out_8272532734560600531[7] = 0;
   out_8272532734560600531[8] = 0;
}
void h_29(double *state, double *unused, double *out_6865056532680937847) {
   out_6865056532680937847[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5587538078445783436) {
   out_5587538078445783436[0] = 0;
   out_5587538078445783436[1] = 1;
   out_5587538078445783436[2] = 0;
   out_5587538078445783436[3] = 0;
   out_5587538078445783436[4] = 0;
   out_5587538078445783436[5] = 0;
   out_5587538078445783436[6] = 0;
   out_5587538078445783436[7] = 0;
   out_5587538078445783436[8] = 0;
}
void h_28(double *state, double *unused, double *out_5064638629681387879) {
   out_5064638629681387879[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7776806978194237606) {
   out_7776806978194237606[0] = 1;
   out_7776806978194237606[1] = 0;
   out_7776806978194237606[2] = 0;
   out_7776806978194237606[3] = 0;
   out_7776806978194237606[4] = 0;
   out_7776806978194237606[5] = 0;
   out_7776806978194237606[6] = 0;
   out_7776806978194237606[7] = 0;
   out_7776806978194237606[8] = 0;
}
void h_31(double *state, double *unused, double *out_1359536787619898648) {
   out_1359536787619898648[0] = state[8];
}
void H_31(double *state, double *unused, double *out_5462930271334719669) {
   out_5462930271334719669[0] = 0;
   out_5462930271334719669[1] = 0;
   out_5462930271334719669[2] = 0;
   out_5462930271334719669[3] = 0;
   out_5462930271334719669[4] = 0;
   out_5462930271334719669[5] = 0;
   out_5462930271334719669[6] = 0;
   out_5462930271334719669[7] = 0;
   out_5462930271334719669[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5490557007678757153) {
  err_fun(nom_x, delta_x, out_5490557007678757153);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8915261011539861709) {
  inv_err_fun(nom_x, true_x, out_8915261011539861709);
}
void car_H_mod_fun(double *state, double *out_1909303659468267564) {
  H_mod_fun(state, out_1909303659468267564);
}
void car_f_fun(double *state, double dt, double *out_5619520264811798499) {
  f_fun(state,  dt, out_5619520264811798499);
}
void car_F_fun(double *state, double dt, double *out_4962809153804984575) {
  F_fun(state,  dt, out_4962809153804984575);
}
void car_h_25(double *state, double *unused, double *out_1588189202735586313) {
  h_25(state, unused, out_1588189202735586313);
}
void car_H_25(double *state, double *unused, double *out_5432284309457759241) {
  H_25(state, unused, out_5432284309457759241);
}
void car_h_24(double *state, double *unused, double *out_5086606811221189508) {
  h_24(state, unused, out_5086606811221189508);
}
void car_H_24(double *state, double *unused, double *out_7657992093436627803) {
  H_24(state, unused, out_7657992093436627803);
}
void car_h_30(double *state, double *unused, double *out_5182646023614764623) {
  h_30(state, unused, out_5182646023614764623);
}
void car_H_30(double *state, double *unused, double *out_6097769422760175620) {
  H_30(state, unused, out_6097769422760175620);
}
void car_h_26(double *state, double *unused, double *out_4467788585828789853) {
  h_26(state, unused, out_4467788585828789853);
}
void car_H_26(double *state, double *unused, double *out_6089138373568071145) {
  H_26(state, unused, out_6089138373568071145);
}
void car_h_27(double *state, double *unused, double *out_7503819956469448649) {
  h_27(state, unused, out_7503819956469448649);
}
void car_H_27(double *state, double *unused, double *out_8272532734560600531) {
  H_27(state, unused, out_8272532734560600531);
}
void car_h_29(double *state, double *unused, double *out_6865056532680937847) {
  h_29(state, unused, out_6865056532680937847);
}
void car_H_29(double *state, double *unused, double *out_5587538078445783436) {
  H_29(state, unused, out_5587538078445783436);
}
void car_h_28(double *state, double *unused, double *out_5064638629681387879) {
  h_28(state, unused, out_5064638629681387879);
}
void car_H_28(double *state, double *unused, double *out_7776806978194237606) {
  H_28(state, unused, out_7776806978194237606);
}
void car_h_31(double *state, double *unused, double *out_1359536787619898648) {
  h_31(state, unused, out_1359536787619898648);
}
void car_H_31(double *state, double *unused, double *out_5462930271334719669) {
  H_31(state, unused, out_5462930271334719669);
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
