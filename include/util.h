/*
 * Copyright (c) <2023> NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cassert>

// mappings for Mathematica CForm[] output:
#define Sqrt sqrt
#define Power pow
#define Log log
#define Cosh cosh
#define Sinh sinh

const double Pi(M_PI);

#define INV_M_PI 0.31830988618379067153f        /* 1/pi */
#define SQRT_M_PI 1.77245385090551602729f       /* sqrt(pi) */
#define SQRT_2 1.41421356237309504880f          /* sqrt(2) */
#define INV_SQRT_M_PI 0.56418958354775628694f   /* 1/sqrt(pi) */
#define INV_2_SQRT_M_PI 0.28209479177387814347f /* 0.5/sqrt(pi) */
#define INV_SQRT_2_M_PI 0.3989422804014326779f  /* 1/sqrt(2*pi) */
#define INV_SQRT_2 0.7071067811865475244f       /* 1/sqrt(2) */

//////////////////////////////////////////////////////////////////////////////////
// utilities
//////////////////////////////////////////////////////////////////////////////////

template <typename T>
T StringToNumber(const std::string &Text)
{
    std::stringstream ss(Text);
    T result;
    return ss >> result ? result : 0;
}

double sqr(double x)
{
    return x * x;
}

// clamp a value into a specified range
double Clamp(const double x, const double min, const double max)
{
    return std::max(std::min(max, x), min);
}

// map a continuous range [min,max] into dx sized intervals and return the integer index
// of an element x
size_t discreteMap(const double min, const double max, const double dx, const double x)
{
    const double clampx = Clamp(x, min, max);
    return size_t(floor((clampx - min) / dx));
}

//////////////////////////////////////////////////////////////////////////////////
// Gauss Quadrature points over [0,1]
//////////////////////////////////////////////////////////////////////////////////

const double Gauss100xs[100] = {0.0001431366132793599, 0.0007540246802020256, 0.001852432633437484,
                                0.003437531481278233, 0.005507802378504123, 0.008061229646971535, 0.01109532075654085,
                                0.014607112118146803, 0.01859317287209228, 0.02304960853725413, 0.027972064931871987,
                                0.03335573247846024, 0.03919535092733306, 0.04548521450873522, 0.05221917751463656,
                                0.05939066030749074, 0.06699265575141766, 0.07501773606020434, 0.08345806005579959,
                                0.09230538083041195, 0.10155105380484275, 0.11118604517525221, 0.12120094074014642,
                                0.13158595509898963, 0.14233094121347178, 0.15342540032209895, 0.16485849219842952,
                                0.1766190457429353, 0.18869556989814606, 0.20107626487641062, 0.21374903368930942,
                                0.22670149396745298, 0.2399209900591185, 0.2533946053959045, 0.267109175113321,
                                0.2810512989139843, 0.2952073541608492, 0.30956350918768505, 0.3241057368137892,
                                0.3388198280497354, 0.353691405980764, 0.36870593981424826, 0.38384875907751304,
                                0.39910506795213196, 0.4144599597306984, 0.42989843138194306, 0.4454053982099695,
                                0.4609657085932817, 0.4765641587892042, 0.4921855077892284, 0.5078144922107716,
                                0.5234358412107958, 0.5390342914067183, 0.5545946017900305, 0.5701015686180569,
                                0.5855400402693016, 0.600894932047868, 0.616151240922487, 0.6312940601857517,
                                0.646308594019236, 0.6611801719502646, 0.6758942631862108, 0.690436490812315,
                                0.7047926458391508, 0.7189487010860157, 0.732890824886679, 0.7466053946040955,
                                0.7600790099408815, 0.773298506032547, 0.7862509663106906, 0.7989237351235894,
                                0.8113044301018539, 0.8233809542570647, 0.8351415078015705, 0.846574599677901,
                                0.8576690587865282, 0.8684140449010104, 0.8787990592598536, 0.8888139548247478,
                                0.8984489461951572, 0.907694619169588, 0.9165419399442004, 0.9249822639397957,
                                0.9330073442485823, 0.9406093396925093, 0.9477808224853634, 0.9545147854912648,
                                0.9608046490726669, 0.9666442675215398, 0.972027935068128, 0.9769503914627459,
                                0.9814068271279077, 0.9853928878818532, 0.9889046792434592, 0.9919387703530285,
                                0.9944921976214959, 0.9965624685187218, 0.9981475673665625, 0.999245975319798,
                                0.9998568633867206};
const double Gauss100ws[100] = {0.00036731724524932316, 0.0008546963267554215, 0.0013419626857791437,
                                0.0018279806006622767, 0.002312225031711083, 0.002794214001933608, 0.0032734742254225493,
                                0.0037495366277319757, 0.004221935734834934, 0.004690209826847327, 0.005153901287434295,
                                0.005612557011593201, 0.006065728831490082, 0.006512973946486294, 0.006953855351859815,
                                0.007387942263720422, 0.007814810538772953, 0.008234043088072605, 0.008645230284161875,
                                0.009047970361064483, 0.009441869806687491, 0.009826543747217534, 0.010201616323104836,
                                0.010566721056263852, 0.010921501208123853, 0.011265610128168027, 0.011598711592627197,
                                0.01192048013298404, 0.01223060135397848, 0.012528772240789849, 0.012814701455104213,
                                0.013088109619773088, 0.013348729591785617, 0.01359630672328859, 0.01383059911039636,
                                0.01405137782955077, 0.014258427161197655, 0.014451544800562783, 0.014630542055319343,
                                0.01479524402995644, 0.014945489796666525, 0.015081132552584713, 0.015202039763227548,
                                0.015308093291990342, 0.015399189515576422, 0.015475239425245637, 0.015536168713783409,
                                0.015581917848105089, 0.015612442127424813, 0.01562771172693182, 0.01562771172693182,
                                0.015612442127424813, 0.015581917848105089, 0.015536168713783409, 0.015475239425245637,
                                0.015399189515576422, 0.015308093291990342, 0.015202039763227548, 0.015081132552584713,
                                0.014945489796666525, 0.01479524402995644, 0.014630542055319343, 0.014451544800562783,
                                0.014258427161197655, 0.01405137782955077, 0.01383059911039636, 0.01359630672328859,
                                0.013348729591785617, 0.013088109619773088, 0.012814701455104213, 0.012528772240789849,
                                0.01223060135397848, 0.01192048013298404, 0.011598711592627197, 0.011265610128168027,
                                0.010921501208123853, 0.010566721056263852, 0.010201616323104836, 0.009826543747217534,
                                0.009441869806687491, 0.009047970361064483, 0.008645230284161875, 0.008234043088072605,
                                0.007814810538772953, 0.007387942263720422, 0.006953855351859815, 0.006512973946486294,
                                0.006065728831490082, 0.005612557011593201, 0.005153901287434295, 0.004690209826847327,
                                0.004221935734834934, 0.0037495366277319757, 0.0032734742254225493, 0.002794214001933608,
                                0.002312225031711083, 0.0018279806006622767, 0.0013419626857791437,
                                0.0008546963267554215, 0.00036731724524932316};

//////////////////////////////////////////////////////////////////////////////////
// Lobatto Quadrature points over [0,1] (which include the interval endpoints)
//////////////////////////////////////////////////////////////////////////////////

const double Lobatto100xs[100] = {0, 0.000370711017377538597, 0.001242375481435694907, 0.002611346404772358912,
                                  0.004476153143535852271, 0.0068349180915945049708, 0.0096852846389917529964,
                                  0.0130244094961698053349, 0.016848963279590500672, 0.0211551331595129402674,
                                  0.0259386264188233776701, 0.0311946746322406739235, 0.036918038373885555008,
                                  0.043103012417379119138, 0.04974343141092531795, 0.056832676016351728468,
                                  0.0643636795034798662743, 0.0723289347920048358038, 0.080720501933212326136,
                                  0.0895300160237179806443, 0.0987486955431374767109, 0.1083673511072566450853,
                                  0.1183763946279038126606, 0.1287658488703484705308, 0.139525357398670443759,
                                  0.1506441948991670226592, 0.162111277871494969447, 0.173915175676881780936,
                                  0.18604412193238728922, 0.198486026239853485001, 0.2112284862378480089263,
                                  0.224258799964585602476, 0.2375639785195023862961, 0.2511307590108605290052,
                                  0.2649456177764760327272, 0.2789947838643903116662, 0.2932642527600472719697,
                                  0.3077398003462919891057, 0.3224069970822750790546, 0.3372512223871287108446,
                                  0.3522576792140761333, 0.3674114088004467956906, 0.3826973055788938222698,
                                  0.398100132234949931316, 0.413604534895912031852, 0.42919505843591383225,
                                  0.444856161881929985787, 0.460572233905354694641, 0.47632760838371239727,
                                  0.4921065800169882588148, 0.5078934199830117411852, 0.5236723916162876027252,
                                  0.5394277660946453053591, 0.5551438381180700142132, 0.570804941564086167745,
                                  0.5863954651040879681482, 0.6018998677650500686836, 0.6173026944211061777302,
                                  0.6325885911995532043093, 0.647742320785923866699, 0.662748777612871289155,
                                  0.6775930029177249209453, 0.692260199653708010894, 0.7067357472399527280302,
                                  0.7210052161356096883338, 0.7350543822235239672728, 0.7488692409891394709948,
                                  0.762436021480497613704, 0.7757412000354143975236, 0.7887715137621519910737,
                                  0.8015139737601465149983, 0.81395587806761271078, 0.8260848243231182190637,
                                  0.8378887221285050305528, 0.8493558051008329773408, 0.8604746426013295562404,
                                  0.8712341511296515294692, 0.8816236053720961873394, 0.8916326488927433549146,
                                  0.9012513044568625232891, 0.9104699839762820193557, 0.919279498066787673864,
                                  0.9276710652079951641961, 0.9356363204965201337256, 0.9431673239836482715319,
                                  0.9502565685890746820448, 0.9568969875826208808618, 0.9630819616261144449912,
                                  0.9688053253677593260764, 0.9740613735811766223299, 0.9788448668404870597326,
                                  0.983151036720409499328, 0.9869755905038301946651, 0.9903147153610082470036,
                                  0.9931650819084054950291, 0.9955238468564641477293, 0.9973886535952276410876,
                                  0.9987576245185643050931, 0.9996292889826224614031, 1};
const double Lobatto100ws[100] = {0.0002020202020202020202, 0.0012450766591352942893, 0.00224107975508296304,
                                  0.0032343259236349601274, 0.00422427633165450744, 0.005209998070585079867,
                                  0.006190520319146799369, 0.007164869223011786039, 0.008132074847738999054,
                                  0.009091173626580326381, 0.010041209778500831941, 0.010981236426462550781,
                                  0.01191031660877146948, 0.012827524243262733436, 0.0137319450650154626976,
                                  0.014622677545198368306, 0.015498833793784865807, 0.01635954044691377603,
                                  0.01720393953882560454, 0.018031189357921348572, 0.0188404652863124740298,
                                  0.019630960622148179418, 0.020401887383970712731, 0.02115247709633855397,
                                  0.02188198155595957279, 0.022589673577586142378, 0.02327484771893864316,
                                  0.023936820983941188731, 0.02457493350357283128, 0.0251885491936584163,
                                  0.02577705638894533387, 0.026339868452835451554, 0.026876424362165378012,
                                  0.027386189266452805112, 0.0278686550210519396, 0.028323340693686911759,
                                  0.028749793043858492721, 0.0291475869746464259332, 0.029516325956457147251,
                                  0.029855642422294598437, 0.030165198134160199712, 0.03044468452021680701,
                                  0.030693822982380608454, 0.03091236517403438183, 0.031100093247585310487,
                                  0.031256820071620608072, 0.0313823894174445036, 0.031476676114810655384,
                                  0.031539586176694766221, 0.031571056892983030979, 0.031571056892983030979,
                                  0.03153958617669476622, 0.03147667611481065538, 0.031382389417444503601,
                                  0.031256820071620608072, 0.031100093247585310487, 0.03091236517403438183,
                                  0.030693822982380608454, 0.03044468452021680701, 0.030165198134160199712,
                                  0.029855642422294598437, 0.029516325956457147251, 0.029147586974646425933,
                                  0.02874979304385849272, 0.02832334069368691176, 0.0278686550210519396,
                                  0.02738618926645280511, 0.02687642436216537801, 0.02633986845283545155,
                                  0.02577705638894533387, 0.0251885491936584163, 0.02457493350357283128,
                                  0.023936820983941188731, 0.023274847718938643155, 0.02258967357758614238,
                                  0.02188198155595957279, 0.021152477096338553971, 0.02040188738397071273,
                                  0.019630960622148179418, 0.01884046528631247403, 0.01803118935792134857,
                                  0.017203939538825604536, 0.016359540446913776, 0.01549883379378486581,
                                  0.01462267754519836831, 0.0137319450650154627, 0.012827524243262733436,
                                  0.01191031660877146948, 0.010981236426462550781, 0.010041209778500831941,
                                  0.009091173626580326381, 0.00813207484773899905, 0.007164869223011786039,
                                  0.006190520319146799369, 0.00520999807058507987, 0.0042242763316545074348,
                                  0.003234325923634960127, 0.00224107975508296304, 0.001245076659135294289,
                                  0.0002020202020202020202};