#include "node.h"
#include <sstream>

void NBlock::AddStatement(NStatement* statement)
{
	mStatements.push_back(statement);
}

void NBlock::CodeGen(CodeContext& context) const
{
	// TODO: Loop through statements in list and code gen them
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
    
}

NAttack::NAttack()
{
}

void NAttack::CodeGen(CodeContext &context) const
{
    
}

NRangedAttack::NRangedAttack()
{
}

void NRangedAttack::CodeGen(CodeContext &context) const
{
    
}

NIfElse::NIfElse(NBoolean* val, NBlock* ifBlock, NBlock* elseBlock)
    : mValue(val), mIf(ifBlock), mElse(elseBlock)
{
}

void NIfElse::CodeGen(CodeContext &context) const
{
    
}

NIsHuman::NIsHuman(NNumeric* val)
    : mVal(val)
{
}

void NIsHuman::CodeGen(CodeContext &context) const
{
    
}

NIsZombie::NIsZombie(NNumeric* val)
    : mVal(val)
{
}

void NIsZombie::CodeGen(CodeContext &context) const
{
    
}

NIsPassable::NIsPassable()
{
}

void NIsPassable::CodeGen(CodeContext &context) const
{
    
}

NIsRandom::NIsRandom()
{
}

void NIsRandom::CodeGen(CodeContext &context) const
{
    
}
