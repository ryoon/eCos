#ifndef CYGONCE_LIBM_SCABNF_H
#define CYGONCE_LIBM_SCABNF_H
//===========================================================================
//
//      scalbf.h
//
//      Test vectors for testing of scalbf() math library function
//
//===========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####
// -------------------------------------------
// This file is part of eCos, the Embedded Configurable Operating System.
// Copyright (C) 2012 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 or (at your option) any later
// version.
//
// eCos is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License
// along with eCos; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
// As a special exception, if other files instantiate templates or use
// macros or inline functions from this file, or you compile this file
// and link it with other works to produce a work based on this file,
// this file does not by itself cause the resulting work to be covered by
// the GNU General Public License. However the source code for this file
// must still be made available in accordance with section (3) of the GNU
// General Public License v2.
//
// This exception does not invalidate any other reasons why a work based
// on this file might be covered by the GNU General Public License.
// -------------------------------------------
// ####ECOSGPLCOPYRIGHTEND####
//===========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):
// Contributors:  visar, ilijak
// Date:        1998-02-13
// Purpose:
// Description:
// Usage:       #include "vectors/scalbf.h"
//
//####DESCRIPTIONEND####
//
//===========================================================================


// CONFIGURATION

#include <pkgconf/libm.h>   // Configuration header


// INCLUDES

#include <cyg/infra/cyg_type.h>    // Common type definitions and support
#include "vectors/vector_support_float.h"// extra support for math tests

#define SCALBF_TOLERANCE 1.0E-04

static const Cyg_libm_test_float_vec_t scalbf_vec[] = {

// AUTOMATICALLY GENERATED VECTORS START

{0, 3212836864u, 3212836864u, 3204448256u, 0, SCALBF_TOLERANCE, 0},
{1, 3211998003u, 3212836864u, 3203609395u, 0, SCALBF_TOLERANCE, 0},
{2, 3211159142u, 3212836864u, 3202770534u, 0, SCALBF_TOLERANCE, 0},
{3, 3210320282u, 3212836864u, 3201931674u, 0, SCALBF_TOLERANCE, 0},
{4, 3209481421u, 3212836864u, 3201092813u, 0, SCALBF_TOLERANCE, 0},
{5, 3208642560u, 3212836864u, 3200253952u, 0, SCALBF_TOLERANCE, 0},
{6, 3207803699u, 3212836864u, 3199415091u, 0, SCALBF_TOLERANCE, 0},
{7, 3206964838u, 3212836864u, 3198576230u, 0, SCALBF_TOLERANCE, 0},
{8, 3206125978u, 3212836864u, 3197737370u, 0, SCALBF_TOLERANCE, 0},
{9, 3205287117u, 3212836864u, 3196898509u, 0, SCALBF_TOLERANCE, 0},
{10, 3204448256u, 3212836864u, 3196059648u, 0, SCALBF_TOLERANCE, 0},
{11, 3202770534u, 3212836864u, 3194381926u, 0, SCALBF_TOLERANCE, 0},
{12, 3201092813u, 3212836864u, 3192704205u, 0, SCALBF_TOLERANCE, 0},
{13, 3199415091u, 3212836864u, 3191026483u, 0, SCALBF_TOLERANCE, 0},
{14, 3197737370u, 3212836864u, 3189348762u, 0, SCALBF_TOLERANCE, 0},
{15, 3196059648u, 3212836864u, 3187671040u, 0, SCALBF_TOLERANCE, 0},
{16, 3192704205u, 3212836864u, 3184315597u, 0, SCALBF_TOLERANCE, 0},
{17, 3189348762u, 3212836864u, 3180960154u, 0, SCALBF_TOLERANCE, 0},
{18, 3184315597u, 3212836864u, 3175926989u, 0, SCALBF_TOLERANCE, 0},
{19, 3175926989u, 3212836864u, 3167538381u, 0, SCALBF_TOLERANCE, 0},
{20, 1028443341u, 3212836864u, 1020054733u, 0, SCALBF_TOLERANCE, 0},
{21, 1036831949u, 3212836864u, 1028443341u, 0, SCALBF_TOLERANCE, 0},
{22, 1041865114u, 3212836864u, 1033476506u, 0, SCALBF_TOLERANCE, 0},
{23, 1045220557u, 3212836864u, 1036831949u, 0, SCALBF_TOLERANCE, 0},
{24, 1048576000u, 3212836864u, 1040187392u, 0, SCALBF_TOLERANCE, 0},
{25, 1050253722u, 3212836864u, 1041865114u, 0, SCALBF_TOLERANCE, 0},
{26, 1051931443u, 3212836864u, 1043542835u, 0, SCALBF_TOLERANCE, 0},
{27, 1053609165u, 3212836864u, 1045220557u, 0, SCALBF_TOLERANCE, 0},
{28, 1055286886u, 3212836864u, 1046898278u, 0, SCALBF_TOLERANCE, 0},
{29, 1056964608u, 3212836864u, 1048576000u, 0, SCALBF_TOLERANCE, 0},
{30, 1057803469u, 3212836864u, 1049414861u, 0, SCALBF_TOLERANCE, 0},
{31, 1058642330u, 3212836864u, 1050253722u, 0, SCALBF_TOLERANCE, 0},
{32, 1059481190u, 3212836864u, 1051092582u, 0, SCALBF_TOLERANCE, 0},
{33, 1060320051u, 3212836864u, 1051931443u, 0, SCALBF_TOLERANCE, 0},
{34, 1061158912u, 3212836864u, 1052770304u, 0, SCALBF_TOLERANCE, 0},
{35, 1061997773u, 3212836864u, 1053609165u, 0, SCALBF_TOLERANCE, 0},
{36, 1062836634u, 3212836864u, 1054448026u, 0, SCALBF_TOLERANCE, 0},
{37, 1063675494u, 3212836864u, 1055286886u, 0, SCALBF_TOLERANCE, 0},
{38, 1064514355u, 3212836864u, 1056125747u, 0, SCALBF_TOLERANCE, 0},
{39, 1341514497u, 3466051188u, 0u, 0, SCALBF_TOLERANCE, 0},
{40, 1001673627u, 3462631271u, 0u, 0, SCALBF_TOLERANCE, 0},
{41, 3048866608u, 3449209899u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{42, 1333134799u, 1338107877u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{43, 1187847971u, 1317663644u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{44, 3444653659u, 1279248024u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{45, 974547519u, 3475164509u, 0u, 0, SCALBF_TOLERANCE, 0},
{46, 3182301130u, 3460764044u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{47, 3417964312u, 1321337529u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{48, 1148867223u, 1256486202u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{49, 3319315516u, 3422089012u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{50, 1134593658u, 3456812581u, 0u, 0, SCALBF_TOLERANCE, 0},
{51, 3316278408u, 3455589207u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{52, 3131791114u, 3408392958u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{53, 881280146u, 3421884736u, 0u, 0, SCALBF_TOLERANCE, 0},
{54, 1268194719u, 1332489410u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{55, 1133420220u, 1245770860u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{56, 3295996963u, 3453334307u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{57, 3424831780u, 1304806106u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{58, 1257596246u, 3420832544u, 0u, 0, SCALBF_TOLERANCE, 0},
{59, 3235326590u, 1271705594u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{60, 1106502045u, 1290849316u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{61, 3427296372u, 3455289118u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{62, 1198917460u, 1327195159u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{63, 3114686212u, 3476082461u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{64, 1165195428u, 3390323168u, 0u, 0, SCALBF_TOLERANCE, 0},
{65, 3275973009u, 3450721670u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{66, 3391162308u, 1291220039u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{67, 1089986803u, 3462160118u, 0u, 0, SCALBF_TOLERANCE, 0},
{68, 3262169538u, 1268270462u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{69, 3404372005u, 3450484255u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{70, 999985470u, 3409354318u, 0u, 0, SCALBF_TOLERANCE, 0},
{71, 3132541814u, 3444521949u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{72, 1164046161u, 3440635788u, 0u, 0, SCALBF_TOLERANCE, 0},
{73, 3469748379u, 3412765608u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{74, 948775569u, 3485444126u, 0u, 0, SCALBF_TOLERANCE, 0},
{75, 3157534378u, 3451674717u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{76, 3162548604u, 3461790298u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{77, 3424264117u, 3434026174u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{78, 1311706596u, 1254918706u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{79, 1337315179u, 3461361185u, 0u, 0, SCALBF_TOLERANCE, 0},
{80, 3337499209u, 1226297264u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{81, 3220979495u, 3429223871u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{82, 1017239798u, 3438501281u, 0u, 0, SCALBF_TOLERANCE, 0},
{83, 3092982276u, 3445282331u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{84, 1168098747u, 1316854744u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{85, 3301009024u, 3406174560u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{86, 1032920919u, 3449126417u, 0u, 0, SCALBF_TOLERANCE, 0},
{87, 3388153589u, 3426245389u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{88, 1258369714u, 3462258576u, 0u, 0, SCALBF_TOLERANCE, 0},
{89, 3462285635u, 3444030332u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{90, 3131219358u, 3471261157u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{91, 3418753236u, 3481843070u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{92, 1277417964u, 3487506626u, 0u, 0, SCALBF_TOLERANCE, 0},
{93, 3320923228u, 3464544249u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{94, 1337400405u, 3488844154u, 0u, 0, SCALBF_TOLERANCE, 0},
{95, 1215968622u, 3469884568u, 0u, 0, SCALBF_TOLERANCE, 0},
{96, 3091024506u, 3456196859u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{97, 1157186482u, 1288722647u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{98, 3477008113u, 1331845018u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{99, 3292127294u, 3409957764u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{100, 1160162706u, 1264067367u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{101, 1096155623u, 1256423752u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{102, 3475052219u, 1284049853u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{103, 3154720153u, 3443720494u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{104, 3108347547u, 3434003435u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{105, 3272661536u, 3461799138u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{106, 3086068902u, 3484245751u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{107, 1086717248u, 3423795374u, 0u, 0, SCALBF_TOLERANCE, 0},
{108, 1200927971u, 1317167489u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{109, 3326858092u, 3452602832u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{110, 3316611992u, 3394732912u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{111, 3066654389u, 3443934204u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{112, 3295326432u, 1313396175u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{113, 3455131757u, 1260217257u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{114, 3157626955u, 3483653298u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{115, 1105291533u, 3482971524u, 0u, 0, SCALBF_TOLERANCE, 0},
{116, 3370691006u, 1295870514u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{117, 3335212901u, 3486414589u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{118, 3283471961u, 1260093226u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{119, 1288901567u, 1296370667u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{120, 3100289712u, 3456334210u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{121, 3375507013u, 1306310823u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{122, 1258114435u, 1291336083u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{123, 3445262427u, 3465211174u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{124, 1102061604u, 3424449935u, 0u, 0, SCALBF_TOLERANCE, 0},
{125, 1284174954u, 3436881197u, 0u, 0, SCALBF_TOLERANCE, 0},
{126, 1306695905u, 1292690378u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{127, 903129873u, 3416864271u, 0u, 0, SCALBF_TOLERANCE, 0},
{128, 1208345407u, 1254181270u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{129, 1258634105u, 1247426200u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{130, 1248478509u, 1287895126u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{131, 1153863988u, 3430539165u, 0u, 0, SCALBF_TOLERANCE, 0},
{132, 3319723279u, 3414482416u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{133, 3237813668u, 3441016803u, 2147483648u, 0, SCALBF_TOLERANCE, 0},
{134, 1315857601u, 3487600045u, 0u, 0, SCALBF_TOLERANCE, 0},
{135, 1028355074u, 3442294040u, 0u, 0, SCALBF_TOLERANCE, 0},
{136, 3392827417u, 1277961150u, 4286578688u, 0, SCALBF_TOLERANCE, 0},
{137, 1161241793u, 1328003707u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{138, 1171318485u, 3374409104u, 0u, 0, SCALBF_TOLERANCE, 0},
{139, 944050180u, 3452557879u, 0u, 0, SCALBF_TOLERANCE, 0},
{140, 1155775526u, 1255814444u, 2139095040u, 0, SCALBF_TOLERANCE, 0},
{141, 1234491880u, 3408568717u, 0u, 0, SCALBF_TOLERANCE, 0}

// AUTOMATICALLY GENERATED VECTORS STOP

};

#endif // CYGONCE_LIBM_SCABNF_H multiple inclusion protection

// EOF scalbf.h