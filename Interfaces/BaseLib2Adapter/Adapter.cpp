/*
 * Copyright 2011 EFDA | European Fusion Development Agreement
 *
 * Licensed under the EUPL, Version 1.1 or - as soon they 
   will be approved by the European Commission - subsequent  
   versions of the EUPL (the "Licence"); 
 * You may not use this work except in compliance with the 
   Licence. 
 * You may obtain a copy of the Licence at: 
 *  
 * http://ec.europa.eu/idabc/eupl
 *
 * Unless required by applicable law or agreed to in 
   writing, software distributed under the Licence is 
   distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either 
   express or implied. 
 * See the Licence for the specific language governing 
   permissions and limitations under the Licence. 
 *
 * $Id: Adapter.cpp 3 2012-01-15 16:26:07Z aneto $
 *
**/

#include "ConfigurationDataBase.h"
#include "Adapter.h"
#include "GlobalObjectDataBase.h"
#include "MenuContainer.h"
#include "LoggerService.h"

namespace BaseLib2 {
Adapter *Adapter::Instance() {
    static Adapter plumber;
    return &plumber;
}

Adapter::Adapter() {
    ProcessorType::defaultCPUs = 1u;
}

Adapter::~Adapter() {
}

bool Adapter::LoadObjects(const char *config) {
    ConfigurationDataBase cdb;
    FString configStr = config;
    configStr.Seek(0);
    bool ok = cdb->ReadFromStream(configStr);
    if (ok) {
        ok = GetGlobalObjectDataBase()->ObjectLoadSetup(cdb, NULL);
    }
    return ok;
}

bool Adapter::SendMessageToBaseLib2(const char *destination, const char *content, unsigned int code) {
    GCRTemplate<Message> gcrtm(GCFT_Create);
    GCRTemplate<MessageEnvelope> mec(GCFT_Create);
    gcrtm->Init(code, content); 
    bool ok = mec->PrepareMessageEnvelope(gcrtm, destination);
    if (ok) {
        ok = MessageHandler::SendMessage(mec);
    }
    return ok;
}
}
