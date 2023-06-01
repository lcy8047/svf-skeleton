#include <SVF-LLVM/LLVMModule.h>
#include <SVF-LLVM/LLVMUtil.h>
#include <SVF-LLVM/SVFIRBuilder.h>

#include "TestLib.h"

void Print( void )
{
    for ( const llvm::Module& M : SVF::LLVMModuleSet::getLLVMModuleSet()->getLLVMModules() )
    {
        for ( const llvm::Function& fun : M )
        {
            fun.print( llvm::outs() );
        }
    }
}