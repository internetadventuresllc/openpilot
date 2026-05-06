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
void err_fun(double *nom_x, double *delta_x, double *out_495600354373200881) {
   out_495600354373200881[0] = delta_x[0] + nom_x[0];
   out_495600354373200881[1] = delta_x[1] + nom_x[1];
   out_495600354373200881[2] = delta_x[2] + nom_x[2];
   out_495600354373200881[3] = delta_x[3] + nom_x[3];
   out_495600354373200881[4] = delta_x[4] + nom_x[4];
   out_495600354373200881[5] = delta_x[5] + nom_x[5];
   out_495600354373200881[6] = delta_x[6] + nom_x[6];
   out_495600354373200881[7] = delta_x[7] + nom_x[7];
   out_495600354373200881[8] = delta_x[8] + nom_x[8];
   out_495600354373200881[9] = delta_x[9] + nom_x[9];
   out_495600354373200881[10] = delta_x[10] + nom_x[10];
   out_495600354373200881[11] = delta_x[11] + nom_x[11];
   out_495600354373200881[12] = delta_x[12] + nom_x[12];
   out_495600354373200881[13] = delta_x[13] + nom_x[13];
   out_495600354373200881[14] = delta_x[14] + nom_x[14];
   out_495600354373200881[15] = delta_x[15] + nom_x[15];
   out_495600354373200881[16] = delta_x[16] + nom_x[16];
   out_495600354373200881[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1169161554918362952) {
   out_1169161554918362952[0] = -nom_x[0] + true_x[0];
   out_1169161554918362952[1] = -nom_x[1] + true_x[1];
   out_1169161554918362952[2] = -nom_x[2] + true_x[2];
   out_1169161554918362952[3] = -nom_x[3] + true_x[3];
   out_1169161554918362952[4] = -nom_x[4] + true_x[4];
   out_1169161554918362952[5] = -nom_x[5] + true_x[5];
   out_1169161554918362952[6] = -nom_x[6] + true_x[6];
   out_1169161554918362952[7] = -nom_x[7] + true_x[7];
   out_1169161554918362952[8] = -nom_x[8] + true_x[8];
   out_1169161554918362952[9] = -nom_x[9] + true_x[9];
   out_1169161554918362952[10] = -nom_x[10] + true_x[10];
   out_1169161554918362952[11] = -nom_x[11] + true_x[11];
   out_1169161554918362952[12] = -nom_x[12] + true_x[12];
   out_1169161554918362952[13] = -nom_x[13] + true_x[13];
   out_1169161554918362952[14] = -nom_x[14] + true_x[14];
   out_1169161554918362952[15] = -nom_x[15] + true_x[15];
   out_1169161554918362952[16] = -nom_x[16] + true_x[16];
   out_1169161554918362952[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_269990567082015073) {
   out_269990567082015073[0] = 1.0;
   out_269990567082015073[1] = 0.0;
   out_269990567082015073[2] = 0.0;
   out_269990567082015073[3] = 0.0;
   out_269990567082015073[4] = 0.0;
   out_269990567082015073[5] = 0.0;
   out_269990567082015073[6] = 0.0;
   out_269990567082015073[7] = 0.0;
   out_269990567082015073[8] = 0.0;
   out_269990567082015073[9] = 0.0;
   out_269990567082015073[10] = 0.0;
   out_269990567082015073[11] = 0.0;
   out_269990567082015073[12] = 0.0;
   out_269990567082015073[13] = 0.0;
   out_269990567082015073[14] = 0.0;
   out_269990567082015073[15] = 0.0;
   out_269990567082015073[16] = 0.0;
   out_269990567082015073[17] = 0.0;
   out_269990567082015073[18] = 0.0;
   out_269990567082015073[19] = 1.0;
   out_269990567082015073[20] = 0.0;
   out_269990567082015073[21] = 0.0;
   out_269990567082015073[22] = 0.0;
   out_269990567082015073[23] = 0.0;
   out_269990567082015073[24] = 0.0;
   out_269990567082015073[25] = 0.0;
   out_269990567082015073[26] = 0.0;
   out_269990567082015073[27] = 0.0;
   out_269990567082015073[28] = 0.0;
   out_269990567082015073[29] = 0.0;
   out_269990567082015073[30] = 0.0;
   out_269990567082015073[31] = 0.0;
   out_269990567082015073[32] = 0.0;
   out_269990567082015073[33] = 0.0;
   out_269990567082015073[34] = 0.0;
   out_269990567082015073[35] = 0.0;
   out_269990567082015073[36] = 0.0;
   out_269990567082015073[37] = 0.0;
   out_269990567082015073[38] = 1.0;
   out_269990567082015073[39] = 0.0;
   out_269990567082015073[40] = 0.0;
   out_269990567082015073[41] = 0.0;
   out_269990567082015073[42] = 0.0;
   out_269990567082015073[43] = 0.0;
   out_269990567082015073[44] = 0.0;
   out_269990567082015073[45] = 0.0;
   out_269990567082015073[46] = 0.0;
   out_269990567082015073[47] = 0.0;
   out_269990567082015073[48] = 0.0;
   out_269990567082015073[49] = 0.0;
   out_269990567082015073[50] = 0.0;
   out_269990567082015073[51] = 0.0;
   out_269990567082015073[52] = 0.0;
   out_269990567082015073[53] = 0.0;
   out_269990567082015073[54] = 0.0;
   out_269990567082015073[55] = 0.0;
   out_269990567082015073[56] = 0.0;
   out_269990567082015073[57] = 1.0;
   out_269990567082015073[58] = 0.0;
   out_269990567082015073[59] = 0.0;
   out_269990567082015073[60] = 0.0;
   out_269990567082015073[61] = 0.0;
   out_269990567082015073[62] = 0.0;
   out_269990567082015073[63] = 0.0;
   out_269990567082015073[64] = 0.0;
   out_269990567082015073[65] = 0.0;
   out_269990567082015073[66] = 0.0;
   out_269990567082015073[67] = 0.0;
   out_269990567082015073[68] = 0.0;
   out_269990567082015073[69] = 0.0;
   out_269990567082015073[70] = 0.0;
   out_269990567082015073[71] = 0.0;
   out_269990567082015073[72] = 0.0;
   out_269990567082015073[73] = 0.0;
   out_269990567082015073[74] = 0.0;
   out_269990567082015073[75] = 0.0;
   out_269990567082015073[76] = 1.0;
   out_269990567082015073[77] = 0.0;
   out_269990567082015073[78] = 0.0;
   out_269990567082015073[79] = 0.0;
   out_269990567082015073[80] = 0.0;
   out_269990567082015073[81] = 0.0;
   out_269990567082015073[82] = 0.0;
   out_269990567082015073[83] = 0.0;
   out_269990567082015073[84] = 0.0;
   out_269990567082015073[85] = 0.0;
   out_269990567082015073[86] = 0.0;
   out_269990567082015073[87] = 0.0;
   out_269990567082015073[88] = 0.0;
   out_269990567082015073[89] = 0.0;
   out_269990567082015073[90] = 0.0;
   out_269990567082015073[91] = 0.0;
   out_269990567082015073[92] = 0.0;
   out_269990567082015073[93] = 0.0;
   out_269990567082015073[94] = 0.0;
   out_269990567082015073[95] = 1.0;
   out_269990567082015073[96] = 0.0;
   out_269990567082015073[97] = 0.0;
   out_269990567082015073[98] = 0.0;
   out_269990567082015073[99] = 0.0;
   out_269990567082015073[100] = 0.0;
   out_269990567082015073[101] = 0.0;
   out_269990567082015073[102] = 0.0;
   out_269990567082015073[103] = 0.0;
   out_269990567082015073[104] = 0.0;
   out_269990567082015073[105] = 0.0;
   out_269990567082015073[106] = 0.0;
   out_269990567082015073[107] = 0.0;
   out_269990567082015073[108] = 0.0;
   out_269990567082015073[109] = 0.0;
   out_269990567082015073[110] = 0.0;
   out_269990567082015073[111] = 0.0;
   out_269990567082015073[112] = 0.0;
   out_269990567082015073[113] = 0.0;
   out_269990567082015073[114] = 1.0;
   out_269990567082015073[115] = 0.0;
   out_269990567082015073[116] = 0.0;
   out_269990567082015073[117] = 0.0;
   out_269990567082015073[118] = 0.0;
   out_269990567082015073[119] = 0.0;
   out_269990567082015073[120] = 0.0;
   out_269990567082015073[121] = 0.0;
   out_269990567082015073[122] = 0.0;
   out_269990567082015073[123] = 0.0;
   out_269990567082015073[124] = 0.0;
   out_269990567082015073[125] = 0.0;
   out_269990567082015073[126] = 0.0;
   out_269990567082015073[127] = 0.0;
   out_269990567082015073[128] = 0.0;
   out_269990567082015073[129] = 0.0;
   out_269990567082015073[130] = 0.0;
   out_269990567082015073[131] = 0.0;
   out_269990567082015073[132] = 0.0;
   out_269990567082015073[133] = 1.0;
   out_269990567082015073[134] = 0.0;
   out_269990567082015073[135] = 0.0;
   out_269990567082015073[136] = 0.0;
   out_269990567082015073[137] = 0.0;
   out_269990567082015073[138] = 0.0;
   out_269990567082015073[139] = 0.0;
   out_269990567082015073[140] = 0.0;
   out_269990567082015073[141] = 0.0;
   out_269990567082015073[142] = 0.0;
   out_269990567082015073[143] = 0.0;
   out_269990567082015073[144] = 0.0;
   out_269990567082015073[145] = 0.0;
   out_269990567082015073[146] = 0.0;
   out_269990567082015073[147] = 0.0;
   out_269990567082015073[148] = 0.0;
   out_269990567082015073[149] = 0.0;
   out_269990567082015073[150] = 0.0;
   out_269990567082015073[151] = 0.0;
   out_269990567082015073[152] = 1.0;
   out_269990567082015073[153] = 0.0;
   out_269990567082015073[154] = 0.0;
   out_269990567082015073[155] = 0.0;
   out_269990567082015073[156] = 0.0;
   out_269990567082015073[157] = 0.0;
   out_269990567082015073[158] = 0.0;
   out_269990567082015073[159] = 0.0;
   out_269990567082015073[160] = 0.0;
   out_269990567082015073[161] = 0.0;
   out_269990567082015073[162] = 0.0;
   out_269990567082015073[163] = 0.0;
   out_269990567082015073[164] = 0.0;
   out_269990567082015073[165] = 0.0;
   out_269990567082015073[166] = 0.0;
   out_269990567082015073[167] = 0.0;
   out_269990567082015073[168] = 0.0;
   out_269990567082015073[169] = 0.0;
   out_269990567082015073[170] = 0.0;
   out_269990567082015073[171] = 1.0;
   out_269990567082015073[172] = 0.0;
   out_269990567082015073[173] = 0.0;
   out_269990567082015073[174] = 0.0;
   out_269990567082015073[175] = 0.0;
   out_269990567082015073[176] = 0.0;
   out_269990567082015073[177] = 0.0;
   out_269990567082015073[178] = 0.0;
   out_269990567082015073[179] = 0.0;
   out_269990567082015073[180] = 0.0;
   out_269990567082015073[181] = 0.0;
   out_269990567082015073[182] = 0.0;
   out_269990567082015073[183] = 0.0;
   out_269990567082015073[184] = 0.0;
   out_269990567082015073[185] = 0.0;
   out_269990567082015073[186] = 0.0;
   out_269990567082015073[187] = 0.0;
   out_269990567082015073[188] = 0.0;
   out_269990567082015073[189] = 0.0;
   out_269990567082015073[190] = 1.0;
   out_269990567082015073[191] = 0.0;
   out_269990567082015073[192] = 0.0;
   out_269990567082015073[193] = 0.0;
   out_269990567082015073[194] = 0.0;
   out_269990567082015073[195] = 0.0;
   out_269990567082015073[196] = 0.0;
   out_269990567082015073[197] = 0.0;
   out_269990567082015073[198] = 0.0;
   out_269990567082015073[199] = 0.0;
   out_269990567082015073[200] = 0.0;
   out_269990567082015073[201] = 0.0;
   out_269990567082015073[202] = 0.0;
   out_269990567082015073[203] = 0.0;
   out_269990567082015073[204] = 0.0;
   out_269990567082015073[205] = 0.0;
   out_269990567082015073[206] = 0.0;
   out_269990567082015073[207] = 0.0;
   out_269990567082015073[208] = 0.0;
   out_269990567082015073[209] = 1.0;
   out_269990567082015073[210] = 0.0;
   out_269990567082015073[211] = 0.0;
   out_269990567082015073[212] = 0.0;
   out_269990567082015073[213] = 0.0;
   out_269990567082015073[214] = 0.0;
   out_269990567082015073[215] = 0.0;
   out_269990567082015073[216] = 0.0;
   out_269990567082015073[217] = 0.0;
   out_269990567082015073[218] = 0.0;
   out_269990567082015073[219] = 0.0;
   out_269990567082015073[220] = 0.0;
   out_269990567082015073[221] = 0.0;
   out_269990567082015073[222] = 0.0;
   out_269990567082015073[223] = 0.0;
   out_269990567082015073[224] = 0.0;
   out_269990567082015073[225] = 0.0;
   out_269990567082015073[226] = 0.0;
   out_269990567082015073[227] = 0.0;
   out_269990567082015073[228] = 1.0;
   out_269990567082015073[229] = 0.0;
   out_269990567082015073[230] = 0.0;
   out_269990567082015073[231] = 0.0;
   out_269990567082015073[232] = 0.0;
   out_269990567082015073[233] = 0.0;
   out_269990567082015073[234] = 0.0;
   out_269990567082015073[235] = 0.0;
   out_269990567082015073[236] = 0.0;
   out_269990567082015073[237] = 0.0;
   out_269990567082015073[238] = 0.0;
   out_269990567082015073[239] = 0.0;
   out_269990567082015073[240] = 0.0;
   out_269990567082015073[241] = 0.0;
   out_269990567082015073[242] = 0.0;
   out_269990567082015073[243] = 0.0;
   out_269990567082015073[244] = 0.0;
   out_269990567082015073[245] = 0.0;
   out_269990567082015073[246] = 0.0;
   out_269990567082015073[247] = 1.0;
   out_269990567082015073[248] = 0.0;
   out_269990567082015073[249] = 0.0;
   out_269990567082015073[250] = 0.0;
   out_269990567082015073[251] = 0.0;
   out_269990567082015073[252] = 0.0;
   out_269990567082015073[253] = 0.0;
   out_269990567082015073[254] = 0.0;
   out_269990567082015073[255] = 0.0;
   out_269990567082015073[256] = 0.0;
   out_269990567082015073[257] = 0.0;
   out_269990567082015073[258] = 0.0;
   out_269990567082015073[259] = 0.0;
   out_269990567082015073[260] = 0.0;
   out_269990567082015073[261] = 0.0;
   out_269990567082015073[262] = 0.0;
   out_269990567082015073[263] = 0.0;
   out_269990567082015073[264] = 0.0;
   out_269990567082015073[265] = 0.0;
   out_269990567082015073[266] = 1.0;
   out_269990567082015073[267] = 0.0;
   out_269990567082015073[268] = 0.0;
   out_269990567082015073[269] = 0.0;
   out_269990567082015073[270] = 0.0;
   out_269990567082015073[271] = 0.0;
   out_269990567082015073[272] = 0.0;
   out_269990567082015073[273] = 0.0;
   out_269990567082015073[274] = 0.0;
   out_269990567082015073[275] = 0.0;
   out_269990567082015073[276] = 0.0;
   out_269990567082015073[277] = 0.0;
   out_269990567082015073[278] = 0.0;
   out_269990567082015073[279] = 0.0;
   out_269990567082015073[280] = 0.0;
   out_269990567082015073[281] = 0.0;
   out_269990567082015073[282] = 0.0;
   out_269990567082015073[283] = 0.0;
   out_269990567082015073[284] = 0.0;
   out_269990567082015073[285] = 1.0;
   out_269990567082015073[286] = 0.0;
   out_269990567082015073[287] = 0.0;
   out_269990567082015073[288] = 0.0;
   out_269990567082015073[289] = 0.0;
   out_269990567082015073[290] = 0.0;
   out_269990567082015073[291] = 0.0;
   out_269990567082015073[292] = 0.0;
   out_269990567082015073[293] = 0.0;
   out_269990567082015073[294] = 0.0;
   out_269990567082015073[295] = 0.0;
   out_269990567082015073[296] = 0.0;
   out_269990567082015073[297] = 0.0;
   out_269990567082015073[298] = 0.0;
   out_269990567082015073[299] = 0.0;
   out_269990567082015073[300] = 0.0;
   out_269990567082015073[301] = 0.0;
   out_269990567082015073[302] = 0.0;
   out_269990567082015073[303] = 0.0;
   out_269990567082015073[304] = 1.0;
   out_269990567082015073[305] = 0.0;
   out_269990567082015073[306] = 0.0;
   out_269990567082015073[307] = 0.0;
   out_269990567082015073[308] = 0.0;
   out_269990567082015073[309] = 0.0;
   out_269990567082015073[310] = 0.0;
   out_269990567082015073[311] = 0.0;
   out_269990567082015073[312] = 0.0;
   out_269990567082015073[313] = 0.0;
   out_269990567082015073[314] = 0.0;
   out_269990567082015073[315] = 0.0;
   out_269990567082015073[316] = 0.0;
   out_269990567082015073[317] = 0.0;
   out_269990567082015073[318] = 0.0;
   out_269990567082015073[319] = 0.0;
   out_269990567082015073[320] = 0.0;
   out_269990567082015073[321] = 0.0;
   out_269990567082015073[322] = 0.0;
   out_269990567082015073[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2663299199207308722) {
   out_2663299199207308722[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2663299199207308722[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2663299199207308722[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2663299199207308722[3] = dt*state[12] + state[3];
   out_2663299199207308722[4] = dt*state[13] + state[4];
   out_2663299199207308722[5] = dt*state[14] + state[5];
   out_2663299199207308722[6] = state[6];
   out_2663299199207308722[7] = state[7];
   out_2663299199207308722[8] = state[8];
   out_2663299199207308722[9] = state[9];
   out_2663299199207308722[10] = state[10];
   out_2663299199207308722[11] = state[11];
   out_2663299199207308722[12] = state[12];
   out_2663299199207308722[13] = state[13];
   out_2663299199207308722[14] = state[14];
   out_2663299199207308722[15] = state[15];
   out_2663299199207308722[16] = state[16];
   out_2663299199207308722[17] = state[17];
}
void F_fun(double *state, double dt, double *out_502897361153597694) {
   out_502897361153597694[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_502897361153597694[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_502897361153597694[2] = 0;
   out_502897361153597694[3] = 0;
   out_502897361153597694[4] = 0;
   out_502897361153597694[5] = 0;
   out_502897361153597694[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_502897361153597694[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_502897361153597694[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_502897361153597694[9] = 0;
   out_502897361153597694[10] = 0;
   out_502897361153597694[11] = 0;
   out_502897361153597694[12] = 0;
   out_502897361153597694[13] = 0;
   out_502897361153597694[14] = 0;
   out_502897361153597694[15] = 0;
   out_502897361153597694[16] = 0;
   out_502897361153597694[17] = 0;
   out_502897361153597694[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_502897361153597694[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_502897361153597694[20] = 0;
   out_502897361153597694[21] = 0;
   out_502897361153597694[22] = 0;
   out_502897361153597694[23] = 0;
   out_502897361153597694[24] = 0;
   out_502897361153597694[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_502897361153597694[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_502897361153597694[27] = 0;
   out_502897361153597694[28] = 0;
   out_502897361153597694[29] = 0;
   out_502897361153597694[30] = 0;
   out_502897361153597694[31] = 0;
   out_502897361153597694[32] = 0;
   out_502897361153597694[33] = 0;
   out_502897361153597694[34] = 0;
   out_502897361153597694[35] = 0;
   out_502897361153597694[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_502897361153597694[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_502897361153597694[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_502897361153597694[39] = 0;
   out_502897361153597694[40] = 0;
   out_502897361153597694[41] = 0;
   out_502897361153597694[42] = 0;
   out_502897361153597694[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_502897361153597694[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_502897361153597694[45] = 0;
   out_502897361153597694[46] = 0;
   out_502897361153597694[47] = 0;
   out_502897361153597694[48] = 0;
   out_502897361153597694[49] = 0;
   out_502897361153597694[50] = 0;
   out_502897361153597694[51] = 0;
   out_502897361153597694[52] = 0;
   out_502897361153597694[53] = 0;
   out_502897361153597694[54] = 0;
   out_502897361153597694[55] = 0;
   out_502897361153597694[56] = 0;
   out_502897361153597694[57] = 1;
   out_502897361153597694[58] = 0;
   out_502897361153597694[59] = 0;
   out_502897361153597694[60] = 0;
   out_502897361153597694[61] = 0;
   out_502897361153597694[62] = 0;
   out_502897361153597694[63] = 0;
   out_502897361153597694[64] = 0;
   out_502897361153597694[65] = 0;
   out_502897361153597694[66] = dt;
   out_502897361153597694[67] = 0;
   out_502897361153597694[68] = 0;
   out_502897361153597694[69] = 0;
   out_502897361153597694[70] = 0;
   out_502897361153597694[71] = 0;
   out_502897361153597694[72] = 0;
   out_502897361153597694[73] = 0;
   out_502897361153597694[74] = 0;
   out_502897361153597694[75] = 0;
   out_502897361153597694[76] = 1;
   out_502897361153597694[77] = 0;
   out_502897361153597694[78] = 0;
   out_502897361153597694[79] = 0;
   out_502897361153597694[80] = 0;
   out_502897361153597694[81] = 0;
   out_502897361153597694[82] = 0;
   out_502897361153597694[83] = 0;
   out_502897361153597694[84] = 0;
   out_502897361153597694[85] = dt;
   out_502897361153597694[86] = 0;
   out_502897361153597694[87] = 0;
   out_502897361153597694[88] = 0;
   out_502897361153597694[89] = 0;
   out_502897361153597694[90] = 0;
   out_502897361153597694[91] = 0;
   out_502897361153597694[92] = 0;
   out_502897361153597694[93] = 0;
   out_502897361153597694[94] = 0;
   out_502897361153597694[95] = 1;
   out_502897361153597694[96] = 0;
   out_502897361153597694[97] = 0;
   out_502897361153597694[98] = 0;
   out_502897361153597694[99] = 0;
   out_502897361153597694[100] = 0;
   out_502897361153597694[101] = 0;
   out_502897361153597694[102] = 0;
   out_502897361153597694[103] = 0;
   out_502897361153597694[104] = dt;
   out_502897361153597694[105] = 0;
   out_502897361153597694[106] = 0;
   out_502897361153597694[107] = 0;
   out_502897361153597694[108] = 0;
   out_502897361153597694[109] = 0;
   out_502897361153597694[110] = 0;
   out_502897361153597694[111] = 0;
   out_502897361153597694[112] = 0;
   out_502897361153597694[113] = 0;
   out_502897361153597694[114] = 1;
   out_502897361153597694[115] = 0;
   out_502897361153597694[116] = 0;
   out_502897361153597694[117] = 0;
   out_502897361153597694[118] = 0;
   out_502897361153597694[119] = 0;
   out_502897361153597694[120] = 0;
   out_502897361153597694[121] = 0;
   out_502897361153597694[122] = 0;
   out_502897361153597694[123] = 0;
   out_502897361153597694[124] = 0;
   out_502897361153597694[125] = 0;
   out_502897361153597694[126] = 0;
   out_502897361153597694[127] = 0;
   out_502897361153597694[128] = 0;
   out_502897361153597694[129] = 0;
   out_502897361153597694[130] = 0;
   out_502897361153597694[131] = 0;
   out_502897361153597694[132] = 0;
   out_502897361153597694[133] = 1;
   out_502897361153597694[134] = 0;
   out_502897361153597694[135] = 0;
   out_502897361153597694[136] = 0;
   out_502897361153597694[137] = 0;
   out_502897361153597694[138] = 0;
   out_502897361153597694[139] = 0;
   out_502897361153597694[140] = 0;
   out_502897361153597694[141] = 0;
   out_502897361153597694[142] = 0;
   out_502897361153597694[143] = 0;
   out_502897361153597694[144] = 0;
   out_502897361153597694[145] = 0;
   out_502897361153597694[146] = 0;
   out_502897361153597694[147] = 0;
   out_502897361153597694[148] = 0;
   out_502897361153597694[149] = 0;
   out_502897361153597694[150] = 0;
   out_502897361153597694[151] = 0;
   out_502897361153597694[152] = 1;
   out_502897361153597694[153] = 0;
   out_502897361153597694[154] = 0;
   out_502897361153597694[155] = 0;
   out_502897361153597694[156] = 0;
   out_502897361153597694[157] = 0;
   out_502897361153597694[158] = 0;
   out_502897361153597694[159] = 0;
   out_502897361153597694[160] = 0;
   out_502897361153597694[161] = 0;
   out_502897361153597694[162] = 0;
   out_502897361153597694[163] = 0;
   out_502897361153597694[164] = 0;
   out_502897361153597694[165] = 0;
   out_502897361153597694[166] = 0;
   out_502897361153597694[167] = 0;
   out_502897361153597694[168] = 0;
   out_502897361153597694[169] = 0;
   out_502897361153597694[170] = 0;
   out_502897361153597694[171] = 1;
   out_502897361153597694[172] = 0;
   out_502897361153597694[173] = 0;
   out_502897361153597694[174] = 0;
   out_502897361153597694[175] = 0;
   out_502897361153597694[176] = 0;
   out_502897361153597694[177] = 0;
   out_502897361153597694[178] = 0;
   out_502897361153597694[179] = 0;
   out_502897361153597694[180] = 0;
   out_502897361153597694[181] = 0;
   out_502897361153597694[182] = 0;
   out_502897361153597694[183] = 0;
   out_502897361153597694[184] = 0;
   out_502897361153597694[185] = 0;
   out_502897361153597694[186] = 0;
   out_502897361153597694[187] = 0;
   out_502897361153597694[188] = 0;
   out_502897361153597694[189] = 0;
   out_502897361153597694[190] = 1;
   out_502897361153597694[191] = 0;
   out_502897361153597694[192] = 0;
   out_502897361153597694[193] = 0;
   out_502897361153597694[194] = 0;
   out_502897361153597694[195] = 0;
   out_502897361153597694[196] = 0;
   out_502897361153597694[197] = 0;
   out_502897361153597694[198] = 0;
   out_502897361153597694[199] = 0;
   out_502897361153597694[200] = 0;
   out_502897361153597694[201] = 0;
   out_502897361153597694[202] = 0;
   out_502897361153597694[203] = 0;
   out_502897361153597694[204] = 0;
   out_502897361153597694[205] = 0;
   out_502897361153597694[206] = 0;
   out_502897361153597694[207] = 0;
   out_502897361153597694[208] = 0;
   out_502897361153597694[209] = 1;
   out_502897361153597694[210] = 0;
   out_502897361153597694[211] = 0;
   out_502897361153597694[212] = 0;
   out_502897361153597694[213] = 0;
   out_502897361153597694[214] = 0;
   out_502897361153597694[215] = 0;
   out_502897361153597694[216] = 0;
   out_502897361153597694[217] = 0;
   out_502897361153597694[218] = 0;
   out_502897361153597694[219] = 0;
   out_502897361153597694[220] = 0;
   out_502897361153597694[221] = 0;
   out_502897361153597694[222] = 0;
   out_502897361153597694[223] = 0;
   out_502897361153597694[224] = 0;
   out_502897361153597694[225] = 0;
   out_502897361153597694[226] = 0;
   out_502897361153597694[227] = 0;
   out_502897361153597694[228] = 1;
   out_502897361153597694[229] = 0;
   out_502897361153597694[230] = 0;
   out_502897361153597694[231] = 0;
   out_502897361153597694[232] = 0;
   out_502897361153597694[233] = 0;
   out_502897361153597694[234] = 0;
   out_502897361153597694[235] = 0;
   out_502897361153597694[236] = 0;
   out_502897361153597694[237] = 0;
   out_502897361153597694[238] = 0;
   out_502897361153597694[239] = 0;
   out_502897361153597694[240] = 0;
   out_502897361153597694[241] = 0;
   out_502897361153597694[242] = 0;
   out_502897361153597694[243] = 0;
   out_502897361153597694[244] = 0;
   out_502897361153597694[245] = 0;
   out_502897361153597694[246] = 0;
   out_502897361153597694[247] = 1;
   out_502897361153597694[248] = 0;
   out_502897361153597694[249] = 0;
   out_502897361153597694[250] = 0;
   out_502897361153597694[251] = 0;
   out_502897361153597694[252] = 0;
   out_502897361153597694[253] = 0;
   out_502897361153597694[254] = 0;
   out_502897361153597694[255] = 0;
   out_502897361153597694[256] = 0;
   out_502897361153597694[257] = 0;
   out_502897361153597694[258] = 0;
   out_502897361153597694[259] = 0;
   out_502897361153597694[260] = 0;
   out_502897361153597694[261] = 0;
   out_502897361153597694[262] = 0;
   out_502897361153597694[263] = 0;
   out_502897361153597694[264] = 0;
   out_502897361153597694[265] = 0;
   out_502897361153597694[266] = 1;
   out_502897361153597694[267] = 0;
   out_502897361153597694[268] = 0;
   out_502897361153597694[269] = 0;
   out_502897361153597694[270] = 0;
   out_502897361153597694[271] = 0;
   out_502897361153597694[272] = 0;
   out_502897361153597694[273] = 0;
   out_502897361153597694[274] = 0;
   out_502897361153597694[275] = 0;
   out_502897361153597694[276] = 0;
   out_502897361153597694[277] = 0;
   out_502897361153597694[278] = 0;
   out_502897361153597694[279] = 0;
   out_502897361153597694[280] = 0;
   out_502897361153597694[281] = 0;
   out_502897361153597694[282] = 0;
   out_502897361153597694[283] = 0;
   out_502897361153597694[284] = 0;
   out_502897361153597694[285] = 1;
   out_502897361153597694[286] = 0;
   out_502897361153597694[287] = 0;
   out_502897361153597694[288] = 0;
   out_502897361153597694[289] = 0;
   out_502897361153597694[290] = 0;
   out_502897361153597694[291] = 0;
   out_502897361153597694[292] = 0;
   out_502897361153597694[293] = 0;
   out_502897361153597694[294] = 0;
   out_502897361153597694[295] = 0;
   out_502897361153597694[296] = 0;
   out_502897361153597694[297] = 0;
   out_502897361153597694[298] = 0;
   out_502897361153597694[299] = 0;
   out_502897361153597694[300] = 0;
   out_502897361153597694[301] = 0;
   out_502897361153597694[302] = 0;
   out_502897361153597694[303] = 0;
   out_502897361153597694[304] = 1;
   out_502897361153597694[305] = 0;
   out_502897361153597694[306] = 0;
   out_502897361153597694[307] = 0;
   out_502897361153597694[308] = 0;
   out_502897361153597694[309] = 0;
   out_502897361153597694[310] = 0;
   out_502897361153597694[311] = 0;
   out_502897361153597694[312] = 0;
   out_502897361153597694[313] = 0;
   out_502897361153597694[314] = 0;
   out_502897361153597694[315] = 0;
   out_502897361153597694[316] = 0;
   out_502897361153597694[317] = 0;
   out_502897361153597694[318] = 0;
   out_502897361153597694[319] = 0;
   out_502897361153597694[320] = 0;
   out_502897361153597694[321] = 0;
   out_502897361153597694[322] = 0;
   out_502897361153597694[323] = 1;
}
void h_4(double *state, double *unused, double *out_1859606723148110361) {
   out_1859606723148110361[0] = state[6] + state[9];
   out_1859606723148110361[1] = state[7] + state[10];
   out_1859606723148110361[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8742993852831669419) {
   out_8742993852831669419[0] = 0;
   out_8742993852831669419[1] = 0;
   out_8742993852831669419[2] = 0;
   out_8742993852831669419[3] = 0;
   out_8742993852831669419[4] = 0;
   out_8742993852831669419[5] = 0;
   out_8742993852831669419[6] = 1;
   out_8742993852831669419[7] = 0;
   out_8742993852831669419[8] = 0;
   out_8742993852831669419[9] = 1;
   out_8742993852831669419[10] = 0;
   out_8742993852831669419[11] = 0;
   out_8742993852831669419[12] = 0;
   out_8742993852831669419[13] = 0;
   out_8742993852831669419[14] = 0;
   out_8742993852831669419[15] = 0;
   out_8742993852831669419[16] = 0;
   out_8742993852831669419[17] = 0;
   out_8742993852831669419[18] = 0;
   out_8742993852831669419[19] = 0;
   out_8742993852831669419[20] = 0;
   out_8742993852831669419[21] = 0;
   out_8742993852831669419[22] = 0;
   out_8742993852831669419[23] = 0;
   out_8742993852831669419[24] = 0;
   out_8742993852831669419[25] = 1;
   out_8742993852831669419[26] = 0;
   out_8742993852831669419[27] = 0;
   out_8742993852831669419[28] = 1;
   out_8742993852831669419[29] = 0;
   out_8742993852831669419[30] = 0;
   out_8742993852831669419[31] = 0;
   out_8742993852831669419[32] = 0;
   out_8742993852831669419[33] = 0;
   out_8742993852831669419[34] = 0;
   out_8742993852831669419[35] = 0;
   out_8742993852831669419[36] = 0;
   out_8742993852831669419[37] = 0;
   out_8742993852831669419[38] = 0;
   out_8742993852831669419[39] = 0;
   out_8742993852831669419[40] = 0;
   out_8742993852831669419[41] = 0;
   out_8742993852831669419[42] = 0;
   out_8742993852831669419[43] = 0;
   out_8742993852831669419[44] = 1;
   out_8742993852831669419[45] = 0;
   out_8742993852831669419[46] = 0;
   out_8742993852831669419[47] = 1;
   out_8742993852831669419[48] = 0;
   out_8742993852831669419[49] = 0;
   out_8742993852831669419[50] = 0;
   out_8742993852831669419[51] = 0;
   out_8742993852831669419[52] = 0;
   out_8742993852831669419[53] = 0;
}
void h_10(double *state, double *unused, double *out_8451494295132406513) {
   out_8451494295132406513[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8451494295132406513[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8451494295132406513[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7097327689072921534) {
   out_7097327689072921534[0] = 0;
   out_7097327689072921534[1] = 9.8100000000000005*cos(state[1]);
   out_7097327689072921534[2] = 0;
   out_7097327689072921534[3] = 0;
   out_7097327689072921534[4] = -state[8];
   out_7097327689072921534[5] = state[7];
   out_7097327689072921534[6] = 0;
   out_7097327689072921534[7] = state[5];
   out_7097327689072921534[8] = -state[4];
   out_7097327689072921534[9] = 0;
   out_7097327689072921534[10] = 0;
   out_7097327689072921534[11] = 0;
   out_7097327689072921534[12] = 1;
   out_7097327689072921534[13] = 0;
   out_7097327689072921534[14] = 0;
   out_7097327689072921534[15] = 1;
   out_7097327689072921534[16] = 0;
   out_7097327689072921534[17] = 0;
   out_7097327689072921534[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7097327689072921534[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7097327689072921534[20] = 0;
   out_7097327689072921534[21] = state[8];
   out_7097327689072921534[22] = 0;
   out_7097327689072921534[23] = -state[6];
   out_7097327689072921534[24] = -state[5];
   out_7097327689072921534[25] = 0;
   out_7097327689072921534[26] = state[3];
   out_7097327689072921534[27] = 0;
   out_7097327689072921534[28] = 0;
   out_7097327689072921534[29] = 0;
   out_7097327689072921534[30] = 0;
   out_7097327689072921534[31] = 1;
   out_7097327689072921534[32] = 0;
   out_7097327689072921534[33] = 0;
   out_7097327689072921534[34] = 1;
   out_7097327689072921534[35] = 0;
   out_7097327689072921534[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7097327689072921534[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7097327689072921534[38] = 0;
   out_7097327689072921534[39] = -state[7];
   out_7097327689072921534[40] = state[6];
   out_7097327689072921534[41] = 0;
   out_7097327689072921534[42] = state[4];
   out_7097327689072921534[43] = -state[3];
   out_7097327689072921534[44] = 0;
   out_7097327689072921534[45] = 0;
   out_7097327689072921534[46] = 0;
   out_7097327689072921534[47] = 0;
   out_7097327689072921534[48] = 0;
   out_7097327689072921534[49] = 0;
   out_7097327689072921534[50] = 1;
   out_7097327689072921534[51] = 0;
   out_7097327689072921534[52] = 0;
   out_7097327689072921534[53] = 1;
}
void h_13(double *state, double *unused, double *out_8832559562355137152) {
   out_8832559562355137152[0] = state[3];
   out_8832559562355137152[1] = state[4];
   out_8832559562355137152[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6491476395545549396) {
   out_6491476395545549396[0] = 0;
   out_6491476395545549396[1] = 0;
   out_6491476395545549396[2] = 0;
   out_6491476395545549396[3] = 1;
   out_6491476395545549396[4] = 0;
   out_6491476395545549396[5] = 0;
   out_6491476395545549396[6] = 0;
   out_6491476395545549396[7] = 0;
   out_6491476395545549396[8] = 0;
   out_6491476395545549396[9] = 0;
   out_6491476395545549396[10] = 0;
   out_6491476395545549396[11] = 0;
   out_6491476395545549396[12] = 0;
   out_6491476395545549396[13] = 0;
   out_6491476395545549396[14] = 0;
   out_6491476395545549396[15] = 0;
   out_6491476395545549396[16] = 0;
   out_6491476395545549396[17] = 0;
   out_6491476395545549396[18] = 0;
   out_6491476395545549396[19] = 0;
   out_6491476395545549396[20] = 0;
   out_6491476395545549396[21] = 0;
   out_6491476395545549396[22] = 1;
   out_6491476395545549396[23] = 0;
   out_6491476395545549396[24] = 0;
   out_6491476395545549396[25] = 0;
   out_6491476395545549396[26] = 0;
   out_6491476395545549396[27] = 0;
   out_6491476395545549396[28] = 0;
   out_6491476395545549396[29] = 0;
   out_6491476395545549396[30] = 0;
   out_6491476395545549396[31] = 0;
   out_6491476395545549396[32] = 0;
   out_6491476395545549396[33] = 0;
   out_6491476395545549396[34] = 0;
   out_6491476395545549396[35] = 0;
   out_6491476395545549396[36] = 0;
   out_6491476395545549396[37] = 0;
   out_6491476395545549396[38] = 0;
   out_6491476395545549396[39] = 0;
   out_6491476395545549396[40] = 0;
   out_6491476395545549396[41] = 1;
   out_6491476395545549396[42] = 0;
   out_6491476395545549396[43] = 0;
   out_6491476395545549396[44] = 0;
   out_6491476395545549396[45] = 0;
   out_6491476395545549396[46] = 0;
   out_6491476395545549396[47] = 0;
   out_6491476395545549396[48] = 0;
   out_6491476395545549396[49] = 0;
   out_6491476395545549396[50] = 0;
   out_6491476395545549396[51] = 0;
   out_6491476395545549396[52] = 0;
   out_6491476395545549396[53] = 0;
}
void h_14(double *state, double *unused, double *out_2493859926449381385) {
   out_2493859926449381385[0] = state[6];
   out_2493859926449381385[1] = state[7];
   out_2493859926449381385[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5740509364538397668) {
   out_5740509364538397668[0] = 0;
   out_5740509364538397668[1] = 0;
   out_5740509364538397668[2] = 0;
   out_5740509364538397668[3] = 0;
   out_5740509364538397668[4] = 0;
   out_5740509364538397668[5] = 0;
   out_5740509364538397668[6] = 1;
   out_5740509364538397668[7] = 0;
   out_5740509364538397668[8] = 0;
   out_5740509364538397668[9] = 0;
   out_5740509364538397668[10] = 0;
   out_5740509364538397668[11] = 0;
   out_5740509364538397668[12] = 0;
   out_5740509364538397668[13] = 0;
   out_5740509364538397668[14] = 0;
   out_5740509364538397668[15] = 0;
   out_5740509364538397668[16] = 0;
   out_5740509364538397668[17] = 0;
   out_5740509364538397668[18] = 0;
   out_5740509364538397668[19] = 0;
   out_5740509364538397668[20] = 0;
   out_5740509364538397668[21] = 0;
   out_5740509364538397668[22] = 0;
   out_5740509364538397668[23] = 0;
   out_5740509364538397668[24] = 0;
   out_5740509364538397668[25] = 1;
   out_5740509364538397668[26] = 0;
   out_5740509364538397668[27] = 0;
   out_5740509364538397668[28] = 0;
   out_5740509364538397668[29] = 0;
   out_5740509364538397668[30] = 0;
   out_5740509364538397668[31] = 0;
   out_5740509364538397668[32] = 0;
   out_5740509364538397668[33] = 0;
   out_5740509364538397668[34] = 0;
   out_5740509364538397668[35] = 0;
   out_5740509364538397668[36] = 0;
   out_5740509364538397668[37] = 0;
   out_5740509364538397668[38] = 0;
   out_5740509364538397668[39] = 0;
   out_5740509364538397668[40] = 0;
   out_5740509364538397668[41] = 0;
   out_5740509364538397668[42] = 0;
   out_5740509364538397668[43] = 0;
   out_5740509364538397668[44] = 1;
   out_5740509364538397668[45] = 0;
   out_5740509364538397668[46] = 0;
   out_5740509364538397668[47] = 0;
   out_5740509364538397668[48] = 0;
   out_5740509364538397668[49] = 0;
   out_5740509364538397668[50] = 0;
   out_5740509364538397668[51] = 0;
   out_5740509364538397668[52] = 0;
   out_5740509364538397668[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_495600354373200881) {
  err_fun(nom_x, delta_x, out_495600354373200881);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1169161554918362952) {
  inv_err_fun(nom_x, true_x, out_1169161554918362952);
}
void pose_H_mod_fun(double *state, double *out_269990567082015073) {
  H_mod_fun(state, out_269990567082015073);
}
void pose_f_fun(double *state, double dt, double *out_2663299199207308722) {
  f_fun(state,  dt, out_2663299199207308722);
}
void pose_F_fun(double *state, double dt, double *out_502897361153597694) {
  F_fun(state,  dt, out_502897361153597694);
}
void pose_h_4(double *state, double *unused, double *out_1859606723148110361) {
  h_4(state, unused, out_1859606723148110361);
}
void pose_H_4(double *state, double *unused, double *out_8742993852831669419) {
  H_4(state, unused, out_8742993852831669419);
}
void pose_h_10(double *state, double *unused, double *out_8451494295132406513) {
  h_10(state, unused, out_8451494295132406513);
}
void pose_H_10(double *state, double *unused, double *out_7097327689072921534) {
  H_10(state, unused, out_7097327689072921534);
}
void pose_h_13(double *state, double *unused, double *out_8832559562355137152) {
  h_13(state, unused, out_8832559562355137152);
}
void pose_H_13(double *state, double *unused, double *out_6491476395545549396) {
  H_13(state, unused, out_6491476395545549396);
}
void pose_h_14(double *state, double *unused, double *out_2493859926449381385) {
  h_14(state, unused, out_2493859926449381385);
}
void pose_H_14(double *state, double *unused, double *out_5740509364538397668) {
  H_14(state, unused, out_5740509364538397668);
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
