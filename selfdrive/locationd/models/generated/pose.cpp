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
void err_fun(double *nom_x, double *delta_x, double *out_6370445090975775647) {
   out_6370445090975775647[0] = delta_x[0] + nom_x[0];
   out_6370445090975775647[1] = delta_x[1] + nom_x[1];
   out_6370445090975775647[2] = delta_x[2] + nom_x[2];
   out_6370445090975775647[3] = delta_x[3] + nom_x[3];
   out_6370445090975775647[4] = delta_x[4] + nom_x[4];
   out_6370445090975775647[5] = delta_x[5] + nom_x[5];
   out_6370445090975775647[6] = delta_x[6] + nom_x[6];
   out_6370445090975775647[7] = delta_x[7] + nom_x[7];
   out_6370445090975775647[8] = delta_x[8] + nom_x[8];
   out_6370445090975775647[9] = delta_x[9] + nom_x[9];
   out_6370445090975775647[10] = delta_x[10] + nom_x[10];
   out_6370445090975775647[11] = delta_x[11] + nom_x[11];
   out_6370445090975775647[12] = delta_x[12] + nom_x[12];
   out_6370445090975775647[13] = delta_x[13] + nom_x[13];
   out_6370445090975775647[14] = delta_x[14] + nom_x[14];
   out_6370445090975775647[15] = delta_x[15] + nom_x[15];
   out_6370445090975775647[16] = delta_x[16] + nom_x[16];
   out_6370445090975775647[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1677323290782450214) {
   out_1677323290782450214[0] = -nom_x[0] + true_x[0];
   out_1677323290782450214[1] = -nom_x[1] + true_x[1];
   out_1677323290782450214[2] = -nom_x[2] + true_x[2];
   out_1677323290782450214[3] = -nom_x[3] + true_x[3];
   out_1677323290782450214[4] = -nom_x[4] + true_x[4];
   out_1677323290782450214[5] = -nom_x[5] + true_x[5];
   out_1677323290782450214[6] = -nom_x[6] + true_x[6];
   out_1677323290782450214[7] = -nom_x[7] + true_x[7];
   out_1677323290782450214[8] = -nom_x[8] + true_x[8];
   out_1677323290782450214[9] = -nom_x[9] + true_x[9];
   out_1677323290782450214[10] = -nom_x[10] + true_x[10];
   out_1677323290782450214[11] = -nom_x[11] + true_x[11];
   out_1677323290782450214[12] = -nom_x[12] + true_x[12];
   out_1677323290782450214[13] = -nom_x[13] + true_x[13];
   out_1677323290782450214[14] = -nom_x[14] + true_x[14];
   out_1677323290782450214[15] = -nom_x[15] + true_x[15];
   out_1677323290782450214[16] = -nom_x[16] + true_x[16];
   out_1677323290782450214[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3468986617292713816) {
   out_3468986617292713816[0] = 1.0;
   out_3468986617292713816[1] = 0.0;
   out_3468986617292713816[2] = 0.0;
   out_3468986617292713816[3] = 0.0;
   out_3468986617292713816[4] = 0.0;
   out_3468986617292713816[5] = 0.0;
   out_3468986617292713816[6] = 0.0;
   out_3468986617292713816[7] = 0.0;
   out_3468986617292713816[8] = 0.0;
   out_3468986617292713816[9] = 0.0;
   out_3468986617292713816[10] = 0.0;
   out_3468986617292713816[11] = 0.0;
   out_3468986617292713816[12] = 0.0;
   out_3468986617292713816[13] = 0.0;
   out_3468986617292713816[14] = 0.0;
   out_3468986617292713816[15] = 0.0;
   out_3468986617292713816[16] = 0.0;
   out_3468986617292713816[17] = 0.0;
   out_3468986617292713816[18] = 0.0;
   out_3468986617292713816[19] = 1.0;
   out_3468986617292713816[20] = 0.0;
   out_3468986617292713816[21] = 0.0;
   out_3468986617292713816[22] = 0.0;
   out_3468986617292713816[23] = 0.0;
   out_3468986617292713816[24] = 0.0;
   out_3468986617292713816[25] = 0.0;
   out_3468986617292713816[26] = 0.0;
   out_3468986617292713816[27] = 0.0;
   out_3468986617292713816[28] = 0.0;
   out_3468986617292713816[29] = 0.0;
   out_3468986617292713816[30] = 0.0;
   out_3468986617292713816[31] = 0.0;
   out_3468986617292713816[32] = 0.0;
   out_3468986617292713816[33] = 0.0;
   out_3468986617292713816[34] = 0.0;
   out_3468986617292713816[35] = 0.0;
   out_3468986617292713816[36] = 0.0;
   out_3468986617292713816[37] = 0.0;
   out_3468986617292713816[38] = 1.0;
   out_3468986617292713816[39] = 0.0;
   out_3468986617292713816[40] = 0.0;
   out_3468986617292713816[41] = 0.0;
   out_3468986617292713816[42] = 0.0;
   out_3468986617292713816[43] = 0.0;
   out_3468986617292713816[44] = 0.0;
   out_3468986617292713816[45] = 0.0;
   out_3468986617292713816[46] = 0.0;
   out_3468986617292713816[47] = 0.0;
   out_3468986617292713816[48] = 0.0;
   out_3468986617292713816[49] = 0.0;
   out_3468986617292713816[50] = 0.0;
   out_3468986617292713816[51] = 0.0;
   out_3468986617292713816[52] = 0.0;
   out_3468986617292713816[53] = 0.0;
   out_3468986617292713816[54] = 0.0;
   out_3468986617292713816[55] = 0.0;
   out_3468986617292713816[56] = 0.0;
   out_3468986617292713816[57] = 1.0;
   out_3468986617292713816[58] = 0.0;
   out_3468986617292713816[59] = 0.0;
   out_3468986617292713816[60] = 0.0;
   out_3468986617292713816[61] = 0.0;
   out_3468986617292713816[62] = 0.0;
   out_3468986617292713816[63] = 0.0;
   out_3468986617292713816[64] = 0.0;
   out_3468986617292713816[65] = 0.0;
   out_3468986617292713816[66] = 0.0;
   out_3468986617292713816[67] = 0.0;
   out_3468986617292713816[68] = 0.0;
   out_3468986617292713816[69] = 0.0;
   out_3468986617292713816[70] = 0.0;
   out_3468986617292713816[71] = 0.0;
   out_3468986617292713816[72] = 0.0;
   out_3468986617292713816[73] = 0.0;
   out_3468986617292713816[74] = 0.0;
   out_3468986617292713816[75] = 0.0;
   out_3468986617292713816[76] = 1.0;
   out_3468986617292713816[77] = 0.0;
   out_3468986617292713816[78] = 0.0;
   out_3468986617292713816[79] = 0.0;
   out_3468986617292713816[80] = 0.0;
   out_3468986617292713816[81] = 0.0;
   out_3468986617292713816[82] = 0.0;
   out_3468986617292713816[83] = 0.0;
   out_3468986617292713816[84] = 0.0;
   out_3468986617292713816[85] = 0.0;
   out_3468986617292713816[86] = 0.0;
   out_3468986617292713816[87] = 0.0;
   out_3468986617292713816[88] = 0.0;
   out_3468986617292713816[89] = 0.0;
   out_3468986617292713816[90] = 0.0;
   out_3468986617292713816[91] = 0.0;
   out_3468986617292713816[92] = 0.0;
   out_3468986617292713816[93] = 0.0;
   out_3468986617292713816[94] = 0.0;
   out_3468986617292713816[95] = 1.0;
   out_3468986617292713816[96] = 0.0;
   out_3468986617292713816[97] = 0.0;
   out_3468986617292713816[98] = 0.0;
   out_3468986617292713816[99] = 0.0;
   out_3468986617292713816[100] = 0.0;
   out_3468986617292713816[101] = 0.0;
   out_3468986617292713816[102] = 0.0;
   out_3468986617292713816[103] = 0.0;
   out_3468986617292713816[104] = 0.0;
   out_3468986617292713816[105] = 0.0;
   out_3468986617292713816[106] = 0.0;
   out_3468986617292713816[107] = 0.0;
   out_3468986617292713816[108] = 0.0;
   out_3468986617292713816[109] = 0.0;
   out_3468986617292713816[110] = 0.0;
   out_3468986617292713816[111] = 0.0;
   out_3468986617292713816[112] = 0.0;
   out_3468986617292713816[113] = 0.0;
   out_3468986617292713816[114] = 1.0;
   out_3468986617292713816[115] = 0.0;
   out_3468986617292713816[116] = 0.0;
   out_3468986617292713816[117] = 0.0;
   out_3468986617292713816[118] = 0.0;
   out_3468986617292713816[119] = 0.0;
   out_3468986617292713816[120] = 0.0;
   out_3468986617292713816[121] = 0.0;
   out_3468986617292713816[122] = 0.0;
   out_3468986617292713816[123] = 0.0;
   out_3468986617292713816[124] = 0.0;
   out_3468986617292713816[125] = 0.0;
   out_3468986617292713816[126] = 0.0;
   out_3468986617292713816[127] = 0.0;
   out_3468986617292713816[128] = 0.0;
   out_3468986617292713816[129] = 0.0;
   out_3468986617292713816[130] = 0.0;
   out_3468986617292713816[131] = 0.0;
   out_3468986617292713816[132] = 0.0;
   out_3468986617292713816[133] = 1.0;
   out_3468986617292713816[134] = 0.0;
   out_3468986617292713816[135] = 0.0;
   out_3468986617292713816[136] = 0.0;
   out_3468986617292713816[137] = 0.0;
   out_3468986617292713816[138] = 0.0;
   out_3468986617292713816[139] = 0.0;
   out_3468986617292713816[140] = 0.0;
   out_3468986617292713816[141] = 0.0;
   out_3468986617292713816[142] = 0.0;
   out_3468986617292713816[143] = 0.0;
   out_3468986617292713816[144] = 0.0;
   out_3468986617292713816[145] = 0.0;
   out_3468986617292713816[146] = 0.0;
   out_3468986617292713816[147] = 0.0;
   out_3468986617292713816[148] = 0.0;
   out_3468986617292713816[149] = 0.0;
   out_3468986617292713816[150] = 0.0;
   out_3468986617292713816[151] = 0.0;
   out_3468986617292713816[152] = 1.0;
   out_3468986617292713816[153] = 0.0;
   out_3468986617292713816[154] = 0.0;
   out_3468986617292713816[155] = 0.0;
   out_3468986617292713816[156] = 0.0;
   out_3468986617292713816[157] = 0.0;
   out_3468986617292713816[158] = 0.0;
   out_3468986617292713816[159] = 0.0;
   out_3468986617292713816[160] = 0.0;
   out_3468986617292713816[161] = 0.0;
   out_3468986617292713816[162] = 0.0;
   out_3468986617292713816[163] = 0.0;
   out_3468986617292713816[164] = 0.0;
   out_3468986617292713816[165] = 0.0;
   out_3468986617292713816[166] = 0.0;
   out_3468986617292713816[167] = 0.0;
   out_3468986617292713816[168] = 0.0;
   out_3468986617292713816[169] = 0.0;
   out_3468986617292713816[170] = 0.0;
   out_3468986617292713816[171] = 1.0;
   out_3468986617292713816[172] = 0.0;
   out_3468986617292713816[173] = 0.0;
   out_3468986617292713816[174] = 0.0;
   out_3468986617292713816[175] = 0.0;
   out_3468986617292713816[176] = 0.0;
   out_3468986617292713816[177] = 0.0;
   out_3468986617292713816[178] = 0.0;
   out_3468986617292713816[179] = 0.0;
   out_3468986617292713816[180] = 0.0;
   out_3468986617292713816[181] = 0.0;
   out_3468986617292713816[182] = 0.0;
   out_3468986617292713816[183] = 0.0;
   out_3468986617292713816[184] = 0.0;
   out_3468986617292713816[185] = 0.0;
   out_3468986617292713816[186] = 0.0;
   out_3468986617292713816[187] = 0.0;
   out_3468986617292713816[188] = 0.0;
   out_3468986617292713816[189] = 0.0;
   out_3468986617292713816[190] = 1.0;
   out_3468986617292713816[191] = 0.0;
   out_3468986617292713816[192] = 0.0;
   out_3468986617292713816[193] = 0.0;
   out_3468986617292713816[194] = 0.0;
   out_3468986617292713816[195] = 0.0;
   out_3468986617292713816[196] = 0.0;
   out_3468986617292713816[197] = 0.0;
   out_3468986617292713816[198] = 0.0;
   out_3468986617292713816[199] = 0.0;
   out_3468986617292713816[200] = 0.0;
   out_3468986617292713816[201] = 0.0;
   out_3468986617292713816[202] = 0.0;
   out_3468986617292713816[203] = 0.0;
   out_3468986617292713816[204] = 0.0;
   out_3468986617292713816[205] = 0.0;
   out_3468986617292713816[206] = 0.0;
   out_3468986617292713816[207] = 0.0;
   out_3468986617292713816[208] = 0.0;
   out_3468986617292713816[209] = 1.0;
   out_3468986617292713816[210] = 0.0;
   out_3468986617292713816[211] = 0.0;
   out_3468986617292713816[212] = 0.0;
   out_3468986617292713816[213] = 0.0;
   out_3468986617292713816[214] = 0.0;
   out_3468986617292713816[215] = 0.0;
   out_3468986617292713816[216] = 0.0;
   out_3468986617292713816[217] = 0.0;
   out_3468986617292713816[218] = 0.0;
   out_3468986617292713816[219] = 0.0;
   out_3468986617292713816[220] = 0.0;
   out_3468986617292713816[221] = 0.0;
   out_3468986617292713816[222] = 0.0;
   out_3468986617292713816[223] = 0.0;
   out_3468986617292713816[224] = 0.0;
   out_3468986617292713816[225] = 0.0;
   out_3468986617292713816[226] = 0.0;
   out_3468986617292713816[227] = 0.0;
   out_3468986617292713816[228] = 1.0;
   out_3468986617292713816[229] = 0.0;
   out_3468986617292713816[230] = 0.0;
   out_3468986617292713816[231] = 0.0;
   out_3468986617292713816[232] = 0.0;
   out_3468986617292713816[233] = 0.0;
   out_3468986617292713816[234] = 0.0;
   out_3468986617292713816[235] = 0.0;
   out_3468986617292713816[236] = 0.0;
   out_3468986617292713816[237] = 0.0;
   out_3468986617292713816[238] = 0.0;
   out_3468986617292713816[239] = 0.0;
   out_3468986617292713816[240] = 0.0;
   out_3468986617292713816[241] = 0.0;
   out_3468986617292713816[242] = 0.0;
   out_3468986617292713816[243] = 0.0;
   out_3468986617292713816[244] = 0.0;
   out_3468986617292713816[245] = 0.0;
   out_3468986617292713816[246] = 0.0;
   out_3468986617292713816[247] = 1.0;
   out_3468986617292713816[248] = 0.0;
   out_3468986617292713816[249] = 0.0;
   out_3468986617292713816[250] = 0.0;
   out_3468986617292713816[251] = 0.0;
   out_3468986617292713816[252] = 0.0;
   out_3468986617292713816[253] = 0.0;
   out_3468986617292713816[254] = 0.0;
   out_3468986617292713816[255] = 0.0;
   out_3468986617292713816[256] = 0.0;
   out_3468986617292713816[257] = 0.0;
   out_3468986617292713816[258] = 0.0;
   out_3468986617292713816[259] = 0.0;
   out_3468986617292713816[260] = 0.0;
   out_3468986617292713816[261] = 0.0;
   out_3468986617292713816[262] = 0.0;
   out_3468986617292713816[263] = 0.0;
   out_3468986617292713816[264] = 0.0;
   out_3468986617292713816[265] = 0.0;
   out_3468986617292713816[266] = 1.0;
   out_3468986617292713816[267] = 0.0;
   out_3468986617292713816[268] = 0.0;
   out_3468986617292713816[269] = 0.0;
   out_3468986617292713816[270] = 0.0;
   out_3468986617292713816[271] = 0.0;
   out_3468986617292713816[272] = 0.0;
   out_3468986617292713816[273] = 0.0;
   out_3468986617292713816[274] = 0.0;
   out_3468986617292713816[275] = 0.0;
   out_3468986617292713816[276] = 0.0;
   out_3468986617292713816[277] = 0.0;
   out_3468986617292713816[278] = 0.0;
   out_3468986617292713816[279] = 0.0;
   out_3468986617292713816[280] = 0.0;
   out_3468986617292713816[281] = 0.0;
   out_3468986617292713816[282] = 0.0;
   out_3468986617292713816[283] = 0.0;
   out_3468986617292713816[284] = 0.0;
   out_3468986617292713816[285] = 1.0;
   out_3468986617292713816[286] = 0.0;
   out_3468986617292713816[287] = 0.0;
   out_3468986617292713816[288] = 0.0;
   out_3468986617292713816[289] = 0.0;
   out_3468986617292713816[290] = 0.0;
   out_3468986617292713816[291] = 0.0;
   out_3468986617292713816[292] = 0.0;
   out_3468986617292713816[293] = 0.0;
   out_3468986617292713816[294] = 0.0;
   out_3468986617292713816[295] = 0.0;
   out_3468986617292713816[296] = 0.0;
   out_3468986617292713816[297] = 0.0;
   out_3468986617292713816[298] = 0.0;
   out_3468986617292713816[299] = 0.0;
   out_3468986617292713816[300] = 0.0;
   out_3468986617292713816[301] = 0.0;
   out_3468986617292713816[302] = 0.0;
   out_3468986617292713816[303] = 0.0;
   out_3468986617292713816[304] = 1.0;
   out_3468986617292713816[305] = 0.0;
   out_3468986617292713816[306] = 0.0;
   out_3468986617292713816[307] = 0.0;
   out_3468986617292713816[308] = 0.0;
   out_3468986617292713816[309] = 0.0;
   out_3468986617292713816[310] = 0.0;
   out_3468986617292713816[311] = 0.0;
   out_3468986617292713816[312] = 0.0;
   out_3468986617292713816[313] = 0.0;
   out_3468986617292713816[314] = 0.0;
   out_3468986617292713816[315] = 0.0;
   out_3468986617292713816[316] = 0.0;
   out_3468986617292713816[317] = 0.0;
   out_3468986617292713816[318] = 0.0;
   out_3468986617292713816[319] = 0.0;
   out_3468986617292713816[320] = 0.0;
   out_3468986617292713816[321] = 0.0;
   out_3468986617292713816[322] = 0.0;
   out_3468986617292713816[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5742408842642162042) {
   out_5742408842642162042[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5742408842642162042[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5742408842642162042[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5742408842642162042[3] = dt*state[12] + state[3];
   out_5742408842642162042[4] = dt*state[13] + state[4];
   out_5742408842642162042[5] = dt*state[14] + state[5];
   out_5742408842642162042[6] = state[6];
   out_5742408842642162042[7] = state[7];
   out_5742408842642162042[8] = state[8];
   out_5742408842642162042[9] = state[9];
   out_5742408842642162042[10] = state[10];
   out_5742408842642162042[11] = state[11];
   out_5742408842642162042[12] = state[12];
   out_5742408842642162042[13] = state[13];
   out_5742408842642162042[14] = state[14];
   out_5742408842642162042[15] = state[15];
   out_5742408842642162042[16] = state[16];
   out_5742408842642162042[17] = state[17];
}
void F_fun(double *state, double dt, double *out_9145761553590380035) {
   out_9145761553590380035[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9145761553590380035[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9145761553590380035[2] = 0;
   out_9145761553590380035[3] = 0;
   out_9145761553590380035[4] = 0;
   out_9145761553590380035[5] = 0;
   out_9145761553590380035[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9145761553590380035[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9145761553590380035[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9145761553590380035[9] = 0;
   out_9145761553590380035[10] = 0;
   out_9145761553590380035[11] = 0;
   out_9145761553590380035[12] = 0;
   out_9145761553590380035[13] = 0;
   out_9145761553590380035[14] = 0;
   out_9145761553590380035[15] = 0;
   out_9145761553590380035[16] = 0;
   out_9145761553590380035[17] = 0;
   out_9145761553590380035[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9145761553590380035[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9145761553590380035[20] = 0;
   out_9145761553590380035[21] = 0;
   out_9145761553590380035[22] = 0;
   out_9145761553590380035[23] = 0;
   out_9145761553590380035[24] = 0;
   out_9145761553590380035[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9145761553590380035[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9145761553590380035[27] = 0;
   out_9145761553590380035[28] = 0;
   out_9145761553590380035[29] = 0;
   out_9145761553590380035[30] = 0;
   out_9145761553590380035[31] = 0;
   out_9145761553590380035[32] = 0;
   out_9145761553590380035[33] = 0;
   out_9145761553590380035[34] = 0;
   out_9145761553590380035[35] = 0;
   out_9145761553590380035[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9145761553590380035[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9145761553590380035[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9145761553590380035[39] = 0;
   out_9145761553590380035[40] = 0;
   out_9145761553590380035[41] = 0;
   out_9145761553590380035[42] = 0;
   out_9145761553590380035[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9145761553590380035[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9145761553590380035[45] = 0;
   out_9145761553590380035[46] = 0;
   out_9145761553590380035[47] = 0;
   out_9145761553590380035[48] = 0;
   out_9145761553590380035[49] = 0;
   out_9145761553590380035[50] = 0;
   out_9145761553590380035[51] = 0;
   out_9145761553590380035[52] = 0;
   out_9145761553590380035[53] = 0;
   out_9145761553590380035[54] = 0;
   out_9145761553590380035[55] = 0;
   out_9145761553590380035[56] = 0;
   out_9145761553590380035[57] = 1;
   out_9145761553590380035[58] = 0;
   out_9145761553590380035[59] = 0;
   out_9145761553590380035[60] = 0;
   out_9145761553590380035[61] = 0;
   out_9145761553590380035[62] = 0;
   out_9145761553590380035[63] = 0;
   out_9145761553590380035[64] = 0;
   out_9145761553590380035[65] = 0;
   out_9145761553590380035[66] = dt;
   out_9145761553590380035[67] = 0;
   out_9145761553590380035[68] = 0;
   out_9145761553590380035[69] = 0;
   out_9145761553590380035[70] = 0;
   out_9145761553590380035[71] = 0;
   out_9145761553590380035[72] = 0;
   out_9145761553590380035[73] = 0;
   out_9145761553590380035[74] = 0;
   out_9145761553590380035[75] = 0;
   out_9145761553590380035[76] = 1;
   out_9145761553590380035[77] = 0;
   out_9145761553590380035[78] = 0;
   out_9145761553590380035[79] = 0;
   out_9145761553590380035[80] = 0;
   out_9145761553590380035[81] = 0;
   out_9145761553590380035[82] = 0;
   out_9145761553590380035[83] = 0;
   out_9145761553590380035[84] = 0;
   out_9145761553590380035[85] = dt;
   out_9145761553590380035[86] = 0;
   out_9145761553590380035[87] = 0;
   out_9145761553590380035[88] = 0;
   out_9145761553590380035[89] = 0;
   out_9145761553590380035[90] = 0;
   out_9145761553590380035[91] = 0;
   out_9145761553590380035[92] = 0;
   out_9145761553590380035[93] = 0;
   out_9145761553590380035[94] = 0;
   out_9145761553590380035[95] = 1;
   out_9145761553590380035[96] = 0;
   out_9145761553590380035[97] = 0;
   out_9145761553590380035[98] = 0;
   out_9145761553590380035[99] = 0;
   out_9145761553590380035[100] = 0;
   out_9145761553590380035[101] = 0;
   out_9145761553590380035[102] = 0;
   out_9145761553590380035[103] = 0;
   out_9145761553590380035[104] = dt;
   out_9145761553590380035[105] = 0;
   out_9145761553590380035[106] = 0;
   out_9145761553590380035[107] = 0;
   out_9145761553590380035[108] = 0;
   out_9145761553590380035[109] = 0;
   out_9145761553590380035[110] = 0;
   out_9145761553590380035[111] = 0;
   out_9145761553590380035[112] = 0;
   out_9145761553590380035[113] = 0;
   out_9145761553590380035[114] = 1;
   out_9145761553590380035[115] = 0;
   out_9145761553590380035[116] = 0;
   out_9145761553590380035[117] = 0;
   out_9145761553590380035[118] = 0;
   out_9145761553590380035[119] = 0;
   out_9145761553590380035[120] = 0;
   out_9145761553590380035[121] = 0;
   out_9145761553590380035[122] = 0;
   out_9145761553590380035[123] = 0;
   out_9145761553590380035[124] = 0;
   out_9145761553590380035[125] = 0;
   out_9145761553590380035[126] = 0;
   out_9145761553590380035[127] = 0;
   out_9145761553590380035[128] = 0;
   out_9145761553590380035[129] = 0;
   out_9145761553590380035[130] = 0;
   out_9145761553590380035[131] = 0;
   out_9145761553590380035[132] = 0;
   out_9145761553590380035[133] = 1;
   out_9145761553590380035[134] = 0;
   out_9145761553590380035[135] = 0;
   out_9145761553590380035[136] = 0;
   out_9145761553590380035[137] = 0;
   out_9145761553590380035[138] = 0;
   out_9145761553590380035[139] = 0;
   out_9145761553590380035[140] = 0;
   out_9145761553590380035[141] = 0;
   out_9145761553590380035[142] = 0;
   out_9145761553590380035[143] = 0;
   out_9145761553590380035[144] = 0;
   out_9145761553590380035[145] = 0;
   out_9145761553590380035[146] = 0;
   out_9145761553590380035[147] = 0;
   out_9145761553590380035[148] = 0;
   out_9145761553590380035[149] = 0;
   out_9145761553590380035[150] = 0;
   out_9145761553590380035[151] = 0;
   out_9145761553590380035[152] = 1;
   out_9145761553590380035[153] = 0;
   out_9145761553590380035[154] = 0;
   out_9145761553590380035[155] = 0;
   out_9145761553590380035[156] = 0;
   out_9145761553590380035[157] = 0;
   out_9145761553590380035[158] = 0;
   out_9145761553590380035[159] = 0;
   out_9145761553590380035[160] = 0;
   out_9145761553590380035[161] = 0;
   out_9145761553590380035[162] = 0;
   out_9145761553590380035[163] = 0;
   out_9145761553590380035[164] = 0;
   out_9145761553590380035[165] = 0;
   out_9145761553590380035[166] = 0;
   out_9145761553590380035[167] = 0;
   out_9145761553590380035[168] = 0;
   out_9145761553590380035[169] = 0;
   out_9145761553590380035[170] = 0;
   out_9145761553590380035[171] = 1;
   out_9145761553590380035[172] = 0;
   out_9145761553590380035[173] = 0;
   out_9145761553590380035[174] = 0;
   out_9145761553590380035[175] = 0;
   out_9145761553590380035[176] = 0;
   out_9145761553590380035[177] = 0;
   out_9145761553590380035[178] = 0;
   out_9145761553590380035[179] = 0;
   out_9145761553590380035[180] = 0;
   out_9145761553590380035[181] = 0;
   out_9145761553590380035[182] = 0;
   out_9145761553590380035[183] = 0;
   out_9145761553590380035[184] = 0;
   out_9145761553590380035[185] = 0;
   out_9145761553590380035[186] = 0;
   out_9145761553590380035[187] = 0;
   out_9145761553590380035[188] = 0;
   out_9145761553590380035[189] = 0;
   out_9145761553590380035[190] = 1;
   out_9145761553590380035[191] = 0;
   out_9145761553590380035[192] = 0;
   out_9145761553590380035[193] = 0;
   out_9145761553590380035[194] = 0;
   out_9145761553590380035[195] = 0;
   out_9145761553590380035[196] = 0;
   out_9145761553590380035[197] = 0;
   out_9145761553590380035[198] = 0;
   out_9145761553590380035[199] = 0;
   out_9145761553590380035[200] = 0;
   out_9145761553590380035[201] = 0;
   out_9145761553590380035[202] = 0;
   out_9145761553590380035[203] = 0;
   out_9145761553590380035[204] = 0;
   out_9145761553590380035[205] = 0;
   out_9145761553590380035[206] = 0;
   out_9145761553590380035[207] = 0;
   out_9145761553590380035[208] = 0;
   out_9145761553590380035[209] = 1;
   out_9145761553590380035[210] = 0;
   out_9145761553590380035[211] = 0;
   out_9145761553590380035[212] = 0;
   out_9145761553590380035[213] = 0;
   out_9145761553590380035[214] = 0;
   out_9145761553590380035[215] = 0;
   out_9145761553590380035[216] = 0;
   out_9145761553590380035[217] = 0;
   out_9145761553590380035[218] = 0;
   out_9145761553590380035[219] = 0;
   out_9145761553590380035[220] = 0;
   out_9145761553590380035[221] = 0;
   out_9145761553590380035[222] = 0;
   out_9145761553590380035[223] = 0;
   out_9145761553590380035[224] = 0;
   out_9145761553590380035[225] = 0;
   out_9145761553590380035[226] = 0;
   out_9145761553590380035[227] = 0;
   out_9145761553590380035[228] = 1;
   out_9145761553590380035[229] = 0;
   out_9145761553590380035[230] = 0;
   out_9145761553590380035[231] = 0;
   out_9145761553590380035[232] = 0;
   out_9145761553590380035[233] = 0;
   out_9145761553590380035[234] = 0;
   out_9145761553590380035[235] = 0;
   out_9145761553590380035[236] = 0;
   out_9145761553590380035[237] = 0;
   out_9145761553590380035[238] = 0;
   out_9145761553590380035[239] = 0;
   out_9145761553590380035[240] = 0;
   out_9145761553590380035[241] = 0;
   out_9145761553590380035[242] = 0;
   out_9145761553590380035[243] = 0;
   out_9145761553590380035[244] = 0;
   out_9145761553590380035[245] = 0;
   out_9145761553590380035[246] = 0;
   out_9145761553590380035[247] = 1;
   out_9145761553590380035[248] = 0;
   out_9145761553590380035[249] = 0;
   out_9145761553590380035[250] = 0;
   out_9145761553590380035[251] = 0;
   out_9145761553590380035[252] = 0;
   out_9145761553590380035[253] = 0;
   out_9145761553590380035[254] = 0;
   out_9145761553590380035[255] = 0;
   out_9145761553590380035[256] = 0;
   out_9145761553590380035[257] = 0;
   out_9145761553590380035[258] = 0;
   out_9145761553590380035[259] = 0;
   out_9145761553590380035[260] = 0;
   out_9145761553590380035[261] = 0;
   out_9145761553590380035[262] = 0;
   out_9145761553590380035[263] = 0;
   out_9145761553590380035[264] = 0;
   out_9145761553590380035[265] = 0;
   out_9145761553590380035[266] = 1;
   out_9145761553590380035[267] = 0;
   out_9145761553590380035[268] = 0;
   out_9145761553590380035[269] = 0;
   out_9145761553590380035[270] = 0;
   out_9145761553590380035[271] = 0;
   out_9145761553590380035[272] = 0;
   out_9145761553590380035[273] = 0;
   out_9145761553590380035[274] = 0;
   out_9145761553590380035[275] = 0;
   out_9145761553590380035[276] = 0;
   out_9145761553590380035[277] = 0;
   out_9145761553590380035[278] = 0;
   out_9145761553590380035[279] = 0;
   out_9145761553590380035[280] = 0;
   out_9145761553590380035[281] = 0;
   out_9145761553590380035[282] = 0;
   out_9145761553590380035[283] = 0;
   out_9145761553590380035[284] = 0;
   out_9145761553590380035[285] = 1;
   out_9145761553590380035[286] = 0;
   out_9145761553590380035[287] = 0;
   out_9145761553590380035[288] = 0;
   out_9145761553590380035[289] = 0;
   out_9145761553590380035[290] = 0;
   out_9145761553590380035[291] = 0;
   out_9145761553590380035[292] = 0;
   out_9145761553590380035[293] = 0;
   out_9145761553590380035[294] = 0;
   out_9145761553590380035[295] = 0;
   out_9145761553590380035[296] = 0;
   out_9145761553590380035[297] = 0;
   out_9145761553590380035[298] = 0;
   out_9145761553590380035[299] = 0;
   out_9145761553590380035[300] = 0;
   out_9145761553590380035[301] = 0;
   out_9145761553590380035[302] = 0;
   out_9145761553590380035[303] = 0;
   out_9145761553590380035[304] = 1;
   out_9145761553590380035[305] = 0;
   out_9145761553590380035[306] = 0;
   out_9145761553590380035[307] = 0;
   out_9145761553590380035[308] = 0;
   out_9145761553590380035[309] = 0;
   out_9145761553590380035[310] = 0;
   out_9145761553590380035[311] = 0;
   out_9145761553590380035[312] = 0;
   out_9145761553590380035[313] = 0;
   out_9145761553590380035[314] = 0;
   out_9145761553590380035[315] = 0;
   out_9145761553590380035[316] = 0;
   out_9145761553590380035[317] = 0;
   out_9145761553590380035[318] = 0;
   out_9145761553590380035[319] = 0;
   out_9145761553590380035[320] = 0;
   out_9145761553590380035[321] = 0;
   out_9145761553590380035[322] = 0;
   out_9145761553590380035[323] = 1;
}
void h_4(double *state, double *unused, double *out_3188976776469400668) {
   out_3188976776469400668[0] = state[6] + state[9];
   out_3188976776469400668[1] = state[7] + state[10];
   out_3188976776469400668[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2271039135409815712) {
   out_2271039135409815712[0] = 0;
   out_2271039135409815712[1] = 0;
   out_2271039135409815712[2] = 0;
   out_2271039135409815712[3] = 0;
   out_2271039135409815712[4] = 0;
   out_2271039135409815712[5] = 0;
   out_2271039135409815712[6] = 1;
   out_2271039135409815712[7] = 0;
   out_2271039135409815712[8] = 0;
   out_2271039135409815712[9] = 1;
   out_2271039135409815712[10] = 0;
   out_2271039135409815712[11] = 0;
   out_2271039135409815712[12] = 0;
   out_2271039135409815712[13] = 0;
   out_2271039135409815712[14] = 0;
   out_2271039135409815712[15] = 0;
   out_2271039135409815712[16] = 0;
   out_2271039135409815712[17] = 0;
   out_2271039135409815712[18] = 0;
   out_2271039135409815712[19] = 0;
   out_2271039135409815712[20] = 0;
   out_2271039135409815712[21] = 0;
   out_2271039135409815712[22] = 0;
   out_2271039135409815712[23] = 0;
   out_2271039135409815712[24] = 0;
   out_2271039135409815712[25] = 1;
   out_2271039135409815712[26] = 0;
   out_2271039135409815712[27] = 0;
   out_2271039135409815712[28] = 1;
   out_2271039135409815712[29] = 0;
   out_2271039135409815712[30] = 0;
   out_2271039135409815712[31] = 0;
   out_2271039135409815712[32] = 0;
   out_2271039135409815712[33] = 0;
   out_2271039135409815712[34] = 0;
   out_2271039135409815712[35] = 0;
   out_2271039135409815712[36] = 0;
   out_2271039135409815712[37] = 0;
   out_2271039135409815712[38] = 0;
   out_2271039135409815712[39] = 0;
   out_2271039135409815712[40] = 0;
   out_2271039135409815712[41] = 0;
   out_2271039135409815712[42] = 0;
   out_2271039135409815712[43] = 0;
   out_2271039135409815712[44] = 1;
   out_2271039135409815712[45] = 0;
   out_2271039135409815712[46] = 0;
   out_2271039135409815712[47] = 1;
   out_2271039135409815712[48] = 0;
   out_2271039135409815712[49] = 0;
   out_2271039135409815712[50] = 0;
   out_2271039135409815712[51] = 0;
   out_2271039135409815712[52] = 0;
   out_2271039135409815712[53] = 0;
}
void h_10(double *state, double *unused, double *out_4978471082043505925) {
   out_4978471082043505925[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4978471082043505925[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4978471082043505925[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6025972524295180069) {
   out_6025972524295180069[0] = 0;
   out_6025972524295180069[1] = 9.8100000000000005*cos(state[1]);
   out_6025972524295180069[2] = 0;
   out_6025972524295180069[3] = 0;
   out_6025972524295180069[4] = -state[8];
   out_6025972524295180069[5] = state[7];
   out_6025972524295180069[6] = 0;
   out_6025972524295180069[7] = state[5];
   out_6025972524295180069[8] = -state[4];
   out_6025972524295180069[9] = 0;
   out_6025972524295180069[10] = 0;
   out_6025972524295180069[11] = 0;
   out_6025972524295180069[12] = 1;
   out_6025972524295180069[13] = 0;
   out_6025972524295180069[14] = 0;
   out_6025972524295180069[15] = 1;
   out_6025972524295180069[16] = 0;
   out_6025972524295180069[17] = 0;
   out_6025972524295180069[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6025972524295180069[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6025972524295180069[20] = 0;
   out_6025972524295180069[21] = state[8];
   out_6025972524295180069[22] = 0;
   out_6025972524295180069[23] = -state[6];
   out_6025972524295180069[24] = -state[5];
   out_6025972524295180069[25] = 0;
   out_6025972524295180069[26] = state[3];
   out_6025972524295180069[27] = 0;
   out_6025972524295180069[28] = 0;
   out_6025972524295180069[29] = 0;
   out_6025972524295180069[30] = 0;
   out_6025972524295180069[31] = 1;
   out_6025972524295180069[32] = 0;
   out_6025972524295180069[33] = 0;
   out_6025972524295180069[34] = 1;
   out_6025972524295180069[35] = 0;
   out_6025972524295180069[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6025972524295180069[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6025972524295180069[38] = 0;
   out_6025972524295180069[39] = -state[7];
   out_6025972524295180069[40] = state[6];
   out_6025972524295180069[41] = 0;
   out_6025972524295180069[42] = state[4];
   out_6025972524295180069[43] = -state[3];
   out_6025972524295180069[44] = 0;
   out_6025972524295180069[45] = 0;
   out_6025972524295180069[46] = 0;
   out_6025972524295180069[47] = 0;
   out_6025972524295180069[48] = 0;
   out_6025972524295180069[49] = 0;
   out_6025972524295180069[50] = 1;
   out_6025972524295180069[51] = 0;
   out_6025972524295180069[52] = 0;
   out_6025972524295180069[53] = 1;
}
void h_13(double *state, double *unused, double *out_3010889495309434270) {
   out_3010889495309434270[0] = state[3];
   out_3010889495309434270[1] = state[4];
   out_3010889495309434270[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6104794598712339736) {
   out_6104794598712339736[0] = 0;
   out_6104794598712339736[1] = 0;
   out_6104794598712339736[2] = 0;
   out_6104794598712339736[3] = 1;
   out_6104794598712339736[4] = 0;
   out_6104794598712339736[5] = 0;
   out_6104794598712339736[6] = 0;
   out_6104794598712339736[7] = 0;
   out_6104794598712339736[8] = 0;
   out_6104794598712339736[9] = 0;
   out_6104794598712339736[10] = 0;
   out_6104794598712339736[11] = 0;
   out_6104794598712339736[12] = 0;
   out_6104794598712339736[13] = 0;
   out_6104794598712339736[14] = 0;
   out_6104794598712339736[15] = 0;
   out_6104794598712339736[16] = 0;
   out_6104794598712339736[17] = 0;
   out_6104794598712339736[18] = 0;
   out_6104794598712339736[19] = 0;
   out_6104794598712339736[20] = 0;
   out_6104794598712339736[21] = 0;
   out_6104794598712339736[22] = 1;
   out_6104794598712339736[23] = 0;
   out_6104794598712339736[24] = 0;
   out_6104794598712339736[25] = 0;
   out_6104794598712339736[26] = 0;
   out_6104794598712339736[27] = 0;
   out_6104794598712339736[28] = 0;
   out_6104794598712339736[29] = 0;
   out_6104794598712339736[30] = 0;
   out_6104794598712339736[31] = 0;
   out_6104794598712339736[32] = 0;
   out_6104794598712339736[33] = 0;
   out_6104794598712339736[34] = 0;
   out_6104794598712339736[35] = 0;
   out_6104794598712339736[36] = 0;
   out_6104794598712339736[37] = 0;
   out_6104794598712339736[38] = 0;
   out_6104794598712339736[39] = 0;
   out_6104794598712339736[40] = 0;
   out_6104794598712339736[41] = 1;
   out_6104794598712339736[42] = 0;
   out_6104794598712339736[43] = 0;
   out_6104794598712339736[44] = 0;
   out_6104794598712339736[45] = 0;
   out_6104794598712339736[46] = 0;
   out_6104794598712339736[47] = 0;
   out_6104794598712339736[48] = 0;
   out_6104794598712339736[49] = 0;
   out_6104794598712339736[50] = 0;
   out_6104794598712339736[51] = 0;
   out_6104794598712339736[52] = 0;
   out_6104794598712339736[53] = 0;
}
void h_14(double *state, double *unused, double *out_7339283631215046728) {
   out_7339283631215046728[0] = state[6];
   out_7339283631215046728[1] = state[7];
   out_7339283631215046728[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8694559123019995480) {
   out_8694559123019995480[0] = 0;
   out_8694559123019995480[1] = 0;
   out_8694559123019995480[2] = 0;
   out_8694559123019995480[3] = 0;
   out_8694559123019995480[4] = 0;
   out_8694559123019995480[5] = 0;
   out_8694559123019995480[6] = 1;
   out_8694559123019995480[7] = 0;
   out_8694559123019995480[8] = 0;
   out_8694559123019995480[9] = 0;
   out_8694559123019995480[10] = 0;
   out_8694559123019995480[11] = 0;
   out_8694559123019995480[12] = 0;
   out_8694559123019995480[13] = 0;
   out_8694559123019995480[14] = 0;
   out_8694559123019995480[15] = 0;
   out_8694559123019995480[16] = 0;
   out_8694559123019995480[17] = 0;
   out_8694559123019995480[18] = 0;
   out_8694559123019995480[19] = 0;
   out_8694559123019995480[20] = 0;
   out_8694559123019995480[21] = 0;
   out_8694559123019995480[22] = 0;
   out_8694559123019995480[23] = 0;
   out_8694559123019995480[24] = 0;
   out_8694559123019995480[25] = 1;
   out_8694559123019995480[26] = 0;
   out_8694559123019995480[27] = 0;
   out_8694559123019995480[28] = 0;
   out_8694559123019995480[29] = 0;
   out_8694559123019995480[30] = 0;
   out_8694559123019995480[31] = 0;
   out_8694559123019995480[32] = 0;
   out_8694559123019995480[33] = 0;
   out_8694559123019995480[34] = 0;
   out_8694559123019995480[35] = 0;
   out_8694559123019995480[36] = 0;
   out_8694559123019995480[37] = 0;
   out_8694559123019995480[38] = 0;
   out_8694559123019995480[39] = 0;
   out_8694559123019995480[40] = 0;
   out_8694559123019995480[41] = 0;
   out_8694559123019995480[42] = 0;
   out_8694559123019995480[43] = 0;
   out_8694559123019995480[44] = 1;
   out_8694559123019995480[45] = 0;
   out_8694559123019995480[46] = 0;
   out_8694559123019995480[47] = 0;
   out_8694559123019995480[48] = 0;
   out_8694559123019995480[49] = 0;
   out_8694559123019995480[50] = 0;
   out_8694559123019995480[51] = 0;
   out_8694559123019995480[52] = 0;
   out_8694559123019995480[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6370445090975775647) {
  err_fun(nom_x, delta_x, out_6370445090975775647);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1677323290782450214) {
  inv_err_fun(nom_x, true_x, out_1677323290782450214);
}
void pose_H_mod_fun(double *state, double *out_3468986617292713816) {
  H_mod_fun(state, out_3468986617292713816);
}
void pose_f_fun(double *state, double dt, double *out_5742408842642162042) {
  f_fun(state,  dt, out_5742408842642162042);
}
void pose_F_fun(double *state, double dt, double *out_9145761553590380035) {
  F_fun(state,  dt, out_9145761553590380035);
}
void pose_h_4(double *state, double *unused, double *out_3188976776469400668) {
  h_4(state, unused, out_3188976776469400668);
}
void pose_H_4(double *state, double *unused, double *out_2271039135409815712) {
  H_4(state, unused, out_2271039135409815712);
}
void pose_h_10(double *state, double *unused, double *out_4978471082043505925) {
  h_10(state, unused, out_4978471082043505925);
}
void pose_H_10(double *state, double *unused, double *out_6025972524295180069) {
  H_10(state, unused, out_6025972524295180069);
}
void pose_h_13(double *state, double *unused, double *out_3010889495309434270) {
  h_13(state, unused, out_3010889495309434270);
}
void pose_H_13(double *state, double *unused, double *out_6104794598712339736) {
  H_13(state, unused, out_6104794598712339736);
}
void pose_h_14(double *state, double *unused, double *out_7339283631215046728) {
  h_14(state, unused, out_7339283631215046728);
}
void pose_H_14(double *state, double *unused, double *out_8694559123019995480) {
  H_14(state, unused, out_8694559123019995480);
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
