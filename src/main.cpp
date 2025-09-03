//  ________  ________  ________  ___  ________  _____ ______      
// |\   __  \|\   __  \|\   ____\|\  \|\   __  \|\   _ \  _   \    
// \ \  \|\  \ \  \|\  \ \  \___|\ \  \ \  \|\  \ \  \\\__\ \  \   
//  \ \   ____\ \   __  \ \  \    \ \  \ \   __  \ \  \\|__| \  \  
//   \ \  \___|\ \  \ \  \ \  \____\ \  \ \  \ \  \ \  \    \ \  \ 
//    \ \__\    \ \__\ \__\ \_______\ \__\ \__\ \__\ \__\    \ \__\
//     \|__|     \|__|\|__|\|_______|\|__|\|__|\|__|\|__|     \|__|



#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <filesystem>
#include "main.h"

constexpr unsigned int hashStr(const char* str, unsigned int hash = 5381) {
    return *str ? hashStr(str + 1, ((hash << 5) + hash) + *str) : hash;
}
namespace fs = std::filesystem;
using namespace std;

string version = "v1.1";


int main(int argc, char** argv) {
    string home_dir = getenv("HOME");
    fs::create_directory(home_dir + "/paciam/");
    fs::create_directory(home_dir + "/paciam/packages/");

    if (argc <= 2) {
        cout << "\x1b[1;32m  ________  ________  ________  ___  ________  _____ ______        \n";
        cout << " |\\   __  \\|\\   __  \\|\\   ____\\|\\  \\|\\   __  \\|\\   _ \\  _   \\      \n";
        cout << " \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\     \n";
        cout << "  \\ \\   ____\\ \\   __  \\ \\  \\    \\ \\  \\ \\   __  \\ \\  \\\\|__| \\  \\    \n";
        cout << "   \\ \\  \\___|\\ \\  \\ \\  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\   \n";
        cout << "    \\ \\__\\    \\ \\__\\ \\__\\ \\_______\\ \\__\\ \\__\\ \\__\\ \\__\\    \\ \\__\\  \n";
        cout << "     \\|__|     \\|__|\\|__|\\|_______|\\|__|\\|__|\\|__|\\|__|     \\|__|  \n";
        cout << "\n\n\n" <<
            "paciam " << version << "\x1b[1;0m" << endl;

        cout << "usage:  paciam <operation> <package(s)>\n";
        cout << helpString << endl;
        return(0);
    }                                                                                                              

    string operation = argv[1];

    switch (hashStr(operation.c_str())) {
        case hashStr("-S"): {
            cout << "\x1b[1;36m  _____     ______     __     __     __   __     __         ______     ______     _____     __     __   __     ______      " << endl;
            cout << " /\\  __-.  /\\  __ \\   /\\ \\  _ \\ \\   /\\ \"-.\\ \\   /\\ \\       /\\  __ \\   /\\  __ \\   /\\  __-.  /\\ \\   /\\ \"-.\\ \\   /\\  ___\\     " << endl;
            cout << " \\ \\ \\/\\ \\ \\ \\ \\/\\ \\  \\ \\ \\/ \".\\ \\  \\ \\ \\-.  \\  \\ \\ \\____  \\ \\ \\/\\ \\  \\ \\  __ \\  \\ \\ \\/\\ \\ \\ \\ \\  \\ \\ \\-.  \\  \\ \\ \\__ \\    " << endl;
            cout << "  \\ \\____-  \\ \\_____\\  \\ \\__/\".~\\_\\  \\ \\_\\\\\"\\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\____-  \\ \\_\\  \\ \\_\\\\\"\\_\\  \\ \\_____\\   " << endl;
            cout << "   \\/____/   \\/_____/   \\/_/   \\/_/   \\/_/ \\/_/   \\/_____/   \\/_____/   \\/_/\\/_/   \\/____/   \\/_/   \\/_/ \\/_/   \\/_____/   " << endl;
            cout << "\x1b[0m\n\n";
            for (int i = 2; i < argc; i++){
                string packagePath = home_dir + "/paciam/packages/"+argv[i];

                if (fs::is_directory(packagePath)) fs::remove_all(packagePath);

                fs::remove_all(packagePath.c_str());

                string gitcommand = 
                    "git clone https://aur.archlinux.org/"+(string)argv[i]+".git " + packagePath + " > /dev/null 2>&1";
                system(gitcommand.c_str());
                    string installcommand =
                    "cd " + packagePath +
                        "; makepkg -si";
                system(installcommand.c_str());
            }
            break;
        }
        case hashStr("-R"): {
            cout << "\x1b[1;31m ______     ______     __    __     ______     __   __   __     __   __     ______    " << endl;
            cout << "/\\  == \\   /\\  ___\\   /\\ \"-./  \\   /\\  __ \\   /\\ \\ / /  /\\ \\   /\\ \"-.\\ \\   /\\  ___\\   " << endl;
            cout << "\\ \\  __<   \\ \\  __\\   \\ \\ \\-./\\ \\  \\ \\ \\/\\ \\  \\ \\ \\'/   \\ \\ \\  \\ \\ \\-.  \\  \\ \\ \\__ \\  " << endl;
            cout << " \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_\\ \\ \\_\\  \\ \\_____\\  \\ \\__|    \\ \\_\\  \\ \\_\\\\\"\\_\\  \\ \\_____\\ " << endl;
            cout << "  \\/_/ /_/   \\/_____/   \\/_/  \\/_/   \\/_____/   \\/_/      \\/_/   \\/_/ \\/_/   \\/_____/ " << endl;
            cout << "\x1b[0m\n\n";
            for (int i = 2; i < argc; i++){
                string packagePath = home_dir + "/paciam/packages/"+argv[i];

                if (fs::is_directory(packagePath)) { 
                    string removecommand = "sudo pacman -R " + (string)argv[i];
                    system(removecommand.c_str());
                    fs::remove_all(packagePath); 
                }
                else {
                    cerr << "error: target not found: " + (string)argv[i]<< endl; 
                }
            }
            break;
        }
    }
}