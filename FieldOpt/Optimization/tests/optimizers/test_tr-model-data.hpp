/*********************************************************************
 Copyright (C) 2018 Mathias Bellout <mathias.bellout@ntnu.no>

 This file is part of the FieldOpt project.

 FieldOpt is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published
 by the Free Software Foundation, either version 3 of the License,
 or (at your option) any later version.

 FieldOpt is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with FieldOpt. If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

#ifndef FIELDOPT_TEST_TR_DFO_DATA_H
#define FIELDOPT_TEST_TR_DFO_DATA_H

#include <Eigen/Core>

namespace TestResources {
    class TrustRegionModelData {

    public:

        struct prob {
            Eigen::MatrixXd xm; // tr_model.points_abs
            Eigen::MatrixXd fm; // tr_model.fvalues

            Eigen::MatrixXd sm; // tr_model.points_shifted

            Eigen::MatrixXd cm; // tr_model.tr_center
            Eigen::MatrixXd rm; // tr_model.radius

            Eigen::MatrixXd pm; // tr_model.pivot_polynomials
            Eigen::MatrixXd vm; // tr_model.pivot_values

        };

        prob prob1;

        TrustRegionModelData() {

            // ========== prob1 ==========
            // seed.Type: twister
            // seed.Seed:      0
            // seed.State:      5489.0 1301868182.0 2938499221.0 2950281878.0 1875628136.0  751856242.0  944701696.0 2243192071.0  694061057.0  219885934.0 2066767472.0 3182869408.0  485472502.0 2336857883.0 1071588843.0 3418470598.0  951210697.0 3693558366.0 2923482051.0 1793174584.0 2982310801.0 1586906132.0 1951078751.0 1808158765.0 1733897588.0  431328322.0 4202539044.0  530658942.0 1714810322.0 3025256284.0 3342585396.0 1937033938.0 2640572511.0 1654299090.0 3692403553.0 4233871309.0 3497650794.0  862629010.0 2943236032.0 2426458545.0 1603307207.0 1133453895.0 3099196360.0 2208657629.0 2747653927.0  931059398.0  761573964.0 3157853227.0  785880413.0  730313442.0  124945756.0 2937117055.0 3295982469.0 1724353043.0 3021675344.0 3884886417.0 4010150098.0 4056961966.0  699635835.0 2681338818.0 1339167484.0  720757518.0 2800161476.0 2376097373.0 1532957371.0 3902664099.0 1238982754.0 3725394514.0 3449176889.0 3570962471.0 4287636090.0 4087307012.0 3603343627.0  202242161.0 2995682783.0 1620962684.0 3704723357.0  371613603.0 2814834333.0 2111005706.0  624778151.0 2094172212.0 4284947003.0 1211977835.0  991917094.0 1570449747.0 2962370480.0 1259410321.0  170182696.0  146300961.0 2836829791.0  619452428.0 2723670296.0 1881399711.0 1161269684.0 1675188680.0 4132175277.0  780088327.0 3409462821.0 1036518241.0 1834958505.0 3048448173.0  161811569.0  618488316.0   44795092.0 3918322701.0 1924681712.0 3239478144.0  383254043.0 4042306580.0 2146983041.0 3992780527.0 3518029708.0 3545545436.0 3901231469.0 1896136409.0 2028528556.0 2339662006.0  501326714.0 2060962201.0 2502746480.0  561575027.0  581893337.0 3393774360.0 1778912547.0 3626131687.0 2175155826.0  319853231.0  986875531.0  819755096.0 2915734330.0 2688355739.0 3482074849.0    2736559.0 2296975761.0 1029741190.0 2876812646.0  690154749.0  579200347.0 4027461746.0 1285330465.0 2701024045.0 4117700889.0  759495121.0 3332270341.0 2313004527.0 2277067795.0 4131855432.0 2722057515.0 1264804546.0 3848622725.0 2211267957.0 4100593547.0  959123777.0 2130745407.0 3194437393.0  486673947.0 1377371204.0   17472727.0  352317554.0 3955548058.0  159652094.0 1232063192.0 3835177280.0   49423123.0 3083993636.0     733092.0 2120519771.0 2573409834.0 1112952433.0 3239502554.0  761045320.0 1087580692.0 2540165110.0  641058802.0 1792435497.0 2261799288.0 1579184083.0  627146892.0 2165744623.0 2200142389.0 2167590760.0 2381418376.0 1793358889.0 3081659520.0 1663384067.0 2009658756.0 2689600308.0  739136266.0 2304581039.0 3529067263.0  591360555.0  525209271.0 3131882996.0  294230224.0 2076220115.0 3113580446.0 1245621585.0 1386885462.0 3203270426.0  123512128.0   12350217.0  354956375.0 4282398238.0 3356876605.0 3888857667.0  157639694.0 2616064085.0 1563068963.0 2762125883.0 4045394511.0 4180452559.0 3294769488.0 1684529556.0 1002945951.0 3181438866.0   22506664.0  691783457.0 2685221343.0  171579916.0 3878728600.0 2475806724.0 2030324028.0 3331164912.0 1708711359.0 1970023127.0 2859691344.0 2588476477.0 2748146879.0  136111222.0 2967685492.0  909517429.0 2835297809.0 3206906216.0 3186870716.0  341264097.0 2542035121.0 3353277068.0  548223577.0 3170936588.0 1678403446.0  297435620.0 2337555430.0  466603495.0 1132321815.0 1208589219.0  696392160.0  894244439.0 2562678859.0  470224582.0 3306867480.0  201364898.0 2075966438.0 1767227936.0 2929737987.0 3674877796.0 2654196643.0 3692734598.0 3528895099.0 2796780123.0 3048728353.0  842329300.0  191554730.0 2922459673.0 3489020079.0 3979110629.0 1022523848.0 2202932467.0 3583655201.0 3565113719.0  587085778.0 4176046313.0 3013713762.0  950944241.0  396426791.0 3784844662.0 3477431613.0 3594592395.0 2782043838.0 3392093507.0 3106564952.0 2829419931.0 1358665591.0 2206918825.0 3170783123.0   31522386.0 2988194168.0 1782249537.0 1105080928.0  843500134.0 1225290080.0 1521001832.0 3605886097.0 2802786495.0 2728923319.0 3996284304.0  903417639.0 1171249804.0 1020374987.0 2824535874.0  423621996.0 1988534473.0 2493544470.0 1008604435.0 1756003503.0 1488867287.0 1386808992.0  732088248.0 1780630732.0 2482101014.0  976561178.0 1543448953.0 2602866064.0 2021139923.0 1952599828.0 2360242564.0 2117959962.0 2753061860.0 2388623612.0 4138193781.0 2962920654.0 2284970429.0  766920861.0 3457264692.0 2879611383.0  815055854.0 2332929068.0 1254853997.0 3740375268.0 3799380844.0 4091048725.0 2006331129.0 1982546212.0  686850534.0 1907447564.0 2682801776.0 2780821066.0  998290361.0 1342433871.0 4195430425.0  607905174.0 3902331779.0 2454067926.0 1708133115.0 1170874362.0 2008609376.0 3260320415.0 2211196135.0  433538229.0 2728786374.0 2189520818.0  262554063.0 1182318347.0 3710237267.0 1221022450.0  715966018.0 2417068910.0 2591870721.0 2870691989.0 3418190842.0 4238214053.0 1540704231.0 1575580968.0 2095917976.0 4078310857.0 2313532447.0 2110690783.0 4056346629.0 4061784526.0 1123218514.0  551538993.0  597148360.0 4120175196.0 3581618160.0 3181170517.0  422862282.0 3227524138.0 1713114790.0  662317149.0 1230418732.0  928171837.0 1324564878.0 1928816105.0 1786535431.0 2878099422.0 3290185549.0  539474248.0 1657512683.0  552370646.0 1671741683.0 3655312128.0 1552739510.0 2605208763.0 1441755014.0  181878989.0 3124053868.0 1447103986.0 3183906156.0 1728556020.0 3502241336.0 3055466967.0 1013272474.0  818402132.0 1715099063.0 2900113506.0  397254517.0 4194863039.0 1009068739.0  232864647.0 2540223708.0 2608288560.0 2415367765.0  478404847.0 3455100648.0 3182600021.0 2115988978.0  434269567.0 4117179324.0 3461774077.0  887256537.0 3545801025.0  286388911.0 3451742129.0 1981164769.0  786667016.0 3310123729.0 3097811076.0 2224235657.0 2959658883.0 3370969234.0 2514770915.0 3345656436.0 2677010851.0 2206236470.0  271648054.0 2342188545.0 4292848611.0 3646533909.0 3754009956.0 3803931226.0 4160647125.0 1477814055.0 4043852216.0 1876372354.0 3133294443.0 3871104810.0 3177020907.0 2074304428.0 3479393793.0  759562891.0  164128153.0 1839069216.0 2114162633.0 3989947309.0 3611054956.0 1333547922.0  835429831.0  494987340.0  171987910.0 1252001001.0  370809172.0 3508925425.0 2535703112.0 1276855041.0 1922855120.0  835673414.0 3030664304.0  613287117.0  171219893.0 3423096126.0 3376881639.0 2287770315.0 1658692645.0 1262815245.0 3957234326.0 1168096164.0 2968737525.0 2655813712.0 2132313144.0 3976047964.0  326516571.0  353088456.0 3679188938.0 3205649712.0 2654036126.0 1249024881.0  880166166.0  691800469.0 2229503665.0 1673458056.0 4032208375.0 1851778863.0 2563757330.0  376742205.0 1794655231.0  340247333.0 1505873033.0  396524441.0  879666767.0 3335579166.0 3260764261.0 3335999539.0  506221798.0 4214658741.0  975887814.0 2080536343.0 3360539560.0  571586418.0  138896374.0 4234352651.0 2737620262.0 3928362291.0 1516365296.0   38056726.0 3599462320.0 3585007266.0 3850961033.0  471667319.0 1536883193.0 2310166751.0 1861637689.0 2530999841.0 4139843801.0 2710569485.0  827578615.0 2012334720.0 2907369459.0 3029312804.0 2820112398.0 1965028045.0   35518606.0 2478379033.0  643747771.0 1924139484.0 4123405127.0 3811735531.0 3429660832.0 3285177704.0 1948416081.0 1311525291.0 1183517742.0 1739192232.0 3979815115.0 2567840007.0 4116821529.0  213304419.0 4125718577.0 1473064925.0 2442436592.0 1893310111.0 4195361916.0 3747569474.0  828465101.0 2991227658.0  750582866.0 1205170309.0 1409813056.0  678418130.0 1171531016.0 3821236156.0  354504587.0 4202874632.0 3882511497.0 1893248677.0 1903078632.0   26340130.0 2069166240.0 3657122492.0 3725758099.0  831344905.0  811453383.0 3447711422.0 2434543565.0 4166886888.0 3358210805.0 4142984013.0 2988152326.0 3527824853.0  982082992.0 2809155763.0  190157081.0 3340214818.0 2365432395.0 2548636180.0 2894533366.0 3474657421.0 2372634704.0 2845748389.0   43024175.0 2774226648.0 1987702864.0 3186502468.0  453610222.0 4204736567.0 1392892630.0 2471323686.0 2470534280.0 3541393095.0 4269885866.0 3909911300.0  759132955.0 1482612480.0  667715263.0 1795580598.0 2337923983.0 3390586366.0  581426223.0 1515718634.0  476374295.0  705213300.0  363062054.0 2084697697.0 2407503428.0 2292957699.0 2426213835.0 2199989172.0 1987356470.0 4026755612.0 2147252133.0  270400031.0 1367820199.0 2369854699.0 2844269403.0   79981964.0        624.0

            // --- Initial points ---
            // x1: -1.2000000000002.000000000000
            // f1: 4.840000000000
            // x2: -0.8852763136072.405791937076
            // f2: 3.554266778647

            prob1.xm.resize(2,2);
            prob1.fm.resize(1,2);

            prob1.xm.col(0) << -1.200000000000, 2.000000000000;
            prob1.fm.col(0) << 4.840000000000;

            prob1.xm.col(1) << -0.885276313607, 2.405791937076;
            prob1.fm.col(1) << 3.554266778647;


            prob1.cm.resize(1,1); // model.tr_center
            prob1.rm.resize(1,1); // model.radius
            prob1.pm.resize(6,1); // model.pivot_polynomials.coefficients
            prob1.vm.resize(6,1); // model.pivot_values

            // Trust region center:
            prob1.cm.col(0) << 1.000000000000;
            // Trust region radius:
            prob1.rm.col(0) << 1.000000000000;
            // Pivot polynomials:
            prob1.pm.col(0) << 1.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000;
            // Pivot values:
            prob1.vm.col(0) << 1.000000000000, 0.314723686393, 0.000000000000, 0.000000000000, 0.000000000000, 0.000000000000;

        }

    };

}

#endif //FIELDOPT_TEST_TR_DFO_DATA_H
