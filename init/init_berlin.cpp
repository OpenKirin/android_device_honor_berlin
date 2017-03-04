/*
   Copyright (c) 2017, The Lineage OS Project
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdlib>
#include <fstream>
#include <string>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_hi6250.h"

void init_target_properties()
{
    std::string platform;
    std::ifstream fin;
    std::string buf;

    platform = property_get("ro.board.platform");
    if (platform != ANDROID_TARGET)
        return;

    fin.open("/sys/firmware/devicetree/base/hisi,product_name");
    while (getline(fin, buf))
        if ((buf.find("BLN-L21") != std::string::npos) || (buf.find("BLN-L22") != std::string::npos) || (buf.find("BLN-L24") != std::string::npos))
            break;
    fin.close();

    if (buf.find("BLN-L21") != std::string::npos) {
        property_set("ro.product.model", "BLN-L21");
    }

    if (buf.find("BLN-L22") != std::string::npos) {
        property_set("ro.product.model", "BLN-L22");
    }

    if (buf.find("BLN-L24") != std::string::npos) {
        property_set("ro.product.model", "BLN-L24");
        property_set("ro.build.description", "BLN-L24-user 6.0 HONORBLN-L24C567B110 release-keys");
        property_set("ro.build.fingerprint", "HONOR/BLN-L24/HWBLN-H:6.0/HONORBLN-L24/C567B110:user/release-keys");
    }

	property_set("ro.boardid.product", "61201");
        property_set("ro.product.device", "HONOR-6X");
        property_set("ro.build.product", "berlin");
	property_set("persist.radio.multisim.config", "dsds");
	property_set("ro.telephony.ril.config", "simactivation,sim2gsmonly");
}
