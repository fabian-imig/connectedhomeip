/*
 *
 *    Copyright (c) 2023, 2025 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include "OtaPrivate.h"
#include <lib/support/Span.h>
#include <platform/nxp/common/ota/OTATlvProcessor.h>

/* Posted Operations Size Info */
#define NB_PENDING_TRANSACTIONS 12
#define TRANSACTION_SZ (sizeof(FLASH_TransactionOpNode_t))

namespace chip {

class OTAFirmwareProcessor : public OTATlvProcessor
{
public:
    struct Descriptor
    {
        uint32_t version;
        char versionString[kVersionStringSize];
        char buildDate[kBuildDateSize];
    };

    CHIP_ERROR Init() override;
    CHIP_ERROR Clear() override;
    CHIP_ERROR ApplyAction() override;
    CHIP_ERROR AbortAction() override;
    CHIP_ERROR ExitAction() override;

private:
    CHIP_ERROR ProcessInternal(ByteSpan & block) override;
    CHIP_ERROR ProcessDescriptor(ByteSpan & block);

    OTADataAccumulator mAccumulator;
    bool mDescriptorProcessed = false;
#if OTA_ENCRYPTION_ENABLE
    uint32_t mUnalignmentNum;
#endif

    alignas(4) uint8_t mPostedOperationsStorage[NB_PENDING_TRANSACTIONS * TRANSACTION_SZ];
};

} // namespace chip
