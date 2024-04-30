#ifndef HIGHRATEAUTOPILOTMSG_H
#define HIGHRATEAUTOPILOTMSG_H

#include "MessagePayloadTemplate.hxx"

#include "MsgIds.hpp"

struct HighRateAutopilotData
{
    float fin1Cmd;
    float fin2Cmd;
    float fin3Cmd;
    float fin4Cmd;

    float scsDelta1Cmd;
    float scsDelta2Cmd;
    float scsDelta3Cmd;
    float scsDelta4Cmd;

    void Default()
    {
        fin1Cmd = 0.0;
        fin2Cmd = 0.0;
        fin3Cmd = 0.0;
        fin4Cmd = 0.0;

        scsDelta1Cmd = 0.0;
        scsDelta2Cmd = 0.0;
        scsDelta3Cmd = 0.0;
        scsDelta4Cmd = 0.0;
    }

    HighRateAutopilotData()
        : fin1Cmd()
        , fin2Cmd()
        , fin3Cmd()
        , fin4Cmd()

        , scsDelta1Cmd()
        , scsDelta2Cmd()
        , scsDelta3Cmd()
        , scsDelta4Cmd()
    {
        Default();
    }
};

MESSAGE_PAYLOAD( HighRateAutopilotMsg, HighRateAutopilotData, HighRateApMsgId )


#endif // HIGHRATEAUTOPILOTMSG_H
