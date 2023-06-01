#include <iostream>
#include <unistd.h>

// SVF
#include <SVF-LLVM/LLVMModule.h>
#include <SVF-LLVM/LLVMUtil.h>
#include <SVF-LLVM/SVFIRBuilder.h>

// llvm
#include <Util/Options.h>

#include "TestLib.h"

static llvm::cl::opt<std::string> IRFile(llvm::cl::Positional,
        llvm::cl::desc("<input bitcode>"), llvm::cl::init("-"));

void usage( void )
{
    std::cerr << "usage : ./main -i <llvm ir file>" << "\n";
}

int main( int argc, char *argv[] )
{
    int arg_num = 0;
    char **arg_value = new char*[argc];
    std::vector<std::string> moduleNameVec;
    SVF::LLVMUtil::processArguments(argc, argv, arg_num, arg_value, moduleNameVec);
    llvm::cl::ParseCommandLineOptions(arg_num, arg_value,"test\n");
    SVF::SVFModule* svf_module = SVF::LLVMModuleSet::getLLVMModuleSet()->buildSVFModule( moduleNameVec );
    // SVF::SVFIRBuilder builder( svf_module );
    // SVF::SVFIR* pag = builder.build();

    while ( true )
    {
        std::cout << "0. print all function" << "\n";
        std::cout << "select option : " << std::flush;
        int select;
        std::cin >> select;
        switch( select )
        {
            case 0:
            {
                Print();
                break;
            }
            case 1:
            {
                
                break;
            }
            default:
                std::cout << "wrong input" << "\n";   
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }

    return 0;
}