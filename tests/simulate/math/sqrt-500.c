/* Copyright (c) 2007  Dmitry Xmelkov
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. */

/* Test of sqrt() function.  500 random cases. */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "progmem.h"

union lofl_u {
    long lo;
    float fl;
};

volatile union lofl_u v = { .lo = 1 };

PROGMEM const struct {		/* Table of test cases.	*/
    long x;		/* argument	*/
    long z;		/* sqrt(x)	*/
} t[] = {

    /* x, sqrt(x)	*/
    { 0x3fd50d40, 0x3fa52361 },  /*   1:  1.6644669e+00  1.2901422e+00 */
    { 0x3a4140fc, 0x3cde6cdc },  /*   2:  7.3720491e-04  2.7151518e-02 */
    { 0x41c59add, 0x409f0a02 },  /*   3:  2.4700617e+01  4.9699715e+00 */
    { 0x36818acf, 0x3b00c4d0 },  /*   4:  3.8606590e-06  1.9648560e-03 */
    { 0x426de65e, 0x40f6c8b7 },  /*   5:  5.9474968e+01  7.7120016e+00 */
    { 0x37d0bc9a, 0x3ba37514 },  /*   6:  2.4883357e-05  4.9883220e-03 */
    { 0x4a11bbc2, 0x44c126f4 },  /*   7:  2.3876965e+06  1.5452173e+03 */
    { 0x41af6a84, 0x4095d818 },  /*   8:  2.1927010e+01  4.6826285e+00 */
    { 0x40f3b303, 0x40309de9 },  /*   9:  7.6156020e+00  2.7596380e+00 */
    { 0x3d56e5c6, 0x3e6a8cd7 },  /*  10:  5.2465223e-02  2.2905288e-01 */
    { 0x40db7c2f, 0x40279ce8 },  /*  11:  6.8589091e+00  2.6189519e+00 */
    { 0x3e2c996c, 0x3ed2340b },  /*  12:  1.6855401e-01  4.1055329e-01 */
    { 0x46062cae, 0x42b9557f },  /*  13:  8.5871699e+03  9.2666984e+01 */
    { 0x3df2ac40, 0x3eb03e98 },  /*  14:  1.1849260e-01  3.4422755e-01 */
    { 0x40031866, 0x3fb731ea },  /*  15:  2.0483642e+00  1.4312107e+00 */
    { 0x4377da6f, 0x417be4c9 },  /*  16:  2.4785326e+02  1.5743356e+01 */
    { 0x4134b947, 0x405717f9 },  /*  17:  1.1295234e+01  3.3608382e+00 */
    { 0x3f6486a3, 0x3f71df89 },  /*  18:  8.9267939e-01  9.4481712e-01 */
    { 0x3f4d9fe0, 0x3f656f0e },  /*  19:  8.0322075e-01  8.9622584e-01 */
    { 0x2d3319eb, 0x3656203e },  /*  20:  1.0180727e-11  3.1907251e-06 */
    { 0x36b4fa7f, 0x3b18338b },  /*  21:  5.3935796e-06  2.3224081e-03 */
    { 0x3d99be6d, 0x3e8c485a },  /*  22:  7.5070240e-02  2.7398949e-01 */
    { 0x3c2b5614, 0x3dd16ec9 },  /*  23:  1.0457534e-02  1.0226209e-01 */
    { 0x3eecd238, 0x3f2e1b4a },  /*  24:  4.6254134e-01  6.8010392e-01 */
    { 0x49d2b294, 0x44a4392a },  /*  25:  1.7260345e+06  1.3137863e+03 */
    { 0x407c2922, 0x3ffe12b6 },  /*  26:  3.9400105e+00  1.9849460e+00 */
    { 0x413991b9, 0x4059f544 },  /*  27:  1.1598077e+01  3.4055949e+00 */
    { 0x3f461bdb, 0x3f6133aa },  /*  28:  7.7386254e-01  8.7969457e-01 */
    { 0x3a9aabbc, 0x3d0cb474 },  /*  29:  1.1800448e-03  3.4351781e-02 */
    { 0x3f28541f, 0x3f4f9620 },  /*  30:  6.5753359e-01  8.1088445e-01 */
    { 0x3f03e9cb, 0x3f37c3fe },  /*  31:  5.1528615e-01  7.1783435e-01 */
    { 0x416e0233, 0x4076d727 },  /*  32:  1.4875537e+01  3.8568818e+00 */
    { 0x46d08fed, 0x43236395 },  /*  33:  2.6695963e+04  1.6338899e+02 */
    { 0x3f0e5686, 0x3f3ee387 },  /*  34:  5.5600774e-01  7.4565927e-01 */
    { 0x41fe7dcf, 0x40b47c36 },  /*  35:  3.1811430e+01  5.6401622e+00 */
    { 0x3a755a13, 0x3cfa9e90 },  /*  36:  9.3594304e-04  3.0593186e-02 */
    { 0x4395d0ba, 0x418a7a8f },  /*  37:  2.9963068e+02  1.7309843e+01 */
    { 0x3f3ac851, 0x3f5aab5f },  /*  38:  7.2961909e-01  8.5417743e-01 */
    { 0x437d1c24, 0x417e8d05 },  /*  39:  2.5310992e+02  1.5909429e+01 */
    { 0x3cb6ef68, 0x3e19059c },  /*  40:  2.2330955e-02  1.4943545e-01 */
    { 0x00000000, 0x00000000 },  /*  41:  0.0000000e+00  0.0000000e+00 */
    { 0x3fea54df, 0x3fad3063 },  /*  42:  1.8307151e+00  1.3530392e+00 */
    { 0x41645521, 0x4071c554 },  /*  43:  1.4270783e+01  3.7776690e+00 */
    { 0x3feff5a8, 0x3faf41a8 },  /*  44:  1.8746843e+00  1.3691911e+00 */
    { 0x3e769e49, 0x3efb43ef },  /*  45:  2.4083818e-01  4.9075267e-01 */
    { 0x3992eb8a, 0x3c892256 },  /*  46:  2.8022780e-04  1.6740006e-02 */
    { 0x4779776a, 0x437cb64d },  /*  47:  6.3863414e+04  2.5271212e+02 */
    { 0x00000000, 0x00000000 },  /*  48:  0.0000000e+00  0.0000000e+00 */
    { 0x347c8a1a, 0x39fe438b },  /*  49:  2.3519570e-07  4.8496979e-04 */
    { 0x401a6e2e, 0x3fc6d501 },  /*  50:  2.4129748e+00  1.5533753e+00 */
    { 0x40756a70, 0x3ffaa6eb },  /*  51:  3.8346214e+00  1.9582189e+00 */
    { 0x3e76e4fa, 0x3efb67f0 },  /*  52:  2.4110785e-01  4.9102734e-01 */
    { 0x3d955d28, 0x3e8a451b },  /*  53:  7.2931588e-02  2.7005849e-01 */
    { 0x3f151724, 0x3f435d37 },  /*  54:  5.8238435e-01  7.6314111e-01 */
    { 0x3f23126f, 0x3f4c51c7 },  /*  55:  6.3700002e-01  7.9812281e-01 */
    { 0x3f0e141f, 0x3f3eb6fb },  /*  56:  5.5499452e-01  7.4497955e-01 */
    { 0x4228e3a4, 0x40cfee8c },  /*  57:  4.2222305e+01  6.4978693e+00 */
    { 0x3b6d17e6, 0x3d765d89 },  /*  58:  3.6177575e-03  6.0147797e-02 */
    { 0x4b6178ea, 0x45704074 },  /*  59:  1.4776554e+07  3.8440284e+03 */
    { 0x3d48cc24, 0x3e62b98d },  /*  60:  4.9022809e-02  2.2141095e-01 */
    { 0x38407ec6, 0x3bddfcfd },  /*  61:  4.5894434e-05  6.7745431e-03 */
    { 0x3dbad716, 0x3e9aa582 },  /*  62:  9.1230556e-02  3.0204396e-01 */
    { 0x42338642, 0x40d660f7 },  /*  63:  4.4881111e+01  6.6993366e+00 */
    { 0x3dc30fe6, 0x3e9e0333 },  /*  64:  9.5245168e-02  3.0861816e-01 */
    { 0x3fe9c165, 0x3facf9db },  /*  65:  1.8262144e+00  1.3513750e+00 */
    { 0x4392f190, 0x41892526 },  /*  66:  2.9388721e+02  1.7143139e+01 */
    { 0x3a4490ea, 0x3ce052c0 },  /*  67:  7.4984005e-04  2.7383207e-02 */
    { 0x418e9d2b, 0x40871c0a },  /*  68:  1.7826742e+01  4.2221727e+00 */
    { 0x3ad3d518, 0x3d24aa3a },  /*  69:  1.6161529e-03  4.0201405e-02 */
    { 0x3f34058f, 0x3f56acec },  /*  70:  7.0320982e-01  8.3857607e-01 */
    { 0x4011464b, 0x3fc0d90d },  /*  71:  2.2699153e+00  1.5066238e+00 */
    { 0x413afced, 0x405aca29 },  /*  72:  1.1686749e+01  3.4185888e+00 */
    { 0x3fd7d7fb, 0x3fa63779 },  /*  73:  1.6862787e+00  1.2985679e+00 */
    { 0x44d321c9, 0x4224647b },  /*  74:  1.6890558e+03  4.1098124e+01 */
    { 0x3fca8a98, 0x3fa1036a },  /*  75:  1.5823545e+00  1.2579167e+00 */
    { 0x4195efdb, 0x408a88f1 },  /*  76:  1.8742117e+01  4.3292167e+00 */
    { 0x3e3fe9df, 0x3edda710 },  /*  77:  1.8741558e-01  4.3291522e-01 */
    { 0x3e301ea4, 0x3ed4560e },  /*  78:  1.7199188e-01  4.1471904e-01 */
    { 0x3813f9e3, 0x3bc2a1f8 },  /*  79:  3.5280256e-05  5.9397185e-03 */
    { 0x4213b331, 0x40c27375 },  /*  80:  3.6924992e+01  6.0765938e+00 */
    { 0x3b0aec17, 0x3d3c959e },  /*  81:  2.1197849e-03  4.6041122e-02 */
    { 0x3f147bd9, 0x3f42f75e },  /*  82:  5.8001477e-01  7.6158700e-01 */
    { 0x3f1badcb, 0x3f47a258 },  /*  83:  6.0812062e-01  7.7982089e-01 */
    { 0x00000000, 0x00000000 },  /*  84:  0.0000000e+00  0.0000000e+00 */
    { 0x3f03a11a, 0x3f379155 },  /*  85:  5.1417696e-01  7.1706134e-01 */
    { 0x3f2996c9, 0x3f505cb6 },  /*  86:  6.6245705e-01  8.1391464e-01 */
    { 0x5372dae3, 0x49795746 },  /*  87:  1.0430544e+12  1.0213003e+06 */
    { 0x3ddf0985, 0x3ea8f6ba },  /*  88:  1.0890488e-01  3.3000739e-01 */
    { 0x3f2584c3, 0x3f4dd8b1 },  /*  89:  6.4655703e-01  8.0408770e-01 */
    { 0x3f275006, 0x3f4ef580 },  /*  90:  6.5356481e-01  8.0843355e-01 */
    { 0x3dd88231, 0x3ea678f6 },  /*  91:  1.0571707e-01  3.2514162e-01 */
    { 0x3edcaf96, 0x3f281220 },  /*  92:  4.3102711e-01  6.5652655e-01 */
    { 0x3f017e30, 0x3f36126a },  /*  93:  5.0583172e-01  7.1121847e-01 */
    { 0x4192ae5d, 0x408905c6 },  /*  94:  1.8335138e+01  4.2819550e+00 */
    { 0x3ee3bdbe, 0x3f2abc7c },  /*  95:  4.4480699e-01  6.6693852e-01 */
    { 0x3fdf7a40, 0x3fa92168 },  /*  96:  1.7459183e+00  1.3213320e+00 */
    { 0x413e61a6, 0x405cc41c },  /*  97:  1.1898840e+01  3.4494695e+00 */
    { 0x38bbc814, 0x3c1b091d },  /*  98:  8.9541223e-05  9.4626224e-03 */
    { 0x39cdb5c3, 0x3ca24497 },  /*  99:  3.9236070e-04  1.9808097e-02 */
    { 0x3fe3c76f, 0x3faac01e },  /* 100:  1.7795237e+00  1.3339879e+00 */
    { 0x00000000, 0x00000000 },  /* 101:  0.0000000e+00  0.0000000e+00 */
    { 0x3b7c1836, 0x3d7e0a2f },  /* 102:  3.8466579e-03  6.2021431e-02 */
    { 0x3f248bb8, 0x3f4d3d9a },  /* 103:  6.4275694e-01  8.0172124e-01 */
    { 0x3f0bee02, 0x3f3d445c },  /* 104:  5.4660046e-01  7.3932433e-01 */
    { 0x3b98395e, 0x3d8b966a },  /* 105:  4.6455106e-03  6.8157982e-02 */
    { 0x3d5aaa1b, 0x3e6c98d0 },  /* 106:  5.3384881e-02  2.3105169e-01 */
    { 0x42f393ae, 0x4130928e },  /* 107:  1.2178844e+02  1.1035780e+01 */
    { 0x3ced7c91, 0x3e2e59dd },  /* 108:  2.8990062e-02  1.7026468e-01 */
    { 0x3f17a5c5, 0x3f45084c },  /* 109:  5.9237319e-01  7.6965784e-01 */
    { 0x3f608fe1, 0x3f6fc42c },  /* 110:  8.7719542e-01  9.3658711e-01 */
    { 0x3f24548a, 0x3f4d1b2e },  /* 111:  6.4191496e-01  8.0119596e-01 */
    { 0x41ef1b4f, 0x40aef1d9 },  /* 112:  2.9888334e+01  5.4670224e+00 */
    { 0x3cbb542e, 0x3e1ad93e },  /* 113:  2.2867288e-02  1.5121934e-01 */
    { 0x3eff78e0, 0x3f34d527 },  /* 114:  4.9896908e-01  7.0637743e-01 */
    { 0x40fcb320, 0x4033d946 },  /* 115:  7.8968658e+00  2.8101363e+00 */
    { 0x42d9793b, 0x4126d7d4 },  /* 116:  1.0873678e+02  1.0427693e+01 */
    { 0x41223963, 0x404bc9a0 },  /* 117:  1.0139010e+01  3.1841813e+00 */
    { 0x42f1a927, 0x412fe068 },  /* 118:  1.2083038e+02  1.0992287e+01 */
    { 0x3d09545e, 0x3e3b8014 },  /* 119:  3.3527724e-02  1.8310577e-01 */
    { 0x3fdf052c, 0x3fa8f515 },  /* 120:  1.7423453e+00  1.3199793e+00 */
    { 0x3e37fae9, 0x3ed905d8 },  /* 121:  1.7966808e-01  4.2387272e-01 */
    { 0x4cf4cf20, 0x463104bf },  /* 122:  1.2835046e+08  1.1329186e+04 */
    { 0x40e8adbe, 0x402c93c0 },  /* 123:  7.2712088e+00  2.6965179e+00 */
    { 0x3ac869d1, 0x3d202a4e },  /* 124:  1.5290325e-03  3.9102845e-02 */
    { 0x419d164e, 0x408dccb9 },  /* 125:  1.9635891e+01  4.4312403e+00 */
    { 0x3f3ce48b, 0x3f5be6b6 },  /* 126:  7.3786229e-01  8.5898911e-01 */
    { 0x411ee22c, 0x4049adab },  /* 127:  9.9302177e+00  3.1512248e+00 */
    { 0x3e378f01, 0x3ed8c62a },  /* 128:  1.7925645e-01  4.2338688e-01 */
    { 0x3fde00cc, 0x3fa89257 },  /* 129:  1.7343993e+00  1.3169660e+00 */
    { 0x40077623, 0x3fba387e },  /* 130:  2.1165855e+00  1.4548490e+00 */
    { 0x3d1beb38, 0x3e47c9b6 },  /* 131:  3.8066119e-02  1.9510540e-01 */
    { 0x3e440e3c, 0x3ee00822 },  /* 132:  1.9146055e-01  4.3756205e-01 */
    { 0x4125a25f, 0x404deb1a },  /* 133:  1.0352141e+01  3.2174744e+00 */
    { 0x4a535195, 0x44e896c0 },  /* 134:  3.4622452e+06  1.8607110e+03 */
    { 0x496e1398, 0x4476e02c },  /* 135:  9.7516150e+05  9.8750266e+02 */
    { 0x3dff8ce7, 0x3eb4dc3d },  /* 136:  1.2478047e-01  3.5324279e-01 */
    { 0x45e9cf88, 0x42acff16 },  /* 137:  7.4819414e+03  8.6498216e+01 */
    { 0x7ab3a783, 0x5d17a4bd },  /* 138:  4.6640934e+35  6.8294168e+17 */
    { 0x3d161031, 0x3e440020 },  /* 139:  3.6636535e-02  1.9140673e-01 */
    { 0x410fe869, 0x403ff045 },  /* 140:  8.9942408e+00  2.9990400e+00 */
    { 0x4deeed45, 0x46aee101 },  /* 141:  5.0106589e+08  2.2384501e+04 */
    { 0x48a2d1bd, 0x44105d19 },  /* 142:  3.3345391e+05  5.7745468e+02 */
    { 0x3f204dc4, 0x3f4a93eb },  /* 143:  6.2618661e-01  7.9131954e-01 */
    { 0x45da28d3, 0x42a71b22 },  /* 144:  6.9811030e+03  8.3552995e+01 */
    { 0x3cd9c7fd, 0x3e26f608 },  /* 145:  2.6584620e-02  1.6304791e-01 */
    { 0x408e44bb, 0x4006f21f },  /* 146:  4.4458899e+00  2.1085279e+00 */
    { 0x3fdca532, 0x3fa80e2b },  /* 147:  1.7237914e+00  1.3129324e+00 */
    { 0x41277626, 0x404f0d13 },  /* 148:  1.0466345e+01  3.2351731e+00 */
    { 0x414d610f, 0x40654c00 },  /* 149:  1.2836196e+01  3.5827637e+00 */
    { 0x3fe9ef82, 0x3fad0aea },  /* 150:  1.8276217e+00  1.3518956e+00 */
    { 0x3e6c5281, 0x3ef5f6e5 },  /* 151:  2.3078348e-01  4.8039929e-01 */
    { 0x43a928de, 0x419325cd },  /* 152:  3.3831927e+02  1.8393457e+01 */
    { 0x3752d09c, 0x3b684fbb },  /* 153:  1.2565546e-05  3.5447914e-03 */
    { 0x3fff4153, 0x3fb4c17d },  /* 154:  1.9941810e+00  1.4121547e+00 */
    { 0x3fcf2611, 0x3fa2d59a },  /* 155:  1.6183492e+00  1.2721435e+00 */
    { 0x409fdd2a, 0x400f0c28 },  /* 156:  4.9957476e+00  2.2351169e+00 */
    { 0x401faf22, 0x3fca2f96 },  /* 157:  2.4950643e+00  1.5795772e+00 */
    { 0x38748871, 0x3bfa3368 },  /* 158:  5.8301204e-05  7.6355225e-03 */
    { 0x44fa5f7e, 0x423304d3 },  /* 159:  2.0029841e+03  4.4754711e+01 */
    { 0x3f173904, 0x3f44c199 },  /* 160:  5.9071374e-01  7.6857904e-01 */
    { 0x3eff0104, 0x3f34aab6 },  /* 161:  4.9805462e-01  7.0572985e-01 */
    { 0x420bfdcf, 0x40bd4f0b },  /* 162:  3.4997860e+01  5.9158989e+00 */
    { 0x607ce79b, 0x4ffe7299 },  /* 163:  7.2894819e+19  8.5378463e+09 */
    { 0x417e659f, 0x407f327d },  /* 164:  1.5899810e+01  3.9874566e+00 */
    { 0x3a7a58b2, 0x3cfd284f },  /* 165:  9.5499598e-04  3.0903009e-02 */
    { 0x3e422eb8, 0x3edef581 },  /* 166:  1.8963134e-01  4.3546681e-01 */
    { 0x3e1defb1, 0x3ec9138b },  /* 167:  1.5423466e-01  3.9272721e-01 */
    { 0x433c08b7, 0x415b669b },  /* 168:  1.8803404e+02  1.3712551e+01 */
    { 0x41c08ffa, 0x409cff2d },  /* 169:  2.4070301e+01  4.9061493e+00 */
    { 0x3f6c4ccb, 0x3f75f3ec },  /* 170:  9.2304677e-01  9.6075323e-01 */
    { 0x3f133325, 0x3f421f19 },  /* 171:  5.7499915e-01  7.5828699e-01 */
    { 0x3de3408b, 0x3eaa8d87 },  /* 172:  1.1096295e-01  3.3311102e-01 */
    { 0x3fe35fed, 0x3faa994d },  /* 173:  1.7763649e+00  1.3328034e+00 */
    { 0x43eea443, 0x41aec647 },  /* 174:  4.7728329e+02  2.1846814e+01 */
    { 0x4004e141, 0x3fb8700b },  /* 175:  2.0762484e+00  1.4409193e+00 */
    { 0x4308daeb, 0x413b2d19 },  /* 176:  1.3685515e+02  1.1698511e+01 */
    { 0x3faddada, 0x3f952d03 },  /* 177:  1.3582413e+00  1.1654361e+00 */
    { 0x00000000, 0x00000000 },  /* 178:  0.0000000e+00  0.0000000e+00 */
    { 0x40eba82f, 0x402dad9a },  /* 179:  7.3642802e+00  2.7137207e+00 */
    { 0x2f95213b, 0x378a295c },  /* 180:  2.7126554e-10  1.6470141e-05 */
    { 0x3e04a082, 0x3eb84317 },  /* 181:  1.2951854e-01  3.5988684e-01 */
    { 0x406548ce, 0x3ff24634 },  /* 182:  3.5825686e+00  1.8927675e+00 */
    { 0x41426830, 0x405f167d },  /* 183:  1.2150436e+01  3.4857476e+00 */
    { 0x49c1cd5d, 0x449d805a },  /* 184:  1.5876276e+06  1.2600110e+03 */
    { 0x415f5ed6, 0x406f211c },  /* 185:  1.3960653e+01  3.7363958e+00 */
    { 0x3c7d7e9b, 0x3dfebe84 },  /* 186:  1.5472080e-02  1.2438681e-01 */
    { 0x3f30ccfe, 0x3f54bf0e },  /* 187:  6.9062793e-01  8.3104027e-01 */
    { 0x412eecd0, 0x40539d62 },  /* 188:  1.0932816e+01  3.3064808e+00 */
    { 0x3fc0c54a, 0x3f9d14e7 },  /* 189:  1.5060208e+00  1.2272004e+00 */
    { 0x3e96d94f, 0x3f0af4a1 },  /* 190:  2.9462668e-01  5.4279525e-01 */
    { 0x43d6a771, 0x41a5c20e },  /* 191:  4.2930814e+02  2.0719752e+01 */
    { 0x40bc3bb7, 0x401b38d2 },  /* 192:  5.8822894e+00  2.4253432e+00 */
    { 0x41ed11c8, 0x40ae32a6 },  /* 193:  2.9633682e+01  5.4436828e+00 */
    { 0x3fb4cde1, 0x3f9820c7 },  /* 194:  1.4125329e+00  1.1885003e+00 */
    { 0x42dc83df, 0x4128017a },  /* 195:  1.1025756e+02  1.0500360e+01 */
    { 0x414debf1, 0x4065997a },  /* 196:  1.2870103e+01  3.5874926e+00 */
    { 0x3e308288, 0x3ed4923d },  /* 197:  1.7237294e-01  4.1517820e-01 */
    { 0x3fc99321, 0x3fa0a0ef },  /* 198:  1.5748025e+00  1.2549114e+00 */
    { 0x417c764b, 0x407e3992 },  /* 199:  1.5778880e+01  3.9722639e+00 */
    { 0x3fd0a274, 0x3fa36ad7 },  /* 200:  1.6299577e+00  1.2766980e+00 */
    { 0x40a387b7, 0x4010adb0 },  /* 201:  5.1103168e+00  2.2606010e+00 */
    { 0x40eead8c, 0x402ec9ad },  /* 202:  7.4586849e+00  2.7310593e+00 */
    { 0x3fa9f40e, 0x3f937e12 },  /* 203:  1.3277605e+00  1.1522849e+00 */
    { 0x411f3d2f, 0x4049e766 },  /* 204:  9.9524374e+00  3.1547484e+00 */
    { 0x3ff07d69, 0x3faf7334 },  /* 205:  1.8788272e+00  1.3707032e+00 */
    { 0x3f527557, 0x3f681d6c },  /* 206:  8.2210296e-01  9.0669894e-01 */
    { 0x45698b99, 0x427483d9 },  /* 207:  3.7367249e+03  6.1128756e+01 */
    { 0x3f38c57a, 0x3f597d31 },  /* 208:  7.2176325e-01  8.4956651e-01 */
    { 0x40f51d63, 0x40312108 },  /* 209:  7.6598372e+00  2.7676411e+00 */
    { 0x40f31072, 0x403062f6 },  /* 210:  7.5957575e+00  2.7560402e+00 */
    { 0x41d10b7b, 0x40a393f3 },  /* 211:  2.6130606e+01  5.1118104e+00 */
    { 0x2f3ae10a, 0x375ab9d8 },  /* 212:  1.6996551e-10  1.3037082e-05 */
    { 0x419c9629, 0x408d92d6 },  /* 213:  1.9573320e+01  4.4241745e+00 */
    { 0x3c66daa3, 0x3df31a24 },  /* 214:  1.4090213e-02  1.1870220e-01 */
    { 0x3dca2278, 0x3ea0da02 },  /* 215:  9.8698556e-02  3.1416326e-01 */
    { 0x40f2e29a, 0x40305253 },  /* 216:  7.5901613e+00  2.7550247e+00 */
    { 0x445c05cf, 0x41ed54a1 },  /* 217:  8.8009076e+02  2.9666324e+01 */
    { 0x3f325734, 0x3f55abb8 },  /* 218:  6.9664311e-01  8.3465149e-01 */
    { 0x3f05bfd1, 0x3f390a40 },  /* 219:  5.2245814e-01  7.2281266e-01 */
    { 0x3f3175ec, 0x3f552499 },  /* 220:  6.9320560e-01  8.3258969e-01 */
    { 0x3db83366, 0x3e998ce1 },  /* 221:  8.9941785e-02  2.9990296e-01 */
    { 0x3c210040, 0x3dcb0492 },  /* 222:  9.8267198e-03  9.9129813e-02 */
    { 0x3df86189, 0x3eb24e26 },  /* 223:  1.2127978e-01  3.4825247e-01 */
    { 0x21736673, 0x30799ee0 },  /* 224:  8.2467193e-19  9.0811449e-10 */
    { 0x408b040f, 0x400564ee },  /* 225:  4.3442454e+00  2.0842854e+00 */
    { 0x414cc4e0, 0x4064f4c0 },  /* 226:  1.2798065e+01  3.5774384e+00 */
    { 0x3fcfaed7, 0x3fa30b52 },  /* 227:  1.6225232e+00  1.2737830e+00 */
    { 0x41ba25cc, 0x409a5c11 },  /* 228:  2.3268456e+01  4.8237387e+00 */
    { 0x3d95845c, 0x3e8a573f },  /* 229:  7.3006362e-02  2.7019689e-01 */
    { 0x3eadba2f, 0x3f151efe },  /* 230:  3.3931109e-01  5.8250416e-01 */
    { 0x3c6c9e5e, 0x3df61e5d },  /* 231:  1.4442055e-02  1.2017510e-01 */
    { 0x3f010bce, 0x3f35c1ee },  /* 232:  5.0408638e-01  7.0999041e-01 */
    { 0x4290ed0e, 0x41083348 },  /* 233:  7.2462997e+01  8.5125200e+00 */
    { 0x3ee236ba, 0x3f2a29aa },  /* 234:  4.4182378e-01  6.6469826e-01 */
    { 0x3fd753f2, 0x3fa6049b },  /* 235:  1.6822493e+00  1.2970155e+00 */
    { 0x27054761, 0x3338b6dd },  /* 236:  1.8496152e-15  4.3007153e-08 */
    { 0x40fa9041, 0x40331641 },  /* 237:  7.8301091e+00  2.7982332e+00 */
    { 0x41df33de, 0x40a906c4 },  /* 238:  2.7900326e+01  5.2820759e+00 */
    { 0x3635bd84, 0x3ad7b29f },  /* 239:  2.7081414e-06  1.6456432e-03 */
    { 0x3bb7b053, 0x3d995636 },  /* 240:  5.6057363e-03  7.4871465e-02 */
    { 0x3e24ed1b, 0x3ecd7a4e },  /* 241:  1.6106074e-01  4.0132373e-01 */
    { 0x3c071ddc, 0x3db9fbc6 },  /* 242:  8.2468651e-03  9.0812252e-02 */
    { 0x4109898a, 0x403ba45d },  /* 243:  8.5960789e+00  2.9319070e+00 */
    { 0x3fdce502, 0x3fa82676 },  /* 244:  1.7257388e+00  1.3136738e+00 */
    { 0x3da4457d, 0x3e91018a },  /* 245:  8.0210663e-02  2.8321487e-01 */
    { 0x388040e2, 0x3c00206d },  /* 246:  6.1156010e-05  7.8202308e-03 */
    { 0x513f649e, 0x485d5a0f },  /* 247:  5.1376677e+10  2.2666424e+05 */
    { 0x3f2df26f, 0x3f5305b9 },  /* 248:  6.7948049e-01  8.2430607e-01 */
    { 0x3f1aec2a, 0x3f47260b },  /* 249:  6.0516608e-01  7.7792421e-01 */
    { 0x3c0ad70b, 0x3dbc8754 },  /* 250:  8.4741218e-03  9.2054993e-02 */
    { 0x3fcb7eba, 0x3fa16457 },  /* 251:  1.5898049e+00  1.2608747e+00 */
    { 0x3d87f918, 0x3e83ed22 },  /* 252:  6.6393077e-02  2.5766854e-01 */
    { 0x3ba8548e, 0x3d92c958 },  /* 253:  5.1370328e-03  7.1673097e-02 */
    { 0x36e70ec3, 0x3b2bf996 },  /* 254:  6.8860550e-06  2.6241294e-03 */
    { 0x3a03b69a, 0x3cb7a052 },  /* 255:  5.0244632e-04  2.2415314e-02 */
    { 0x3de141ce, 0x3ea9cd73 },  /* 256:  1.0998879e-01  3.3164558e-01 */
    { 0x3f38954e, 0x3f5960d5 },  /* 257:  7.2102821e-01  8.4913380e-01 */
    { 0x61593e6b, 0x506bd3bc },  /* 258:  2.5046507e+20  1.5826088e+10 */
    { 0x430bec16, 0x413d430f },  /* 259:  1.3992221e+02  1.1828872e+01 */
    { 0x410d96d1, 0x403e62cf },  /* 260:  8.8493204e+00  2.9747807e+00 */
    { 0x3b75680a, 0x3d7aa5b2 },  /* 261:  3.7446045e-03  6.1193174e-02 */
    { 0x3feb184f, 0x3fad788d },  /* 262:  1.8366793e+00  1.3552414e+00 */
    { 0x3fee021e, 0x3fae8adc },  /* 263:  1.8594396e+00  1.3636127e+00 */
    { 0x42000673, 0x40b50983 },  /* 264:  3.2006298e+01  5.6574109e+00 */
    { 0x40794088, 0x3ffc9a7f },  /* 265:  3.8945637e+00  1.9734649e+00 */
    { 0x3fc255f0, 0x3f9db7cf },  /* 266:  1.5182476e+00  1.2321719e+00 */
    { 0x3f08939c, 0x3f3afc4f },  /* 267:  5.3350234e-01  7.3041245e-01 */
    { 0x3f37efb0, 0x3f58ff3a },  /* 268:  7.1850109e-01  8.4764444e-01 */
    { 0x3f1d06fb, 0x3f487f31 },  /* 269:  6.1338776e-01  7.8319076e-01 */
    { 0x3fbdc979, 0x3f9bdc7c },  /* 270:  1.4827110e+00  1.2176662e+00 */
    { 0x42d79403, 0x41261d4c },  /* 271:  1.0778909e+02  1.0382152e+01 */
    { 0x3d8f0397, 0x3e874c85 },  /* 272:  6.9831066e-02  2.6425568e-01 */
    { 0x3f109a8d, 0x3f4066ed },  /* 273:  5.6485826e-01  7.5157053e-01 */
    { 0x3deab25f, 0x3ead52ed },  /* 274:  1.1459803e-01  3.3852331e-01 */
    { 0x3bfc6d39, 0x3db3c064 },  /* 275:  7.7034500e-03  8.7769300e-02 */
    { 0x3dfbcb64, 0x3eb386bc },  /* 276:  1.2294653e-01  3.5063732e-01 */
    { 0x41482013, 0x40625854 },  /* 277:  1.2507831e+01  3.5366411e+00 */
    { 0x42e9dac3, 0x412d033e },  /* 278:  1.1692727e+02  1.0813291e+01 */
    { 0x42ec8f33, 0x412e02a6 },  /* 279:  1.1827969e+02  1.0875646e+01 */
    { 0x4008d29b, 0x3fbb276a },  /* 280:  2.1378543e+00  1.4621403e+00 */
    { 0x28af6426, 0x3415d55f },  /* 281:  1.9472335e-14  1.3954331e-07 */
    { 0x41227585, 0x404bef62 },  /* 282:  1.0153691e+01  3.1864857e+00 */
    { 0x3a24b738, 0x3ccd58ba },  /* 283:  6.2834052e-04  2.5066721e-02 */
    { 0x3e32febe, 0x3ed60ffe },  /* 284:  1.7479989e-01  4.1809077e-01 */
    { 0x3de2c197, 0x3eaa5ddd },  /* 285:  1.1072081e-01  3.3274736e-01 */
    { 0x3c769d68, 0x3dfb437d },  /* 286:  1.5052177e-02  1.2268731e-01 */
    { 0x3f3dff84, 0x3f5c8b2f },  /* 287:  7.4218011e-01  8.6149876e-01 */
    { 0x3b528aea, 0x3d682951 },  /* 288:  3.2126256e-03  5.6680028e-02 */
    { 0x410c7084, 0x403d9c8a },  /* 289:  8.7774696e+00  2.9626795e+00 */
    { 0x439204a3, 0x4188b669 },  /* 290:  2.9203622e+02  1.7089067e+01 */
    { 0x3d89bf4a, 0x3e84c8c2 },  /* 291:  6.7259386e-02  2.5934415e-01 */
    { 0x410953d8, 0x403b7fb9 },  /* 292:  8.5829697e+00  2.9296706e+00 */
    { 0x3c5195cd, 0x3de7a206 },  /* 293:  1.2792063e-02  1.1310200e-01 */
    { 0x3f2b945b, 0x3f5194d5 },  /* 294:  6.7023247e-01  8.1867727e-01 */
    { 0x3fd8ed95, 0x3fa6a23a },  /* 295:  1.6947504e+00  1.3018258e+00 */
    { 0x40d5ad34, 0x40256153 },  /* 296:  6.6773930e+00  2.5840652e+00 */
    { 0x411003c6, 0x40400284 },  /* 297:  9.0009212e+00  3.0001535e+00 */
    { 0x3dcdbbf8, 0x3ea2470a },  /* 298:  1.0045618e-01  3.1694823e-01 */
    { 0x3da4ad37, 0x3e912f4b },  /* 299:  8.0408506e-02  2.8356394e-01 */
    { 0x3efa70e4, 0x3f330b0b },  /* 300:  4.8914254e-01  6.9938726e-01 */
    { 0x3efab1d8, 0x3f332241 },  /* 301:  4.8963809e-01  6.9974145e-01 */
    { 0x3e18f018, 0x3ec5de6f },  /* 302:  1.4935338e-01  3.8646266e-01 */
    { 0x3294f213, 0x390a1382 },  /* 303:  1.7339550e-08  1.3167973e-04 */
    { 0x3dd6bcae, 0x3ea5ca41 },  /* 304:  1.0485207e-01  3.2380869e-01 */
    { 0x3ffc3d11, 0x3fb3af3e },  /* 305:  1.9706136e+00  1.4037855e+00 */
    { 0x37d02573, 0x3ba339db },  /* 306:  2.4812971e-05  4.9812620e-03 */
    { 0x4160a1c6, 0x406fcdba },  /* 307:  1.4039495e+01  3.7469315e+00 */
    { 0x3fcaf073, 0x3fa12be2 },  /* 308:  1.5854629e+00  1.2591517e+00 */
    { 0x429135fd, 0x41085589 },  /* 309:  7.2605446e+01  8.5208829e+00 */
    { 0x3fbfccae, 0x3f9caf7c },  /* 310:  1.4984338e+00  1.2241053e+00 */
    { 0x3d386fa7, 0x3e594aa8 },  /* 311:  4.5028355e-02  2.1219886e-01 */
    { 0x4129a7e9, 0x4050673b },  /* 312:  1.0603494e+01  3.2563006e+00 */
    { 0x3b53411f, 0x3d688db1 },  /* 313:  3.2234860e-03  5.6775752e-02 */
    { 0x3d71abfb, 0x3e78bb95 },  /* 314:  5.9001904e-02  2.4290308e-01 */
    { 0x3fee9572, 0x3faec0da },  /* 315:  1.8639357e+00  1.3652603e+00 */
    { 0x414a55bc, 0x40639756 },  /* 316:  1.2645931e+01  3.5561118e+00 */
    { 0x3fda3571, 0x3fa71ff7 },  /* 317:  1.7047559e+00  1.3056630e+00 */
    { 0x416478f1, 0x4071d849 },  /* 318:  1.4279527e+01  3.7788261e+00 */
    { 0x3ff0189b, 0x3faf4e6a },  /* 319:  1.8757509e+00  1.3695806e+00 */
    { 0x2675c2fd, 0x32fad41f },  /* 320:  8.5265709e-16  2.9200293e-08 */
    { 0x410421f6, 0x4037eb19 },  /* 321:  8.2582912e+00  2.8737243e+00 */
    { 0x41ceba6a, 0x40a2ab44 },  /* 322:  2.5841022e+01  5.0834066e+00 */
    { 0x3d614911, 0x3e7026f5 },  /* 323:  5.5001322e-02  2.3452361e-01 */
    { 0x3feb7675, 0x3fad9b46 },  /* 324:  1.8395525e+00  1.3563010e+00 */
    { 0x3f114ca6, 0x3f40dd45 },  /* 325:  5.6757581e-01  7.5337628e-01 */
    { 0x42edcdb6, 0x412e77a4 },  /* 326:  1.1890178e+02  1.0904209e+01 */
    { 0x3fe13bce, 0x3fa9cb30 },  /* 327:  1.7596376e+00  1.3265133e+00 */
    { 0x3fdcd54c, 0x3fa8207b },  /* 328:  1.7252593e+00  1.3134913e+00 */
    { 0x3ef5fc7f, 0x3f317193 },  /* 329:  4.8044202e-01  6.9313925e-01 */
    { 0x45352b10, 0x42575ba5 },  /* 330:  2.8986914e+03  5.3839497e+01 */
    { 0x3e04c060, 0x3eb85938 },  /* 331:  1.2964010e-01  3.6005569e-01 */
    { 0x3f1cb049, 0x3f4847d0 },  /* 332:  6.1206490e-01  7.8234577e-01 */
    { 0x3f278ac4, 0x3f4f19d2 },  /* 333:  6.5446115e-01  8.0898773e-01 */
    { 0x38a9b50e, 0x3c1362b9 },  /* 334:  8.0922720e-05  8.9957057e-03 */
    { 0x40cb3b2a, 0x4021498a },  /* 335:  6.3509722e+00  2.5201135e+00 */
    { 0x3fbad9ac, 0x3f9aa694 },  /* 336:  1.4597678e+00  1.2082085e+00 */
    { 0x4125bce0, 0x404dfb93 },  /* 337:  1.0358612e+01  3.2184798e+00 */
    { 0x3d5eff95, 0x3e6eee1a },  /* 338:  5.4442961e-02  2.3333015e-01 */
    { 0x170cd29c, 0x2b3ddeb7 },  /* 339:  4.5502266e-25  6.7455368e-13 */
    { 0x3f2742f2, 0x3f4eed6a },  /* 340:  6.5336525e-01  8.0831012e-01 */
    { 0x40eabb63, 0x402d5641 },  /* 341:  7.3353744e+00  2.7083896e+00 */
    { 0x3f14bcda, 0x3f432206 },  /* 342:  5.8100665e-01  7.6223792e-01 */
    { 0x3fd3beb8, 0x3fa4a188 },  /* 343:  1.6542578e+00  1.2861795e+00 */
    { 0x3ff2ed22, 0x3fb05626 },  /* 344:  1.8978617e+00  1.3776290e+00 */
    { 0x3e3ef649, 0x3edd1a39 },  /* 345:  1.8648638e-01  4.3184069e-01 */
    { 0x3d9d0eaa, 0x3e8dc946 },  /* 346:  7.6688126e-02  2.7692621e-01 */
    { 0x403cf40f, 0x3fdbefbe },  /* 347:  2.9523962e+00  1.7182538e+00 */
    { 0x4482595e, 0x42012b51 },  /* 348:  1.0427927e+03  3.2292301e+01 */
    { 0x3e780e30, 0x3efbff14 },  /* 349:  2.4224162e-01  4.9218048e-01 */
    { 0x3fdcd02c, 0x3fa81e88 },  /* 350:  1.7251029e+00  1.3134317e+00 */
    { 0x42fb00a9, 0x41333e68 },  /* 351:  1.2550129e+02  1.1202736e+01 */
    { 0x3e2bc316, 0x3ed1b15e },  /* 352:  1.6773638e-01  4.0955632e-01 */
    { 0x3e45133d, 0x3ee09d10 },  /* 353:  1.9245620e-01  4.3869830e-01 */
    { 0x41f96082, 0x40b2a993 },  /* 354:  3.1172123e+01  5.5832001e+00 */
    { 0x41b5a9fc, 0x40987d44 },  /* 355:  2.2708000e+01  4.7652912e+00 */
    { 0x439acb4e, 0x418cc2cf },  /* 356:  3.0958832e+02  1.7595122e+01 */
    { 0x3fb6b7da, 0x3f98ee5e },  /* 357:  1.4274857e+00  1.1947743e+00 */
    { 0x3ff1d746, 0x3faff130 },  /* 358:  1.8893821e+00  1.3745480e+00 */
    { 0x42f6f720, 0x4131cbe1 },  /* 359:  1.2348267e+02  1.1112275e+01 */
    { 0x3fe6120a, 0x3fab9b6f },  /* 360:  1.7974255e+00  1.3406810e+00 */
    { 0x414d44f4, 0x40653c4f },  /* 361:  1.2829334e+01  3.5818060e+00 */
    { 0x3b629dce, 0x3d70dc4d },  /* 362:  3.4578922e-03  5.8803845e-02 */
    { 0x409c6fff, 0x400d8195 },  /* 363:  4.8886714e+00  2.2110340e+00 */
    { 0x3ff0644b, 0x3faf6a0a },  /* 364:  1.8780607e+00  1.3704235e+00 */
    { 0x3e7fc6e3, 0x3effe370 },  /* 365:  2.4978213e-01  4.9978208e-01 */
    { 0x3f105f53, 0x3f403f82 },  /* 366:  5.6395453e-01  7.5096906e-01 */
    { 0x3cfd4a70, 0x3e340f16 },  /* 367:  3.0919284e-02  1.7583880e-01 */
    { 0x3e542abf, 0x3ee90e24 },  /* 368:  2.0719431e-01  4.5518602e-01 */
    { 0x3fee6ab3, 0x3faeb131 },  /* 369:  1.8626312e+00  1.3647825e+00 */
    { 0x448b852d, 0x4205a2d3 },  /* 370:  1.1161617e+03  3.3409007e+01 */
    { 0x40db9dbc, 0x4027a9b8 },  /* 371:  6.8630047e+00  2.6197337e+00 */
    { 0x3dbb6083, 0x3e9ade57 },  /* 372:  9.1492675e-02  3.0247756e-01 */
    { 0x3e3e0935, 0x3edc90cf },  /* 373:  1.8558200e-01  4.3079229e-01 */
    { 0x3dd62620, 0x3ea59018 },  /* 374:  1.0456491e-01  3.2336497e-01 */
    { 0x3ce309c0, 0x3e2a78f6 },  /* 375:  2.7714610e-02  1.6647706e-01 */
    { 0x3e445a3c, 0x3ee0338a },  /* 376:  1.9175047e-01  4.3789321e-01 */
    { 0x3f265909, 0x3f4e5c86 },  /* 377:  6.4979607e-01  8.0609929e-01 */
    { 0x31cc28ca, 0x38a1a7b9 },  /* 378:  5.9418186e-09  7.7083193e-05 */
    { 0x614907d0, 0x5062db3b },  /* 379:  2.3177241e+20  1.5224073e+10 */
    { 0x41c8bf06, 0x40a04c57 },  /* 380:  2.5093273e+01  5.0093186e+00 */
    { 0x410eb318, 0x403f218f },  /* 381:  8.9187241e+00  2.9864233e+00 */
    { 0x3feb7efa, 0x3fad9e6a },  /* 382:  1.8398125e+00  1.3563969e+00 */
    { 0x3fdef41c, 0x3fa8ee9e },  /* 383:  1.7418246e+00  1.3197820e+00 */
    { 0x3c301109, 0x3dd44dda },  /* 384:  1.0746249e-02  1.0366412e-01 */
    { 0x40fc0213, 0x40339a3a },  /* 385:  7.8752532e+00  2.8062882e+00 */
    { 0x43c14084, 0x419d4714 },  /* 386:  3.8650403e+02  1.9659706e+01 */
    { 0x3fccb328, 0x3fa1de78 },  /* 387:  1.5992174e+00  1.2646017e+00 */
    { 0x4145f1af, 0x40611bb0 },  /* 388:  1.2371505e+01  3.5173150e+00 */
    { 0x44bee29a, 0x421c4fc2 },  /* 389:  1.5270813e+03  3.9077888e+01 */
    { 0x3cd12cb9, 0x3e23a0f4 },  /* 390:  2.5534021e-02  1.5979368e-01 */
    { 0x3d4b95ee, 0x3e644b24 },  /* 391:  4.9703531e-02  2.2294289e-01 */
    { 0x1bcb3e3d, 0x2da14ac3 },  /* 392:  3.3623753e-22  1.8336781e-11 */
    { 0x41104db3, 0x404033c6 },  /* 393:  9.0189695e+00  3.0031599e+00 */
    { 0x406beb90, 0x3ff5c14d },  /* 394:  3.6862526e+00  1.9199616e+00 */
    { 0x40ed8efb, 0x402e60a0 },  /* 395:  7.4237037e+00  2.7246474e+00 */
    { 0x3ff3088f, 0x3fb0601a },  /* 396:  1.8986987e+00  1.3779328e+00 */
    { 0x42d08648, 0x41235fce },  /* 397:  1.0426227e+02  1.0210890e+01 */
    { 0x3b6b64f0, 0x3d757b25 },  /* 398:  3.5918318e-03  5.9931893e-02 */
    { 0x3f21d651, 0x3f4b8b5d },  /* 399:  6.3217646e-01  7.9509525e-01 */
    { 0x40d49599, 0x4024f4fb },  /* 400:  6.6432614e+00  2.5774525e+00 */
    { 0x41d787b6, 0x40a6188e },  /* 401:  2.6941265e+01  5.1904976e+00 */
    { 0x3f0ff720, 0x3f3ffa15 },  /* 402:  5.6236458e-01  7.4990971e-01 */
    { 0x3f42910c, 0x3f5f2ded },  /* 403:  7.6002574e-01  8.7179455e-01 */
    { 0x3e00c143, 0x3eb58d68 },  /* 404:  1.2573723e-01  3.5459447e-01 */
    { 0x40e786f9, 0x402c264c },  /* 405:  7.2352262e+00  2.6898376e+00 */
    { 0x3d6fffcf, 0x3e77dedc },  /* 406:  5.8593567e-02  2.4206108e-01 */
    { 0x3fd46e33, 0x3fa4e5b1 },  /* 407:  1.6596130e+00  1.2882597e+00 */
    { 0x3f2aed0a, 0x3f512e8d },  /* 408:  6.6767943e-01  8.1711653e-01 */
    { 0x4e1b0603, 0x46c736a7 },  /* 409:  6.5021562e+08  2.5499326e+04 */
    { 0x3f321842, 0x3f558600 },  /* 410:  6.9568264e-01  8.3407592e-01 */
    { 0x3f13e3f5, 0x3f42938c },  /* 411:  5.7769710e-01  7.6006388e-01 */
    { 0x3e7dc2fe, 0x3efee0de },  /* 412:  2.4781415e-01  4.9780935e-01 */
    { 0x40e627e2, 0x402ba395 },  /* 413:  7.1923685e+00  2.6818592e+00 */
    { 0x41e2fb78, 0x40aa7399 },  /* 414:  2.8372787e+01  5.3266113e+00 */
    { 0x3fb0418d, 0x3f9633d4 },  /* 415:  1.3770005e+00  1.1734566e+00 */
    { 0x3cf23784, 0x3e30142f },  /* 416:  2.9567488e-02  1.7195199e-01 */
    { 0x41df436a, 0x40a90ca7 },  /* 417:  2.7907917e+01  5.2827944e+00 */
    { 0x3bdec705, 0x3da8dd88 },  /* 418:  6.7986273e-03  8.2453789e-02 */
    { 0x4ab43196, 0x4517def8 },  /* 419:  5.9045870e+06  2.4299356e+03 */
    { 0x3b86db45, 0x3d836230 },  /* 420:  4.1154944e-03  6.4152119e-02 */
    { 0x40089174, 0x3fbafad5 },  /* 421:  2.1338778e+00  1.4607798e+00 */
    { 0x4d029e3d, 0x4636dc7b },  /* 422:  1.3696302e+08  1.1703120e+04 */
    { 0x3fd57185, 0x3fa54a39 },  /* 423:  1.6675268e+00  1.2913275e+00 */
    { 0x4282190d, 0x41010b6f },  /* 424:  6.5048927e+01  8.0652915e+00 */
    { 0x3f521e79, 0x3f67ed80 },  /* 425:  8.2077748e-01  9.0596770e-01 */
    { 0x4360dd04, 0x416fed57 },  /* 426:  2.2486334e+02  1.4995444e+01 */
    { 0x3fca9bd0, 0x3fa10a42 },  /* 427:  1.5828800e+00  1.2581256e+00 */
    { 0x40b12f8f, 0x4016991b },  /* 428:  5.5370555e+00  2.3530949e+00 */
    { 0x3ffeafd7, 0x3fb48df2 },  /* 429:  1.9897412e+00  1.4105819e+00 */
    { 0x3eedf1f6, 0x3f2e84f0 },  /* 430:  4.6473664e-01  6.8171595e-01 */
    { 0x3f00b45c, 0x3f35844f },  /* 431:  5.0275207e-01  7.0905012e-01 */
    { 0x3f131d4f, 0x3f4210b2 },  /* 432:  5.7466596e-01  7.5806726e-01 */
    { 0x40e6fb6a, 0x402bf262 },  /* 433:  7.2181902e+00  2.6866690e+00 */
    { 0x3fd3ac09, 0x3fa49a44 },  /* 434:  1.6536876e+00  1.2859579e+00 */
    { 0x3f098988, 0x3f3ba45c },  /* 435:  5.3725481e-01  7.3297668e-01 */
    { 0x3bdf9d77, 0x3da92ebb },  /* 436:  6.8241912e-03  8.2608663e-02 */
    { 0x3f4b67a4, 0x3f64312e },  /* 437:  7.9455018e-01  8.9137544e-01 */
    { 0x3fd446bf, 0x3fa4d661 },  /* 438:  1.6584090e+00  1.2877923e+00 */
    { 0x3fd5dfec, 0x3fa574f2 },  /* 439:  1.6708961e+00  1.2926314e+00 */
    { 0x3943aec8, 0x3c5fd192 },  /* 440:  1.8661760e-04  1.3660805e-02 */
    { 0x3e2a7a48, 0x3ed0e848 },  /* 441:  1.6648209e-01  4.0802217e-01 */
    { 0x416e368e, 0x4076f24b },  /* 442:  1.4888319e+01  3.8585385e+00 */
    { 0x3fb26438, 0x3f971c0e },  /* 443:  1.3936834e+00  1.1805437e+00 */
    { 0x3d417b4f, 0x3e5e8e6a },  /* 444:  4.7236737e-02  2.1734014e-01 */
    { 0x3b0cdb9f, 0x3d3de4ca },  /* 445:  2.1493209e-03  4.6360769e-02 */
    { 0x3f0c4952, 0x3f3d8213 },  /* 446:  5.4799378e-01  7.4026602e-01 */
    { 0x414ff2f6, 0x4066ba1e },  /* 447:  1.2996817e+01  3.6051098e+00 */
    { 0x4276f9a1, 0x40fb7273 },  /* 448:  6.1743778e+01  7.8577209e+00 */
    { 0x40b1d835, 0x4016e0b6 },  /* 449:  5.5576425e+00  2.3574653e+00 */
    { 0x411cfac7, 0x40487766 },  /* 450:  9.8112249e+00  3.1322875e+00 */
    { 0x604dbf77, 0x4fe580ad },  /* 451:  5.9302797e+19  7.7008310e+09 */
    { 0x3bb945a6, 0x3d99ff06 },  /* 452:  5.6540547e-03  7.5193448e-02 */
    { 0x3ff26926, 0x3fb02638 },  /* 453:  1.8938339e+00  1.3761664e+00 */
    { 0x4402a0cf, 0x41b6de48 },  /* 454:  5.2251263e+02  2.2858535e+01 */
    { 0x3dabc3a6, 0x3e9446b3 },  /* 455:  8.3869264e-02  2.8960191e-01 */
    { 0x414d07ae, 0x40651a16 },  /* 456:  1.2814375e+01  3.5797172e+00 */
    { 0x40ca5184, 0x4020ecb9 },  /* 457:  6.3224506e+00  2.5144484e+00 */
    { 0x3d7961b5, 0x3e7cab4e },  /* 458:  6.0884196e-02  2.4674723e-01 */
    { 0x3eef56e4, 0x3f2f07a4 },  /* 459:  4.6745980e-01  6.8371032e-01 */
    { 0x3bae42b7, 0x3d95598b },  /* 460:  5.3180116e-03  7.2924698e-02 */
    { 0x3e01c7a2, 0x3eb64605 },  /* 461:  1.2673810e-01  3.5600295e-01 */
    { 0x3e700535, 0x3ef7e1a6 },  /* 462:  2.3439486e-01  4.8414343e-01 */
    { 0x3dea812d, 0x3ead40c2 },  /* 463:  1.1450420e-01  3.3838469e-01 */
    { 0x43923bf1, 0x4188d04a },  /* 464:  2.9246829e+02  1.7101704e+01 */
    { 0x3dfd0e74, 0x3eb3f9c3 },  /* 465:  1.2356272e-01  3.5151490e-01 */
    { 0x40dd236a, 0x40283e35 },  /* 466:  6.9105730e+00  2.6287969e+00 */
    { 0x3886070e, 0x3c02faa7 },  /* 467:  6.3909320e-05  7.9943305e-03 */
    { 0x4737548c, 0x4358a3a3 },  /* 468:  4.6932547e+04  2.1663921e+02 */
    { 0x40f89957, 0x4032622c },  /* 469:  7.7687182e+00  2.7872420e+00 */
    { 0x3e83eb0f, 0x3f01f1c0 },  /* 470:  2.5765273e-01  5.0759505e-01 */
    { 0x3d7043a0, 0x3e7801df },  /* 471:  5.8658242e-02  2.4219464e-01 */
    { 0x3e87e557, 0x3f03e38c },  /* 472:  2.6542160e-01  5.1519084e-01 */
    { 0x3fe4ebf4, 0x3fab2d9f },  /* 473:  1.7884507e+00  1.3373297e+00 */
    { 0x3f1539a4, 0x3f4373d0 },  /* 474:  5.8291078e-01  7.6348594e-01 */
    { 0x3cd50579, 0x3e25205d },  /* 475:  2.6003586e-02  1.6125627e-01 */
    { 0x69cd7ed0, 0x54a22ee9 },  /* 476:  3.1053581e+25  5.5725740e+12 */
    { 0x3e8fa8cf, 0x3f079a96 },  /* 477:  2.8058478e-01  5.2970254e-01 */
    { 0x3f0d85eb, 0x3f3e5772 },  /* 478:  5.5282468e-01  7.4352181e-01 */
    { 0x3f37ff18, 0x3f590850 },  /* 479:  7.1873617e-01  8.4778309e-01 */
    { 0x424bc81f, 0x40e46746 },  /* 480:  5.0945431e+01  7.1376068e+00 */
    { 0x3e760e2d, 0x3efafa7b },  /* 481:  2.4028845e-01  4.9019226e-01 */
    { 0x4103977d, 0x40378aa1 },  /* 482:  8.2244844e+00  2.8678362e+00 */
    { 0x41acccf1, 0x4094b909 },  /* 483:  2.1600069e+01  4.6475874e+00 */
    { 0x3f50790a, 0x3f670474 },  /* 484:  8.1434691e-01  9.0241172e-01 */
    { 0x41f60d74, 0x40b177b0 },  /* 485:  3.0756569e+01  5.5458605e+00 */
    { 0x3ff52b93, 0x3fb12628 },  /* 486:  1.9153923e+00  1.3839770e+00 */
    { 0x3c60e365, 0x3deff0be },  /* 487:  1.3726090e-02  1.1715840e-01 */
    { 0x410dccd6, 0x403e871d },  /* 488:  8.8625088e+00  2.9769966e+00 */
    { 0x39a9a08a, 0x3c9359d1 },  /* 489:  3.2353803e-04  1.7987163e-02 */
    { 0x190ac8b2, 0x2c3c7d96 },  /* 490:  7.1749629e-24  2.6786121e-12 */
    { 0x3f25f864, 0x3f4e208b },  /* 491:  6.4832139e-01  8.0518407e-01 */
    { 0x3fec7f2c, 0x3fadfcc1 },  /* 492:  1.8476310e+00  1.3592759e+00 */
    { 0x413b45a7, 0x405af4b1 },  /* 493:  1.1704505e+01  3.4211847e+00 */
    { 0x3e4cbae9, 0x3ee4ef2e },  /* 494:  1.9993176e-01  4.4713729e-01 */
    { 0x3dd62832, 0x3ea590e5 },  /* 495:  1.0456885e-01  3.2337108e-01 */
    { 0x3c40b05c, 0x3dde1992 },  /* 496:  1.1760797e-02  1.0844721e-01 */
    { 0x3dbce0a8, 0x3e9b7cc6 },  /* 497:  9.2225373e-02  3.0368631e-01 */
    { 0x6c9d01b0, 0x560dc36a },  /* 498:  1.5184746e+27  3.8967609e+13 */
    { 0x4213f697, 0x40c29fcd },  /* 499:  3.6990810e+01  6.0820071e+00 */
    { 0x4256e459, 0x40ea8c10 },  /* 500:  5.3722996e+01  7.3295972e+00 */
};

void x_exit (int index)
{
#ifndef	__AVR__
    fprintf (stderr, "t[%d]:  %#lx\n", index - 1, v.lo);
#endif
    exit (index ? index : -1);
}

int main ()
{
    union lofl_u x, z;
    int i;
    
    for (i = 0; i < (int) (sizeof(t) / sizeof(t[0])); i++) {
	x.lo = pgm_read_dword (& t[i].x);
	z.lo = pgm_read_dword (& t[i].z);
	v.fl = sqrt (x.fl);
	/* Comparison is integer to verify the zero sign.	*/
	if (v.lo != z.lo)
	    x_exit (i+1);
    }
    return 0;
}
