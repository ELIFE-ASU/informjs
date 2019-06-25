// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <ginger/unit.h>

IMPORT_SUITE(ActiveInformation);
IMPORT_SUITE(BlockEntropy);
IMPORT_SUITE(Canary);
IMPORT_SUITE(ConditionalEntropy);
IMPORT_SUITE(CrossEntropy);
IMPORT_SUITE(Distribution);
IMPORT_SUITE(EffectiveInformation);
IMPORT_SUITE(EntropyRate);
IMPORT_SUITE(ExcessEntropy);
IMPORT_SUITE(InformationFlow);
IMPORT_SUITE(Integration);
IMPORT_SUITE(MutualInfo);
IMPORT_SUITE(PID);
IMPORT_SUITE(PredictiveInformation);
IMPORT_SUITE(RelativeEntropy);
IMPORT_SUITE(SeparableInformation);
IMPORT_SUITE(ShannonMulti);
IMPORT_SUITE(ShannonUni);
IMPORT_SUITE(TransferEntropy);
IMPORT_SUITE(Utilities);

BEGIN_REGISTRATION
    REGISTER(ActiveInformation)
    REGISTER(BlockEntropy)
    REGISTER(Canary)
    REGISTER(ConditionalEntropy)
    REGISTER(CrossEntropy)
    REGISTER(Distribution)
    REGISTER(EffectiveInformation)
    REGISTER(EntropyRate)
    REGISTER(ExcessEntropy)
    REGISTER(InformationFlow)
    REGISTER(Integration)
    REGISTER(MutualInfo)
    REGISTER(PID)
    REGISTER(PredictiveInformation)
    REGISTER(RelativeEntropy)
    REGISTER(SeparableInformation)
    REGISTER(ShannonMulti)
    REGISTER(ShannonUni)
    REGISTER(TransferEntropy)
    REGISTER(Utilities)
END_REGISTRATION

UNIT_MAIN();
