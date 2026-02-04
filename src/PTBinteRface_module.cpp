#include <Rcpp.h>
#include <para_tb_model.h>

int runPTBmodel()
{
  /* content of main.cpp from underlying package


   //vDataFiles = {"BirthFemaleEvents_withId.csv", "CullingRates_withId.csv", "Headcounts_withId.csv", "Network_withId_and_breedType_coderace.csv"};
   //BirthFemaleEvents_withId.csv
   //12345678	0	0	1	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	2	2	0	0	2	2	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	1	0	0	1	0	2	0	0	0	0	0	0	0	1	0	0	0	0	0	0	1	3	1	0	0	0	1	0	0	1	1	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	1	0	0	1	0	0	1	0	0	0	1	0	0	1	0	1	2	0	1	0	0	0	0	1	0	0	0	0	0	0	1	0	0	0	2	1	0	0	0	0	0	0	0	2	0	1	0	0	0	1	0	0	0	0	1	0	0	3	0	0	0	0	1	0	0	2	1	0	0	0	0	0	1	0	0	1	0	0	0	1	0	1	2	0	0	0	0	0	0	1	0	2	0	0	0	0	0	0	0	1	0	0	0	1	1	0	2	0	0	0	0	1	0	2	0	0	0	0	0	0	0	0	3	0	0	0	0	0	0	0	1	0	0	0	1	0	0	0	1	0	0	0	0	1	0	0	0	0	1	0	1	0	0	1	0	0	0	0	1	0	1	0	0	0	0	0	1	0	0	1	0	0	1	0	0	3	1	0	0	1	1	0	0	1	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	3	2	0	0	0	0	0	0	3	0	0	0	1	1	0	1	1	0	0	1	1	0	0	1	0	0	0	0	0	0	0	2	0	0	0	0	0	1	0	1	0	0	0	0	0	0	1	0	0	0	1	0	0	0	1	1	0	0	0	0	0	0	0	0	1	0	0	0	4	0	0	1	0	0	0	1	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0
   //Headcounts_withId.csv
   //12345678	0	1	0	0	0	1	0	0	0	0	0	2	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	1	0	1	0	0	1	0	0	0	0	1	0	0	1	0	0	0	0	0	0	0	0	0	1	1	0	2	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	3	0	0	0	0	0	0	0	0	0	2	0	0	0	0	0	0	1	0	0	0	0	0	12	12	9	1	3
   //CullingRates_withId.csv
   //12345678	0.000	0.000000	0.000000	0.000152	0.000250	0.000476	0.000000	0.001462	0.000000	0.071	0.000000	0.000000	0.000000	0.000000	0.001266	0.001158	0.000849	0.000000	0.000	0.000000	0.000000	0.000593	0.000910	0.000000	0.000779	0.000350	0.000630	0.000	0.000000	0.002621	0.000373	0.000000	0.000428	0.001046	0.000946	0.000935	0.000	0.000000	0.001142	0.000763	0.000229	0.000482	0.000000	0.001320	0.000900	0.071	0.000000	0.001751	0.000099	0.000000	0.000506	0.000285	0.000534	0.001470	0.000	0.003460	0.000000	0.000286	0.000223	0.000000	0.002069	0.002353	0.003303	0.000	0.000000	0.004065	0.000547	0.000000	0.000000	0.000984	0.000000	0.000338	0.000	0.000000	0.002155	0.000344	0.000000	0.000000	0.000298	0.002676	0.001821
   //Network_withId_and_breedType_coderace.csv
   //22222222	12345678	196	135	L	66
   //12345678	outside	462	133	L	66
   //12345678	outside	462	133	L	66
   //12345678	outside	193	3	X	39
   //12345678	outside	462	133	L	66
   //outside	12345678	203	132	L	66
   //12345678	outside	188	4	X	39
   //12345678	outside	462	133	L	66
   //12345678	outside	462	133	L	66
   //12345678	33333333	467	134	L	66
   //12345678	44444444	463	14	L	66
   //12345678	44444444	463	4	L	66
   //55555555	12345678	184	135	L	66
   //66666666	12345678	2	131	L	66
   //77777777	12345678	203	135	L	66
   //12345678	outside	462	132	L	66
   //66666666	12345678	5	117	L	66
   //12345678	outside	462	131	L	66
   //12345678	outside	462	132	L	66
   //12345678	outside	462	132	L	66
   //outside	12345678	203	132	L	66
   //12345678	outside	462	132	L	66
   //12345678	outside	462	133	L	66
   //12345678	outside	462	133	L	66
   //12345678	outside	462	133	L	66
   //12345678	outside	462	133	L	66
   //12345678	outside	462	133	L	66
   //12345678	33333333	467	133	L	66
   //12345678	outside	369	2	X	39
   //12345678	outside	462	133	L	66
   //88888888	12345678	9	131	L	19
   //12345678	88888888	16	131	L	19
   //12345678	outside	197	133	L	66
   //12345678	outside	462	132	L	66
   //12345678	outside	233	3	X	39
   //77777777	12345678	203	129	L	66
   //12345678	outside	462	132	L	66
   //outside	12345678	203	117	L	66
   //12345678	outside	462	135	L	66
   //12345678	99999999	6	3	X	39
   //00000000	12345678	187	135	L	66
   //12345678	outside	462	132	L	66
   //11111111	12345678	203	131	L	66
   //12345678	01111111	467	135	L	66
   //02222222	12345678	195	131	L	66
   //04444444	12345678	2	132	L	66
   //12345678	outside	16	132	L	66
   //02222222	12345678	195	133	L	66
   //12345678	outside	462	134	L	66
   //12345678	outside	462	134	L	66
   //12345678	outside	428	133	L	66
   //12345678	outside	462	134	L	66
   //12345678	outside	369	3	X	39
   //12345678	outside	462	131	L	66
   //12345678	outside	462	131	L	66
   //12345678	outside	462	134	L	66
   //12345678	outside	462	135	L	66
   //12345678	outside	462	135	L	66
   //03333333	12345678	202	131	L	66
   //12345678	outside	16	135	L	66
   //12345678	05555555	71	3	X	39
   //12345678	outside	462	135	L	66
   //12345678	outside	16	135	L	66
   //03333333	12345678	202	132	L	66
   //12345678	outside	462	131	L	66
   //12345678	outside	462	131	L	66
   //12345678	outside	462	131	L	66
   //12345678	outside	16	134	L	66
   //12345678	outside	395	2	X	39
   //04444444	12345678	8	132	L	66
   //initialInf_r10_e0.35_d_y.txt
   //12345678  6       11      43
   //selectedInitScenarioForPrev_1to90.csv
   //SR,T,L,Is,Ic,SR1,SR2,SR3,SR4,SR5,SR6,SR7,SR8,SR9,SR10,SR11,SR12,SR13,SR14,SR15,SR16,SR17,SR18,SR19,SR20,SR21,SR22,SR23,SR24,SR25,SR26,SR27,SR28,SR29,SR30,SR31,SR32,SR33,SR34,SR35,SR36,SR37,SR38,SR39,SR40,SR41,SR42,SR43,SR44,SR45,SR46,SR47,SR48,SR49,SR50,SR51,SR52,SR53,SR54,SR55,SR56,SR57,SR58,SR59,SR60,SR61,SR62,SR63,SR64,SR65,SR66,SR67,SR68,SR69,SR70,SR71,SR72,SR73,SR74,SR75,SR76,SR77,SR78,SR79,SR80,SR81,SR82,SR83,SR84,SR85,SR86,SR87,SR88,SR89,SR90,SR91,SR92,SR93,SR94,SR95,SR96,SR97,SR98,SR99,SR100,SR101,SR102,SR103,SR104,SR105,SR106,SR107,SR108,SR109,SR110,SR111,SR112,SR113,SR114,SR115,SR116,SR117,SR118,SR119,SR120,SR121,SR122,SR123,SR124,SR125,SR126,SR127,SR128,SR129,SR130,SR131,SR132,SR133,SR134,SR135,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45,T46,T47,T48,T49,T50,T51,T52,T53,T54,T55,T56,T57,T58,T59,T60,T61,T62,T63,T64,T65,T66,T67,T68,T69,T70,T71,T72,T73,T74,T75,T76,T77,T78,T79,T80,T81,T82,T83,T84,T85,T86,T87,T88,T89,T90,T91,T92,T93,T94,T95,T96,T97,T98,T99,T100,T101,T102,T103,T104,T105,T106,T107,T108,T109,T110,T111,T112,T113,T114,T115,T116,T117,T118,T119,T120,T121,T122,T123,T124,T125,T126,T127,T128,T129,T130,T131,T132,T133,T134,T135,L1,L2,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,L14,L15,L16,L17,L18,L19,L20,L21,L22,L23,L24,L25,L26,L27,L28,L29,L30,L31,L32,L33,L34,L35,L36,L37,L38,L39,L40,L41,L42,L43,L44,L45,L46,L47,L48,L49,L50,L51,L52,L53,L54,L55,L56,L57,L58,L59,L60,L61,L62,L63,L64,L65,L66,L67,L68,L69,L70,L71,L72,L73,L74,L75,L76,L77,L78,L79,L80,L81,L82,L83,L84,L85,L86,L87,L88,L89,L90,L91,L92,L93,L94,L95,L96,L97,L98,L99,L100,L101,L102,L103,L104,L105,L106,L107,L108,L109,L110,L111,L112,L113,L114,L115,L116,L117,L118,L119,L120,L121,L122,L123,L124,L125,L126,L127,L128,L129,L130,L131,L132,L133,L134,L135,Is1,Is2,Is3,Is4,Is5,Is6,Is7,Is8,Is9,Is10,Is11,Is12,Is13,Is14,Is15,Is16,Is17,Is18,Is19,Is20,Is21,Is22,Is23,Is24,Is25,Is26,Is27,Is28,Is29,Is30,Is31,Is32,Is33,Is34,Is35,Is36,Is37,Is38,Is39,Is40,Is41,Is42,Is43,Is44,Is45,Is46,Is47,Is48,Is49,Is50,Is51,Is52,Is53,Is54,Is55,Is56,Is57,Is58,Is59,Is60,Is61,Is62,Is63,Is64,Is65,Is66,Is67,Is68,Is69,Is70,Is71,Is72,Is73,Is74,Is75,Is76,Is77,Is78,Is79,Is80,Is81,Is82,Is83,Is84,Is85,Is86,Is87,Is88,Is89,Is90,Is91,Is92,Is93,Is94,Is95,Is96,Is97,Is98,Is99,Is100,Is101,Is102,Is103,Is104,Is105,Is106,Is107,Is108,Is109,Is110,Is111,Is112,Is113,Is114,Is115,Is116,Is117,Is118,Is119,Is120,Is121,Is122,Is123,Is124,Is125,Is126,Is127,Is128,Is129,Is130,Is131,Is132,Is133,Is134,Is135,Ic1,Ic2,Ic3,Ic4,Ic5,Ic6,Ic7,Ic8,Ic9,Ic10,Ic11,Ic12,Ic13,Ic14,Ic15,Ic16,Ic17,Ic18,Ic19,Ic20,Ic21,Ic22,Ic23,Ic24,Ic25,Ic26,Ic27,Ic28,Ic29,Ic30,Ic31,Ic32,Ic33,Ic34,Ic35,Ic36,Ic37,Ic38,Ic39,Ic40,Ic41,Ic42,Ic43,Ic44,Ic45,Ic46,Ic47,Ic48,Ic49,Ic50,Ic51,Ic52,Ic53,Ic54,Ic55,Ic56,Ic57,Ic58,Ic59,Ic60,Ic61,Ic62,Ic63,Ic64,Ic65,Ic66,Ic67,Ic68,Ic69,Ic70,Ic71,Ic72,Ic73,Ic74,Ic75,Ic76,Ic77,Ic78,Ic79,Ic80,Ic81,Ic82,Ic83,Ic84,Ic85,Ic86,Ic87,Ic88,Ic89,Ic90,Ic91,Ic92,Ic93,Ic94,Ic95,Ic96,Ic97,Ic98,Ic99,Ic100,Ic101,Ic102,Ic103,Ic104,Ic105,Ic106,Ic107,Ic108,Ic109,Ic110,Ic111,Ic112,Ic113,Ic114,Ic115,Ic116,Ic117,Ic118,Ic119,Ic120,Ic121,Ic122,Ic123,Ic124,Ic125,Ic126,Ic127,Ic128,Ic129,Ic130,Ic131,Ic132,Ic133,Ic134,Ic135,int1,int2,int3,int4,int5,intg,ext1,ext2,ext3,extg,milk,colstrum
   //0.890071,0.039007099999999996,0.0638298,0.0035461,0.0035461,0.0106383,0.0,0.0070922,0.0035461,0.0070922,0.0,0.0,0.0035461,0.0,0.0,0.0070922,0.0070922,0.0070922,0.0070922,0.0,0.0,0.0,0.0,0.0,0.0070922,0.0035461,0.0035461,0.0035461,0.0070922,0.0177305,0.0,0.0,0.0106383,0.0,0.0035461,0.0070922,0.0070922,0.0035461,0.0,0.0035461,0.0035461,0.0,0.0,0.0035461,0.0035461,0.0,0.0106383,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0035461,0.0,0.0106383,0.0035461,0.0,0.0,0.0,0.0035461,0.0,0.0,0.0,0.0070922,0.0035461,0.0,0.0070922,0.0,0.0070922,0.0070922,0.0,0.0070922,0.0070922,0.0,0.0,0.0035461,0.0,0.0035461,0.0,0.0,0.0106383,0.0177305,0.0070922,0.0070922,0.0035461,0.0070922,0.0070922,0.0141844,0.0,0.0,0.0106383,0.0,0.0,0.0035461,0.0070922,0.0035461,0.0177305,0.0070922,0.0177305,0.0,0.0070922,0.0,0.0,0.0,0.0035461,0.0,0.0070922,0.0141844,0.0035461,0.0,0.0035461,0.0070922,0.0035461,0.0141844,0.0,0.0035461,0.0106383,0.0070922,0.0035461,0.0070922,0.0070922,0.0106383,0.0106383,0.0035461,0.0,0.0,0.0,0.0,0.0035461,0.0,0.0106383,0.10638299999999999,0.117021,0.0638298,0.0460993,0.039007099999999996,0.0,0.0,0.0,0.0,0.0,0.0035461,0.0,0.0035461,0.0,0.0,0.0035461,0.0,0.0,0.0,0.0,0.0035461,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0035461,0.0,0.0,0.0,0.0,0.0,0.0035461,0.0035461,0.0,0.0035461,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0035461,0.0035461,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0035461,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0035461,0.0,0.0035461,0.0035461,0.0,0.0,0.0,0.0,0.0035461,0.0035461,0.0035461,0.0070922,0.0,0.0106383,0.0070922,0.0,0.0,0.0035461,0.0,0.0,0.0,0.0,0.0,0.0070922,0.0,0.0,0.0,0.0,0.0,0.0,0.0035461,0.0,0.0,0.0,0.0,0.0,0.0035461,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0035461,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0035461,0.0,0.0,0.0,0.0,1470440.0,9137040.0,20961900.0,0.0,1657160000000.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0


    TCLAP::CmdLine cmd("Simulate bovine paratuberculosis (PTB) spread between dairy herds in a region. It is data-driven and mechanistic.\nSee README for more information.", ' ', "0.1");
    TCLAP::ValueArg<int> iRunsNbArg("r", "runsNb", "number of repetitions (default=1)", false, 1, "int");
    //years nb?
    TCLAP::ValueArg<float> iCalfExposureArg("e", "calfExposure", "calf rearing improvement is defined as a reduced exposure to the general environment by varying parameter from 1.0 to 0.35 (default=1.0)", false, 1.0, "float");
    TCLAP::ValueArg<float> iCullingRateIhArg("k", "cullingRateIh", "culling rate of detected Ih animals (default=1/26.)", false, 0.0384615, "float");
    //same for Im?
    //+ prop?
    TCLAP::ValueArg<std::string> iOutDirectoryPathArg("o", "outDirectoryPath", "relative folder path to write all output files (default='../results/')", false, "../results/", "string");
    TCLAP::ValueArg<std::string> iInitInFilePathArg("i", "initInFilePath", "if not empty, then load initial 'infection' from this file: 1 line = 1 infected herd with id, nbInfectedAnimals, prevalence and repetitionNum refering to a line in 'initCondFileName' (default='')", false, "", "string");
    TCLAP::ValueArg<float> iTestSensitivityItIlArg("", "testSensitivityItIl", "test sensitivity of low positive animals. (default=0.15)", false, 0.15, "float");
    TCLAP::ValueArg<float> iTestSensitivityImArg("", "testSensitivityIm", "test sensitivity of moderately positive animals. (default=0.47)", false, 0.47, "float");
    TCLAP::ValueArg<float> iTestSensitivityIhArg("", "testSensitivityIh", "test sensitivity of highly positive animals. (default=0.71)", false, 0.71, "float");
    TCLAP::ValueArg<float> iTestSpecificityArg("", "testSpecificity", "test specificity. (default=1.0)", false, 1.0, "float");
    //test frequency
    //TCLAP::ValueArg<float> iProbaToPurchaseSArg("v", "probaToPurchaseS", "probability to purchase a susceptible animal for AAA herds (used with herd history (see -q), default=1.0)", false, 1.0, "float");
    //cmd.add(iProbaToPurchaseSArg);
   // TCLAP::SwitchArg iUsePurchaseProba("f", "usePurchaseProba", "a fixed probability to purchase a susceptible animal will be used (see -v), instead of the prevalence in the source herd (used with herd history)", cmd, false);
    TCLAP::ValueArg<float> iStartGrazingArg("", "startGrazing", "Grazing start week (from 0 to 51, default=14, beginning of April)", false, 14, "int");
    TCLAP::ValueArg<float> iEndGrazingArg("", "endGrazing", "Grazing end week (from 0 to 51, default=46, mid November)", false, 46, "int");
    TCLAP::ValueArg<float> iAgeAtWeaningArg("", "ageAtWeaning", "From this age, in terms of number of weeks, the animal is weaned (default=10)", false, 10, "int");
    TCLAP::ValueArg<float> iAgeAtGrazingArg("", "ageAtGrazing", "From this age, in terms of number of weeks, the animal can go outside during grazing period (default=26)", false, 26, "int");
    TCLAP::ValueArg<float> iAgeYoungHeiferArg("", "ageYoungHeifer", "From this age, in terms of number of weeks, the animal is considered to be a young heifer (default=52, one year old)", false, 52, "int");
    TCLAP::ValueArg<float> iAgeHeiferArg("", "ageHeifer", "From this age, in terms of number of weeks, the animal is considered to be a heifer, starts reproduction (default=91)", false, 91, "int");
    TCLAP::ValueArg<float> iAgeAtFirstCalvingArg("", "ageAtFirstCalving", "From this age, in terms of number of weeks, the animal is considered to be a cow, calves for the first time (default=130)", false, 130, "int");
    cmd.add(iAgeAtWeaningArg);
    cmd.add(iAgeAtGrazingArg);
    cmd.add(iAgeYoungHeiferArg);
    cmd.add(iAgeHeiferArg);
    cmd.add(iAgeAtFirstCalvingArg);
    cmd.add(iStartGrazingArg);
    cmd.add(iEndGrazingArg);
    cmd.add(iTestSensitivityItIlArg);
    cmd.add(iTestSensitivityImArg);
    cmd.add(iTestSensitivityIhArg);
    cmd.add(iTestSpecificityArg);
    cmd.add(iInitInFilePathArg);
    cmd.add(iOutDirectoryPathArg);
    cmd.add(iCullingRateIhArg);
    cmd.add(iCalfExposureArg);
    TCLAP::SwitchArg iNoInfection("n", "noInfection", "all herds will be initialized without infected animals, so no PTB spread", cmd, false);
    cmd.add(iRunsNbArg);
    cmd.parse(argc, argv);

	ParametersT<false>& iParams = ParametersT<false>::getInstance();
    iParams.runsNb = iRunsNbArg.getValue();
    iParams.dontInfect = iNoInfection.getValue();
    iParams.defaultCalfExpo = iCalfExposureArg.getValue();
    if (iCullingRateIhArg.getValue() > 0.0384615){  //6 months => 1/(52/2) = 0.0384615
        iParams.areDetectedIhCulledEarlier = true;
        iParams.cullingProbaOfDetectedIh = 1 - std::exp(-(iCullingRateIhArg.getValue()));   //1 month => 1/(52/12) = 0.230769
    }
    iParams.resultsPath = iOutDirectoryPathArg.getValue();
    iParams.isRewiringAllowed = false;
//    iParams.usePurchaseProba = iUsePurchaseProba.getValue();
//    iParams.probaToPurchaseS = iProbaToPurchaseSArg.getValue();
    int seed = 0;
    if (seed == 0){
        iParams.gen.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    } else {
        iParams.gen.seed(seed);
    }

    iParams._testSensitivityIt = iTestSensitivityItIlArg.getValue();
    iParams._testSensitivityIl = iTestSensitivityItIlArg.getValue();
    iParams._testSensitivityIm = iTestSensitivityImArg.getValue();
    iParams._testSensitivityIh = iTestSensitivityIhArg.getValue();
    iParams._startGrazing = iStartGrazingArg.getValue();
    iParams._endGrazing = iEndGrazingArg.getValue();
    iParams._ageWeaning = iAgeAtWeaningArg.getValue();
    iParams._ageGrazing = iAgeAtGrazingArg.getValue();
    iParams._ageYoungHeifer = iAgeYoungHeiferArg.getValue();
    iParams._ageHeifer = iAgeHeiferArg.getValue();
    iParams._ageFirstCalving = iAgeAtFirstCalvingArg.getValue();

    if (iParams.dontInfect){
        iParams.propOfHerdsToInfect = 0;
    } else { //then option '-p' or '-i' or '-d' will be used
        iParams.vHerdPropPerStatus.clear();
    }
    if (iInitInFilePathArg.getValue() != ""){
        iParams.doLoadingOfInitialInfection = true;
        iParams.initInFile = iInitInFilePathArg.getValue();
    }
    iParams.updateAfterSetting();

    ModelT<false> iModel = ModelT<false>();
    iModel.loadDemography();
    iModel.loadMovements();
    if (iParams.doLoadingOfInitialInfection){
        iModel.loadInitialInfection();
    }
    iModel.loadInitPrevMatrix();
    iModel.run();

    MetapopT<false>::kill();
    ParametersT<false>::kill();
  */

  return 1;

}

RCPP_MODULE(PTBinteRface_module){

	using namespace Rcpp;

  function("runPTBmodel", &runPTBmodel);

}
