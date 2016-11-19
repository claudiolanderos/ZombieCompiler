#include "node.h"
#include <sstream>

void NBlock::AddStatement(NStatement* statement)
{
	mStatements.push_back(statement);
}

void NBlock::CodeGen(CodeContext& context) const
{
    for (auto& i : mStatements) {
        i->CodeGen(context);
    }
    if(mbMainBlock)
    {
        context.mOps.push_back("goto,1");
    }
}

NNumeric::NNumeric(std::string& value)
{
	mvalue = std::atoi(value.c_str());
}

NRotate::NRotate(NNumeric* dir)
	: mDir(dir)
{
}

void NRotate::CodeGen(CodeContext& context) const
{
	if (mDir->mvalue == 0)
	{
		context.mOps.push_back("rotate,0");
	}
	else if (mDir->mvalue == 1)
	{
		context.mOps.push_back("rotate,1");
	}
}

NForward::NForward()
{
}

void NForward::CodeGen(CodeContext &context) const
{
    context.mOps.push_back("forward");
}

NAttack::NAttack()
{
}

void NAttack::CodeGen(CodeContext &context) const
{
    context.mOps.push_back("attack");
}

NRangedAttack::NRangedAttack()
{
}

void NRangedAttack::CodeGen(CodeContext &context) const
{
    context.mOps.push_back("ranged_attack");
}

NIfElse::NIfElse(NBoolean* val, NBlock* ifBlock, NBlock* elseBlock)
    : mValue(val), mIf(ifBlock), mElse(elseBlock)
{
}

void NIfElse::CodeGen(CodeContext &context) const
{
    mValue->CodeGen(context);
    int jeLocation = static_cast<int>(context.mOps.size());
    std::string temp = "je to if block";
    context.mOps.push_back(temp);
    mElse->CodeGen(context);
    int gotoLocation = static_cast<int>(context.mOps.size());
    context.mOps.push_back("goto past the if block");
    context.mOps.at(jeLocation) = "je," + std::to_string(context.mOps.size()+1);
    mIf->CodeGen(context);
    context.mOps.at(gotoLocation) = "goto," + std::to_string(context.mOps.size()+1);
}

NIsHuman::NIsHuman(NNumeric* val)
    : mVal(val)
{
}

void NIsHuman::CodeGen(CodeContext &context) const
{
    if (mVal->mvalue == 1)
    {
        context.mOps.push_back("test_human,1");
    }
    else if (mVal->mvalue == 2)
    {
        context.mOps.push_back("test_human,2");
    }
}

NIsZombie::NIsZombie(NNumeric* val)
    : mVal(val)
{
}

void NIsZombie::CodeGen(CodeContext &context) const
{
    if (mVal->mvalue == 1)
    {
        context.mOps.push_back("test_zombie,1");
    }
    else if (mVal->mvalue == 2)
    {
        context.mOps.push_back("test_zombie,2");
    }
}

NIsPassable::NIsPassable()
{
}

void NIsPassable::CodeGen(CodeContext &context) const
{
    context.mOps.push_back("test_passable");
}

NIsRandom::NIsRandom()
{
}

void NIsRandom::CodeGen(CodeContext &context) const
{
    context.mOps.push_back("test_random");
}
