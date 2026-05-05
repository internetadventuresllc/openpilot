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
void err_fun(double *nom_x, double *delta_x, double *out_1524410796143659703) {
   out_1524410796143659703[0] = delta_x[0] + nom_x[0];
   out_1524410796143659703[1] = delta_x[1] + nom_x[1];
   out_1524410796143659703[2] = delta_x[2] + nom_x[2];
   out_1524410796143659703[3] = delta_x[3] + nom_x[3];
   out_1524410796143659703[4] = delta_x[4] + nom_x[4];
   out_1524410796143659703[5] = delta_x[5] + nom_x[5];
   out_1524410796143659703[6] = delta_x[6] + nom_x[6];
   out_1524410796143659703[7] = delta_x[7] + nom_x[7];
   out_1524410796143659703[8] = delta_x[8] + nom_x[8];
   out_1524410796143659703[9] = delta_x[9] + nom_x[9];
   out_1524410796143659703[10] = delta_x[10] + nom_x[10];
   out_1524410796143659703[11] = delta_x[11] + nom_x[11];
   out_1524410796143659703[12] = delta_x[12] + nom_x[12];
   out_1524410796143659703[13] = delta_x[13] + nom_x[13];
   out_1524410796143659703[14] = delta_x[14] + nom_x[14];
   out_1524410796143659703[15] = delta_x[15] + nom_x[15];
   out_1524410796143659703[16] = delta_x[16] + nom_x[16];
   out_1524410796143659703[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7721887411546703304) {
   out_7721887411546703304[0] = -nom_x[0] + true_x[0];
   out_7721887411546703304[1] = -nom_x[1] + true_x[1];
   out_7721887411546703304[2] = -nom_x[2] + true_x[2];
   out_7721887411546703304[3] = -nom_x[3] + true_x[3];
   out_7721887411546703304[4] = -nom_x[4] + true_x[4];
   out_7721887411546703304[5] = -nom_x[5] + true_x[5];
   out_7721887411546703304[6] = -nom_x[6] + true_x[6];
   out_7721887411546703304[7] = -nom_x[7] + true_x[7];
   out_7721887411546703304[8] = -nom_x[8] + true_x[8];
   out_7721887411546703304[9] = -nom_x[9] + true_x[9];
   out_7721887411546703304[10] = -nom_x[10] + true_x[10];
   out_7721887411546703304[11] = -nom_x[11] + true_x[11];
   out_7721887411546703304[12] = -nom_x[12] + true_x[12];
   out_7721887411546703304[13] = -nom_x[13] + true_x[13];
   out_7721887411546703304[14] = -nom_x[14] + true_x[14];
   out_7721887411546703304[15] = -nom_x[15] + true_x[15];
   out_7721887411546703304[16] = -nom_x[16] + true_x[16];
   out_7721887411546703304[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3381743124655291129) {
   out_3381743124655291129[0] = 1.0;
   out_3381743124655291129[1] = 0.0;
   out_3381743124655291129[2] = 0.0;
   out_3381743124655291129[3] = 0.0;
   out_3381743124655291129[4] = 0.0;
   out_3381743124655291129[5] = 0.0;
   out_3381743124655291129[6] = 0.0;
   out_3381743124655291129[7] = 0.0;
   out_3381743124655291129[8] = 0.0;
   out_3381743124655291129[9] = 0.0;
   out_3381743124655291129[10] = 0.0;
   out_3381743124655291129[11] = 0.0;
   out_3381743124655291129[12] = 0.0;
   out_3381743124655291129[13] = 0.0;
   out_3381743124655291129[14] = 0.0;
   out_3381743124655291129[15] = 0.0;
   out_3381743124655291129[16] = 0.0;
   out_3381743124655291129[17] = 0.0;
   out_3381743124655291129[18] = 0.0;
   out_3381743124655291129[19] = 1.0;
   out_3381743124655291129[20] = 0.0;
   out_3381743124655291129[21] = 0.0;
   out_3381743124655291129[22] = 0.0;
   out_3381743124655291129[23] = 0.0;
   out_3381743124655291129[24] = 0.0;
   out_3381743124655291129[25] = 0.0;
   out_3381743124655291129[26] = 0.0;
   out_3381743124655291129[27] = 0.0;
   out_3381743124655291129[28] = 0.0;
   out_3381743124655291129[29] = 0.0;
   out_3381743124655291129[30] = 0.0;
   out_3381743124655291129[31] = 0.0;
   out_3381743124655291129[32] = 0.0;
   out_3381743124655291129[33] = 0.0;
   out_3381743124655291129[34] = 0.0;
   out_3381743124655291129[35] = 0.0;
   out_3381743124655291129[36] = 0.0;
   out_3381743124655291129[37] = 0.0;
   out_3381743124655291129[38] = 1.0;
   out_3381743124655291129[39] = 0.0;
   out_3381743124655291129[40] = 0.0;
   out_3381743124655291129[41] = 0.0;
   out_3381743124655291129[42] = 0.0;
   out_3381743124655291129[43] = 0.0;
   out_3381743124655291129[44] = 0.0;
   out_3381743124655291129[45] = 0.0;
   out_3381743124655291129[46] = 0.0;
   out_3381743124655291129[47] = 0.0;
   out_3381743124655291129[48] = 0.0;
   out_3381743124655291129[49] = 0.0;
   out_3381743124655291129[50] = 0.0;
   out_3381743124655291129[51] = 0.0;
   out_3381743124655291129[52] = 0.0;
   out_3381743124655291129[53] = 0.0;
   out_3381743124655291129[54] = 0.0;
   out_3381743124655291129[55] = 0.0;
   out_3381743124655291129[56] = 0.0;
   out_3381743124655291129[57] = 1.0;
   out_3381743124655291129[58] = 0.0;
   out_3381743124655291129[59] = 0.0;
   out_3381743124655291129[60] = 0.0;
   out_3381743124655291129[61] = 0.0;
   out_3381743124655291129[62] = 0.0;
   out_3381743124655291129[63] = 0.0;
   out_3381743124655291129[64] = 0.0;
   out_3381743124655291129[65] = 0.0;
   out_3381743124655291129[66] = 0.0;
   out_3381743124655291129[67] = 0.0;
   out_3381743124655291129[68] = 0.0;
   out_3381743124655291129[69] = 0.0;
   out_3381743124655291129[70] = 0.0;
   out_3381743124655291129[71] = 0.0;
   out_3381743124655291129[72] = 0.0;
   out_3381743124655291129[73] = 0.0;
   out_3381743124655291129[74] = 0.0;
   out_3381743124655291129[75] = 0.0;
   out_3381743124655291129[76] = 1.0;
   out_3381743124655291129[77] = 0.0;
   out_3381743124655291129[78] = 0.0;
   out_3381743124655291129[79] = 0.0;
   out_3381743124655291129[80] = 0.0;
   out_3381743124655291129[81] = 0.0;
   out_3381743124655291129[82] = 0.0;
   out_3381743124655291129[83] = 0.0;
   out_3381743124655291129[84] = 0.0;
   out_3381743124655291129[85] = 0.0;
   out_3381743124655291129[86] = 0.0;
   out_3381743124655291129[87] = 0.0;
   out_3381743124655291129[88] = 0.0;
   out_3381743124655291129[89] = 0.0;
   out_3381743124655291129[90] = 0.0;
   out_3381743124655291129[91] = 0.0;
   out_3381743124655291129[92] = 0.0;
   out_3381743124655291129[93] = 0.0;
   out_3381743124655291129[94] = 0.0;
   out_3381743124655291129[95] = 1.0;
   out_3381743124655291129[96] = 0.0;
   out_3381743124655291129[97] = 0.0;
   out_3381743124655291129[98] = 0.0;
   out_3381743124655291129[99] = 0.0;
   out_3381743124655291129[100] = 0.0;
   out_3381743124655291129[101] = 0.0;
   out_3381743124655291129[102] = 0.0;
   out_3381743124655291129[103] = 0.0;
   out_3381743124655291129[104] = 0.0;
   out_3381743124655291129[105] = 0.0;
   out_3381743124655291129[106] = 0.0;
   out_3381743124655291129[107] = 0.0;
   out_3381743124655291129[108] = 0.0;
   out_3381743124655291129[109] = 0.0;
   out_3381743124655291129[110] = 0.0;
   out_3381743124655291129[111] = 0.0;
   out_3381743124655291129[112] = 0.0;
   out_3381743124655291129[113] = 0.0;
   out_3381743124655291129[114] = 1.0;
   out_3381743124655291129[115] = 0.0;
   out_3381743124655291129[116] = 0.0;
   out_3381743124655291129[117] = 0.0;
   out_3381743124655291129[118] = 0.0;
   out_3381743124655291129[119] = 0.0;
   out_3381743124655291129[120] = 0.0;
   out_3381743124655291129[121] = 0.0;
   out_3381743124655291129[122] = 0.0;
   out_3381743124655291129[123] = 0.0;
   out_3381743124655291129[124] = 0.0;
   out_3381743124655291129[125] = 0.0;
   out_3381743124655291129[126] = 0.0;
   out_3381743124655291129[127] = 0.0;
   out_3381743124655291129[128] = 0.0;
   out_3381743124655291129[129] = 0.0;
   out_3381743124655291129[130] = 0.0;
   out_3381743124655291129[131] = 0.0;
   out_3381743124655291129[132] = 0.0;
   out_3381743124655291129[133] = 1.0;
   out_3381743124655291129[134] = 0.0;
   out_3381743124655291129[135] = 0.0;
   out_3381743124655291129[136] = 0.0;
   out_3381743124655291129[137] = 0.0;
   out_3381743124655291129[138] = 0.0;
   out_3381743124655291129[139] = 0.0;
   out_3381743124655291129[140] = 0.0;
   out_3381743124655291129[141] = 0.0;
   out_3381743124655291129[142] = 0.0;
   out_3381743124655291129[143] = 0.0;
   out_3381743124655291129[144] = 0.0;
   out_3381743124655291129[145] = 0.0;
   out_3381743124655291129[146] = 0.0;
   out_3381743124655291129[147] = 0.0;
   out_3381743124655291129[148] = 0.0;
   out_3381743124655291129[149] = 0.0;
   out_3381743124655291129[150] = 0.0;
   out_3381743124655291129[151] = 0.0;
   out_3381743124655291129[152] = 1.0;
   out_3381743124655291129[153] = 0.0;
   out_3381743124655291129[154] = 0.0;
   out_3381743124655291129[155] = 0.0;
   out_3381743124655291129[156] = 0.0;
   out_3381743124655291129[157] = 0.0;
   out_3381743124655291129[158] = 0.0;
   out_3381743124655291129[159] = 0.0;
   out_3381743124655291129[160] = 0.0;
   out_3381743124655291129[161] = 0.0;
   out_3381743124655291129[162] = 0.0;
   out_3381743124655291129[163] = 0.0;
   out_3381743124655291129[164] = 0.0;
   out_3381743124655291129[165] = 0.0;
   out_3381743124655291129[166] = 0.0;
   out_3381743124655291129[167] = 0.0;
   out_3381743124655291129[168] = 0.0;
   out_3381743124655291129[169] = 0.0;
   out_3381743124655291129[170] = 0.0;
   out_3381743124655291129[171] = 1.0;
   out_3381743124655291129[172] = 0.0;
   out_3381743124655291129[173] = 0.0;
   out_3381743124655291129[174] = 0.0;
   out_3381743124655291129[175] = 0.0;
   out_3381743124655291129[176] = 0.0;
   out_3381743124655291129[177] = 0.0;
   out_3381743124655291129[178] = 0.0;
   out_3381743124655291129[179] = 0.0;
   out_3381743124655291129[180] = 0.0;
   out_3381743124655291129[181] = 0.0;
   out_3381743124655291129[182] = 0.0;
   out_3381743124655291129[183] = 0.0;
   out_3381743124655291129[184] = 0.0;
   out_3381743124655291129[185] = 0.0;
   out_3381743124655291129[186] = 0.0;
   out_3381743124655291129[187] = 0.0;
   out_3381743124655291129[188] = 0.0;
   out_3381743124655291129[189] = 0.0;
   out_3381743124655291129[190] = 1.0;
   out_3381743124655291129[191] = 0.0;
   out_3381743124655291129[192] = 0.0;
   out_3381743124655291129[193] = 0.0;
   out_3381743124655291129[194] = 0.0;
   out_3381743124655291129[195] = 0.0;
   out_3381743124655291129[196] = 0.0;
   out_3381743124655291129[197] = 0.0;
   out_3381743124655291129[198] = 0.0;
   out_3381743124655291129[199] = 0.0;
   out_3381743124655291129[200] = 0.0;
   out_3381743124655291129[201] = 0.0;
   out_3381743124655291129[202] = 0.0;
   out_3381743124655291129[203] = 0.0;
   out_3381743124655291129[204] = 0.0;
   out_3381743124655291129[205] = 0.0;
   out_3381743124655291129[206] = 0.0;
   out_3381743124655291129[207] = 0.0;
   out_3381743124655291129[208] = 0.0;
   out_3381743124655291129[209] = 1.0;
   out_3381743124655291129[210] = 0.0;
   out_3381743124655291129[211] = 0.0;
   out_3381743124655291129[212] = 0.0;
   out_3381743124655291129[213] = 0.0;
   out_3381743124655291129[214] = 0.0;
   out_3381743124655291129[215] = 0.0;
   out_3381743124655291129[216] = 0.0;
   out_3381743124655291129[217] = 0.0;
   out_3381743124655291129[218] = 0.0;
   out_3381743124655291129[219] = 0.0;
   out_3381743124655291129[220] = 0.0;
   out_3381743124655291129[221] = 0.0;
   out_3381743124655291129[222] = 0.0;
   out_3381743124655291129[223] = 0.0;
   out_3381743124655291129[224] = 0.0;
   out_3381743124655291129[225] = 0.0;
   out_3381743124655291129[226] = 0.0;
   out_3381743124655291129[227] = 0.0;
   out_3381743124655291129[228] = 1.0;
   out_3381743124655291129[229] = 0.0;
   out_3381743124655291129[230] = 0.0;
   out_3381743124655291129[231] = 0.0;
   out_3381743124655291129[232] = 0.0;
   out_3381743124655291129[233] = 0.0;
   out_3381743124655291129[234] = 0.0;
   out_3381743124655291129[235] = 0.0;
   out_3381743124655291129[236] = 0.0;
   out_3381743124655291129[237] = 0.0;
   out_3381743124655291129[238] = 0.0;
   out_3381743124655291129[239] = 0.0;
   out_3381743124655291129[240] = 0.0;
   out_3381743124655291129[241] = 0.0;
   out_3381743124655291129[242] = 0.0;
   out_3381743124655291129[243] = 0.0;
   out_3381743124655291129[244] = 0.0;
   out_3381743124655291129[245] = 0.0;
   out_3381743124655291129[246] = 0.0;
   out_3381743124655291129[247] = 1.0;
   out_3381743124655291129[248] = 0.0;
   out_3381743124655291129[249] = 0.0;
   out_3381743124655291129[250] = 0.0;
   out_3381743124655291129[251] = 0.0;
   out_3381743124655291129[252] = 0.0;
   out_3381743124655291129[253] = 0.0;
   out_3381743124655291129[254] = 0.0;
   out_3381743124655291129[255] = 0.0;
   out_3381743124655291129[256] = 0.0;
   out_3381743124655291129[257] = 0.0;
   out_3381743124655291129[258] = 0.0;
   out_3381743124655291129[259] = 0.0;
   out_3381743124655291129[260] = 0.0;
   out_3381743124655291129[261] = 0.0;
   out_3381743124655291129[262] = 0.0;
   out_3381743124655291129[263] = 0.0;
   out_3381743124655291129[264] = 0.0;
   out_3381743124655291129[265] = 0.0;
   out_3381743124655291129[266] = 1.0;
   out_3381743124655291129[267] = 0.0;
   out_3381743124655291129[268] = 0.0;
   out_3381743124655291129[269] = 0.0;
   out_3381743124655291129[270] = 0.0;
   out_3381743124655291129[271] = 0.0;
   out_3381743124655291129[272] = 0.0;
   out_3381743124655291129[273] = 0.0;
   out_3381743124655291129[274] = 0.0;
   out_3381743124655291129[275] = 0.0;
   out_3381743124655291129[276] = 0.0;
   out_3381743124655291129[277] = 0.0;
   out_3381743124655291129[278] = 0.0;
   out_3381743124655291129[279] = 0.0;
   out_3381743124655291129[280] = 0.0;
   out_3381743124655291129[281] = 0.0;
   out_3381743124655291129[282] = 0.0;
   out_3381743124655291129[283] = 0.0;
   out_3381743124655291129[284] = 0.0;
   out_3381743124655291129[285] = 1.0;
   out_3381743124655291129[286] = 0.0;
   out_3381743124655291129[287] = 0.0;
   out_3381743124655291129[288] = 0.0;
   out_3381743124655291129[289] = 0.0;
   out_3381743124655291129[290] = 0.0;
   out_3381743124655291129[291] = 0.0;
   out_3381743124655291129[292] = 0.0;
   out_3381743124655291129[293] = 0.0;
   out_3381743124655291129[294] = 0.0;
   out_3381743124655291129[295] = 0.0;
   out_3381743124655291129[296] = 0.0;
   out_3381743124655291129[297] = 0.0;
   out_3381743124655291129[298] = 0.0;
   out_3381743124655291129[299] = 0.0;
   out_3381743124655291129[300] = 0.0;
   out_3381743124655291129[301] = 0.0;
   out_3381743124655291129[302] = 0.0;
   out_3381743124655291129[303] = 0.0;
   out_3381743124655291129[304] = 1.0;
   out_3381743124655291129[305] = 0.0;
   out_3381743124655291129[306] = 0.0;
   out_3381743124655291129[307] = 0.0;
   out_3381743124655291129[308] = 0.0;
   out_3381743124655291129[309] = 0.0;
   out_3381743124655291129[310] = 0.0;
   out_3381743124655291129[311] = 0.0;
   out_3381743124655291129[312] = 0.0;
   out_3381743124655291129[313] = 0.0;
   out_3381743124655291129[314] = 0.0;
   out_3381743124655291129[315] = 0.0;
   out_3381743124655291129[316] = 0.0;
   out_3381743124655291129[317] = 0.0;
   out_3381743124655291129[318] = 0.0;
   out_3381743124655291129[319] = 0.0;
   out_3381743124655291129[320] = 0.0;
   out_3381743124655291129[321] = 0.0;
   out_3381743124655291129[322] = 0.0;
   out_3381743124655291129[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7882480926820665595) {
   out_7882480926820665595[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7882480926820665595[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7882480926820665595[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7882480926820665595[3] = dt*state[12] + state[3];
   out_7882480926820665595[4] = dt*state[13] + state[4];
   out_7882480926820665595[5] = dt*state[14] + state[5];
   out_7882480926820665595[6] = state[6];
   out_7882480926820665595[7] = state[7];
   out_7882480926820665595[8] = state[8];
   out_7882480926820665595[9] = state[9];
   out_7882480926820665595[10] = state[10];
   out_7882480926820665595[11] = state[11];
   out_7882480926820665595[12] = state[12];
   out_7882480926820665595[13] = state[13];
   out_7882480926820665595[14] = state[14];
   out_7882480926820665595[15] = state[15];
   out_7882480926820665595[16] = state[16];
   out_7882480926820665595[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7514173121064358506) {
   out_7514173121064358506[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7514173121064358506[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7514173121064358506[2] = 0;
   out_7514173121064358506[3] = 0;
   out_7514173121064358506[4] = 0;
   out_7514173121064358506[5] = 0;
   out_7514173121064358506[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7514173121064358506[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7514173121064358506[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7514173121064358506[9] = 0;
   out_7514173121064358506[10] = 0;
   out_7514173121064358506[11] = 0;
   out_7514173121064358506[12] = 0;
   out_7514173121064358506[13] = 0;
   out_7514173121064358506[14] = 0;
   out_7514173121064358506[15] = 0;
   out_7514173121064358506[16] = 0;
   out_7514173121064358506[17] = 0;
   out_7514173121064358506[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7514173121064358506[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7514173121064358506[20] = 0;
   out_7514173121064358506[21] = 0;
   out_7514173121064358506[22] = 0;
   out_7514173121064358506[23] = 0;
   out_7514173121064358506[24] = 0;
   out_7514173121064358506[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7514173121064358506[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7514173121064358506[27] = 0;
   out_7514173121064358506[28] = 0;
   out_7514173121064358506[29] = 0;
   out_7514173121064358506[30] = 0;
   out_7514173121064358506[31] = 0;
   out_7514173121064358506[32] = 0;
   out_7514173121064358506[33] = 0;
   out_7514173121064358506[34] = 0;
   out_7514173121064358506[35] = 0;
   out_7514173121064358506[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7514173121064358506[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7514173121064358506[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7514173121064358506[39] = 0;
   out_7514173121064358506[40] = 0;
   out_7514173121064358506[41] = 0;
   out_7514173121064358506[42] = 0;
   out_7514173121064358506[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7514173121064358506[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7514173121064358506[45] = 0;
   out_7514173121064358506[46] = 0;
   out_7514173121064358506[47] = 0;
   out_7514173121064358506[48] = 0;
   out_7514173121064358506[49] = 0;
   out_7514173121064358506[50] = 0;
   out_7514173121064358506[51] = 0;
   out_7514173121064358506[52] = 0;
   out_7514173121064358506[53] = 0;
   out_7514173121064358506[54] = 0;
   out_7514173121064358506[55] = 0;
   out_7514173121064358506[56] = 0;
   out_7514173121064358506[57] = 1;
   out_7514173121064358506[58] = 0;
   out_7514173121064358506[59] = 0;
   out_7514173121064358506[60] = 0;
   out_7514173121064358506[61] = 0;
   out_7514173121064358506[62] = 0;
   out_7514173121064358506[63] = 0;
   out_7514173121064358506[64] = 0;
   out_7514173121064358506[65] = 0;
   out_7514173121064358506[66] = dt;
   out_7514173121064358506[67] = 0;
   out_7514173121064358506[68] = 0;
   out_7514173121064358506[69] = 0;
   out_7514173121064358506[70] = 0;
   out_7514173121064358506[71] = 0;
   out_7514173121064358506[72] = 0;
   out_7514173121064358506[73] = 0;
   out_7514173121064358506[74] = 0;
   out_7514173121064358506[75] = 0;
   out_7514173121064358506[76] = 1;
   out_7514173121064358506[77] = 0;
   out_7514173121064358506[78] = 0;
   out_7514173121064358506[79] = 0;
   out_7514173121064358506[80] = 0;
   out_7514173121064358506[81] = 0;
   out_7514173121064358506[82] = 0;
   out_7514173121064358506[83] = 0;
   out_7514173121064358506[84] = 0;
   out_7514173121064358506[85] = dt;
   out_7514173121064358506[86] = 0;
   out_7514173121064358506[87] = 0;
   out_7514173121064358506[88] = 0;
   out_7514173121064358506[89] = 0;
   out_7514173121064358506[90] = 0;
   out_7514173121064358506[91] = 0;
   out_7514173121064358506[92] = 0;
   out_7514173121064358506[93] = 0;
   out_7514173121064358506[94] = 0;
   out_7514173121064358506[95] = 1;
   out_7514173121064358506[96] = 0;
   out_7514173121064358506[97] = 0;
   out_7514173121064358506[98] = 0;
   out_7514173121064358506[99] = 0;
   out_7514173121064358506[100] = 0;
   out_7514173121064358506[101] = 0;
   out_7514173121064358506[102] = 0;
   out_7514173121064358506[103] = 0;
   out_7514173121064358506[104] = dt;
   out_7514173121064358506[105] = 0;
   out_7514173121064358506[106] = 0;
   out_7514173121064358506[107] = 0;
   out_7514173121064358506[108] = 0;
   out_7514173121064358506[109] = 0;
   out_7514173121064358506[110] = 0;
   out_7514173121064358506[111] = 0;
   out_7514173121064358506[112] = 0;
   out_7514173121064358506[113] = 0;
   out_7514173121064358506[114] = 1;
   out_7514173121064358506[115] = 0;
   out_7514173121064358506[116] = 0;
   out_7514173121064358506[117] = 0;
   out_7514173121064358506[118] = 0;
   out_7514173121064358506[119] = 0;
   out_7514173121064358506[120] = 0;
   out_7514173121064358506[121] = 0;
   out_7514173121064358506[122] = 0;
   out_7514173121064358506[123] = 0;
   out_7514173121064358506[124] = 0;
   out_7514173121064358506[125] = 0;
   out_7514173121064358506[126] = 0;
   out_7514173121064358506[127] = 0;
   out_7514173121064358506[128] = 0;
   out_7514173121064358506[129] = 0;
   out_7514173121064358506[130] = 0;
   out_7514173121064358506[131] = 0;
   out_7514173121064358506[132] = 0;
   out_7514173121064358506[133] = 1;
   out_7514173121064358506[134] = 0;
   out_7514173121064358506[135] = 0;
   out_7514173121064358506[136] = 0;
   out_7514173121064358506[137] = 0;
   out_7514173121064358506[138] = 0;
   out_7514173121064358506[139] = 0;
   out_7514173121064358506[140] = 0;
   out_7514173121064358506[141] = 0;
   out_7514173121064358506[142] = 0;
   out_7514173121064358506[143] = 0;
   out_7514173121064358506[144] = 0;
   out_7514173121064358506[145] = 0;
   out_7514173121064358506[146] = 0;
   out_7514173121064358506[147] = 0;
   out_7514173121064358506[148] = 0;
   out_7514173121064358506[149] = 0;
   out_7514173121064358506[150] = 0;
   out_7514173121064358506[151] = 0;
   out_7514173121064358506[152] = 1;
   out_7514173121064358506[153] = 0;
   out_7514173121064358506[154] = 0;
   out_7514173121064358506[155] = 0;
   out_7514173121064358506[156] = 0;
   out_7514173121064358506[157] = 0;
   out_7514173121064358506[158] = 0;
   out_7514173121064358506[159] = 0;
   out_7514173121064358506[160] = 0;
   out_7514173121064358506[161] = 0;
   out_7514173121064358506[162] = 0;
   out_7514173121064358506[163] = 0;
   out_7514173121064358506[164] = 0;
   out_7514173121064358506[165] = 0;
   out_7514173121064358506[166] = 0;
   out_7514173121064358506[167] = 0;
   out_7514173121064358506[168] = 0;
   out_7514173121064358506[169] = 0;
   out_7514173121064358506[170] = 0;
   out_7514173121064358506[171] = 1;
   out_7514173121064358506[172] = 0;
   out_7514173121064358506[173] = 0;
   out_7514173121064358506[174] = 0;
   out_7514173121064358506[175] = 0;
   out_7514173121064358506[176] = 0;
   out_7514173121064358506[177] = 0;
   out_7514173121064358506[178] = 0;
   out_7514173121064358506[179] = 0;
   out_7514173121064358506[180] = 0;
   out_7514173121064358506[181] = 0;
   out_7514173121064358506[182] = 0;
   out_7514173121064358506[183] = 0;
   out_7514173121064358506[184] = 0;
   out_7514173121064358506[185] = 0;
   out_7514173121064358506[186] = 0;
   out_7514173121064358506[187] = 0;
   out_7514173121064358506[188] = 0;
   out_7514173121064358506[189] = 0;
   out_7514173121064358506[190] = 1;
   out_7514173121064358506[191] = 0;
   out_7514173121064358506[192] = 0;
   out_7514173121064358506[193] = 0;
   out_7514173121064358506[194] = 0;
   out_7514173121064358506[195] = 0;
   out_7514173121064358506[196] = 0;
   out_7514173121064358506[197] = 0;
   out_7514173121064358506[198] = 0;
   out_7514173121064358506[199] = 0;
   out_7514173121064358506[200] = 0;
   out_7514173121064358506[201] = 0;
   out_7514173121064358506[202] = 0;
   out_7514173121064358506[203] = 0;
   out_7514173121064358506[204] = 0;
   out_7514173121064358506[205] = 0;
   out_7514173121064358506[206] = 0;
   out_7514173121064358506[207] = 0;
   out_7514173121064358506[208] = 0;
   out_7514173121064358506[209] = 1;
   out_7514173121064358506[210] = 0;
   out_7514173121064358506[211] = 0;
   out_7514173121064358506[212] = 0;
   out_7514173121064358506[213] = 0;
   out_7514173121064358506[214] = 0;
   out_7514173121064358506[215] = 0;
   out_7514173121064358506[216] = 0;
   out_7514173121064358506[217] = 0;
   out_7514173121064358506[218] = 0;
   out_7514173121064358506[219] = 0;
   out_7514173121064358506[220] = 0;
   out_7514173121064358506[221] = 0;
   out_7514173121064358506[222] = 0;
   out_7514173121064358506[223] = 0;
   out_7514173121064358506[224] = 0;
   out_7514173121064358506[225] = 0;
   out_7514173121064358506[226] = 0;
   out_7514173121064358506[227] = 0;
   out_7514173121064358506[228] = 1;
   out_7514173121064358506[229] = 0;
   out_7514173121064358506[230] = 0;
   out_7514173121064358506[231] = 0;
   out_7514173121064358506[232] = 0;
   out_7514173121064358506[233] = 0;
   out_7514173121064358506[234] = 0;
   out_7514173121064358506[235] = 0;
   out_7514173121064358506[236] = 0;
   out_7514173121064358506[237] = 0;
   out_7514173121064358506[238] = 0;
   out_7514173121064358506[239] = 0;
   out_7514173121064358506[240] = 0;
   out_7514173121064358506[241] = 0;
   out_7514173121064358506[242] = 0;
   out_7514173121064358506[243] = 0;
   out_7514173121064358506[244] = 0;
   out_7514173121064358506[245] = 0;
   out_7514173121064358506[246] = 0;
   out_7514173121064358506[247] = 1;
   out_7514173121064358506[248] = 0;
   out_7514173121064358506[249] = 0;
   out_7514173121064358506[250] = 0;
   out_7514173121064358506[251] = 0;
   out_7514173121064358506[252] = 0;
   out_7514173121064358506[253] = 0;
   out_7514173121064358506[254] = 0;
   out_7514173121064358506[255] = 0;
   out_7514173121064358506[256] = 0;
   out_7514173121064358506[257] = 0;
   out_7514173121064358506[258] = 0;
   out_7514173121064358506[259] = 0;
   out_7514173121064358506[260] = 0;
   out_7514173121064358506[261] = 0;
   out_7514173121064358506[262] = 0;
   out_7514173121064358506[263] = 0;
   out_7514173121064358506[264] = 0;
   out_7514173121064358506[265] = 0;
   out_7514173121064358506[266] = 1;
   out_7514173121064358506[267] = 0;
   out_7514173121064358506[268] = 0;
   out_7514173121064358506[269] = 0;
   out_7514173121064358506[270] = 0;
   out_7514173121064358506[271] = 0;
   out_7514173121064358506[272] = 0;
   out_7514173121064358506[273] = 0;
   out_7514173121064358506[274] = 0;
   out_7514173121064358506[275] = 0;
   out_7514173121064358506[276] = 0;
   out_7514173121064358506[277] = 0;
   out_7514173121064358506[278] = 0;
   out_7514173121064358506[279] = 0;
   out_7514173121064358506[280] = 0;
   out_7514173121064358506[281] = 0;
   out_7514173121064358506[282] = 0;
   out_7514173121064358506[283] = 0;
   out_7514173121064358506[284] = 0;
   out_7514173121064358506[285] = 1;
   out_7514173121064358506[286] = 0;
   out_7514173121064358506[287] = 0;
   out_7514173121064358506[288] = 0;
   out_7514173121064358506[289] = 0;
   out_7514173121064358506[290] = 0;
   out_7514173121064358506[291] = 0;
   out_7514173121064358506[292] = 0;
   out_7514173121064358506[293] = 0;
   out_7514173121064358506[294] = 0;
   out_7514173121064358506[295] = 0;
   out_7514173121064358506[296] = 0;
   out_7514173121064358506[297] = 0;
   out_7514173121064358506[298] = 0;
   out_7514173121064358506[299] = 0;
   out_7514173121064358506[300] = 0;
   out_7514173121064358506[301] = 0;
   out_7514173121064358506[302] = 0;
   out_7514173121064358506[303] = 0;
   out_7514173121064358506[304] = 1;
   out_7514173121064358506[305] = 0;
   out_7514173121064358506[306] = 0;
   out_7514173121064358506[307] = 0;
   out_7514173121064358506[308] = 0;
   out_7514173121064358506[309] = 0;
   out_7514173121064358506[310] = 0;
   out_7514173121064358506[311] = 0;
   out_7514173121064358506[312] = 0;
   out_7514173121064358506[313] = 0;
   out_7514173121064358506[314] = 0;
   out_7514173121064358506[315] = 0;
   out_7514173121064358506[316] = 0;
   out_7514173121064358506[317] = 0;
   out_7514173121064358506[318] = 0;
   out_7514173121064358506[319] = 0;
   out_7514173121064358506[320] = 0;
   out_7514173121064358506[321] = 0;
   out_7514173121064358506[322] = 0;
   out_7514173121064358506[323] = 1;
}
void h_4(double *state, double *unused, double *out_7035079041829046455) {
   out_7035079041829046455[0] = state[6] + state[9];
   out_7035079041829046455[1] = state[7] + state[10];
   out_7035079041829046455[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_107521045864341876) {
   out_107521045864341876[0] = 0;
   out_107521045864341876[1] = 0;
   out_107521045864341876[2] = 0;
   out_107521045864341876[3] = 0;
   out_107521045864341876[4] = 0;
   out_107521045864341876[5] = 0;
   out_107521045864341876[6] = 1;
   out_107521045864341876[7] = 0;
   out_107521045864341876[8] = 0;
   out_107521045864341876[9] = 1;
   out_107521045864341876[10] = 0;
   out_107521045864341876[11] = 0;
   out_107521045864341876[12] = 0;
   out_107521045864341876[13] = 0;
   out_107521045864341876[14] = 0;
   out_107521045864341876[15] = 0;
   out_107521045864341876[16] = 0;
   out_107521045864341876[17] = 0;
   out_107521045864341876[18] = 0;
   out_107521045864341876[19] = 0;
   out_107521045864341876[20] = 0;
   out_107521045864341876[21] = 0;
   out_107521045864341876[22] = 0;
   out_107521045864341876[23] = 0;
   out_107521045864341876[24] = 0;
   out_107521045864341876[25] = 1;
   out_107521045864341876[26] = 0;
   out_107521045864341876[27] = 0;
   out_107521045864341876[28] = 1;
   out_107521045864341876[29] = 0;
   out_107521045864341876[30] = 0;
   out_107521045864341876[31] = 0;
   out_107521045864341876[32] = 0;
   out_107521045864341876[33] = 0;
   out_107521045864341876[34] = 0;
   out_107521045864341876[35] = 0;
   out_107521045864341876[36] = 0;
   out_107521045864341876[37] = 0;
   out_107521045864341876[38] = 0;
   out_107521045864341876[39] = 0;
   out_107521045864341876[40] = 0;
   out_107521045864341876[41] = 0;
   out_107521045864341876[42] = 0;
   out_107521045864341876[43] = 0;
   out_107521045864341876[44] = 1;
   out_107521045864341876[45] = 0;
   out_107521045864341876[46] = 0;
   out_107521045864341876[47] = 1;
   out_107521045864341876[48] = 0;
   out_107521045864341876[49] = 0;
   out_107521045864341876[50] = 0;
   out_107521045864341876[51] = 0;
   out_107521045864341876[52] = 0;
   out_107521045864341876[53] = 0;
}
void h_10(double *state, double *unused, double *out_2457497411718140254) {
   out_2457497411718140254[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2457497411718140254[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2457497411718140254[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1300624195109537119) {
   out_1300624195109537119[0] = 0;
   out_1300624195109537119[1] = 9.8100000000000005*cos(state[1]);
   out_1300624195109537119[2] = 0;
   out_1300624195109537119[3] = 0;
   out_1300624195109537119[4] = -state[8];
   out_1300624195109537119[5] = state[7];
   out_1300624195109537119[6] = 0;
   out_1300624195109537119[7] = state[5];
   out_1300624195109537119[8] = -state[4];
   out_1300624195109537119[9] = 0;
   out_1300624195109537119[10] = 0;
   out_1300624195109537119[11] = 0;
   out_1300624195109537119[12] = 1;
   out_1300624195109537119[13] = 0;
   out_1300624195109537119[14] = 0;
   out_1300624195109537119[15] = 1;
   out_1300624195109537119[16] = 0;
   out_1300624195109537119[17] = 0;
   out_1300624195109537119[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1300624195109537119[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1300624195109537119[20] = 0;
   out_1300624195109537119[21] = state[8];
   out_1300624195109537119[22] = 0;
   out_1300624195109537119[23] = -state[6];
   out_1300624195109537119[24] = -state[5];
   out_1300624195109537119[25] = 0;
   out_1300624195109537119[26] = state[3];
   out_1300624195109537119[27] = 0;
   out_1300624195109537119[28] = 0;
   out_1300624195109537119[29] = 0;
   out_1300624195109537119[30] = 0;
   out_1300624195109537119[31] = 1;
   out_1300624195109537119[32] = 0;
   out_1300624195109537119[33] = 0;
   out_1300624195109537119[34] = 1;
   out_1300624195109537119[35] = 0;
   out_1300624195109537119[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1300624195109537119[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1300624195109537119[38] = 0;
   out_1300624195109537119[39] = -state[7];
   out_1300624195109537119[40] = state[6];
   out_1300624195109537119[41] = 0;
   out_1300624195109537119[42] = state[4];
   out_1300624195109537119[43] = -state[3];
   out_1300624195109537119[44] = 0;
   out_1300624195109537119[45] = 0;
   out_1300624195109537119[46] = 0;
   out_1300624195109537119[47] = 0;
   out_1300624195109537119[48] = 0;
   out_1300624195109537119[49] = 0;
   out_1300624195109537119[50] = 1;
   out_1300624195109537119[51] = 0;
   out_1300624195109537119[52] = 0;
   out_1300624195109537119[53] = 1;
}
void h_13(double *state, double *unused, double *out_8699612882877262612) {
   out_8699612882877262612[0] = state[3];
   out_8699612882877262612[1] = state[4];
   out_8699612882877262612[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3319794871196674677) {
   out_3319794871196674677[0] = 0;
   out_3319794871196674677[1] = 0;
   out_3319794871196674677[2] = 0;
   out_3319794871196674677[3] = 1;
   out_3319794871196674677[4] = 0;
   out_3319794871196674677[5] = 0;
   out_3319794871196674677[6] = 0;
   out_3319794871196674677[7] = 0;
   out_3319794871196674677[8] = 0;
   out_3319794871196674677[9] = 0;
   out_3319794871196674677[10] = 0;
   out_3319794871196674677[11] = 0;
   out_3319794871196674677[12] = 0;
   out_3319794871196674677[13] = 0;
   out_3319794871196674677[14] = 0;
   out_3319794871196674677[15] = 0;
   out_3319794871196674677[16] = 0;
   out_3319794871196674677[17] = 0;
   out_3319794871196674677[18] = 0;
   out_3319794871196674677[19] = 0;
   out_3319794871196674677[20] = 0;
   out_3319794871196674677[21] = 0;
   out_3319794871196674677[22] = 1;
   out_3319794871196674677[23] = 0;
   out_3319794871196674677[24] = 0;
   out_3319794871196674677[25] = 0;
   out_3319794871196674677[26] = 0;
   out_3319794871196674677[27] = 0;
   out_3319794871196674677[28] = 0;
   out_3319794871196674677[29] = 0;
   out_3319794871196674677[30] = 0;
   out_3319794871196674677[31] = 0;
   out_3319794871196674677[32] = 0;
   out_3319794871196674677[33] = 0;
   out_3319794871196674677[34] = 0;
   out_3319794871196674677[35] = 0;
   out_3319794871196674677[36] = 0;
   out_3319794871196674677[37] = 0;
   out_3319794871196674677[38] = 0;
   out_3319794871196674677[39] = 0;
   out_3319794871196674677[40] = 0;
   out_3319794871196674677[41] = 1;
   out_3319794871196674677[42] = 0;
   out_3319794871196674677[43] = 0;
   out_3319794871196674677[44] = 0;
   out_3319794871196674677[45] = 0;
   out_3319794871196674677[46] = 0;
   out_3319794871196674677[47] = 0;
   out_3319794871196674677[48] = 0;
   out_3319794871196674677[49] = 0;
   out_3319794871196674677[50] = 0;
   out_3319794871196674677[51] = 0;
   out_3319794871196674677[52] = 0;
   out_3319794871196674677[53] = 0;
}
void h_14(double *state, double *unused, double *out_8616340880415210732) {
   out_8616340880415210732[0] = state[6];
   out_8616340880415210732[1] = state[7];
   out_8616340880415210732[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4070761902203826405) {
   out_4070761902203826405[0] = 0;
   out_4070761902203826405[1] = 0;
   out_4070761902203826405[2] = 0;
   out_4070761902203826405[3] = 0;
   out_4070761902203826405[4] = 0;
   out_4070761902203826405[5] = 0;
   out_4070761902203826405[6] = 1;
   out_4070761902203826405[7] = 0;
   out_4070761902203826405[8] = 0;
   out_4070761902203826405[9] = 0;
   out_4070761902203826405[10] = 0;
   out_4070761902203826405[11] = 0;
   out_4070761902203826405[12] = 0;
   out_4070761902203826405[13] = 0;
   out_4070761902203826405[14] = 0;
   out_4070761902203826405[15] = 0;
   out_4070761902203826405[16] = 0;
   out_4070761902203826405[17] = 0;
   out_4070761902203826405[18] = 0;
   out_4070761902203826405[19] = 0;
   out_4070761902203826405[20] = 0;
   out_4070761902203826405[21] = 0;
   out_4070761902203826405[22] = 0;
   out_4070761902203826405[23] = 0;
   out_4070761902203826405[24] = 0;
   out_4070761902203826405[25] = 1;
   out_4070761902203826405[26] = 0;
   out_4070761902203826405[27] = 0;
   out_4070761902203826405[28] = 0;
   out_4070761902203826405[29] = 0;
   out_4070761902203826405[30] = 0;
   out_4070761902203826405[31] = 0;
   out_4070761902203826405[32] = 0;
   out_4070761902203826405[33] = 0;
   out_4070761902203826405[34] = 0;
   out_4070761902203826405[35] = 0;
   out_4070761902203826405[36] = 0;
   out_4070761902203826405[37] = 0;
   out_4070761902203826405[38] = 0;
   out_4070761902203826405[39] = 0;
   out_4070761902203826405[40] = 0;
   out_4070761902203826405[41] = 0;
   out_4070761902203826405[42] = 0;
   out_4070761902203826405[43] = 0;
   out_4070761902203826405[44] = 1;
   out_4070761902203826405[45] = 0;
   out_4070761902203826405[46] = 0;
   out_4070761902203826405[47] = 0;
   out_4070761902203826405[48] = 0;
   out_4070761902203826405[49] = 0;
   out_4070761902203826405[50] = 0;
   out_4070761902203826405[51] = 0;
   out_4070761902203826405[52] = 0;
   out_4070761902203826405[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1524410796143659703) {
  err_fun(nom_x, delta_x, out_1524410796143659703);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7721887411546703304) {
  inv_err_fun(nom_x, true_x, out_7721887411546703304);
}
void pose_H_mod_fun(double *state, double *out_3381743124655291129) {
  H_mod_fun(state, out_3381743124655291129);
}
void pose_f_fun(double *state, double dt, double *out_7882480926820665595) {
  f_fun(state,  dt, out_7882480926820665595);
}
void pose_F_fun(double *state, double dt, double *out_7514173121064358506) {
  F_fun(state,  dt, out_7514173121064358506);
}
void pose_h_4(double *state, double *unused, double *out_7035079041829046455) {
  h_4(state, unused, out_7035079041829046455);
}
void pose_H_4(double *state, double *unused, double *out_107521045864341876) {
  H_4(state, unused, out_107521045864341876);
}
void pose_h_10(double *state, double *unused, double *out_2457497411718140254) {
  h_10(state, unused, out_2457497411718140254);
}
void pose_H_10(double *state, double *unused, double *out_1300624195109537119) {
  H_10(state, unused, out_1300624195109537119);
}
void pose_h_13(double *state, double *unused, double *out_8699612882877262612) {
  h_13(state, unused, out_8699612882877262612);
}
void pose_H_13(double *state, double *unused, double *out_3319794871196674677) {
  H_13(state, unused, out_3319794871196674677);
}
void pose_h_14(double *state, double *unused, double *out_8616340880415210732) {
  h_14(state, unused, out_8616340880415210732);
}
void pose_H_14(double *state, double *unused, double *out_4070761902203826405) {
  H_14(state, unused, out_4070761902203826405);
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
