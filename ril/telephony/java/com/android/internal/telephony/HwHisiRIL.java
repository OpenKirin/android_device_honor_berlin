/*
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 * Not a Contribution.
 *
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.internal.telephony;

import static com.android.internal.telephony.RILConstants.*;

import android.content.Context;
import android.os.Parcel;

import android.telephony.Rlog;
import android.telephony.SignalStrength;

public class HwHisiRIL extends RIL {

    public HwHisiRIL(Context context, int networkMode, int cdmaSubscription, Integer instanceId) {
        super(context, networkMode, cdmaSubscription, instanceId);
    }

    private static final String RILJ_LOG_TAG = "RILJ-HwHisiRil";

    @Override
    protected Object
    responseFailCause(Parcel p) {
        int numInts;
        int response[];

        numInts = p.readInt();
        response = new int[numInts];
        for (int i = 0 ; i < numInts ; i++) {
            response[i] = p.readInt();
        }
        LastCallFailCause failCause = new LastCallFailCause();
        failCause.causeCode = response[0];
        if (p.dataAvail() > 0) {
          failCause.vendorCause = p.readString();
        }
        return failCause;
    }

    @Override
    protected void
    send(RILRequest rr) {
        if (rr.mRequest >= 132) {
            Rlog.i(RILJ_LOG_TAG, ": Unsupported request " + rr.mRequest);
            rr.onError(REQUEST_NOT_SUPPORTED, null);
            rr.release();
        } else {
            super.send(rr);
        }
    }

    @Override
    protected Object
    responseSignalStrength(Parcel p) {
        Rlog.e(RILJ_LOG_TAG, "responseSignalStrength called");

        int[] response = new int[16];
        for (int i = 0 ; i < 16 ; i++) {
            response[i] = p.readInt();
        }

        int gsmSignalStrength = response[0]; // Valid values are (0-31, 99) as defined in TS 27.007 8.5
        int gsmBitErrorRate = response[1]; // bit error rate (0-7, 99) as defined in TS 27.007 8.5
        int mWcdmaRscp = response[2]; // added by huawei
        int mWcdmaEcio = response[3]; // added by huawei
        int cdmaDbm = response[4];
        int cdmaEcio = response[5];
        int evdoDbm = response[6]; // -75 to -105, 99
        int evdoEcio = response[7];
        int evdoSnr = response[8]; // Valid values are 0-8.  8 is the highest signal to noise ratio
        int lteSignalStrength = response[9]; // 0 to 12, 63
        int lteRsrp = response[10]; // -85 to -140, -44
        int lteRsrq = response[11]; // -3 to -20
        int lteRssnr = response[12]; // 130 to -30, -200
        int lteCqi = response[13];
        int mGsm = response[14];
        int mRat = response[15]; // added by huawei 

        if (lteRsrp != 0) /* Connected to LTE */ {
            if (lteRsrp > -20) lteSignalStrength = 64; /* Too high = none */
            else if (lteRsrp >= -97) lteSignalStrength = 63; /* Excellent */
        } else if (lteRsrp >= -85) { // Great
            lteSignalStrength = 63;
            lteRssnr = 300;
        } else if (lteRsrp >= -95) { // Good
            lteSignalStrength = 11;
            lteRssnr = 129;
        } else if (lteRsrp >= -105) { // Moderate
            lteSignalStrength = 7;
            lteRssnr = 44;
        } else if (lteRsrp >= -115) { // Poor
            lteSignalStrength = 4;
            lteRssnr = 9;
        } else if (lteRsrp >= -140) { // None or Unknown
            lteSignalStrength = 64;
            lteRssnr = -200;
        } else if (mWcdmaRscp == 0 && lteRsrp == 0) // 2G
        {
            lteRsrp = (gsmSignalStrength & 0xFF) - 256;

            if (lteRsrp > -20) { // None or Unknown
                lteSignalStrength = 64;
                lteRsrq = -21;
                lteRssnr = -200;
            } else if (lteRsrp >= -85) { // Great
                lteSignalStrength = 63;
                lteRsrq = -3;
                lteRssnr = 300;
            } else if (lteRsrp >= -95) { // Good
                lteSignalStrength = 11;
                lteRsrq = -7;
                lteRssnr = 129;
            } else if (lteRsrp >= -105) { // Moderate
                lteSignalStrength = 7;
                lteRsrq = -12;
                lteRssnr = 44;
            } else if (lteRsrp >= -115) { // Poor
                lteSignalStrength = 4;
                lteRsrq = -17;
                lteRssnr = 9;
            } else if (lteRsrp >= -140) { // None or Unknown
                lteSignalStrength = 64;
                lteRsrq = -21;
                lteRssnr = -200;
            }
        }

        gsmSignalStrength = 0;
        gsmBitErrorRate = 0;
        cdmaDbm = -1;
        cdmaEcio = -1;
        evdoDbm = -1;
        evdoEcio = -1;
        evdoSnr = -1;

        Rlog.d(RILJ_LOG_TAG, "---------- MOD ----------");
        Rlog.d(RILJ_LOG_TAG, "lteSignalStrength:" + lteSignalStrength);
        Rlog.d(RILJ_LOG_TAG, "lteRsrp:" + lteRsrp);
        Rlog.d(RILJ_LOG_TAG, "lteRsrq:" + lteRsrq);
        Rlog.d(RILJ_LOG_TAG, "lteRssnr:" + lteRssnr);
        Rlog.d(RILJ_LOG_TAG, "lteCqi:" + lteCqi);
        Rlog.d(RILJ_LOG_TAG, "-------------------------");

        SignalStrength signalStrength = new SignalStrength(
            gsmSignalStrength, gsmBitErrorRate, cdmaDbm, cdmaEcio, evdoDbm, 
            evdoEcio, evdoSnr, lteSignalStrength, -lteRsrp, -lteRsrq, 
            lteRssnr, lteCqi, true);

        return signalStrength;
    }
}
