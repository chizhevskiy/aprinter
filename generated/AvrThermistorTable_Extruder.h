/*
 * Copyright (c) 2013 Ambroz Bizjak
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* 
 * This file was automatically generated using gen_avr_thermistor_table.py.
 * The following parameters were used for generation:
 * 
 * Name = Extruder
 * ResistorR = 4700.0
 * ThermistorR0 = 100000.0
 * ThermistorBeta = 3960.0
 * StartTemp = 20.0
 * EndTemp = 300.0
 * 
 * The file can be regenerated with the following command:
 * 
 * python gen_avr_thermistor_table.py "Extruder" 4700.0 100000.0 3960.0 20.0 300.0
 */

#ifndef AMBROLIB_AVR_THERMISTOR_Extruder_H
#define AMBROLIB_AVR_THERMISTOR_Extruder_H

#include <stdint.h>
#include <math.h>
#include <avr/pgmspace.h>

class AvrThermistorTable_Extruder {
public:
    static double call (uint16_t adc_value)
    {
        uint16_t entry =
            (adc_value < 36) ? 0 :
            (adc_value > 988 - 1) ? (952 - 1) :
            (adc_value - 36);
        return ldexp(pgm_read_word(&table[entry]), -7);
    }
    
private:
    static uint16_t const table[952] PROGMEM;
};

uint16_t const AvrThermistorTable_Extruder::table[952] PROGMEM = {
UINT16_C(38368), UINT16_C(38068), UINT16_C(37778), UINT16_C(37497), UINT16_C(37225), 
UINT16_C(36962), UINT16_C(36707), UINT16_C(36459), UINT16_C(36218), UINT16_C(35984), UINT16_C(35756), UINT16_C(35535), UINT16_C(35319), 
UINT16_C(35109), UINT16_C(34903), UINT16_C(34703), UINT16_C(34508), UINT16_C(34318), UINT16_C(34131), UINT16_C(33949), UINT16_C(33771), 
UINT16_C(33597), UINT16_C(33427), UINT16_C(33260), UINT16_C(33096), UINT16_C(32936), UINT16_C(32779), UINT16_C(32625), UINT16_C(32474), 
UINT16_C(32326), UINT16_C(32181), UINT16_C(32038), UINT16_C(31898), UINT16_C(31760), UINT16_C(31625), UINT16_C(31492), UINT16_C(31361), 
UINT16_C(31232), UINT16_C(31106), UINT16_C(30982), UINT16_C(30859), UINT16_C(30739), UINT16_C(30620), UINT16_C(30503), UINT16_C(30388), 
UINT16_C(30275), UINT16_C(30163), UINT16_C(30053), UINT16_C(29944), UINT16_C(29837), UINT16_C(29731), UINT16_C(29627), UINT16_C(29525), 
UINT16_C(29423), UINT16_C(29323), UINT16_C(29225), UINT16_C(29127), UINT16_C(29031), UINT16_C(28936), UINT16_C(28842), UINT16_C(28750), 
UINT16_C(28658), UINT16_C(28568), UINT16_C(28479), UINT16_C(28390), UINT16_C(28303), UINT16_C(28217), UINT16_C(28132), UINT16_C(28047), 
UINT16_C(27964), UINT16_C(27881), UINT16_C(27800), UINT16_C(27719), UINT16_C(27639), UINT16_C(27560), UINT16_C(27482), UINT16_C(27405), 
UINT16_C(27328), UINT16_C(27253), UINT16_C(27178), UINT16_C(27103), UINT16_C(27030), UINT16_C(26957), UINT16_C(26885), UINT16_C(26814), 
UINT16_C(26743), UINT16_C(26673), UINT16_C(26603), UINT16_C(26535), UINT16_C(26466), UINT16_C(26399), UINT16_C(26332), UINT16_C(26266), 
UINT16_C(26200), UINT16_C(26135), UINT16_C(26070), UINT16_C(26006), UINT16_C(25943), UINT16_C(25880), UINT16_C(25817), UINT16_C(25755), 
UINT16_C(25694), UINT16_C(25633), UINT16_C(25572), UINT16_C(25512), UINT16_C(25453), UINT16_C(25394), UINT16_C(25335), UINT16_C(25277), 
UINT16_C(25220), UINT16_C(25163), UINT16_C(25106), UINT16_C(25049), UINT16_C(24994), UINT16_C(24938), UINT16_C(24883), UINT16_C(24828), 
UINT16_C(24774), UINT16_C(24720), UINT16_C(24667), UINT16_C(24613), UINT16_C(24561), UINT16_C(24508), UINT16_C(24456), UINT16_C(24405), 
UINT16_C(24353), UINT16_C(24302), UINT16_C(24252), UINT16_C(24201), UINT16_C(24151), UINT16_C(24102), UINT16_C(24052), UINT16_C(24003), 
UINT16_C(23955), UINT16_C(23906), UINT16_C(23858), UINT16_C(23810), UINT16_C(23763), UINT16_C(23716), UINT16_C(23669), UINT16_C(23622), 
UINT16_C(23576), UINT16_C(23530), UINT16_C(23484), UINT16_C(23439), UINT16_C(23393), UINT16_C(23348), UINT16_C(23304), UINT16_C(23259), 
UINT16_C(23215), UINT16_C(23171), UINT16_C(23128), UINT16_C(23084), UINT16_C(23041), UINT16_C(22998), UINT16_C(22955), UINT16_C(22913), 
UINT16_C(22871), UINT16_C(22829), UINT16_C(22787), UINT16_C(22745), UINT16_C(22704), UINT16_C(22663), UINT16_C(22622), UINT16_C(22581), 
UINT16_C(22541), UINT16_C(22500), UINT16_C(22460), UINT16_C(22420), UINT16_C(22381), UINT16_C(22341), UINT16_C(22302), UINT16_C(22263), 
UINT16_C(22224), UINT16_C(22185), UINT16_C(22147), UINT16_C(22108), UINT16_C(22070), UINT16_C(22032), UINT16_C(21995), UINT16_C(21957), 
UINT16_C(21920), UINT16_C(21882), UINT16_C(21845), UINT16_C(21808), UINT16_C(21772), UINT16_C(21735), UINT16_C(21699), UINT16_C(21663), 
UINT16_C(21626), UINT16_C(21591), UINT16_C(21555), UINT16_C(21519), UINT16_C(21484), UINT16_C(21448), UINT16_C(21413), UINT16_C(21378), 
UINT16_C(21344), UINT16_C(21309), UINT16_C(21274), UINT16_C(21240), UINT16_C(21206), UINT16_C(21172), UINT16_C(21138), UINT16_C(21104), 
UINT16_C(21070), UINT16_C(21037), UINT16_C(21003), UINT16_C(20970), UINT16_C(20937), UINT16_C(20904), UINT16_C(20871), UINT16_C(20838), 
UINT16_C(20806), UINT16_C(20773), UINT16_C(20741), UINT16_C(20708), UINT16_C(20676), UINT16_C(20644), UINT16_C(20612), UINT16_C(20581), 
UINT16_C(20549), UINT16_C(20517), UINT16_C(20486), UINT16_C(20455), UINT16_C(20424), UINT16_C(20393), UINT16_C(20362), UINT16_C(20331), 
UINT16_C(20300), UINT16_C(20269), UINT16_C(20239), UINT16_C(20208), UINT16_C(20178), UINT16_C(20148), UINT16_C(20118), UINT16_C(20088), 
UINT16_C(20058), UINT16_C(20028), UINT16_C(19999), UINT16_C(19969), UINT16_C(19939), UINT16_C(19910), UINT16_C(19881), UINT16_C(19852), 
UINT16_C(19823), UINT16_C(19794), UINT16_C(19765), UINT16_C(19736), UINT16_C(19707), UINT16_C(19679), UINT16_C(19650), UINT16_C(19622), 
UINT16_C(19593), UINT16_C(19565), UINT16_C(19537), UINT16_C(19509), UINT16_C(19481), UINT16_C(19453), UINT16_C(19425), UINT16_C(19397), 
UINT16_C(19369), UINT16_C(19342), UINT16_C(19314), UINT16_C(19287), UINT16_C(19260), UINT16_C(19232), UINT16_C(19205), UINT16_C(19178), 
UINT16_C(19151), UINT16_C(19124), UINT16_C(19097), UINT16_C(19071), UINT16_C(19044), UINT16_C(19017), UINT16_C(18991), UINT16_C(18964), 
UINT16_C(18938), UINT16_C(18911), UINT16_C(18885), UINT16_C(18859), UINT16_C(18833), UINT16_C(18807), UINT16_C(18781), UINT16_C(18755), 
UINT16_C(18729), UINT16_C(18703), UINT16_C(18678), UINT16_C(18652), UINT16_C(18626), UINT16_C(18601), UINT16_C(18575), UINT16_C(18550), 
UINT16_C(18525), UINT16_C(18499), UINT16_C(18474), UINT16_C(18449), UINT16_C(18424), UINT16_C(18399), UINT16_C(18374), UINT16_C(18349), 
UINT16_C(18325), UINT16_C(18300), UINT16_C(18275), UINT16_C(18250), UINT16_C(18226), UINT16_C(18201), UINT16_C(18177), UINT16_C(18153), 
UINT16_C(18128), UINT16_C(18104), UINT16_C(18080), UINT16_C(18056), UINT16_C(18031), UINT16_C(18007), UINT16_C(17983), UINT16_C(17959), 
UINT16_C(17936), UINT16_C(17912), UINT16_C(17888), UINT16_C(17864), UINT16_C(17840), UINT16_C(17817), UINT16_C(17793), UINT16_C(17770), 
UINT16_C(17746), UINT16_C(17723), UINT16_C(17699), UINT16_C(17676), UINT16_C(17653), UINT16_C(17630), UINT16_C(17606), UINT16_C(17583), 
UINT16_C(17560), UINT16_C(17537), UINT16_C(17514), UINT16_C(17491), UINT16_C(17468), UINT16_C(17446), UINT16_C(17423), UINT16_C(17400), 
UINT16_C(17377), UINT16_C(17355), UINT16_C(17332), UINT16_C(17309), UINT16_C(17287), UINT16_C(17264), UINT16_C(17242), UINT16_C(17219), 
UINT16_C(17197), UINT16_C(17175), UINT16_C(17153), UINT16_C(17130), UINT16_C(17108), UINT16_C(17086), UINT16_C(17064), UINT16_C(17042), 
UINT16_C(17020), UINT16_C(16998), UINT16_C(16976), UINT16_C(16954), UINT16_C(16932), UINT16_C(16910), UINT16_C(16888), UINT16_C(16867), 
UINT16_C(16845), UINT16_C(16823), UINT16_C(16802), UINT16_C(16780), UINT16_C(16758), UINT16_C(16737), UINT16_C(16715), UINT16_C(16694), 
UINT16_C(16672), UINT16_C(16651), UINT16_C(16630), UINT16_C(16608), UINT16_C(16587), UINT16_C(16566), UINT16_C(16545), UINT16_C(16523), 
UINT16_C(16502), UINT16_C(16481), UINT16_C(16460), UINT16_C(16439), UINT16_C(16418), UINT16_C(16397), UINT16_C(16376), UINT16_C(16355), 
UINT16_C(16334), UINT16_C(16313), UINT16_C(16292), UINT16_C(16272), UINT16_C(16251), UINT16_C(16230), UINT16_C(16209), UINT16_C(16189), 
UINT16_C(16168), UINT16_C(16147), UINT16_C(16127), UINT16_C(16106), UINT16_C(16086), UINT16_C(16065), UINT16_C(16045), UINT16_C(16024), 
UINT16_C(16004), UINT16_C(15983), UINT16_C(15963), UINT16_C(15943), UINT16_C(15922), UINT16_C(15902), UINT16_C(15882), UINT16_C(15862), 
UINT16_C(15841), UINT16_C(15821), UINT16_C(15801), UINT16_C(15781), UINT16_C(15761), UINT16_C(15741), UINT16_C(15721), UINT16_C(15701), 
UINT16_C(15681), UINT16_C(15661), UINT16_C(15641), UINT16_C(15621), UINT16_C(15601), UINT16_C(15581), UINT16_C(15561), UINT16_C(15541), 
UINT16_C(15521), UINT16_C(15502), UINT16_C(15482), UINT16_C(15462), UINT16_C(15442), UINT16_C(15423), UINT16_C(15403), UINT16_C(15383), 
UINT16_C(15364), UINT16_C(15344), UINT16_C(15324), UINT16_C(15305), UINT16_C(15285), UINT16_C(15266), UINT16_C(15246), UINT16_C(15227), 
UINT16_C(15207), UINT16_C(15188), UINT16_C(15168), UINT16_C(15149), UINT16_C(15130), UINT16_C(15110), UINT16_C(15091), UINT16_C(15071), 
UINT16_C(15052), UINT16_C(15033), UINT16_C(15014), UINT16_C(14994), UINT16_C(14975), UINT16_C(14956), UINT16_C(14937), UINT16_C(14917), 
UINT16_C(14898), UINT16_C(14879), UINT16_C(14860), UINT16_C(14841), UINT16_C(14822), UINT16_C(14802), UINT16_C(14783), UINT16_C(14764), 
UINT16_C(14745), UINT16_C(14726), UINT16_C(14707), UINT16_C(14688), UINT16_C(14669), UINT16_C(14650), UINT16_C(14631), UINT16_C(14612), 
UINT16_C(14593), UINT16_C(14574), UINT16_C(14556), UINT16_C(14537), UINT16_C(14518), UINT16_C(14499), UINT16_C(14480), UINT16_C(14461), 
UINT16_C(14442), UINT16_C(14424), UINT16_C(14405), UINT16_C(14386), UINT16_C(14367), UINT16_C(14348), UINT16_C(14330), UINT16_C(14311), 
UINT16_C(14292), UINT16_C(14274), UINT16_C(14255), UINT16_C(14236), UINT16_C(14218), UINT16_C(14199), UINT16_C(14180), UINT16_C(14162), 
UINT16_C(14143), UINT16_C(14124), UINT16_C(14106), UINT16_C(14087), UINT16_C(14068), UINT16_C(14050), UINT16_C(14031), UINT16_C(14013), 
UINT16_C(13994), UINT16_C(13976), UINT16_C(13957), UINT16_C(13939), UINT16_C(13920), UINT16_C(13902), UINT16_C(13883), UINT16_C(13865), 
UINT16_C(13846), UINT16_C(13828), UINT16_C(13809), UINT16_C(13791), UINT16_C(13772), UINT16_C(13754), UINT16_C(13735), UINT16_C(13717), 
UINT16_C(13699), UINT16_C(13680), UINT16_C(13662), UINT16_C(13643), UINT16_C(13625), UINT16_C(13607), UINT16_C(13588), UINT16_C(13570), 
UINT16_C(13551), UINT16_C(13533), UINT16_C(13515), UINT16_C(13496), UINT16_C(13478), UINT16_C(13460), UINT16_C(13441), UINT16_C(13423), 
UINT16_C(13405), UINT16_C(13386), UINT16_C(13368), UINT16_C(13350), UINT16_C(13331), UINT16_C(13313), UINT16_C(13295), UINT16_C(13276), 
UINT16_C(13258), UINT16_C(13240), UINT16_C(13222), UINT16_C(13203), UINT16_C(13185), UINT16_C(13167), UINT16_C(13148), UINT16_C(13130), 
UINT16_C(13112), UINT16_C(13094), UINT16_C(13075), UINT16_C(13057), UINT16_C(13039), UINT16_C(13021), UINT16_C(13002), UINT16_C(12984), 
UINT16_C(12966), UINT16_C(12948), UINT16_C(12929), UINT16_C(12911), UINT16_C(12893), UINT16_C(12875), UINT16_C(12856), UINT16_C(12838), 
UINT16_C(12820), UINT16_C(12802), UINT16_C(12783), UINT16_C(12765), UINT16_C(12747), UINT16_C(12729), UINT16_C(12710), UINT16_C(12692), 
UINT16_C(12674), UINT16_C(12656), UINT16_C(12637), UINT16_C(12619), UINT16_C(12601), UINT16_C(12583), UINT16_C(12564), UINT16_C(12546), 
UINT16_C(12528), UINT16_C(12509), UINT16_C(12491), UINT16_C(12473), UINT16_C(12455), UINT16_C(12436), UINT16_C(12418), UINT16_C(12400), 
UINT16_C(12381), UINT16_C(12363), UINT16_C(12345), UINT16_C(12327), UINT16_C(12308), UINT16_C(12290), UINT16_C(12272), UINT16_C(12253), 
UINT16_C(12235), UINT16_C(12217), UINT16_C(12198), UINT16_C(12180), UINT16_C(12162), UINT16_C(12143), UINT16_C(12125), UINT16_C(12106), 
UINT16_C(12088), UINT16_C(12070), UINT16_C(12051), UINT16_C(12033), UINT16_C(12015), UINT16_C(11996), UINT16_C(11978), UINT16_C(11959), 
UINT16_C(11941), UINT16_C(11922), UINT16_C(11904), UINT16_C(11886), UINT16_C(11867), UINT16_C(11849), UINT16_C(11830), UINT16_C(11812), 
UINT16_C(11793), UINT16_C(11775), UINT16_C(11756), UINT16_C(11738), UINT16_C(11719), UINT16_C(11701), UINT16_C(11682), UINT16_C(11663), 
UINT16_C(11645), UINT16_C(11626), UINT16_C(11608), UINT16_C(11589), UINT16_C(11570), UINT16_C(11552), UINT16_C(11533), UINT16_C(11515), 
UINT16_C(11496), UINT16_C(11477), UINT16_C(11459), UINT16_C(11440), UINT16_C(11421), UINT16_C(11402), UINT16_C(11384), UINT16_C(11365), 
UINT16_C(11346), UINT16_C(11327), UINT16_C(11309), UINT16_C(11290), UINT16_C(11271), UINT16_C(11252), UINT16_C(11233), UINT16_C(11214), 
UINT16_C(11196), UINT16_C(11177), UINT16_C(11158), UINT16_C(11139), UINT16_C(11120), UINT16_C(11101), UINT16_C(11082), UINT16_C(11063), 
UINT16_C(11044), UINT16_C(11025), UINT16_C(11006), UINT16_C(10987), UINT16_C(10968), UINT16_C(10949), UINT16_C(10930), UINT16_C(10910), 
UINT16_C(10891), UINT16_C(10872), UINT16_C(10853), UINT16_C(10834), UINT16_C(10814), UINT16_C(10795), UINT16_C(10776), UINT16_C(10757), 
UINT16_C(10737), UINT16_C(10718), UINT16_C(10699), UINT16_C(10679), UINT16_C(10660), UINT16_C(10641), UINT16_C(10621), UINT16_C(10602), 
UINT16_C(10582), UINT16_C(10563), UINT16_C(10543), UINT16_C(10524), UINT16_C(10504), UINT16_C(10484), UINT16_C(10465), UINT16_C(10445), 
UINT16_C(10426), UINT16_C(10406), UINT16_C(10386), UINT16_C(10366), UINT16_C(10347), UINT16_C(10327), UINT16_C(10307), UINT16_C(10287), 
UINT16_C(10267), UINT16_C(10247), UINT16_C(10227), UINT16_C(10208), UINT16_C(10188), UINT16_C(10168), UINT16_C(10148), UINT16_C(10127), 
UINT16_C(10107), UINT16_C(10087), UINT16_C(10067), UINT16_C(10047), UINT16_C(10027), UINT16_C(10006), UINT16_C(9986), UINT16_C(9966), 
UINT16_C(9945), UINT16_C(9925), UINT16_C(9905), UINT16_C(9884), UINT16_C(9864), UINT16_C(9843), UINT16_C(9823), UINT16_C(9802), 
UINT16_C(9782), UINT16_C(9761), UINT16_C(9740), UINT16_C(9720), UINT16_C(9699), UINT16_C(9678), UINT16_C(9657), UINT16_C(9636), 
UINT16_C(9615), UINT16_C(9594), UINT16_C(9573), UINT16_C(9552), UINT16_C(9531), UINT16_C(9510), UINT16_C(9489), UINT16_C(9468), 
UINT16_C(9447), UINT16_C(9426), UINT16_C(9404), UINT16_C(9383), UINT16_C(9362), UINT16_C(9340), UINT16_C(9319), UINT16_C(9297), 
UINT16_C(9276), UINT16_C(9254), UINT16_C(9232), UINT16_C(9211), UINT16_C(9189), UINT16_C(9167), UINT16_C(9145), UINT16_C(9123), 
UINT16_C(9101), UINT16_C(9079), UINT16_C(9057), UINT16_C(9035), UINT16_C(9013), UINT16_C(8991), UINT16_C(8969), UINT16_C(8946), 
UINT16_C(8924), UINT16_C(8902), UINT16_C(8879), UINT16_C(8857), UINT16_C(8834), UINT16_C(8812), UINT16_C(8789), UINT16_C(8766), 
UINT16_C(8743), UINT16_C(8720), UINT16_C(8698), UINT16_C(8675), UINT16_C(8652), UINT16_C(8628), UINT16_C(8605), UINT16_C(8582), 
UINT16_C(8559), UINT16_C(8536), UINT16_C(8512), UINT16_C(8489), UINT16_C(8465), UINT16_C(8441), UINT16_C(8418), UINT16_C(8394), 
UINT16_C(8370), UINT16_C(8346), UINT16_C(8322), UINT16_C(8298), UINT16_C(8274), UINT16_C(8250), UINT16_C(8226), UINT16_C(8202), 
UINT16_C(8177), UINT16_C(8153), UINT16_C(8128), UINT16_C(8104), UINT16_C(8079), UINT16_C(8054), UINT16_C(8029), UINT16_C(8004), 
UINT16_C(7979), UINT16_C(7954), UINT16_C(7929), UINT16_C(7904), UINT16_C(7878), UINT16_C(7853), UINT16_C(7827), UINT16_C(7802), 
UINT16_C(7776), UINT16_C(7750), UINT16_C(7724), UINT16_C(7698), UINT16_C(7672), UINT16_C(7646), UINT16_C(7619), UINT16_C(7593), 
UINT16_C(7566), UINT16_C(7540), UINT16_C(7513), UINT16_C(7486), UINT16_C(7459), UINT16_C(7432), UINT16_C(7405), UINT16_C(7378), 
UINT16_C(7351), UINT16_C(7323), UINT16_C(7295), UINT16_C(7268), UINT16_C(7240), UINT16_C(7212), UINT16_C(7184), UINT16_C(7156), 
UINT16_C(7127), UINT16_C(7099), UINT16_C(7070), UINT16_C(7041), UINT16_C(7013), UINT16_C(6984), UINT16_C(6954), UINT16_C(6925), 
UINT16_C(6896), UINT16_C(6866), UINT16_C(6836), UINT16_C(6807), UINT16_C(6777), UINT16_C(6746), UINT16_C(6716), UINT16_C(6686), 
UINT16_C(6655), UINT16_C(6624), UINT16_C(6593), UINT16_C(6562), UINT16_C(6531), UINT16_C(6499), UINT16_C(6468), UINT16_C(6436), 
UINT16_C(6404), UINT16_C(6372), UINT16_C(6339), UINT16_C(6307), UINT16_C(6274), UINT16_C(6241), UINT16_C(6208), UINT16_C(6174), 
UINT16_C(6141), UINT16_C(6107), UINT16_C(6073), UINT16_C(6039), UINT16_C(6004), UINT16_C(5970), UINT16_C(5935), UINT16_C(5900), 
UINT16_C(5864), UINT16_C(5829), UINT16_C(5793), UINT16_C(5757), UINT16_C(5720), UINT16_C(5684), UINT16_C(5647), UINT16_C(5609), 
UINT16_C(5572), UINT16_C(5534), UINT16_C(5496), UINT16_C(5458), UINT16_C(5419), UINT16_C(5380), UINT16_C(5341), UINT16_C(5301), 
UINT16_C(5261), UINT16_C(5221), UINT16_C(5181), UINT16_C(5140), UINT16_C(5098), UINT16_C(5057), UINT16_C(5014), UINT16_C(4972), 
UINT16_C(4929), UINT16_C(4886), UINT16_C(4842), UINT16_C(4798), UINT16_C(4754), UINT16_C(4709), UINT16_C(4663), UINT16_C(4617), 
UINT16_C(4571), UINT16_C(4524), UINT16_C(4476), UINT16_C(4428), UINT16_C(4380), UINT16_C(4331), UINT16_C(4281), UINT16_C(4231), 
UINT16_C(4180), UINT16_C(4129), UINT16_C(4077), UINT16_C(4024), UINT16_C(3971), UINT16_C(3916), UINT16_C(3861), UINT16_C(3806), 
UINT16_C(3749), UINT16_C(3692), UINT16_C(3634), UINT16_C(3575), UINT16_C(3515), UINT16_C(3455), UINT16_C(3393), UINT16_C(3330), 
UINT16_C(3266), UINT16_C(3202), UINT16_C(3136), UINT16_C(3068), UINT16_C(3000), UINT16_C(2930), UINT16_C(2859), UINT16_C(2787), 
UINT16_C(2713), UINT16_C(2638), UINT16_C(2561), 
};

#endif 
