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
void err_fun(double *nom_x, double *delta_x, double *out_5180017016346976199) {
   out_5180017016346976199[0] = delta_x[0] + nom_x[0];
   out_5180017016346976199[1] = delta_x[1] + nom_x[1];
   out_5180017016346976199[2] = delta_x[2] + nom_x[2];
   out_5180017016346976199[3] = delta_x[3] + nom_x[3];
   out_5180017016346976199[4] = delta_x[4] + nom_x[4];
   out_5180017016346976199[5] = delta_x[5] + nom_x[5];
   out_5180017016346976199[6] = delta_x[6] + nom_x[6];
   out_5180017016346976199[7] = delta_x[7] + nom_x[7];
   out_5180017016346976199[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8487031610083345537) {
   out_8487031610083345537[0] = -nom_x[0] + true_x[0];
   out_8487031610083345537[1] = -nom_x[1] + true_x[1];
   out_8487031610083345537[2] = -nom_x[2] + true_x[2];
   out_8487031610083345537[3] = -nom_x[3] + true_x[3];
   out_8487031610083345537[4] = -nom_x[4] + true_x[4];
   out_8487031610083345537[5] = -nom_x[5] + true_x[5];
   out_8487031610083345537[6] = -nom_x[6] + true_x[6];
   out_8487031610083345537[7] = -nom_x[7] + true_x[7];
   out_8487031610083345537[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5706437107101781759) {
   out_5706437107101781759[0] = 1.0;
   out_5706437107101781759[1] = 0.0;
   out_5706437107101781759[2] = 0.0;
   out_5706437107101781759[3] = 0.0;
   out_5706437107101781759[4] = 0.0;
   out_5706437107101781759[5] = 0.0;
   out_5706437107101781759[6] = 0.0;
   out_5706437107101781759[7] = 0.0;
   out_5706437107101781759[8] = 0.0;
   out_5706437107101781759[9] = 0.0;
   out_5706437107101781759[10] = 1.0;
   out_5706437107101781759[11] = 0.0;
   out_5706437107101781759[12] = 0.0;
   out_5706437107101781759[13] = 0.0;
   out_5706437107101781759[14] = 0.0;
   out_5706437107101781759[15] = 0.0;
   out_5706437107101781759[16] = 0.0;
   out_5706437107101781759[17] = 0.0;
   out_5706437107101781759[18] = 0.0;
   out_5706437107101781759[19] = 0.0;
   out_5706437107101781759[20] = 1.0;
   out_5706437107101781759[21] = 0.0;
   out_5706437107101781759[22] = 0.0;
   out_5706437107101781759[23] = 0.0;
   out_5706437107101781759[24] = 0.0;
   out_5706437107101781759[25] = 0.0;
   out_5706437107101781759[26] = 0.0;
   out_5706437107101781759[27] = 0.0;
   out_5706437107101781759[28] = 0.0;
   out_5706437107101781759[29] = 0.0;
   out_5706437107101781759[30] = 1.0;
   out_5706437107101781759[31] = 0.0;
   out_5706437107101781759[32] = 0.0;
   out_5706437107101781759[33] = 0.0;
   out_5706437107101781759[34] = 0.0;
   out_5706437107101781759[35] = 0.0;
   out_5706437107101781759[36] = 0.0;
   out_5706437107101781759[37] = 0.0;
   out_5706437107101781759[38] = 0.0;
   out_5706437107101781759[39] = 0.0;
   out_5706437107101781759[40] = 1.0;
   out_5706437107101781759[41] = 0.0;
   out_5706437107101781759[42] = 0.0;
   out_5706437107101781759[43] = 0.0;
   out_5706437107101781759[44] = 0.0;
   out_5706437107101781759[45] = 0.0;
   out_5706437107101781759[46] = 0.0;
   out_5706437107101781759[47] = 0.0;
   out_5706437107101781759[48] = 0.0;
   out_5706437107101781759[49] = 0.0;
   out_5706437107101781759[50] = 1.0;
   out_5706437107101781759[51] = 0.0;
   out_5706437107101781759[52] = 0.0;
   out_5706437107101781759[53] = 0.0;
   out_5706437107101781759[54] = 0.0;
   out_5706437107101781759[55] = 0.0;
   out_5706437107101781759[56] = 0.0;
   out_5706437107101781759[57] = 0.0;
   out_5706437107101781759[58] = 0.0;
   out_5706437107101781759[59] = 0.0;
   out_5706437107101781759[60] = 1.0;
   out_5706437107101781759[61] = 0.0;
   out_5706437107101781759[62] = 0.0;
   out_5706437107101781759[63] = 0.0;
   out_5706437107101781759[64] = 0.0;
   out_5706437107101781759[65] = 0.0;
   out_5706437107101781759[66] = 0.0;
   out_5706437107101781759[67] = 0.0;
   out_5706437107101781759[68] = 0.0;
   out_5706437107101781759[69] = 0.0;
   out_5706437107101781759[70] = 1.0;
   out_5706437107101781759[71] = 0.0;
   out_5706437107101781759[72] = 0.0;
   out_5706437107101781759[73] = 0.0;
   out_5706437107101781759[74] = 0.0;
   out_5706437107101781759[75] = 0.0;
   out_5706437107101781759[76] = 0.0;
   out_5706437107101781759[77] = 0.0;
   out_5706437107101781759[78] = 0.0;
   out_5706437107101781759[79] = 0.0;
   out_5706437107101781759[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1153822413136816832) {
   out_1153822413136816832[0] = state[0];
   out_1153822413136816832[1] = state[1];
   out_1153822413136816832[2] = state[2];
   out_1153822413136816832[3] = state[3];
   out_1153822413136816832[4] = state[4];
   out_1153822413136816832[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1153822413136816832[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1153822413136816832[7] = state[7];
   out_1153822413136816832[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8315107788488877245) {
   out_8315107788488877245[0] = 1;
   out_8315107788488877245[1] = 0;
   out_8315107788488877245[2] = 0;
   out_8315107788488877245[3] = 0;
   out_8315107788488877245[4] = 0;
   out_8315107788488877245[5] = 0;
   out_8315107788488877245[6] = 0;
   out_8315107788488877245[7] = 0;
   out_8315107788488877245[8] = 0;
   out_8315107788488877245[9] = 0;
   out_8315107788488877245[10] = 1;
   out_8315107788488877245[11] = 0;
   out_8315107788488877245[12] = 0;
   out_8315107788488877245[13] = 0;
   out_8315107788488877245[14] = 0;
   out_8315107788488877245[15] = 0;
   out_8315107788488877245[16] = 0;
   out_8315107788488877245[17] = 0;
   out_8315107788488877245[18] = 0;
   out_8315107788488877245[19] = 0;
   out_8315107788488877245[20] = 1;
   out_8315107788488877245[21] = 0;
   out_8315107788488877245[22] = 0;
   out_8315107788488877245[23] = 0;
   out_8315107788488877245[24] = 0;
   out_8315107788488877245[25] = 0;
   out_8315107788488877245[26] = 0;
   out_8315107788488877245[27] = 0;
   out_8315107788488877245[28] = 0;
   out_8315107788488877245[29] = 0;
   out_8315107788488877245[30] = 1;
   out_8315107788488877245[31] = 0;
   out_8315107788488877245[32] = 0;
   out_8315107788488877245[33] = 0;
   out_8315107788488877245[34] = 0;
   out_8315107788488877245[35] = 0;
   out_8315107788488877245[36] = 0;
   out_8315107788488877245[37] = 0;
   out_8315107788488877245[38] = 0;
   out_8315107788488877245[39] = 0;
   out_8315107788488877245[40] = 1;
   out_8315107788488877245[41] = 0;
   out_8315107788488877245[42] = 0;
   out_8315107788488877245[43] = 0;
   out_8315107788488877245[44] = 0;
   out_8315107788488877245[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8315107788488877245[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8315107788488877245[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8315107788488877245[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8315107788488877245[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8315107788488877245[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8315107788488877245[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8315107788488877245[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8315107788488877245[53] = -9.8100000000000005*dt;
   out_8315107788488877245[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8315107788488877245[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8315107788488877245[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8315107788488877245[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8315107788488877245[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8315107788488877245[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8315107788488877245[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8315107788488877245[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8315107788488877245[62] = 0;
   out_8315107788488877245[63] = 0;
   out_8315107788488877245[64] = 0;
   out_8315107788488877245[65] = 0;
   out_8315107788488877245[66] = 0;
   out_8315107788488877245[67] = 0;
   out_8315107788488877245[68] = 0;
   out_8315107788488877245[69] = 0;
   out_8315107788488877245[70] = 1;
   out_8315107788488877245[71] = 0;
   out_8315107788488877245[72] = 0;
   out_8315107788488877245[73] = 0;
   out_8315107788488877245[74] = 0;
   out_8315107788488877245[75] = 0;
   out_8315107788488877245[76] = 0;
   out_8315107788488877245[77] = 0;
   out_8315107788488877245[78] = 0;
   out_8315107788488877245[79] = 0;
   out_8315107788488877245[80] = 1;
}
void h_25(double *state, double *unused, double *out_6700023275112118041) {
   out_6700023275112118041[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3547118740695532620) {
   out_3547118740695532620[0] = 0;
   out_3547118740695532620[1] = 0;
   out_3547118740695532620[2] = 0;
   out_3547118740695532620[3] = 0;
   out_3547118740695532620[4] = 0;
   out_3547118740695532620[5] = 0;
   out_3547118740695532620[6] = 1;
   out_3547118740695532620[7] = 0;
   out_3547118740695532620[8] = 0;
}
void h_24(double *state, double *unused, double *out_3324231918695756867) {
   out_3324231918695756867[0] = state[4];
   out_3324231918695756867[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5772826524674401182) {
   out_5772826524674401182[0] = 0;
   out_5772826524674401182[1] = 0;
   out_5772826524674401182[2] = 0;
   out_5772826524674401182[3] = 0;
   out_5772826524674401182[4] = 1;
   out_5772826524674401182[5] = 0;
   out_5772826524674401182[6] = 0;
   out_5772826524674401182[7] = 0;
   out_5772826524674401182[8] = 0;
   out_5772826524674401182[9] = 0;
   out_5772826524674401182[10] = 0;
   out_5772826524674401182[11] = 0;
   out_5772826524674401182[12] = 0;
   out_5772826524674401182[13] = 0;
   out_5772826524674401182[14] = 1;
   out_5772826524674401182[15] = 0;
   out_5772826524674401182[16] = 0;
   out_5772826524674401182[17] = 0;
}
void h_30(double *state, double *unused, double *out_5158892872121138412) {
   out_5158892872121138412[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7982934991522402241) {
   out_7982934991522402241[0] = 0;
   out_7982934991522402241[1] = 0;
   out_7982934991522402241[2] = 0;
   out_7982934991522402241[3] = 0;
   out_7982934991522402241[4] = 1;
   out_7982934991522402241[5] = 0;
   out_7982934991522402241[6] = 0;
   out_7982934991522402241[7] = 0;
   out_7982934991522402241[8] = 0;
}
void h_26(double *state, double *unused, double *out_1843869831671927367) {
   out_1843869831671927367[0] = state[7];
}
void H_26(double *state, double *unused, double *out_194384578178523604) {
   out_194384578178523604[0] = 0;
   out_194384578178523604[1] = 0;
   out_194384578178523604[2] = 0;
   out_194384578178523604[3] = 0;
   out_194384578178523604[4] = 0;
   out_194384578178523604[5] = 0;
   out_194384578178523604[6] = 0;
   out_194384578178523604[7] = 1;
   out_194384578178523604[8] = 0;
}
void h_27(double *state, double *unused, double *out_6520813582762108628) {
   out_6520813582762108628[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8289045770386724464) {
   out_8289045770386724464[0] = 0;
   out_8289045770386724464[1] = 0;
   out_8289045770386724464[2] = 0;
   out_8289045770386724464[3] = 1;
   out_8289045770386724464[4] = 0;
   out_8289045770386724464[5] = 0;
   out_8289045770386724464[6] = 0;
   out_8289045770386724464[7] = 0;
   out_8289045770386724464[8] = 0;
}
void h_29(double *state, double *unused, double *out_2883364054508086278) {
   out_2883364054508086278[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7472703647208010057) {
   out_7472703647208010057[0] = 0;
   out_7472703647208010057[1] = 1;
   out_7472703647208010057[2] = 0;
   out_7472703647208010057[3] = 0;
   out_7472703647208010057[4] = 0;
   out_7472703647208010057[5] = 0;
   out_7472703647208010057[6] = 0;
   out_7472703647208010057[7] = 0;
   out_7472703647208010057[8] = 0;
}
void h_28(double *state, double *unused, double *out_1678630012218245207) {
   out_1678630012218245207[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5891641409432010985) {
   out_5891641409432010985[0] = 1;
   out_5891641409432010985[1] = 0;
   out_5891641409432010985[2] = 0;
   out_5891641409432010985[3] = 0;
   out_5891641409432010985[4] = 0;
   out_5891641409432010985[5] = 0;
   out_5891641409432010985[6] = 0;
   out_5891641409432010985[7] = 0;
   out_5891641409432010985[8] = 0;
}
void h_31(double *state, double *unused, double *out_3062573746858095691) {
   out_3062573746858095691[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3577764702572493048) {
   out_3577764702572493048[0] = 0;
   out_3577764702572493048[1] = 0;
   out_3577764702572493048[2] = 0;
   out_3577764702572493048[3] = 0;
   out_3577764702572493048[4] = 0;
   out_3577764702572493048[5] = 0;
   out_3577764702572493048[6] = 0;
   out_3577764702572493048[7] = 0;
   out_3577764702572493048[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5180017016346976199) {
  err_fun(nom_x, delta_x, out_5180017016346976199);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8487031610083345537) {
  inv_err_fun(nom_x, true_x, out_8487031610083345537);
}
void car_H_mod_fun(double *state, double *out_5706437107101781759) {
  H_mod_fun(state, out_5706437107101781759);
}
void car_f_fun(double *state, double dt, double *out_1153822413136816832) {
  f_fun(state,  dt, out_1153822413136816832);
}
void car_F_fun(double *state, double dt, double *out_8315107788488877245) {
  F_fun(state,  dt, out_8315107788488877245);
}
void car_h_25(double *state, double *unused, double *out_6700023275112118041) {
  h_25(state, unused, out_6700023275112118041);
}
void car_H_25(double *state, double *unused, double *out_3547118740695532620) {
  H_25(state, unused, out_3547118740695532620);
}
void car_h_24(double *state, double *unused, double *out_3324231918695756867) {
  h_24(state, unused, out_3324231918695756867);
}
void car_H_24(double *state, double *unused, double *out_5772826524674401182) {
  H_24(state, unused, out_5772826524674401182);
}
void car_h_30(double *state, double *unused, double *out_5158892872121138412) {
  h_30(state, unused, out_5158892872121138412);
}
void car_H_30(double *state, double *unused, double *out_7982934991522402241) {
  H_30(state, unused, out_7982934991522402241);
}
void car_h_26(double *state, double *unused, double *out_1843869831671927367) {
  h_26(state, unused, out_1843869831671927367);
}
void car_H_26(double *state, double *unused, double *out_194384578178523604) {
  H_26(state, unused, out_194384578178523604);
}
void car_h_27(double *state, double *unused, double *out_6520813582762108628) {
  h_27(state, unused, out_6520813582762108628);
}
void car_H_27(double *state, double *unused, double *out_8289045770386724464) {
  H_27(state, unused, out_8289045770386724464);
}
void car_h_29(double *state, double *unused, double *out_2883364054508086278) {
  h_29(state, unused, out_2883364054508086278);
}
void car_H_29(double *state, double *unused, double *out_7472703647208010057) {
  H_29(state, unused, out_7472703647208010057);
}
void car_h_28(double *state, double *unused, double *out_1678630012218245207) {
  h_28(state, unused, out_1678630012218245207);
}
void car_H_28(double *state, double *unused, double *out_5891641409432010985) {
  H_28(state, unused, out_5891641409432010985);
}
void car_h_31(double *state, double *unused, double *out_3062573746858095691) {
  h_31(state, unused, out_3062573746858095691);
}
void car_H_31(double *state, double *unused, double *out_3577764702572493048) {
  H_31(state, unused, out_3577764702572493048);
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
