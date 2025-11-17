#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int root_check(){
    auto user = getuid();
    auto userprivs = geteuid();

    if (userprivs != 0) {
        cout << "Please run the program as root!" << endl;
        exit(0);
    }
    return 0;
}

int argument_check(int argc, char* argv[]) {
    // Check for --help
    if (argc == 2) {
        if (string(argv[1]) == "--help"){
            cout << "arg1: Name of the package you want to add uses flags for" << endl;
            cout << "arg2: The values to add in package.use file (must start with an equals sign)" << endl;
            
            exit(0);
        }
    }

    // Check to see if the user has even put any arguments
    if (argc == 1) {
        cout << "You need to enter at least one argument" << endl;
        cout << "Run with --help to see syntax :3" << endl;
        
        exit(0);
    }

    return 0;
}

int main(int argc, char* argv[]) {
    // Check if the program is being ran via root
    root_check();
    // Run argument checks
    argument_check(argc, argv);

    // Program
    string packagename = argv[1];
    string useflags = argv[2];

    system(("echo '" + useflags + "'" + " >> /etc/portage/package.use/" + packagename).c_str());
    return 0;
}