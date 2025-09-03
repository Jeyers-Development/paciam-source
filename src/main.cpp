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

constexpr unsigned int hashStr(const char* str, unsigned int hash = 5381) {
    return *str ? hashStr(str + 1, ((hash << 5) + hash) + *str) : hash;
}
namespace fs = std::filesystem;
using namespace std;


int main(int argc, char** argv) {
    string home_dir = getenv("HOME");
    fs::create_directory(home_dir + "/paciam/");
    fs::create_directory(home_dir + "/paciam/packages/");

    if (argc <= 2 || argc > 3){

        cout << "  ________  ________  ________  ___  ________  _____ ______        \n";
        cout << " |\\   __  \\|\\   __  \\|\\   ____\\|\\  \\|\\   __  \\|\\   _ \\  _   \\      \n";
        cout << " \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|\\ \\  \\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\     \n";
        cout << "  \\ \\   ____\\ \\   __  \\ \\  \\    \\ \\  \\ \\   __  \\ \\  \\\\|__| \\  \\    \n";
        cout << "   \\ \\  \\___|\\ \\  \\ \\  \\ \\  \\____\\ \\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\   \n";
        cout << "    \\ \\__\\    \\ \\__\\ \\__\\ \\_______\\ \\__\\ \\__\\ \\__\\ \\__\\    \\ \\__\\  \n";
        cout << "     \\|__|     \\|__|\\|__|\\|_______|\\|__|\\|__|\\|__|\\|__|     \\|__|  \n";
        
        return(0);
    }

    string mode = argv[1];
    string packageId = argv[2];

    string packagePath = home_dir + "/paciam/packages/"+packageId;

    switch (hashStr(argv[1])) {
        case hashStr("-S"): {
            if (fs::is_directory(packagePath)) fs::remove_all(packagePath);

            fs::remove_all(packagePath.c_str());

            string gitcommand = 
                "git clone https://aur.archlinux.org/"+packageId+".git " + packagePath + " > /dev/null 2>&1";
            system(gitcommand.c_str());
                string installcommand =
                "cd " + packagePath +
                    "; makepkg -si";
            system(installcommand.c_str());
            break;
        }
        case hashStr("-R"): {
            if (fs::is_directory(packagePath)) { 
                string removecommand = "sudo pacman -R " + packageId;
                system(removecommand.c_str());
                fs::remove_all(packagePath); 
            }
            else {
                cerr << "error: target not found: " + packageId << endl; 
            }
            break;
        }
    }
}