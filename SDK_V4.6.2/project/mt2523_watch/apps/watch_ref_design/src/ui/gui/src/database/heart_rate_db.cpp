/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

#include "gui/database/heart_rate_db.hpp"

HeartRateCache *HeartRateCache::heartRateCache = NULL;

HeartRateCache::HeartRateCache():
    writeIndex(0),
    readIndex(0),
    stepData(0),
    hBPData(0),
    lBPData(0)
{
    //init heart rate database
    int index;
    for (index = 0; index < FrequenceNum; ++index) {
        heartRateData[index] = 0;
    }
}

HeartRateCache::HeartRateCache(const HeartRateCache &heartRateCache)
{
}

int HeartRateCache::getHeartRateData()
{
    int data = -1;
    if (writeIndex != readIndex) {
        data = heartRateData[readIndex];
        readIndex = (readIndex + 1) % FrequenceNum;
    }
    return data;
}

void HeartRateCache::addHeartRateData(int bmp)
{
    int tempIndex = (writeIndex + 1) % FrequenceNum;
    if (tempIndex != readIndex) {
        heartRateData[writeIndex] = bmp;
        writeIndex = tempIndex;
    }
}

void HeartRateCache::addGSensorData(int step)
{
    stepData = step;
}

int HeartRateCache::getGSensorData()
{
    return stepData;
}

void HeartRateCache::addHBPData(int paramHbpData)
{
    hBPData = paramHbpData;
}

int HeartRateCache::getGHBPData()
{
    return hBPData;
}

void HeartRateCache::addLBPData(int paramLbpData)
{
    lBPData = paramLbpData;
}

int HeartRateCache::getLHBPData()
{
    return lBPData;
}
