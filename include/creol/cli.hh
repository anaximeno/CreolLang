#ifndef _CREOL_CLI_HEADER
#define _CREOL_CLI_HEADER

#include "ast.hh"

#include "../external/argparse.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <memory>
#include <algorithm>

namespace ap = argparse;

namespace creol {
    namespace cli {
        void PrintErr(std::string message);
        void PrintErr(std::string message, int exitNum);
        void ExecuteCommand(std::string command);

        class CreolLangParserWraper {
        public:
            static ast::BlockSttmt* ParseCode(std::string Content, bool isFile);
            static void ParseFile(std::string filename);
            static void ParseText(std::string text);
        };

        class Compiler {
            std::string Name;
            std::string Version;
            std::unique_ptr<ap::ArgumentParser> Parser;

            struct {
                std::string filename;
                std::string outfile;
                bool shouldBuildOutput;
                bool shouldFormatOutput;
            } Args;

        public:
            Compiler(std::string Name, std::string Ver)
            : Name(Name), Version(Ver), Parser(std::make_unique<ap::ArgumentParser>(Name, Ver)) {  }
            void Run(const int argc, const char* const* argv);
        private:
            void ParseArgs(const int argc, const char* const* argv);
            void DefineArgs(void);
            void SaveCodeToFile(std::string Code, std::string Filename);
            void BuildCode(std::string Code);
        };
    };
};

#endif // _CREOL_CLI_HEADER