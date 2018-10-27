#pragma once

#include "FrameBase.h"

#include "TreeProject.h"
#include "CreateWidget.h"
#include "Dialog.h"

class BitCoder : public FrameBase
{
    Q_OBJECT

public:
    BitCoder(FrameBase *parent = 0);
    ~BitCoder();


private:
    TreeProject *treeProject;

private slots:
    void createFileOrPro();



};


