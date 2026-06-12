#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_7744429972371327634) {
   out_7744429972371327634[0] = delta_x[0] + nom_x[0];
   out_7744429972371327634[1] = delta_x[1] + nom_x[1];
   out_7744429972371327634[2] = delta_x[2] + nom_x[2];
   out_7744429972371327634[3] = delta_x[3] + nom_x[3];
   out_7744429972371327634[4] = delta_x[4] + nom_x[4];
   out_7744429972371327634[5] = delta_x[5] + nom_x[5];
   out_7744429972371327634[6] = delta_x[6] + nom_x[6];
   out_7744429972371327634[7] = delta_x[7] + nom_x[7];
   out_7744429972371327634[8] = delta_x[8] + nom_x[8];
   out_7744429972371327634[9] = delta_x[9] + nom_x[9];
   out_7744429972371327634[10] = delta_x[10] + nom_x[10];
   out_7744429972371327634[11] = delta_x[11] + nom_x[11];
   out_7744429972371327634[12] = delta_x[12] + nom_x[12];
   out_7744429972371327634[13] = delta_x[13] + nom_x[13];
   out_7744429972371327634[14] = delta_x[14] + nom_x[14];
   out_7744429972371327634[15] = delta_x[15] + nom_x[15];
   out_7744429972371327634[16] = delta_x[16] + nom_x[16];
   out_7744429972371327634[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8537065090514966302) {
   out_8537065090514966302[0] = -nom_x[0] + true_x[0];
   out_8537065090514966302[1] = -nom_x[1] + true_x[1];
   out_8537065090514966302[2] = -nom_x[2] + true_x[2];
   out_8537065090514966302[3] = -nom_x[3] + true_x[3];
   out_8537065090514966302[4] = -nom_x[4] + true_x[4];
   out_8537065090514966302[5] = -nom_x[5] + true_x[5];
   out_8537065090514966302[6] = -nom_x[6] + true_x[6];
   out_8537065090514966302[7] = -nom_x[7] + true_x[7];
   out_8537065090514966302[8] = -nom_x[8] + true_x[8];
   out_8537065090514966302[9] = -nom_x[9] + true_x[9];
   out_8537065090514966302[10] = -nom_x[10] + true_x[10];
   out_8537065090514966302[11] = -nom_x[11] + true_x[11];
   out_8537065090514966302[12] = -nom_x[12] + true_x[12];
   out_8537065090514966302[13] = -nom_x[13] + true_x[13];
   out_8537065090514966302[14] = -nom_x[14] + true_x[14];
   out_8537065090514966302[15] = -nom_x[15] + true_x[15];
   out_8537065090514966302[16] = -nom_x[16] + true_x[16];
   out_8537065090514966302[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3490805559008343978) {
   out_3490805559008343978[0] = 1.0;
   out_3490805559008343978[1] = 0.0;
   out_3490805559008343978[2] = 0.0;
   out_3490805559008343978[3] = 0.0;
   out_3490805559008343978[4] = 0.0;
   out_3490805559008343978[5] = 0.0;
   out_3490805559008343978[6] = 0.0;
   out_3490805559008343978[7] = 0.0;
   out_3490805559008343978[8] = 0.0;
   out_3490805559008343978[9] = 0.0;
   out_3490805559008343978[10] = 0.0;
   out_3490805559008343978[11] = 0.0;
   out_3490805559008343978[12] = 0.0;
   out_3490805559008343978[13] = 0.0;
   out_3490805559008343978[14] = 0.0;
   out_3490805559008343978[15] = 0.0;
   out_3490805559008343978[16] = 0.0;
   out_3490805559008343978[17] = 0.0;
   out_3490805559008343978[18] = 0.0;
   out_3490805559008343978[19] = 1.0;
   out_3490805559008343978[20] = 0.0;
   out_3490805559008343978[21] = 0.0;
   out_3490805559008343978[22] = 0.0;
   out_3490805559008343978[23] = 0.0;
   out_3490805559008343978[24] = 0.0;
   out_3490805559008343978[25] = 0.0;
   out_3490805559008343978[26] = 0.0;
   out_3490805559008343978[27] = 0.0;
   out_3490805559008343978[28] = 0.0;
   out_3490805559008343978[29] = 0.0;
   out_3490805559008343978[30] = 0.0;
   out_3490805559008343978[31] = 0.0;
   out_3490805559008343978[32] = 0.0;
   out_3490805559008343978[33] = 0.0;
   out_3490805559008343978[34] = 0.0;
   out_3490805559008343978[35] = 0.0;
   out_3490805559008343978[36] = 0.0;
   out_3490805559008343978[37] = 0.0;
   out_3490805559008343978[38] = 1.0;
   out_3490805559008343978[39] = 0.0;
   out_3490805559008343978[40] = 0.0;
   out_3490805559008343978[41] = 0.0;
   out_3490805559008343978[42] = 0.0;
   out_3490805559008343978[43] = 0.0;
   out_3490805559008343978[44] = 0.0;
   out_3490805559008343978[45] = 0.0;
   out_3490805559008343978[46] = 0.0;
   out_3490805559008343978[47] = 0.0;
   out_3490805559008343978[48] = 0.0;
   out_3490805559008343978[49] = 0.0;
   out_3490805559008343978[50] = 0.0;
   out_3490805559008343978[51] = 0.0;
   out_3490805559008343978[52] = 0.0;
   out_3490805559008343978[53] = 0.0;
   out_3490805559008343978[54] = 0.0;
   out_3490805559008343978[55] = 0.0;
   out_3490805559008343978[56] = 0.0;
   out_3490805559008343978[57] = 1.0;
   out_3490805559008343978[58] = 0.0;
   out_3490805559008343978[59] = 0.0;
   out_3490805559008343978[60] = 0.0;
   out_3490805559008343978[61] = 0.0;
   out_3490805559008343978[62] = 0.0;
   out_3490805559008343978[63] = 0.0;
   out_3490805559008343978[64] = 0.0;
   out_3490805559008343978[65] = 0.0;
   out_3490805559008343978[66] = 0.0;
   out_3490805559008343978[67] = 0.0;
   out_3490805559008343978[68] = 0.0;
   out_3490805559008343978[69] = 0.0;
   out_3490805559008343978[70] = 0.0;
   out_3490805559008343978[71] = 0.0;
   out_3490805559008343978[72] = 0.0;
   out_3490805559008343978[73] = 0.0;
   out_3490805559008343978[74] = 0.0;
   out_3490805559008343978[75] = 0.0;
   out_3490805559008343978[76] = 1.0;
   out_3490805559008343978[77] = 0.0;
   out_3490805559008343978[78] = 0.0;
   out_3490805559008343978[79] = 0.0;
   out_3490805559008343978[80] = 0.0;
   out_3490805559008343978[81] = 0.0;
   out_3490805559008343978[82] = 0.0;
   out_3490805559008343978[83] = 0.0;
   out_3490805559008343978[84] = 0.0;
   out_3490805559008343978[85] = 0.0;
   out_3490805559008343978[86] = 0.0;
   out_3490805559008343978[87] = 0.0;
   out_3490805559008343978[88] = 0.0;
   out_3490805559008343978[89] = 0.0;
   out_3490805559008343978[90] = 0.0;
   out_3490805559008343978[91] = 0.0;
   out_3490805559008343978[92] = 0.0;
   out_3490805559008343978[93] = 0.0;
   out_3490805559008343978[94] = 0.0;
   out_3490805559008343978[95] = 1.0;
   out_3490805559008343978[96] = 0.0;
   out_3490805559008343978[97] = 0.0;
   out_3490805559008343978[98] = 0.0;
   out_3490805559008343978[99] = 0.0;
   out_3490805559008343978[100] = 0.0;
   out_3490805559008343978[101] = 0.0;
   out_3490805559008343978[102] = 0.0;
   out_3490805559008343978[103] = 0.0;
   out_3490805559008343978[104] = 0.0;
   out_3490805559008343978[105] = 0.0;
   out_3490805559008343978[106] = 0.0;
   out_3490805559008343978[107] = 0.0;
   out_3490805559008343978[108] = 0.0;
   out_3490805559008343978[109] = 0.0;
   out_3490805559008343978[110] = 0.0;
   out_3490805559008343978[111] = 0.0;
   out_3490805559008343978[112] = 0.0;
   out_3490805559008343978[113] = 0.0;
   out_3490805559008343978[114] = 1.0;
   out_3490805559008343978[115] = 0.0;
   out_3490805559008343978[116] = 0.0;
   out_3490805559008343978[117] = 0.0;
   out_3490805559008343978[118] = 0.0;
   out_3490805559008343978[119] = 0.0;
   out_3490805559008343978[120] = 0.0;
   out_3490805559008343978[121] = 0.0;
   out_3490805559008343978[122] = 0.0;
   out_3490805559008343978[123] = 0.0;
   out_3490805559008343978[124] = 0.0;
   out_3490805559008343978[125] = 0.0;
   out_3490805559008343978[126] = 0.0;
   out_3490805559008343978[127] = 0.0;
   out_3490805559008343978[128] = 0.0;
   out_3490805559008343978[129] = 0.0;
   out_3490805559008343978[130] = 0.0;
   out_3490805559008343978[131] = 0.0;
   out_3490805559008343978[132] = 0.0;
   out_3490805559008343978[133] = 1.0;
   out_3490805559008343978[134] = 0.0;
   out_3490805559008343978[135] = 0.0;
   out_3490805559008343978[136] = 0.0;
   out_3490805559008343978[137] = 0.0;
   out_3490805559008343978[138] = 0.0;
   out_3490805559008343978[139] = 0.0;
   out_3490805559008343978[140] = 0.0;
   out_3490805559008343978[141] = 0.0;
   out_3490805559008343978[142] = 0.0;
   out_3490805559008343978[143] = 0.0;
   out_3490805559008343978[144] = 0.0;
   out_3490805559008343978[145] = 0.0;
   out_3490805559008343978[146] = 0.0;
   out_3490805559008343978[147] = 0.0;
   out_3490805559008343978[148] = 0.0;
   out_3490805559008343978[149] = 0.0;
   out_3490805559008343978[150] = 0.0;
   out_3490805559008343978[151] = 0.0;
   out_3490805559008343978[152] = 1.0;
   out_3490805559008343978[153] = 0.0;
   out_3490805559008343978[154] = 0.0;
   out_3490805559008343978[155] = 0.0;
   out_3490805559008343978[156] = 0.0;
   out_3490805559008343978[157] = 0.0;
   out_3490805559008343978[158] = 0.0;
   out_3490805559008343978[159] = 0.0;
   out_3490805559008343978[160] = 0.0;
   out_3490805559008343978[161] = 0.0;
   out_3490805559008343978[162] = 0.0;
   out_3490805559008343978[163] = 0.0;
   out_3490805559008343978[164] = 0.0;
   out_3490805559008343978[165] = 0.0;
   out_3490805559008343978[166] = 0.0;
   out_3490805559008343978[167] = 0.0;
   out_3490805559008343978[168] = 0.0;
   out_3490805559008343978[169] = 0.0;
   out_3490805559008343978[170] = 0.0;
   out_3490805559008343978[171] = 1.0;
   out_3490805559008343978[172] = 0.0;
   out_3490805559008343978[173] = 0.0;
   out_3490805559008343978[174] = 0.0;
   out_3490805559008343978[175] = 0.0;
   out_3490805559008343978[176] = 0.0;
   out_3490805559008343978[177] = 0.0;
   out_3490805559008343978[178] = 0.0;
   out_3490805559008343978[179] = 0.0;
   out_3490805559008343978[180] = 0.0;
   out_3490805559008343978[181] = 0.0;
   out_3490805559008343978[182] = 0.0;
   out_3490805559008343978[183] = 0.0;
   out_3490805559008343978[184] = 0.0;
   out_3490805559008343978[185] = 0.0;
   out_3490805559008343978[186] = 0.0;
   out_3490805559008343978[187] = 0.0;
   out_3490805559008343978[188] = 0.0;
   out_3490805559008343978[189] = 0.0;
   out_3490805559008343978[190] = 1.0;
   out_3490805559008343978[191] = 0.0;
   out_3490805559008343978[192] = 0.0;
   out_3490805559008343978[193] = 0.0;
   out_3490805559008343978[194] = 0.0;
   out_3490805559008343978[195] = 0.0;
   out_3490805559008343978[196] = 0.0;
   out_3490805559008343978[197] = 0.0;
   out_3490805559008343978[198] = 0.0;
   out_3490805559008343978[199] = 0.0;
   out_3490805559008343978[200] = 0.0;
   out_3490805559008343978[201] = 0.0;
   out_3490805559008343978[202] = 0.0;
   out_3490805559008343978[203] = 0.0;
   out_3490805559008343978[204] = 0.0;
   out_3490805559008343978[205] = 0.0;
   out_3490805559008343978[206] = 0.0;
   out_3490805559008343978[207] = 0.0;
   out_3490805559008343978[208] = 0.0;
   out_3490805559008343978[209] = 1.0;
   out_3490805559008343978[210] = 0.0;
   out_3490805559008343978[211] = 0.0;
   out_3490805559008343978[212] = 0.0;
   out_3490805559008343978[213] = 0.0;
   out_3490805559008343978[214] = 0.0;
   out_3490805559008343978[215] = 0.0;
   out_3490805559008343978[216] = 0.0;
   out_3490805559008343978[217] = 0.0;
   out_3490805559008343978[218] = 0.0;
   out_3490805559008343978[219] = 0.0;
   out_3490805559008343978[220] = 0.0;
   out_3490805559008343978[221] = 0.0;
   out_3490805559008343978[222] = 0.0;
   out_3490805559008343978[223] = 0.0;
   out_3490805559008343978[224] = 0.0;
   out_3490805559008343978[225] = 0.0;
   out_3490805559008343978[226] = 0.0;
   out_3490805559008343978[227] = 0.0;
   out_3490805559008343978[228] = 1.0;
   out_3490805559008343978[229] = 0.0;
   out_3490805559008343978[230] = 0.0;
   out_3490805559008343978[231] = 0.0;
   out_3490805559008343978[232] = 0.0;
   out_3490805559008343978[233] = 0.0;
   out_3490805559008343978[234] = 0.0;
   out_3490805559008343978[235] = 0.0;
   out_3490805559008343978[236] = 0.0;
   out_3490805559008343978[237] = 0.0;
   out_3490805559008343978[238] = 0.0;
   out_3490805559008343978[239] = 0.0;
   out_3490805559008343978[240] = 0.0;
   out_3490805559008343978[241] = 0.0;
   out_3490805559008343978[242] = 0.0;
   out_3490805559008343978[243] = 0.0;
   out_3490805559008343978[244] = 0.0;
   out_3490805559008343978[245] = 0.0;
   out_3490805559008343978[246] = 0.0;
   out_3490805559008343978[247] = 1.0;
   out_3490805559008343978[248] = 0.0;
   out_3490805559008343978[249] = 0.0;
   out_3490805559008343978[250] = 0.0;
   out_3490805559008343978[251] = 0.0;
   out_3490805559008343978[252] = 0.0;
   out_3490805559008343978[253] = 0.0;
   out_3490805559008343978[254] = 0.0;
   out_3490805559008343978[255] = 0.0;
   out_3490805559008343978[256] = 0.0;
   out_3490805559008343978[257] = 0.0;
   out_3490805559008343978[258] = 0.0;
   out_3490805559008343978[259] = 0.0;
   out_3490805559008343978[260] = 0.0;
   out_3490805559008343978[261] = 0.0;
   out_3490805559008343978[262] = 0.0;
   out_3490805559008343978[263] = 0.0;
   out_3490805559008343978[264] = 0.0;
   out_3490805559008343978[265] = 0.0;
   out_3490805559008343978[266] = 1.0;
   out_3490805559008343978[267] = 0.0;
   out_3490805559008343978[268] = 0.0;
   out_3490805559008343978[269] = 0.0;
   out_3490805559008343978[270] = 0.0;
   out_3490805559008343978[271] = 0.0;
   out_3490805559008343978[272] = 0.0;
   out_3490805559008343978[273] = 0.0;
   out_3490805559008343978[274] = 0.0;
   out_3490805559008343978[275] = 0.0;
   out_3490805559008343978[276] = 0.0;
   out_3490805559008343978[277] = 0.0;
   out_3490805559008343978[278] = 0.0;
   out_3490805559008343978[279] = 0.0;
   out_3490805559008343978[280] = 0.0;
   out_3490805559008343978[281] = 0.0;
   out_3490805559008343978[282] = 0.0;
   out_3490805559008343978[283] = 0.0;
   out_3490805559008343978[284] = 0.0;
   out_3490805559008343978[285] = 1.0;
   out_3490805559008343978[286] = 0.0;
   out_3490805559008343978[287] = 0.0;
   out_3490805559008343978[288] = 0.0;
   out_3490805559008343978[289] = 0.0;
   out_3490805559008343978[290] = 0.0;
   out_3490805559008343978[291] = 0.0;
   out_3490805559008343978[292] = 0.0;
   out_3490805559008343978[293] = 0.0;
   out_3490805559008343978[294] = 0.0;
   out_3490805559008343978[295] = 0.0;
   out_3490805559008343978[296] = 0.0;
   out_3490805559008343978[297] = 0.0;
   out_3490805559008343978[298] = 0.0;
   out_3490805559008343978[299] = 0.0;
   out_3490805559008343978[300] = 0.0;
   out_3490805559008343978[301] = 0.0;
   out_3490805559008343978[302] = 0.0;
   out_3490805559008343978[303] = 0.0;
   out_3490805559008343978[304] = 1.0;
   out_3490805559008343978[305] = 0.0;
   out_3490805559008343978[306] = 0.0;
   out_3490805559008343978[307] = 0.0;
   out_3490805559008343978[308] = 0.0;
   out_3490805559008343978[309] = 0.0;
   out_3490805559008343978[310] = 0.0;
   out_3490805559008343978[311] = 0.0;
   out_3490805559008343978[312] = 0.0;
   out_3490805559008343978[313] = 0.0;
   out_3490805559008343978[314] = 0.0;
   out_3490805559008343978[315] = 0.0;
   out_3490805559008343978[316] = 0.0;
   out_3490805559008343978[317] = 0.0;
   out_3490805559008343978[318] = 0.0;
   out_3490805559008343978[319] = 0.0;
   out_3490805559008343978[320] = 0.0;
   out_3490805559008343978[321] = 0.0;
   out_3490805559008343978[322] = 0.0;
   out_3490805559008343978[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_904637507366578298) {
   out_904637507366578298[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_904637507366578298[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_904637507366578298[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_904637507366578298[3] = dt*state[12] + state[3];
   out_904637507366578298[4] = dt*state[13] + state[4];
   out_904637507366578298[5] = dt*state[14] + state[5];
   out_904637507366578298[6] = state[6];
   out_904637507366578298[7] = state[7];
   out_904637507366578298[8] = state[8];
   out_904637507366578298[9] = state[9];
   out_904637507366578298[10] = state[10];
   out_904637507366578298[11] = state[11];
   out_904637507366578298[12] = state[12];
   out_904637507366578298[13] = state[13];
   out_904637507366578298[14] = state[14];
   out_904637507366578298[15] = state[15];
   out_904637507366578298[16] = state[16];
   out_904637507366578298[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1053199935176261758) {
   out_1053199935176261758[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1053199935176261758[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1053199935176261758[2] = 0;
   out_1053199935176261758[3] = 0;
   out_1053199935176261758[4] = 0;
   out_1053199935176261758[5] = 0;
   out_1053199935176261758[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1053199935176261758[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1053199935176261758[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1053199935176261758[9] = 0;
   out_1053199935176261758[10] = 0;
   out_1053199935176261758[11] = 0;
   out_1053199935176261758[12] = 0;
   out_1053199935176261758[13] = 0;
   out_1053199935176261758[14] = 0;
   out_1053199935176261758[15] = 0;
   out_1053199935176261758[16] = 0;
   out_1053199935176261758[17] = 0;
   out_1053199935176261758[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1053199935176261758[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1053199935176261758[20] = 0;
   out_1053199935176261758[21] = 0;
   out_1053199935176261758[22] = 0;
   out_1053199935176261758[23] = 0;
   out_1053199935176261758[24] = 0;
   out_1053199935176261758[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1053199935176261758[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1053199935176261758[27] = 0;
   out_1053199935176261758[28] = 0;
   out_1053199935176261758[29] = 0;
   out_1053199935176261758[30] = 0;
   out_1053199935176261758[31] = 0;
   out_1053199935176261758[32] = 0;
   out_1053199935176261758[33] = 0;
   out_1053199935176261758[34] = 0;
   out_1053199935176261758[35] = 0;
   out_1053199935176261758[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1053199935176261758[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1053199935176261758[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1053199935176261758[39] = 0;
   out_1053199935176261758[40] = 0;
   out_1053199935176261758[41] = 0;
   out_1053199935176261758[42] = 0;
   out_1053199935176261758[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1053199935176261758[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1053199935176261758[45] = 0;
   out_1053199935176261758[46] = 0;
   out_1053199935176261758[47] = 0;
   out_1053199935176261758[48] = 0;
   out_1053199935176261758[49] = 0;
   out_1053199935176261758[50] = 0;
   out_1053199935176261758[51] = 0;
   out_1053199935176261758[52] = 0;
   out_1053199935176261758[53] = 0;
   out_1053199935176261758[54] = 0;
   out_1053199935176261758[55] = 0;
   out_1053199935176261758[56] = 0;
   out_1053199935176261758[57] = 1;
   out_1053199935176261758[58] = 0;
   out_1053199935176261758[59] = 0;
   out_1053199935176261758[60] = 0;
   out_1053199935176261758[61] = 0;
   out_1053199935176261758[62] = 0;
   out_1053199935176261758[63] = 0;
   out_1053199935176261758[64] = 0;
   out_1053199935176261758[65] = 0;
   out_1053199935176261758[66] = dt;
   out_1053199935176261758[67] = 0;
   out_1053199935176261758[68] = 0;
   out_1053199935176261758[69] = 0;
   out_1053199935176261758[70] = 0;
   out_1053199935176261758[71] = 0;
   out_1053199935176261758[72] = 0;
   out_1053199935176261758[73] = 0;
   out_1053199935176261758[74] = 0;
   out_1053199935176261758[75] = 0;
   out_1053199935176261758[76] = 1;
   out_1053199935176261758[77] = 0;
   out_1053199935176261758[78] = 0;
   out_1053199935176261758[79] = 0;
   out_1053199935176261758[80] = 0;
   out_1053199935176261758[81] = 0;
   out_1053199935176261758[82] = 0;
   out_1053199935176261758[83] = 0;
   out_1053199935176261758[84] = 0;
   out_1053199935176261758[85] = dt;
   out_1053199935176261758[86] = 0;
   out_1053199935176261758[87] = 0;
   out_1053199935176261758[88] = 0;
   out_1053199935176261758[89] = 0;
   out_1053199935176261758[90] = 0;
   out_1053199935176261758[91] = 0;
   out_1053199935176261758[92] = 0;
   out_1053199935176261758[93] = 0;
   out_1053199935176261758[94] = 0;
   out_1053199935176261758[95] = 1;
   out_1053199935176261758[96] = 0;
   out_1053199935176261758[97] = 0;
   out_1053199935176261758[98] = 0;
   out_1053199935176261758[99] = 0;
   out_1053199935176261758[100] = 0;
   out_1053199935176261758[101] = 0;
   out_1053199935176261758[102] = 0;
   out_1053199935176261758[103] = 0;
   out_1053199935176261758[104] = dt;
   out_1053199935176261758[105] = 0;
   out_1053199935176261758[106] = 0;
   out_1053199935176261758[107] = 0;
   out_1053199935176261758[108] = 0;
   out_1053199935176261758[109] = 0;
   out_1053199935176261758[110] = 0;
   out_1053199935176261758[111] = 0;
   out_1053199935176261758[112] = 0;
   out_1053199935176261758[113] = 0;
   out_1053199935176261758[114] = 1;
   out_1053199935176261758[115] = 0;
   out_1053199935176261758[116] = 0;
   out_1053199935176261758[117] = 0;
   out_1053199935176261758[118] = 0;
   out_1053199935176261758[119] = 0;
   out_1053199935176261758[120] = 0;
   out_1053199935176261758[121] = 0;
   out_1053199935176261758[122] = 0;
   out_1053199935176261758[123] = 0;
   out_1053199935176261758[124] = 0;
   out_1053199935176261758[125] = 0;
   out_1053199935176261758[126] = 0;
   out_1053199935176261758[127] = 0;
   out_1053199935176261758[128] = 0;
   out_1053199935176261758[129] = 0;
   out_1053199935176261758[130] = 0;
   out_1053199935176261758[131] = 0;
   out_1053199935176261758[132] = 0;
   out_1053199935176261758[133] = 1;
   out_1053199935176261758[134] = 0;
   out_1053199935176261758[135] = 0;
   out_1053199935176261758[136] = 0;
   out_1053199935176261758[137] = 0;
   out_1053199935176261758[138] = 0;
   out_1053199935176261758[139] = 0;
   out_1053199935176261758[140] = 0;
   out_1053199935176261758[141] = 0;
   out_1053199935176261758[142] = 0;
   out_1053199935176261758[143] = 0;
   out_1053199935176261758[144] = 0;
   out_1053199935176261758[145] = 0;
   out_1053199935176261758[146] = 0;
   out_1053199935176261758[147] = 0;
   out_1053199935176261758[148] = 0;
   out_1053199935176261758[149] = 0;
   out_1053199935176261758[150] = 0;
   out_1053199935176261758[151] = 0;
   out_1053199935176261758[152] = 1;
   out_1053199935176261758[153] = 0;
   out_1053199935176261758[154] = 0;
   out_1053199935176261758[155] = 0;
   out_1053199935176261758[156] = 0;
   out_1053199935176261758[157] = 0;
   out_1053199935176261758[158] = 0;
   out_1053199935176261758[159] = 0;
   out_1053199935176261758[160] = 0;
   out_1053199935176261758[161] = 0;
   out_1053199935176261758[162] = 0;
   out_1053199935176261758[163] = 0;
   out_1053199935176261758[164] = 0;
   out_1053199935176261758[165] = 0;
   out_1053199935176261758[166] = 0;
   out_1053199935176261758[167] = 0;
   out_1053199935176261758[168] = 0;
   out_1053199935176261758[169] = 0;
   out_1053199935176261758[170] = 0;
   out_1053199935176261758[171] = 1;
   out_1053199935176261758[172] = 0;
   out_1053199935176261758[173] = 0;
   out_1053199935176261758[174] = 0;
   out_1053199935176261758[175] = 0;
   out_1053199935176261758[176] = 0;
   out_1053199935176261758[177] = 0;
   out_1053199935176261758[178] = 0;
   out_1053199935176261758[179] = 0;
   out_1053199935176261758[180] = 0;
   out_1053199935176261758[181] = 0;
   out_1053199935176261758[182] = 0;
   out_1053199935176261758[183] = 0;
   out_1053199935176261758[184] = 0;
   out_1053199935176261758[185] = 0;
   out_1053199935176261758[186] = 0;
   out_1053199935176261758[187] = 0;
   out_1053199935176261758[188] = 0;
   out_1053199935176261758[189] = 0;
   out_1053199935176261758[190] = 1;
   out_1053199935176261758[191] = 0;
   out_1053199935176261758[192] = 0;
   out_1053199935176261758[193] = 0;
   out_1053199935176261758[194] = 0;
   out_1053199935176261758[195] = 0;
   out_1053199935176261758[196] = 0;
   out_1053199935176261758[197] = 0;
   out_1053199935176261758[198] = 0;
   out_1053199935176261758[199] = 0;
   out_1053199935176261758[200] = 0;
   out_1053199935176261758[201] = 0;
   out_1053199935176261758[202] = 0;
   out_1053199935176261758[203] = 0;
   out_1053199935176261758[204] = 0;
   out_1053199935176261758[205] = 0;
   out_1053199935176261758[206] = 0;
   out_1053199935176261758[207] = 0;
   out_1053199935176261758[208] = 0;
   out_1053199935176261758[209] = 1;
   out_1053199935176261758[210] = 0;
   out_1053199935176261758[211] = 0;
   out_1053199935176261758[212] = 0;
   out_1053199935176261758[213] = 0;
   out_1053199935176261758[214] = 0;
   out_1053199935176261758[215] = 0;
   out_1053199935176261758[216] = 0;
   out_1053199935176261758[217] = 0;
   out_1053199935176261758[218] = 0;
   out_1053199935176261758[219] = 0;
   out_1053199935176261758[220] = 0;
   out_1053199935176261758[221] = 0;
   out_1053199935176261758[222] = 0;
   out_1053199935176261758[223] = 0;
   out_1053199935176261758[224] = 0;
   out_1053199935176261758[225] = 0;
   out_1053199935176261758[226] = 0;
   out_1053199935176261758[227] = 0;
   out_1053199935176261758[228] = 1;
   out_1053199935176261758[229] = 0;
   out_1053199935176261758[230] = 0;
   out_1053199935176261758[231] = 0;
   out_1053199935176261758[232] = 0;
   out_1053199935176261758[233] = 0;
   out_1053199935176261758[234] = 0;
   out_1053199935176261758[235] = 0;
   out_1053199935176261758[236] = 0;
   out_1053199935176261758[237] = 0;
   out_1053199935176261758[238] = 0;
   out_1053199935176261758[239] = 0;
   out_1053199935176261758[240] = 0;
   out_1053199935176261758[241] = 0;
   out_1053199935176261758[242] = 0;
   out_1053199935176261758[243] = 0;
   out_1053199935176261758[244] = 0;
   out_1053199935176261758[245] = 0;
   out_1053199935176261758[246] = 0;
   out_1053199935176261758[247] = 1;
   out_1053199935176261758[248] = 0;
   out_1053199935176261758[249] = 0;
   out_1053199935176261758[250] = 0;
   out_1053199935176261758[251] = 0;
   out_1053199935176261758[252] = 0;
   out_1053199935176261758[253] = 0;
   out_1053199935176261758[254] = 0;
   out_1053199935176261758[255] = 0;
   out_1053199935176261758[256] = 0;
   out_1053199935176261758[257] = 0;
   out_1053199935176261758[258] = 0;
   out_1053199935176261758[259] = 0;
   out_1053199935176261758[260] = 0;
   out_1053199935176261758[261] = 0;
   out_1053199935176261758[262] = 0;
   out_1053199935176261758[263] = 0;
   out_1053199935176261758[264] = 0;
   out_1053199935176261758[265] = 0;
   out_1053199935176261758[266] = 1;
   out_1053199935176261758[267] = 0;
   out_1053199935176261758[268] = 0;
   out_1053199935176261758[269] = 0;
   out_1053199935176261758[270] = 0;
   out_1053199935176261758[271] = 0;
   out_1053199935176261758[272] = 0;
   out_1053199935176261758[273] = 0;
   out_1053199935176261758[274] = 0;
   out_1053199935176261758[275] = 0;
   out_1053199935176261758[276] = 0;
   out_1053199935176261758[277] = 0;
   out_1053199935176261758[278] = 0;
   out_1053199935176261758[279] = 0;
   out_1053199935176261758[280] = 0;
   out_1053199935176261758[281] = 0;
   out_1053199935176261758[282] = 0;
   out_1053199935176261758[283] = 0;
   out_1053199935176261758[284] = 0;
   out_1053199935176261758[285] = 1;
   out_1053199935176261758[286] = 0;
   out_1053199935176261758[287] = 0;
   out_1053199935176261758[288] = 0;
   out_1053199935176261758[289] = 0;
   out_1053199935176261758[290] = 0;
   out_1053199935176261758[291] = 0;
   out_1053199935176261758[292] = 0;
   out_1053199935176261758[293] = 0;
   out_1053199935176261758[294] = 0;
   out_1053199935176261758[295] = 0;
   out_1053199935176261758[296] = 0;
   out_1053199935176261758[297] = 0;
   out_1053199935176261758[298] = 0;
   out_1053199935176261758[299] = 0;
   out_1053199935176261758[300] = 0;
   out_1053199935176261758[301] = 0;
   out_1053199935176261758[302] = 0;
   out_1053199935176261758[303] = 0;
   out_1053199935176261758[304] = 1;
   out_1053199935176261758[305] = 0;
   out_1053199935176261758[306] = 0;
   out_1053199935176261758[307] = 0;
   out_1053199935176261758[308] = 0;
   out_1053199935176261758[309] = 0;
   out_1053199935176261758[310] = 0;
   out_1053199935176261758[311] = 0;
   out_1053199935176261758[312] = 0;
   out_1053199935176261758[313] = 0;
   out_1053199935176261758[314] = 0;
   out_1053199935176261758[315] = 0;
   out_1053199935176261758[316] = 0;
   out_1053199935176261758[317] = 0;
   out_1053199935176261758[318] = 0;
   out_1053199935176261758[319] = 0;
   out_1053199935176261758[320] = 0;
   out_1053199935176261758[321] = 0;
   out_1053199935176261758[322] = 0;
   out_1053199935176261758[323] = 1;
}
void h_4(double *state, double *unused, double *out_5407864488122211268) {
   out_5407864488122211268[0] = state[6] + state[9];
   out_5407864488122211268[1] = state[7] + state[10];
   out_5407864488122211268[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_281001650835563594) {
   out_281001650835563594[0] = 0;
   out_281001650835563594[1] = 0;
   out_281001650835563594[2] = 0;
   out_281001650835563594[3] = 0;
   out_281001650835563594[4] = 0;
   out_281001650835563594[5] = 0;
   out_281001650835563594[6] = 1;
   out_281001650835563594[7] = 0;
   out_281001650835563594[8] = 0;
   out_281001650835563594[9] = 1;
   out_281001650835563594[10] = 0;
   out_281001650835563594[11] = 0;
   out_281001650835563594[12] = 0;
   out_281001650835563594[13] = 0;
   out_281001650835563594[14] = 0;
   out_281001650835563594[15] = 0;
   out_281001650835563594[16] = 0;
   out_281001650835563594[17] = 0;
   out_281001650835563594[18] = 0;
   out_281001650835563594[19] = 0;
   out_281001650835563594[20] = 0;
   out_281001650835563594[21] = 0;
   out_281001650835563594[22] = 0;
   out_281001650835563594[23] = 0;
   out_281001650835563594[24] = 0;
   out_281001650835563594[25] = 1;
   out_281001650835563594[26] = 0;
   out_281001650835563594[27] = 0;
   out_281001650835563594[28] = 1;
   out_281001650835563594[29] = 0;
   out_281001650835563594[30] = 0;
   out_281001650835563594[31] = 0;
   out_281001650835563594[32] = 0;
   out_281001650835563594[33] = 0;
   out_281001650835563594[34] = 0;
   out_281001650835563594[35] = 0;
   out_281001650835563594[36] = 0;
   out_281001650835563594[37] = 0;
   out_281001650835563594[38] = 0;
   out_281001650835563594[39] = 0;
   out_281001650835563594[40] = 0;
   out_281001650835563594[41] = 0;
   out_281001650835563594[42] = 0;
   out_281001650835563594[43] = 0;
   out_281001650835563594[44] = 1;
   out_281001650835563594[45] = 0;
   out_281001650835563594[46] = 0;
   out_281001650835563594[47] = 1;
   out_281001650835563594[48] = 0;
   out_281001650835563594[49] = 0;
   out_281001650835563594[50] = 0;
   out_281001650835563594[51] = 0;
   out_281001650835563594[52] = 0;
   out_281001650835563594[53] = 0;
}
void h_10(double *state, double *unused, double *out_3236269100831306834) {
   out_3236269100831306834[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3236269100831306834[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3236269100831306834[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3078753176381222045) {
   out_3078753176381222045[0] = 0;
   out_3078753176381222045[1] = 9.8100000000000005*cos(state[1]);
   out_3078753176381222045[2] = 0;
   out_3078753176381222045[3] = 0;
   out_3078753176381222045[4] = -state[8];
   out_3078753176381222045[5] = state[7];
   out_3078753176381222045[6] = 0;
   out_3078753176381222045[7] = state[5];
   out_3078753176381222045[8] = -state[4];
   out_3078753176381222045[9] = 0;
   out_3078753176381222045[10] = 0;
   out_3078753176381222045[11] = 0;
   out_3078753176381222045[12] = 1;
   out_3078753176381222045[13] = 0;
   out_3078753176381222045[14] = 0;
   out_3078753176381222045[15] = 1;
   out_3078753176381222045[16] = 0;
   out_3078753176381222045[17] = 0;
   out_3078753176381222045[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3078753176381222045[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3078753176381222045[20] = 0;
   out_3078753176381222045[21] = state[8];
   out_3078753176381222045[22] = 0;
   out_3078753176381222045[23] = -state[6];
   out_3078753176381222045[24] = -state[5];
   out_3078753176381222045[25] = 0;
   out_3078753176381222045[26] = state[3];
   out_3078753176381222045[27] = 0;
   out_3078753176381222045[28] = 0;
   out_3078753176381222045[29] = 0;
   out_3078753176381222045[30] = 0;
   out_3078753176381222045[31] = 1;
   out_3078753176381222045[32] = 0;
   out_3078753176381222045[33] = 0;
   out_3078753176381222045[34] = 1;
   out_3078753176381222045[35] = 0;
   out_3078753176381222045[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3078753176381222045[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3078753176381222045[38] = 0;
   out_3078753176381222045[39] = -state[7];
   out_3078753176381222045[40] = state[6];
   out_3078753176381222045[41] = 0;
   out_3078753176381222045[42] = state[4];
   out_3078753176381222045[43] = -state[3];
   out_3078753176381222045[44] = 0;
   out_3078753176381222045[45] = 0;
   out_3078753176381222045[46] = 0;
   out_3078753176381222045[47] = 0;
   out_3078753176381222045[48] = 0;
   out_3078753176381222045[49] = 0;
   out_3078753176381222045[50] = 1;
   out_3078753176381222045[51] = 0;
   out_3078753176381222045[52] = 0;
   out_3078753176381222045[53] = 1;
}
void h_13(double *state, double *unused, double *out_8498957831141607887) {
   out_8498957831141607887[0] = state[3];
   out_8498957831141607887[1] = state[4];
   out_8498957831141607887[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3493275476167896395) {
   out_3493275476167896395[0] = 0;
   out_3493275476167896395[1] = 0;
   out_3493275476167896395[2] = 0;
   out_3493275476167896395[3] = 1;
   out_3493275476167896395[4] = 0;
   out_3493275476167896395[5] = 0;
   out_3493275476167896395[6] = 0;
   out_3493275476167896395[7] = 0;
   out_3493275476167896395[8] = 0;
   out_3493275476167896395[9] = 0;
   out_3493275476167896395[10] = 0;
   out_3493275476167896395[11] = 0;
   out_3493275476167896395[12] = 0;
   out_3493275476167896395[13] = 0;
   out_3493275476167896395[14] = 0;
   out_3493275476167896395[15] = 0;
   out_3493275476167896395[16] = 0;
   out_3493275476167896395[17] = 0;
   out_3493275476167896395[18] = 0;
   out_3493275476167896395[19] = 0;
   out_3493275476167896395[20] = 0;
   out_3493275476167896395[21] = 0;
   out_3493275476167896395[22] = 1;
   out_3493275476167896395[23] = 0;
   out_3493275476167896395[24] = 0;
   out_3493275476167896395[25] = 0;
   out_3493275476167896395[26] = 0;
   out_3493275476167896395[27] = 0;
   out_3493275476167896395[28] = 0;
   out_3493275476167896395[29] = 0;
   out_3493275476167896395[30] = 0;
   out_3493275476167896395[31] = 0;
   out_3493275476167896395[32] = 0;
   out_3493275476167896395[33] = 0;
   out_3493275476167896395[34] = 0;
   out_3493275476167896395[35] = 0;
   out_3493275476167896395[36] = 0;
   out_3493275476167896395[37] = 0;
   out_3493275476167896395[38] = 0;
   out_3493275476167896395[39] = 0;
   out_3493275476167896395[40] = 0;
   out_3493275476167896395[41] = 1;
   out_3493275476167896395[42] = 0;
   out_3493275476167896395[43] = 0;
   out_3493275476167896395[44] = 0;
   out_3493275476167896395[45] = 0;
   out_3493275476167896395[46] = 0;
   out_3493275476167896395[47] = 0;
   out_3493275476167896395[48] = 0;
   out_3493275476167896395[49] = 0;
   out_3493275476167896395[50] = 0;
   out_3493275476167896395[51] = 0;
   out_3493275476167896395[52] = 0;
   out_3493275476167896395[53] = 0;
}
void h_14(double *state, double *unused, double *out_9161980078330107534) {
   out_9161980078330107534[0] = state[6];
   out_9161980078330107534[1] = state[7];
   out_9161980078330107534[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4244242507175048123) {
   out_4244242507175048123[0] = 0;
   out_4244242507175048123[1] = 0;
   out_4244242507175048123[2] = 0;
   out_4244242507175048123[3] = 0;
   out_4244242507175048123[4] = 0;
   out_4244242507175048123[5] = 0;
   out_4244242507175048123[6] = 1;
   out_4244242507175048123[7] = 0;
   out_4244242507175048123[8] = 0;
   out_4244242507175048123[9] = 0;
   out_4244242507175048123[10] = 0;
   out_4244242507175048123[11] = 0;
   out_4244242507175048123[12] = 0;
   out_4244242507175048123[13] = 0;
   out_4244242507175048123[14] = 0;
   out_4244242507175048123[15] = 0;
   out_4244242507175048123[16] = 0;
   out_4244242507175048123[17] = 0;
   out_4244242507175048123[18] = 0;
   out_4244242507175048123[19] = 0;
   out_4244242507175048123[20] = 0;
   out_4244242507175048123[21] = 0;
   out_4244242507175048123[22] = 0;
   out_4244242507175048123[23] = 0;
   out_4244242507175048123[24] = 0;
   out_4244242507175048123[25] = 1;
   out_4244242507175048123[26] = 0;
   out_4244242507175048123[27] = 0;
   out_4244242507175048123[28] = 0;
   out_4244242507175048123[29] = 0;
   out_4244242507175048123[30] = 0;
   out_4244242507175048123[31] = 0;
   out_4244242507175048123[32] = 0;
   out_4244242507175048123[33] = 0;
   out_4244242507175048123[34] = 0;
   out_4244242507175048123[35] = 0;
   out_4244242507175048123[36] = 0;
   out_4244242507175048123[37] = 0;
   out_4244242507175048123[38] = 0;
   out_4244242507175048123[39] = 0;
   out_4244242507175048123[40] = 0;
   out_4244242507175048123[41] = 0;
   out_4244242507175048123[42] = 0;
   out_4244242507175048123[43] = 0;
   out_4244242507175048123[44] = 1;
   out_4244242507175048123[45] = 0;
   out_4244242507175048123[46] = 0;
   out_4244242507175048123[47] = 0;
   out_4244242507175048123[48] = 0;
   out_4244242507175048123[49] = 0;
   out_4244242507175048123[50] = 0;
   out_4244242507175048123[51] = 0;
   out_4244242507175048123[52] = 0;
   out_4244242507175048123[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_7744429972371327634) {
  err_fun(nom_x, delta_x, out_7744429972371327634);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8537065090514966302) {
  inv_err_fun(nom_x, true_x, out_8537065090514966302);
}
void pose_H_mod_fun(double *state, double *out_3490805559008343978) {
  H_mod_fun(state, out_3490805559008343978);
}
void pose_f_fun(double *state, double dt, double *out_904637507366578298) {
  f_fun(state,  dt, out_904637507366578298);
}
void pose_F_fun(double *state, double dt, double *out_1053199935176261758) {
  F_fun(state,  dt, out_1053199935176261758);
}
void pose_h_4(double *state, double *unused, double *out_5407864488122211268) {
  h_4(state, unused, out_5407864488122211268);
}
void pose_H_4(double *state, double *unused, double *out_281001650835563594) {
  H_4(state, unused, out_281001650835563594);
}
void pose_h_10(double *state, double *unused, double *out_3236269100831306834) {
  h_10(state, unused, out_3236269100831306834);
}
void pose_H_10(double *state, double *unused, double *out_3078753176381222045) {
  H_10(state, unused, out_3078753176381222045);
}
void pose_h_13(double *state, double *unused, double *out_8498957831141607887) {
  h_13(state, unused, out_8498957831141607887);
}
void pose_H_13(double *state, double *unused, double *out_3493275476167896395) {
  H_13(state, unused, out_3493275476167896395);
}
void pose_h_14(double *state, double *unused, double *out_9161980078330107534) {
  h_14(state, unused, out_9161980078330107534);
}
void pose_H_14(double *state, double *unused, double *out_4244242507175048123) {
  H_14(state, unused, out_4244242507175048123);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
